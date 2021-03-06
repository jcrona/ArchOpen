#ifndef __DSPSHARED_H
#define __DSPSHARED_H

#define SAMPLECOUNT		    256

// warning : this file is included by both arm and dsp code (thx zig, it's a lot cleaner like this :)

// offset of the area of our control variables in the dsp
// only 2 bytes space required, the rest will be dynamically set
#define DSP_CONTROL_OFFSET 0x90

#ifdef DSPCODE
# define DSP_RAM(a) ((volatile unsigned short *)(a))
#else
# define DSP_RAM(a) ((volatile unsigned short *)(0x40000 + (a)*2))
#endif

#define SDRAM_OFFSET 0x900000L

#define DSP_COM DSP_RAM(DSP_CONTROL_OFFSET)

typedef volatile struct {
  // init
  unsigned short armInitFinished;
  unsigned short chipNum;

  unsigned short armBusy;
  unsigned short sndWantBuf;
  unsigned long sndBufAddr;

  // debug messages
  unsigned short hasDbgMsg;
  short dbgMsg[255];
} tDspCom;


extern tDspCom * dspCom;

#endif /*__DSPSHARED_H*/

