//========================================================================
// syscall.h : Syscall numbers and helper macros
//========================================================================
// The system call numbers are brought in via syscfg.h. In addition we
// provide a set of helper macros which simplify making system calls
// with zero to three arguments.
//
// The current implementation of these macros assumes the following mips
// syscall instruction interface:
//
//  - a0 : syscall argument 0
//  - a1 : syscall argument 1
//  - a2 : syscall argument 2
//  - a3 : error flag (0 = success, 1 = failure)
//  - v0 : syscall id, then return value from system call
//
// The first argument should be just the name of the system call in all
// capital letters. It should correspond to the suffix of
// BRGARM_SYSCFG_SYSCALL so for example, to make the close system call we
// would use something like this:
//
//  int close( int file ) 
//  {
//    int result, error_flag;
//    BRGARM_SYSCALL_ARG1( CLOSE, result, error_flag, file );
//   
//    if ( error_flag == 1 ) {
//      errno = result;
//      return -1;
//    }
//    
//    return 0;
//  }
//

#include <machine/syscfg.h>

//------------------------------------------------------------------------
// BRGARM_SYSCALL_ARG0
//------------------------------------------------------------------------
// berkin: note we don't use eflag for the time being
#define BRGARM_SYSCALL_ARG0( r7_, sys_, res_, eflag_ )                        \
  register __typeof__ (res_)   res_   ## _ asm ("r0");                  \
  register long r7_ ## _ __asm__("r7")=                                      \
                  (long)(BRGARM_SYSCFG_SYSCALL_ ## sys_);               \
  __asm__ volatile                                                      \
  ( "swi 0"                                                             \
    : "=r" (res_ ## _)                                                  \
    : "r" (r7_ ## _)  );                                                     \
  res_   = res_ ## _;                                                   \

// #define BRGARM_SYSCALL_ARG0( sys_, res_, eflag_ )                        \
//   register __typeof__ (res_)   res_   ## _ asm ("v0");                  \
//   register __typeof__ (eflag_) eflag_ ## _ asm ("a3");                  \
//   __asm__ volatile                                                      \
//   ( "li $v0, %2; syscall"                                               \
//     : "=r"(res_ ## _), "=r"(eflag_ ## _)                                \
//     : "i"(BRGARM_SYSCFG_SYSCALL_ ## sys_) );                             \
//   res_   = res_ ## _;                                                   \
//   eflag_ = eflag_ ## _;                                                 \

//------------------------------------------------------------------------
// BRGARM_SYSCALL_ARG1
//------------------------------------------------------------------------

#define BRGARM_SYSCALL_ARG1( r7_, sys_, res_, eflag_, r0_ )                  \
  register __typeof__ (res_)   res_   ## _ asm ("r0");                  \
  register long r7_ ## _ __asm__("r7")=                                      \
                  (long)(BRGARM_SYSCFG_SYSCALL_ ## sys_);               \
  register __typeof__ (r0_)   r0_   ## _ asm ("r0") = r0_;              \
  __asm__ volatile                                                      \
  ( "swi 0"                                                             \
    : "=r" (res_ ## _)                                                  \
    : "r" (r7_ ## _),                                                        \
      "r" (r0_ ## _) );                                                 \
  res_   = res_ ## _;                                                   \

// #define BRGARM_SYSCALL_ARG1( sys_, res_, eflag_, a0_ )                   \
//   register __typeof__ (res_)   res_   ## _ asm ("v0");                  \
//   register __typeof__ (a0_)    a0_    ## _ asm ("a0") = a0_;            \
//   register __typeof__ (eflag_) eflag_ ## _ asm ("a3");                  \
//   __asm__ volatile                                                      \
//   ( "li $v0, %3; syscall"                                               \
//     : "=r"(res_ ## _), "=r"(eflag_ ## _)                                \
//     : "r"(a0_ ## _),                                                    \
//       "i"(BRGARM_SYSCFG_SYSCALL_ ## sys_) );                             \
//   res_   = res_ ## _;                                                   \
//   eflag_ = eflag_ ## _;                                                 \

//------------------------------------------------------------------------
// BRGARM_SYSCALL_ARG2
//------------------------------------------------------------------------

// hack: using a name to avoid name collision
#define BRGARM_SYSCALL_ARG2( r7_, sys_, res_, eflag_, r0_, r1_ )              \
  register __typeof__ (res_)   res_   ## _ asm ("r0");                  \
  register long r7_ ## _ __asm__("r7")=                                      \
                  (long)(BRGARM_SYSCFG_SYSCALL_ ## sys_);               \
  register __typeof__ (r0_)   r0_   ## _ asm ("r0") = r0_;              \
  register __typeof__ (r1_)   r1_   ## _ asm ("r1") = r1_;              \
  __asm__ volatile                                                      \
  ( "swi 0"                                                             \
    : "=r" (res_ ## _)                                                  \
    : "r" (r7_ ## _),                                                        \
      "r" (r0_ ## _),                                                   \
      "r" (r1_ ## _) );                                                 \
  res_   = res_ ## _;                                                   \

// #define BRGARM_SYSCALL_ARG2( sys_, res_, eflag_, a0_, a1_ )              \
//   register __typeof__ (res_)   res_   ## _ asm ("v0");                  \
//   register __typeof__ (a0_)    a0_    ## _ asm ("a0") = a0_;            \
//   register __typeof__ (a1_)    a1_    ## _ asm ("a1") = a1_;            \
//   register __typeof__ (eflag_) eflag_ ## _ asm ("a3");                  \
//   __asm__ volatile                                                      \
//   ( "li $v0, %4; syscall"                                               \
//     : "=r"(res_ ## _), "=r"(eflag_ ## _)                                \
//     : "r"(a0_ ## _), "r"(a1_ ## _),                                     \
//       "i"(BRGARM_SYSCFG_SYSCALL_ ## sys_) );                             \
//   res_   = res_ ## _;                                                   \
//   eflag_ = eflag_ ## _;                                                 \

//------------------------------------------------------------------------
// BRGARM_SYSCALL_ARG3
//------------------------------------------------------------------------

#define BRGARM_SYSCALL_ARG3( r7_, sys_, res_, eflag_, r0_, r1_, r2_ )         \
  register __typeof__ (res_)   res_   ## _ asm ("r0");                  \
  register long r7_ ## _ __asm__("r7")=                                      \
                  (long)(BRGARM_SYSCFG_SYSCALL_ ## sys_);               \
  register __typeof__ (r0_)   r0_   ## _ asm ("r0") = r0_;              \
  register __typeof__ (r1_)   r1_   ## _ asm ("r1") = r1_;              \
  register __typeof__ (r2_)   r2_   ## _ asm ("r2") = r2_;              \
  __asm__ volatile                                                      \
  ( "swi 0"                                                             \
    : "=r" (res_ ## _)                                                  \
    : "r" (r7_ ## _),                                                        \
      "r" (r0_ ## _),                                                   \
      "r" (r1_ ## _),                                                   \
      "r" (r2_ ## _) );                                                 \
  res_   = res_ ## _;                                                   \

// #define BRGARM_SYSCALL_ARG3( sys_, res_, eflag_, a0_, a1_, a2_ )         \
//   register __typeof__ (res_)   res_   ## _ asm ("v0");                  \
//   register __typeof__ (a0_)    a0_    ## _ asm ("a0") = a0_;            \
//   register __typeof__ (a1_)    a1_    ## _ asm ("a1") = a1_;            \
//   register __typeof__ (a2_)    a2_    ## _ asm ("a2") = a2_;            \
//   register __typeof__ (eflag_) eflag_ ## _ asm ("a3");                  \
//   __asm__ volatile                                                      \
//   ( "li $v0, %5; syscall"                                               \
//     : "=r"(res_ ## _), "=r"(eflag_ ## _)                                \
//     : "r"(a0_ ## _), "r"(a1_ ## _), "r"(a2_ ## _),                      \
//       "i"(BRGARM_SYSCFG_SYSCALL_ ## sys_) );                             \
//   res_   = res_ ## _;                                                   \
//   eflag_ = eflag_ ## _;                                                 \


