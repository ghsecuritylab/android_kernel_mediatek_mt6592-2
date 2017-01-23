

#include <stdio.h>

extern unsigned int xlc_double_to_u32 ( double );
asm("\n"
".text\n"
".global xlc_double_to_u32\n"
".type xlc_double_to_u32, @function\n"
"xlc_double_to_u32:\n"
"        stwu    %r1,-48(%r1)\n"
"        addis   %r4,%r0,.const_dr@ha\n"
"        addis   %r0,%r0,17376\n"
"        fabs    %f0,%f1\n"
"        addi    %r3,%r0,0\n"
"        mffs    %f3\n"
"        mtfsb1  4*cr7+so\n"
"        lfs     %f2,.const_dr@l(%r4)\n"
"        fcmpu   0,%f1,%f0\n"
"        fadd    %f0,%f0,%f2\n"
"        mtfsf   255,%f3\n"
"        stfd    %f0,24(%r1)\n"
"        bne-    $+0x1c\n"
"        lwz     %r3,24(%r1)\n"
"        subf    %r0,%r3,%r0\n"
"        srawi   %r0,%r0,31\n"
"        ori     %r0,%r0,0x0000\n"
"        lwz     %r4,28(%r1)\n"
"        or      %r3,%r4,%r0\n"
"        addi    %r1,%r1,48\n"
"        blr\n"
".size xlc_double_to_u32, . - xlc_double_to_u32\n"
"        .long 0\n"
"        .long 0x00000000\n"
"        .long 0x00000000\n"
".previous\n"
"\n"
"        .section        \".rodata\",\"a\"\n"
"        .align  3\n"
"        .type    .const_dr,@object\n"
"        .size    .const_dr,20\n"
".const_dr:\n"
"        .long 0x59804000\n"
"        .long 0x49424d20\n"
"        .long 0x3fe66666\n"
"        .long 0x66666666\n"
"        .long 0x25640a00\n"
".previous\n"
);

int main (int argc, char** argv)
{
  unsigned int r = xlc_double_to_u32 ( 0.7 );
  if (r == 0)
    printf("pass\n");
  else 
    printf("fail\n");

  return 0;
}