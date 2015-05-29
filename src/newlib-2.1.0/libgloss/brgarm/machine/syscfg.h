//========================================================================
// syscfg.h : Maven system configuration macros
//========================================================================
// This is the key file where we place all brgarm system configuration
// macros. All macros in this file should begin with a BRGARM_SYSCFG_
// prefix so that users can immediately know where such macros are
// defined. This file should be replicated in the simulator directories
// and in libgloss here: brgarm/sys/xcc/src/libgloss/brgarm. The libgloss
// makefile is reposible for installing this file into
// ${sysroot}/include/machine so that other brgarm software (proxy
// kernel, libraries, applications) can include it like this:
//
//  #include <machine/syscfg.h>
//

#ifndef BRGARM_SYSCFG_H
#define BRGARM_SYSCFG_H

//------------------------------------------------------------------------
// System Calls
//------------------------------------------------------------------------
// We are using arbitrary system calls which do not map to any
// particular operating system. Standard system calls found on most
// linux/unix machines should use smaller numbers while extra system
// calls specific to brgarm and our infrastructure should start from
// 0x4000. No one should ever refer to the system call number directly
// so we can renumber system calls whenever we like.

// using linux-like mapping
#define BRGARM_SYSCFG_SYSCALL_EXIT                           1
#define BRGARM_SYSCFG_SYSCALL_READ                           3
#define BRGARM_SYSCFG_SYSCALL_WRITE                          4
#define BRGARM_SYSCFG_SYSCALL_OPEN                           5
#define BRGARM_SYSCFG_SYSCALL_CLOSE                          6
#define BRGARM_SYSCFG_SYSCALL_LINK                           9
#define BRGARM_SYSCFG_SYSCALL_UNLINK                        10
#define BRGARM_SYSCFG_SYSCALL_LSEEK                         19
#define BRGARM_SYSCFG_SYSCALL_FSTAT                         108
#define BRGARM_SYSCFG_SYSCALL_STAT                          106
#define BRGARM_SYSCFG_SYSCALL_BRK                           45

//#define BRGARM_SYSCFG_SYSCALL_EXIT                           1
//#define BRGARM_SYSCFG_SYSCALL_READ                           2
//#define BRGARM_SYSCFG_SYSCALL_WRITE                          3
//#define BRGARM_SYSCFG_SYSCALL_OPEN                           4
//#define BRGARM_SYSCFG_SYSCALL_CLOSE                          5
//#define BRGARM_SYSCFG_SYSCALL_LINK                           6
//#define BRGARM_SYSCFG_SYSCALL_UNLINK                         7
//#define BRGARM_SYSCFG_SYSCALL_LSEEK                          8
//#define BRGARM_SYSCFG_SYSCALL_FSTAT                          9
//#define BRGARM_SYSCFG_SYSCALL_STAT                          10
//#define BRGARM_SYSCFG_SYSCALL_BRK                           11

// Extra brgarm specific system calls

#define BRGARM_SYSCFG_SYSCALL_NUMCORES                    4000
#define BRGARM_SYSCFG_SYSCALL_SENDAM                      4001

#define BRGARM_SYSCFG_SYSCALL_BTHREAD_ONCE                4002
#define BRGARM_SYSCFG_SYSCALL_BTHREAD_KEY_CREATE          4003
#define BRGARM_SYSCFG_SYSCALL_BTHREAD_KEY_DELETE          4004
#define BRGARM_SYSCFG_SYSCALL_BTHREAD_KEY_SETSPECIFIC     4005
#define BRGARM_SYSCFG_SYSCALL_BTHREAD_KEY_GETSPECIFIC     4006

#define BRGARM_SYSCFG_SYSCALL_YIELD                       4007

//------------------------------------------------------------------------
// Coprocessor 0 Control Registers
//------------------------------------------------------------------------

#define BRGARM_SYSCFG_REGDEF_COP0_TO_SERV     1
#define BRGARM_SYSCFG_REGDEF_COP0_FROM_SERV   2

#define BRGARM_SYSCFG_REGDEF_COP0_TO_SYSC0    3
#define BRGARM_SYSCFG_REGDEF_COP0_TO_SYSC1    4
#define BRGARM_SYSCFG_REGDEF_COP0_TO_SYSC2    5
#define BRGARM_SYSCFG_REGDEF_COP0_TO_SYSC3    6
#define BRGARM_SYSCFG_REGDEF_COP0_TO_SYSC4    7
#define BRGARM_SYSCFG_REGDEF_COP0_TO_SYSC5    8

#define BRGARM_SYSCFG_REGDEF_COP0_COUNT       9
#define BRGARM_SYSCFG_REGDEF_COP0_COUNT_LO    9

#define BRGARM_SYSCFG_REGDEF_COP0_FROM_SYSC0 10
#define BRGARM_SYSCFG_REGDEF_COP0_FROM_SYSC1 11
#define BRGARM_SYSCFG_REGDEF_COP0_FROM_SYSC2 12
#define BRGARM_SYSCFG_REGDEF_COP0_FROM_SYSC3 13
#define BRGARM_SYSCFG_REGDEF_COP0_FROM_SYSC4 14
#define BRGARM_SYSCFG_REGDEF_COP0_FROM_SYSC5 15

#define BRGARM_SYSCFG_REGDEF_COP0_NUMCORES   16

#define BRGARM_SYSCFG_REGDEF_COP0_CORE_ID    17
#define BRGARM_SYSCFG_REGDEF_COP0_TID_MASK   18
#define BRGARM_SYSCFG_REGDEF_COP0_TID_STOP   19
#define BRGARM_SYSCFG_REGDEF_COP0_STATS_EN   21

#define BRGARM_SYSCFG_REGDEF_COP0_COUNT_HI   25

//------------------------------------------------------------------------
// Maven minimum and maximum vector length
//------------------------------------------------------------------------

#define BRGARM_SYSCFG_VLEN_MIN  4
#define BRGARM_SYSCFG_VLEN_MAX 32

//------------------------------------------------------------------------
// Timing
//------------------------------------------------------------------------

// How many processor cycles per second. Assume brgarm runs at 1 GHz.
#define BRGARM_SYSCFG_CYCLES_PER_SEC 1000000000

//------------------------------------------------------------------------
// Threads
//------------------------------------------------------------------------

// Size of the various stacks
#define BRGARM_SYSCFG_USER_THREAD_STACK_SIZE   0x00100000
#define BRGARM_SYSCFG_KERNEL_THREAD_STACK_SIZE 0x00010000
#define BRGARM_SYSCFG_VP_THREAD_STACK_SIZE     0x00001000

//------------------------------------------------------------------------
// Memory layout
//------------------------------------------------------------------------

#define BRGARM_SYSCFG_MEMORY_SIZE       0x10000000
#define BRGARM_SYSCFG_XCPTHANDLER_START 0x00000020
#define BRGARM_SYSCFG_USER_START        0x00001000
#define BRGARM_SYSCFG_USER_SIZE         0x0BFFF000
#define BRGARM_SYSCFG_KERNEL_START      0x0C000000
#define BRGARM_SYSCFG_KERNEL_SIZE       0x04000000
#define BRGARM_SYSCFG_ARGS_SIZE         0x00010000

#define BRGARM_SYSCFG_MAX_PROCS 8 // maximum number of processors in the system
#define BRGARM_SYSCFG_MAX_KEYS  8 // maximum number of unique keys per thread

#endif /* BRGARM_SYSCFG_H */
