//========================================================================
// syscalls.c : Newlib operating system interface                       
//========================================================================
// This is the brgarm implementation of the narrow newlib operating
// system interface. It is based on the minimum stubs in the newlib
// documentation, the error stubs in libnosys, and the previous scale
// implementation. Please do not include any additional system calls or
// other functions in this file. Additional header and source files
// should be in the machine subdirectory.
//
// Here is a list of the functions which make up the operating system
// interface. The file management instructions execute syscall assembly
// instructions so that a proxy kernel (or the simulator) can marshal up
// the request to the host machine. The process management functions are
// mainly just stubs since for now brgarm only supports a single process.
//
//  - File management functions
//     + open   : (v) open file
//     + lseek  : (v) set position in file
//     + read   : (v) read from file
//     + write  : (v) write to file
//     + fstat  : (z) status of an open file
//     + stat   : (z) status of a file by name
//     + close  : (z) close a file
//     + link   : (z) rename a file
//     + unlink : (z) remote file's directory entry
//
//  - Process management functions
//     + execve : (z) transfer control to new proc
//     + fork   : (z) create a new process 
//     + getpid : (v) get process id 
//     + kill   : (z) send signal to child process
//     + wait   : (z) wait for a child process
//     
//  - Misc functions
//     + isatty : (v) query whether output stream is a terminal
//     + times  : (z) timing information for current process
//     + sbrk   : (v) increase program data space
//     + _exit  : (-) exit program without cleaning up files
//
// There are two types of system calls. Those which return a value when
// everything is okay (marked with (v) in above list) and those which
// return a zero when everything is okay (marked with (z) in above
// list). On an error (ie. when the error flag is 1) the return value is
// always an errno which should correspond to the numbers in
// newlib/libc/include/sys/errno.h 
//
// Note that really I think we are supposed to define versions of these
// functions with an underscore prefix (eg. _open). This is what some of
// the newlib documentation says, and all the newlib code calls the
// underscore version. This is because technically I don't think we are
// supposed to pollute the namespace with these function names. If you
// define MISSING_SYSCALL_NAMES in xcc/src/newlib/configure.host
// then xcc/src/newlib/libc/include/_syslist.h will essentially define
// all of the underscore versions to be equal to the non-underscore
// versions. I tried not defining MISSING_SYSCALL_NAMES, and newlib
// compiled fine but libstdc++ complained about not being able to fine
// write, read, etc. So for now we do not use underscores (and we do
// define MISSING_SYSCALL_NAMES).
//
// See the newlib documentation for more information 
// http://sourceware.org/newlib/libc.html#Syscalls

#include <machine/syscall.h>
#include <sys/stat.h>
#include <sys/timex.h>
#include <sys/times.h>
#include <sys/time.h>
#include <errno.h>
#include <machine/timex.h>

//------------------------------------------------------------------------
// errno                                                                
//------------------------------------------------------------------------
// The newlib documentation notes the following: 
//
// Graceful failure is permitted by returning an error code. A minor
// complication arises here: the C library must be compatible with
// development environments that supply fully functional versions of
// these subroutines. Such environments usually return error codes in a
// global errno. However, the Red Hat newlib C library provides a macro
// definition for errno in the header file errno.h, as part of its
// support for reentrant routines (see Reentrancy).
//
// The bridge between these two interpretations of errno is
// straightforward: the C library routines with OS interface calls
// capture the errno values returned globally, and record them in the
// appropriate field of the reentrancy structure (so that you can query
// them using the errno macro from errno.h).
//
// This mechanism becomes visible when you write stub routines for OS
// interfaces. You must include errno.h, then disable the macro. */

#undef errno
extern int errno;

//------------------------------------------------------------------------
// environment                                                          
//------------------------------------------------------------------------
// A pointer to a list of environment variables and their values. For a
// minimal environment, this empty list is adequate. We used to define
// environ here but it is already defined in
// xcc/src/newlib/libc/stdlib/environ.c so to avoid multiple definition
// errors we have commented this out for now.
//
// char* __env[1] = { 0 };
// char** environ = __env;
              
//------------------------------------------------------------------------
// open                                                                 
//------------------------------------------------------------------------
// Open a file.

int _open( const char* name, int flags, int mode )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG3( open, OPEN, result, error_flag, name, flags, mode );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return result;
}

//------------------------------------------------------------------------
// lseek                                                                
//------------------------------------------------------------------------
// Set position in a file.

int _lseek( int file, int ptr, int dir )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG3( lseek, LSEEK, result, error_flag, file, ptr, dir );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return result;
}

//----------------------------------------------------------------------
// read                                                                 
//----------------------------------------------------------------------
// Read from a file.

int _read( int file, char* ptr, int len )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG3( read, READ, result, error_flag, file, ptr, len );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return result;
}

//------------------------------------------------------------------------
// write                                                                
//------------------------------------------------------------------------
// Write to a file.

int _write( int file, char* ptr, int len )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG3( write, WRITE, result, error_flag, file, ptr, len );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return result;
}

//------------------------------------------------------------------------
// fstat                                                                
//------------------------------------------------------------------------
// Status of an open file. The sys/stat.h header file required is
// distributed in the include subdirectory for this C library.

int _fstat( int file, struct stat* st )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG2( fstat, FSTAT, result, error_flag, file, st );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return 0;
}

//------------------------------------------------------------------------
// stat                                                                 
//------------------------------------------------------------------------
// Status of a file (by name).

int _stat( const char* file, struct stat* st )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG2( stat, STAT, result, error_flag, file, st );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return 0;
}

//------------------------------------------------------------------------
// close                                                                
//------------------------------------------------------------------------
// Close a file.

int _close( int file ) 
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG1( close, CLOSE, result, error_flag, file );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return 0;
}

//------------------------------------------------------------------------
// link                                                                 
//------------------------------------------------------------------------
// Establish a new name for an existing file.

int _link( char* old_name, char* new_name )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG2( link, LINK, result, error_flag, old_name, new_name );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return 0;
}

//------------------------------------------------------------------------
// unlink                                                               
//------------------------------------------------------------------------
// Remove a file's directory entry.

int _unlink( char* name )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG1( unlink, UNLINK, result, error_flag, name );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }
  
  return 0;
}

//------------------------------------------------------------------------
// execve                                                               
//------------------------------------------------------------------------
// Transfer control to a new process. Minimal implementation for a
// system without processes from newlib documentation.

int _execve( char* name, char** argv, char** env )
{
  errno = ENOMEM;
  return -1;
}

//------------------------------------------------------------------------
// fork                                                                 
//------------------------------------------------------------------------
// Create a new process. Minimal implementation for a system without
// processes from newlib documentation.

int _fork() 
{
  errno = EAGAIN;
  return -1;
}

//------------------------------------------------------------------------
// getpid                                                               
//------------------------------------------------------------------------
// Get process id. This is sometimes used to generate strings unlikely
// to conflict with other processes. Minimal implementation for a
// system without processes just returns 1.

int _getpid() 
{
  return 1;
}

//------------------------------------------------------------------------
// kill                                                                 
//------------------------------------------------------------------------
// Send a signal. Minimal implementation for a system without processes
// just causes an error.

int _kill( int pid, int sig )
{
  errno = EINVAL;
  return -1;
}

//------------------------------------------------------------------------
// wait                                                                 
//------------------------------------------------------------------------
// Wait for a child process. Minimal implementation for a system without
// processes just causes an error.

int _wait( int* status )
{
  errno = ECHILD;
  return -1;
}

//------------------------------------------------------------------------
// isatty                                                               
//------------------------------------------------------------------------
// Query whether output stream is a terminal. For consistency with the
// other minimal implementations, which only support output to stdout,
// this minimal implementation is suggested by the newlib docs.

int _isatty( int file )
{
  return 1;
}

//------------------------------------------------------------------------
// times                                                                
//------------------------------------------------------------------------
// Timing information for current process. From
// newlib/libc/include/sys/times.h the tms struct fields are as follows:
//
//  - clock_t tms_utime  : user clock ticks
//  - clock_t tms_stime  : system clock ticks
//  - clock_t tms_cutime : children's user clock ticks
//  - clock_t tms_cstime : children's system clock ticks
//
// Since brgarm does not currently support processes we set both of the
// children's times to zero. Eventually we might want to separately
// account for user vs system time, but for now we just return the total
// number of cycles since starting the program.

clock_t _times( struct tms* buf )
{
  cycles_t cycles_per_clock = get_cycles_per_sec() / CLOCKS_PER_SEC;

  buf->tms_utime = get_cycles() / cycles_per_clock;
  buf->tms_stime  = 0;
  buf->tms_cutime = 0;
  buf->tms_cstime = 0;

  return 0;
}

//----------------------------------------------------------------------
// sbrk
//----------------------------------------------------------------------
// Author: Chris Torng
//
// Increase program data space by increasing the program break value.
// Malloc and other related functions depend on this. This sbrk
// implementation uses brk syscalls inside.

caddr_t _sbrk( int incr )
{
  extern unsigned char _end; // Defined by linker
  int zero_arg;

  int result_initial;
  int error_flag_initial;
  unsigned char* end_initial;

  int result;
  int error_flag;
  unsigned char* end;

  // The heap end variables are unsigned char pointers but are stored as
  // integers. We use integers for convenience because the pkernel returns an
  // integer type result; using int types still retains correct functionality.

  int prev_heap_end;
  int heap_end;

  // We need to pass &_end to the pkernel so it knows where _end is. The
  // pkernel has its own separate _end symbol. Note that a real brk syscall
  // only takes a single argument -- the new break address -- so adding a
  // second argument isn't really 'correct'. But when running simulation that
  // does not use the pkernel, the extra argument will just be ignored. So
  // this remains functionally correct.

  end_initial = &_end;
  end         = &_end;

  zero_arg = 0;

  // An empty brk call returns the current program break value.

  BRGARM_SYSCALL_ARG2( brk1, BRK, result_initial, error_flag_initial, zero_arg, end_initial );

  if ( error_flag_initial == 1 ) {
    errno = result_initial;
    return -1;
  }

  // Save the previous program break value so we can return it later.

  prev_heap_end = result_initial;

  // Compute new program break value.

  heap_end = prev_heap_end + incr;

  // Do another brk syscall to set the new break value.

  BRGARM_SYSCALL_ARG2( brk2, BRK, result, error_flag, heap_end, end );

  if ( error_flag == 1 ) {
    errno = result;
    return -1;
  }

  // Return previous break value.

  return (caddr_t) prev_heap_end;
}

//------------------------------------------------------------------------
// _exit                                                                
//------------------------------------------------------------------------
// Exit a program without cleaning up files.

void _exit( int exit_status )
{
  int result, error_flag;
  BRGARM_SYSCALL_ARG0( exit, EXIT, result, error_flag );

  // Convince gcc this function never returns to avoid warnings (this is
  // from _exit in libnosys)
  for (;;)
    ;
}

