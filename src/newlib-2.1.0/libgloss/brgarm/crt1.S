/*
#=========================================================================
# crt1.S : Basic C runtime startup file
#=========================================================================
# crt0 and crt1 are the basic C runtime startup files. The code in these
# files is the very first thing which is run when a user application
# starts. I think crt0 is an older style startup file and that crt1 is
# more common. crt1 should define the _start symbol as this is what the
# kernel will jump to when starting the program (as defined by the ENTRY
# command in the brgarm linker script). crt1 should then setup registers,
# setup argc/argv, setup the environment, and zero out unitilized data
# regions. It should execute the initialization functions by calling
# _init and register the _fini function (with the termination functions)
# with the runtime so that it is called on exit. Finally it should call
# main, and when main returns it should call exit.
#
# For now we do not proxy the host environment to the running
# application, but eventually we might want to set this up. When we do
# we will need to move the environ definition in syscalls.c to here.
#
# We assume that the application server or proxy kernel has put
# the command line arguments on the stack and initialized the stack
# pointer appropriately as illustrated below.
#
#  address = MEMORY_SIZE - ARGS_SIZE
#  -------------------------------------------
#  argc         : argument count                <--- stack pointer
#  argv[0]      : argument pointer 0
#  argv[1]      : argument pointer 1
#  ...
#  argv[argc-1] : argument pointer argc-1
#  NULL         : end of argument pointers
#  NULL         : extra null pointer
#  -------------------------------------------
#  arg(0)       : argument 0
#  arg(1)       : argument 1
#  ...
#  arg(argc-1)  : argument argc-1
#  -------------------------------------------
#  undefined memory from here to MEMORY_SIZE-1
#  -------------------------------------------
#  address = MEMORY_SIZE - 1
#
# Notice that we reserve a fixed size for all the argument (and
# eventually environment) storage. This is to make sure that the stack
# alignment is not a function of the arguments or environment. Based on
# this layout we need to set a0 and a1 correctly as they are the
# arguments to main(). Basically argc is stored in a0 and equals the
# value pointed to by sp, and argv is stored in a1 equals the sp+4.
#
# The crt1 will setup the stack pointers for each of the hard threads.
# It looks in a control register to see how many hard threads are
# present, and then allocates space for each stack starting at the
# initial stack pointer (MEMORY_SIZE - ARGS_SIZE) and growing towards
# smaller memory addresses. The final memory layout will look something
# like this:
#
#  address = 0
#  -------------------------------------------
#  .text and .rodata sections
#  -------------------------------------------
#  .data sections
#  ------------------------------------------- <--- _end
#  heap                                          | heap grows down
#  ...                                           v
#  -------------------------------------------
#  stack space for thread 1                      ^
#  ...                                           | stack grows up
#  ------------------------------------------- <--- thread 1 sp
#  stack space for thread 0                      ^
#  ...                                           | stack grows up
#  ------------------------------------------- <--- thread 0 sp
#  argument count and argument pointers
#  ...
#  -------------------------------------------
#  argument strings
#  ...
#  -------------------------------------------
#  undefined memory from here to MEMORY_SIZE-1
#  -------------------------------------------
#  address = MEMORY_SIZE - 1
#
*/

#include <machine/syscfg.h>

/* We define some shorter macro names for use in this file */

#define c0_coreid BRGARM_SYSCFG_REGDEF_COP0_CORE_ID
#define tstack_sz BRGARM_SYSCFG_THREAD_STACK_SIZE

/*
#-------------------------------------------------------------------------
# Global symbols defined elsewhere
#-------------------------------------------------------------------------
*/

        .global _init          /* Initialization functions */
        .global _fini          /* Termination functions      */
        .global atexit         /* Register exit functions    */
        .global main           /* User program               */
        .global exit           /* Exit function              */

/*
#-------------------------------------------------------------------------
# _start
#-------------------------------------------------------------------------
*/

        .text
        .global _start
/*        .ent    _start */

/*
# berkin: we're trying to replicate uclibc's crt1.o (I took it from
# /work/bits0/dml257/temp/arm-nothumb-xcc/.build/arm-unknown-linux-uclibcgnueabi/build/build-libc/libc/sysdeps/linux/arm/crt1.S
# and copied it to crt1-uclibc.S)
*/

/*
_start:
        mov   fp, #0
        mov   lr, #0
        pop   {r1}
        mov   r2, sp
        push  {r2}
        push  {r0}
        ldr   ip, [pc #16]
        push  {ip}
        ldr   r0, [pc, #12]
        ldr   r3, [pc, #12]
        b     main
        bl
*/

_start:
	/* Clear the frame pointer and link register since this is the outermost frame.  */
	mov fp, #0
	mov lr, #0

	/* Zero the memory in the .bss section.  */
	movs 	a2, #0			/* Second arg: fill value.  */
	mov	fp, a2			/* Null frame pointer.  */
	mov	r7, a2			/* Null frame pointer for Thumb.  */
	
	ldr	a1, .LC1		/* First arg: start of memory block.  */
	ldr	a3, .LC2	
	subs	a3, a3, a1		/* Third arg: length of block.  */

  bl memset

  //----------------------------------------------------------------------
  // args
  //----------------------------------------------------------------------

  // not sure about this:
	//ldr	r1, .LC30
  ldr r0, [sp]
  //ldr r1, [sp, #4]
  add r1, sp, #4

// 	/*  Parse string at r1.  */
// 	//movs	r0, #0		/* Count of arguments so far.  */
// 	/* Push a NULL argument onto the end of the list.  */
// 	stmfd	sp!, {r0}
// 
// .LC10:
// /*  Skip leading blanks.  */
// 	ldrb	r3, [r1], #1
// 	cmp	r3, #0
// 	beq	.LC12
// 	cmp	r3, #' '
// 	beq	.LC10
// 
// /* See whether we are scanning a string.  */
// 	cmp	r3, #'\"'
// 	cmpne	r3, #'\''
// 	moveq	r2, r3
// 	movne	r2, #' '	/* Terminator type.  */
// 	subne	r1, r1, #1	/* Adjust back to point at start char.  */
// 
// /*  Stack a pointer to the current argument.  */
// 	stmfd	sp!, {r1}
// 	adds	r0, r0, #1
// .LC11:
// 	ldrb	r3, [r1], #1
// 	cmp	r3, #0
// 	beq	.LC12
// 	cmp	r2, r3		/* Reached terminator ?  */
// 	bne	.LC11
// 	movs	r2, #0
// 	subs	r3, r1, #1
// 	strb	r2, [r3]	/* Terminate the arg string.  */
// 	b	.LC10
// 
// .LC12:
// 	mov	r1, sp		/* Point at stacked arg pointers.  */
// 	/* We've now got the stacked args in order, reverse them.  */
// 	add	r2, sp, r0, LSL #2	/* End of args.  */
// 	mov	r3, sp			/* Start of args.  */
// .LC13:	cmp	r2, r3
// 	ldrhi	r4,[r2, #-4]		/* Reverse ends of list.  */
// 	ldrhi	r5, [r3]
// 	strhi	r5, [r2, #-4]!
// 	strhi	r4, [r3], #4
// 	bhi	.LC13
// 	/* Ensure doubleword stack alignment.  */
// 	bic	sp, sp, #7



  //----------------------------------------------------------------------
  // init
  //----------------------------------------------------------------------
	
	/* Some arm/elf targets use the .init and .fini sections
	   to create constructors and destructors, and for these
	   targets we need to call the _init function and arrange
	   for _fini to be called at program exit.  */
	movs	r4, r0
	movs	r5, r1
	ldr	r0, .Lfini
	bl	atexit
	bl	__libc_init_array
	movs	r0, r4
	movs	r1, r5

  //----------------------------------------------------------------------
  // main
  //----------------------------------------------------------------------

	bl	main

	bl	exit		/* Should not return.  */

	/* Pop argc off the stack and save a pointer to argv */
	// ldr a2, [sp], #4
	// mov a3, sp

	// /* Push stack limit */
	// str a3, [sp, #-4]!

	// /* Push rtld_fini */
	// str a1, [sp, #-4]!

	// /* Fetch address of fini */
	// ldr ip, =_fini
	// /* Push fini */
	// str ip, [sp, #-4]!

	// /* Set up the other arguments in registers */
	// ldr a1, =main
	// ldr a4, =_init

	// /* __uClibc_main (main, argc, argv, init, fini, rtld_fini, stack_end) */

	// /* Let the libc call main and exit with its return code.  */
  // /* berkin: we'll just call main directly instead of __uClibc_main */
	// /* b __uClibc_main */
  // /* TODO: this is probably broken */
  // bl main

	/* should never get here....*/
	//bl abort

	.word _fini(GOT)
	.word _init(GOT)
	.word main(GOT)
.LC1:
  .word __bss_start__
.LC2:
  .word __bss_end__
.Lfini:
  .word _fini
//.LC30:
//	.word	CommandLine
//	.word	255


/* Define a symbol for the first piece of initialized data.  */
	.data
	.globl __data_start
__data_start:
	.long 0
	.weak data_start
	data_start = __data_start

  .globl __exidx_start
__exidx_start:
  .word 0
  .globl __exidx_end
__exidx_end:
  .word 0



/*
# _start:
# 
#         la      $gp, _gp        # Initialize global pointer
# 
#         # Normally when using the pkernel, the pkernel-bootstrap.S code
#         # will ensure that only core 0 ever makes it into this
#         # user-level _start function. gem5 is setup such that all cores
#         # begin execution in the _start function. So we check here to see
#         # whether or not this code is being executed by a core other than
#         # core 0. If so we just spin forever, and we will let the SEND_AM
#         # system call take care of making this core do something
#         # interesting.
# 
#         mfc0    $t0, $c0_coreid
# _notcore0:
#         bnez    $t0, _notcore0
# 
# #        la      $v0, _fbss      # Zero out uninitialized data sections
# #        la      $v1, _end       #  (the .sbss and .bss sections). See
# #1:      sw      $0,  0($v0)     #  linker script for how _fbss and
# #        addiu   $v0, $v0, 4     #  _end are defined.
# #        bltu    $v0, $v1, 1b    #
# 
#         jal     _init           # Run global initialization functions
# 
#         la      $a0, _fini      # Register global termination functions
#         jal     atexit          #  to be called upon exit
# 
#         lw      $a0, 0($sp)     # Start the program, setup args
#         addiu   $a1, $sp, 4     #  a0 = argc
#         jal     main            #  a1 = argv
# 
#         move    $a0, $v0        # Call exit function with return value
#         jal     exit            #  from main as exit code
# 
#         .end    _start
*/
