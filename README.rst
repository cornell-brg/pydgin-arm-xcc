==========================================================================
Pydgin ARM Cross-Compiler
==========================================================================

Useful links:

* http://www.ifp.illinois.edu/~nakazato/tips/xgcc.html

--------------------------------------------------------------------------
Components used
--------------------------------------------------------------------------

* ``binutils-2.19.1``
* ``gcc-4.3.3``
* ``gcc-core-4.3.3``
* ``gcc-g++-4.3.3``
* ``newlib-2.1.0``

--------------------------------------------------------------------------
Installation
--------------------------------------------------------------------------

If everything is configured correctly, you can simply use the makefile
provided::

  % make build-all PREFIX=<prefix>

If ``PREFIX`` is not provided, it will install the cross compiler under
``./xcc``.

--------------------------------------------------------------------------
Manual Installation
--------------------------------------------------------------------------

Use these instructions if the above fails.  Untar all to ``src``. Start
version control. First build ``binutils``::

  % cd src/binutils-2.19.1
  % mkdir build-pydgin-arm
  % cd build-pydgin-arm
  % ../configure --target=arm-none-eabi --disable-interwork \
                 --disable-multilib --prefix=`pwd`/../../../build
  % make -j 16
  % make install

Then build ``gcc``. Note that ``with-arc`` is probably a typo. But with
``with-arch=armv5`` doesn't work. More specifically, when it's configuring
``libiberty`` for the target, it says it can't find any of the headers.
The following seemst to work::

  % cd src/gcc-4.3.3
  % mkdir build-pydgin-arm
  % cd build-pydgin-arm
  % ../configure --target=arm-none-eabi --prefix=`pwd`/../../../build \
    --disable-interwork --disable-multilib --enable-languages=c,c++ \
    --with-newlib \
    --with-headers=`pwd`/../../newlib-2.1.0/newlib/libc/include \
    --with-gmp=$STOW_PKGS_PREFIX \
    --with-arc=armv5 --with-float=soft --enable-__cxa_atexit \
    --enable-target-optspace --disable-nls
  % make -j 16
  % make install

Add ``/build/bin`` to ``PATH`` first so that ``newlib`` can find the
compiler::

  % cd src/newlib-2.1.0
  % mkdir build-pydgin-arm
  % cd build-pydgin-arm
  % ../configure --target=arm-none-eabi --prefix=`pwd`/../../../build \
                 --disable-interwork --disable-multiblib
  % make -j 16
  % make install



