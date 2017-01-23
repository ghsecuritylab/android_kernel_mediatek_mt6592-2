/*
 *  Copyright (c) 2010 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vpx/vpx_encoder.h"

#include "../tools_common.h"
#include "../video_writer.h"

static const char *exec_name;

void usage_exit(void) {
  fprintf(stderr,
          "Usage: %s <codec> <width> <height> <infile> <outfile> "
              "<keyframe-interval> [<error-resilient>]\nSee comments in "
              "simple_encoder.c for more information.\n",
          exec_name);
  exit(EXIT_FAILURE);
}

static int encode_frame(vpx_codec_ctx_t *codec,
                        vpx_image_t *img,
                        int frame_index,
                        int flags,
                        VpxVideoWriter *writer) {
  int got_pkts = 0;
  vpx_codec_iter_t iter = NULL;
  const vpx_codec_cx_pkt_t *pkt = NULL;
  const vpx_codec_err_t res = vpx_codec_encode(codec, img, frame_index, 1,
                                               flags, VPX_DL_GOOD_QUALITY);
  if (res != VPX_CODEC_OK)
    die_codec(codec, "Failed to encode frame");

  while ((pkt = vpx_codec_get_cx_data(codec, &iter)) != NULL) {
    got_pkts = 1;

    if (pkt->kind == VPX_CODEC_CX_FRAME_PKT) {
      const int keyframe = (pkt->data.frame.flags & VPX_FRAME_IS_KEY) != 0;
      if (!vpx_video_writer_write_frame(writer,
                                        pkt->data.frame.buf,
                                        pkt->data.frame.sz,
                                        pkt->data.frame.pts)) {
        die_codec(codec, "Failed to write compressed frame");
      }
      printf(keyframe ? "K" : ".");
      fflush(stdout);
    }
  }

  return got_pkts;
}

int main(int argc, char **argv) {
  FILE *infile = NULL;
  vpx_codec_ctx_t codec;
  vpx_codec_enc_cfg_t cfg;
  int frame_count = 0;
  vpx_image_t raw;
  vpx_codec_err_t res;
  VpxVideoInfo info = {0};
  VpxVideoWriter *writer = NULL;
  const VpxInterface *encoder = NULL;
  const int fps = 30;        
  const int bitrate = 200;   
  int keyframe_interval = 0;

  
  
  const char *codec_arg = NULL;
  const char *width_arg = NULL;
  const char *height_arg = NULL;
  const char *infile_arg = NULL;
  const char *outfile_arg = NULL;
  const char *keyframe_interval_arg = NULL;

  exec_name = argv[0];

  if (argc < 7)
    die("Invalid number of arguments");

  codec_arg = argv[1];
  width_arg = argv[2];
  height_arg = argv[3];
  infile_arg = argv[4];
  outfile_arg = argv[5];
  keyframe_interval_arg = argv[6];

  encoder = get_vpx_encoder_by_name(codec_arg);
  if (!encoder)
     die("Unsupported codec.");

  info.codec_fourcc = encoder->fourcc;
  info.frame_width = strtol(width_arg, NULL, 0);
  info.frame_height = strtol(height_arg, NULL, 0);
  info.time_base.numerator = 1;
  info.time_base.denominator = fps;

  if (info.frame_width <= 0 ||
      info.frame_height <= 0 ||
      (info.frame_width % 2) != 0 ||
      (info.frame_height % 2) != 0) {
    die("Invalid frame size: %dx%d", info.frame_width, info.frame_height);
  }

  if (!vpx_img_alloc(&raw, VPX_IMG_FMT_I420, info.frame_width,
                                             info.frame_height, 1)) {
    die("Failed to allocate image.");
  }

  keyframe_interval = strtol(keyframe_interval_arg, NULL, 0);
  if (keyframe_interval < 0)
    die("Invalid keyframe interval value.");

  printf("Using %s\n", vpx_codec_iface_name(encoder->codec_interface()));

  res = vpx_codec_enc_config_default(encoder->codec_interface(), &cfg, 0);
  if (res)
    die_codec(&codec, "Failed to get default codec config.");

  cfg.g_w = info.frame_width;
  cfg.g_h = info.frame_height;
  cfg.g_timebase.num = info.time_base.numerator;
  cfg.g_timebase.den = info.time_base.denominator;
  cfg.rc_target_bitrate = bitrate;
  cfg.g_error_resilient = argc > 7 ? strtol(argv[7], NULL, 0) : 0;

  writer = vpx_video_writer_open(outfile_arg, kContainerIVF, &info);
  if (!writer)
    die("Failed to open %s for writing.", outfile_arg);

  if (!(infile = fopen(infile_arg, "rb")))
    die("Failed to open %s for reading.", infile_arg);

  if (vpx_codec_enc_init(&codec, encoder->codec_interface(), &cfg, 0))
    die_codec(&codec, "Failed to initialize encoder");

  
  while (vpx_img_read(&raw, infile)) {
    int flags = 0;
    if (keyframe_interval > 0 && frame_count % keyframe_interval == 0)
      flags |= VPX_EFLAG_FORCE_KF;
    encode_frame(&codec, &raw, frame_count++, flags, writer);
  }

  
  while (encode_frame(&codec, NULL, -1, 0, writer)) {};

  printf("\n");
  fclose(infile);
  printf("Processed %d frames.\n", frame_count);

  vpx_img_free(&raw);
  if (vpx_codec_destroy(&codec))
    die_codec(&codec, "Failed to destroy codec.");

  vpx_video_writer_close(writer);

  return EXIT_SUCCESS;
}