/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)tcp.h	8.1 (Berkeley) 6/10/93
 */

typedef	u_int32_t	tcp_seq;
struct tcphdr {
	u_int16_t	th_sport;		
	u_int16_t	th_dport;		
	tcp_seq		th_seq;			
	tcp_seq		th_ack;			
	u_int8_t	th_offx2;		
	u_int8_t	th_flags;
	u_int16_t	th_win;			
	u_int16_t	th_sum;			
	u_int16_t	th_urp;			
} UNALIGNED;

#define TH_OFF(th)	(((th)->th_offx2 & 0xf0) >> 4)

#define	TH_FIN     0x01
#define	TH_SYN	   0x02
#define	TH_RST	   0x04
#define	TH_PUSH	   0x08
#define	TH_ACK	   0x10
#define	TH_URG	   0x20
#define TH_ECNECHO 0x40	
#define TH_CWR	   0x80	


#define	TCPOPT_EOL		0
#define	TCPOPT_NOP		1
#define	TCPOPT_MAXSEG		2
#define    TCPOLEN_MAXSEG		4
#define	TCPOPT_WSCALE		3	
#define	TCPOPT_SACKOK		4	
#define	TCPOPT_SACK		5	
#define	TCPOPT_ECHO		6	
#define	TCPOPT_ECHOREPLY	7	
#define TCPOPT_TIMESTAMP	8	
#define    TCPOLEN_TIMESTAMP		10
#define    TCPOLEN_TSTAMP_APPA		(TCPOLEN_TIMESTAMP+2) 
#define TCPOPT_CC		11	
#define TCPOPT_CCNEW		12	
#define TCPOPT_CCECHO		13	
#define TCPOPT_SIGNATURE	19	
#define    TCPOLEN_SIGNATURE		18
#define TCP_SIGLEN 16			
#define TCPOPT_AUTH             20      
#define	TCPOPT_UTO		28	
#define	   TCPOLEN_UTO			4
#define	TCPOPT_MPTCP		30	
#define TCPOPT_EXPERIMENT2	254	

#define TCPOPT_TSTAMP_HDR	\
    (TCPOPT_NOP<<24|TCPOPT_NOP<<16|TCPOPT_TIMESTAMP<<8|TCPOLEN_TIMESTAMP)

#ifndef TELNET_PORT
#define TELNET_PORT             23
#endif
#ifndef BGP_PORT
#define BGP_PORT                179
#endif
#define NETBIOS_SSN_PORT        139
#ifndef OPENFLOW_PORT
#define OPENFLOW_PORT           6633
#endif
#ifndef PPTP_PORT
#define PPTP_PORT	        1723
#endif
#define BEEP_PORT               10288
#ifndef NFS_PORT
#define NFS_PORT	        2049
#endif
#define MSDP_PORT	        639
#define RPKI_RTR_PORT	        323
#define LDP_PORT                646
#ifndef SMB_PORT
#define SMB_PORT                445
#endif