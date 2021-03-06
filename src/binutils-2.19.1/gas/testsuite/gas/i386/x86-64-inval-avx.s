# Check illegal 64bit AVX instructions
	.text
_start:
	vcvtpd2dq (%rcx),%xmm2
	vcvtpd2ps (%rcx),%xmm2
	vcvttpd2dq (%rcx),%xmm2
	vfmaddpd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmaddps $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmaddsd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmaddss $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmaddsubpd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmaddsubps $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmsubaddpd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmsubaddps $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmsubpd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmsubps $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmsubsd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfmsubss $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfnmaddpd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfnmaddps $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfnmaddsd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfnmaddss $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfnmsubpd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfnmsubps $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfnmsubsd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vfnmsubss $17,%xmm4,%xmm2,%xmm1,%xmm3
	vpermil2pd $17,%xmm4,%xmm2,%xmm1,%xmm3
	vpermil2ps $17,%xmm4,%xmm2,%xmm1,%xmm3

	.intel_syntax noprefix
	vcvtpd2dq xmm2,[rcx]
	vcvtpd2ps xmm2,[rcx]
	vcvttpd2dq xmm2,[rcx]
	vfmaddpd xmm3,xmm1,xmm2,xmm4,0x10
	vfmaddps xmm3,xmm1,xmm2,xmm4,0x10
	vfmaddsd xmm3,xmm1,xmm2,xmm4,0x10
	vfmaddss xmm3,xmm1,xmm2,xmm4,0x10
	vfmaddsubpd xmm3,xmm1,xmm2,xmm4,0x10
	vfmaddsubps xmm3,xmm1,xmm2,xmm4,0x10
	vfmsubaddpd xmm3,xmm1,xmm2,xmm4,0x10
	vfmsubaddps xmm3,xmm1,xmm2,xmm4,0x10
	vfmsubpd xmm3,xmm1,xmm2,xmm4,0x10
	vfmsubps xmm3,xmm1,xmm2,xmm4,0x10
	vfmsubsd xmm3,xmm1,xmm2,xmm4,0x10
	vfmsubss xmm3,xmm1,xmm2,xmm4,0x10
	vfnmaddpd xmm3,xmm1,xmm2,xmm4,0x10
	vfnmaddps xmm3,xmm1,xmm2,xmm4,0x10
	vfnmaddsd xmm3,xmm1,xmm2,xmm4,0x10
	vfnmaddss xmm3,xmm1,xmm2,xmm4,0x10
	vfnmsubpd xmm3,xmm1,xmm2,xmm4,0x10
	vfnmsubps xmm3,xmm1,xmm2,xmm4,0x10
	vfnmsubsd xmm3,xmm1,xmm2,xmm4,0x10
	vfnmsubss xmm3,xmm1,xmm2,xmm4,0x10
	vpermil2pd xmm3,xmm1,xmm2,xmm4,0x10
	vpermil2ps xmm3,xmm1,xmm2,xmm4,0x10
