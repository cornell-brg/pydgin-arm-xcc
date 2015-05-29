//========================================================================
// cop0.h : Helper functions to read/write cop0 registers
//========================================================================

#ifndef _BRGARM_COP0_H
#define _BRGARM_COP0_H

#include <machine/syscfg.h>

// Make sure we can use the same lib in both C and C++ programs
#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------
// brgarm_get_cop0_count()
//------------------------------------------------------------------------
// Return the 32b cycle count

static inline unsigned int brgarm_get_cop0_count()
{
  //unsigned int ret;
  //__asm__ ( "mfc0 %0, $%1"
  //          : "=r"(ret) : "i"(BRGARM_SYSCFG_REGDEF_COP0_COUNT) );
  //return ret;
  // berkin: return 0
  return 0;
}

//------------------------------------------------------------------------
// brgarm_get_cop0_core_id()
//------------------------------------------------------------------------
// Return the core id for the current core

static inline unsigned int brgarm_get_cop0_core_id()
{
  //unsigned int ret;
  //__asm__ ( "mfc0 %0, $%1"
  //          : "=r"(ret) : "i"(BRGARM_SYSCFG_REGDEF_COP0_CORE_ID) );
  //return ret;
  // berkin: we're core0
  return 0;
}

//------------------------------------------------------------------------
// brgarm_set_cop0_stats_enable( bool value )
//------------------------------------------------------------------------
// Sets the statistics enable control register

static inline void brgarm_set_cop0_stats_enable( bool value )
{
  //__asm__ ( "mtc0 %0, $%1"
  //          :: "r"(value), "i"(BRGARM_SYSCFG_REGDEF_COP0_STATS_EN) );
  // berkin: we don't have stats, don't do anything
}

#ifdef __cplusplus
}
#endif
#endif /* _BRGARM_COP0_H */

