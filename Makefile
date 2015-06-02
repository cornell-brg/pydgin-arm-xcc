#=========================================================================
# Pydgin ARM Cross-Compiler Makefile
#=========================================================================

# the name to be used to create a directory for gcc, binutils and newlib
# compilation
BUILD_DIR = build

PWD = $(shell pwd)

# the prefix for the produced xcc toolchain
PREFIX = $(PWD)/xcc


COMMON_CONFIGURE_FLAGS = --target=arm-none-eabi --disable-interwork \
												 --disable-multilib

BINUTILS_DIR = $(PWD)/src/binutils-2.19.1
GMP_DIR = $(PWD)/src/gmp-5.1.3
MPFR_DIR = $(PWD)/src/mpfr-3.1.2
GCC_DIR = $(PWD)/src/gcc-4.3.3
NEWLIB_DIR = $(PWD)/src/newlib-2.1.0
NEWLIB_LIBC_HEADER_DIR = $(NEWLIB_DIR)/newlib/libc/include

GMP_INSTALL_DIR = $(GMP_DIR)/install
MPFR_INSTALL_DIR = $(MPFR_DIR)/install

build-all: build-binutils build-gmp build-mpfr build-gcc build-newlib

clean: clean-binutils clean-gmp clean-mpfr clean-gcc clean-newlib

.PHONY: clean

#-------------------------------------------------------------------------
# binutils
#-------------------------------------------------------------------------

BINUTILS_BUILD_DIR = $(BINUTILS_DIR)/$(BUILD_DIR)
BINUTILS_MAKEFILE = $(BINUTILS_BUILD_DIR)/Makefile

build-binutils: $(BINUTILS_MAKEFILE)
	cd $(BINUTILS_BUILD_DIR) && \
	make $(MAKEFLAGS) && \
	make $(MAKEFLAGS) install

$(BINUTILS_MAKEFILE): | $(BINUTILS_BUILD_DIR)
	cd $(BINUTILS_BUILD_DIR) && \
	../configure $(COMMON_CONFIGURE_FLAGS) --prefix=$(PREFIX)

$(BINUTILS_BUILD_DIR):
	mkdir $(BINUTILS_BUILD_DIR)

clean-binutils:
	rm -rf $(BINUTILS_BUILD_DIR)

.PHONY: build-binutils clean-binutils

#-------------------------------------------------------------------------
# gmp
#-------------------------------------------------------------------------

GMP_BUILD_DIR = $(GMP_DIR)/$(BUILD_DIR)
GMP_MAKEFILE = $(GMP_BUILD_DIR)/Makefile

build-gmp: $(GMP_MAKEFILE)
	cd $(GMP_BUILD_DIR) && \
	make $(MAKEFLAGS) && \
	make $(MAKEFLAGS) install

$(GMP_MAKEFILE): | $(GMP_BUILD_DIR)
	cd $(GMP_BUILD_DIR) && \
	../configure --prefix=$(GMP_INSTALL_DIR)

$(GMP_BUILD_DIR):
	mkdir $(GMP_BUILD_DIR)

clean-gmp:
	rm -rf $(GMP_BUILD_DIR) $(GMP_INSTALL_DIR)

.PHONY: build-gmp clean-gmp

#-------------------------------------------------------------------------
# mpfr
#-------------------------------------------------------------------------

MPFR_BUILD_DIR = $(MPFR_DIR)/$(BUILD_DIR)
MPFR_MAKEFILE = $(MPFR_BUILD_DIR)/Makefile
MPFR_CONFIGURE_FLAGS = --with-gmp=$(GMP_INSTALL_DIR)

build-mpfr: build-gmp $(MPFR_MAKEFILE)
	cd $(MPFR_BUILD_DIR) && \
	make $(MAKEFLAGS) && \
	make $(MAKEFLAGS) install

$(MPFR_MAKEFILE): build-gmp | $(MPFR_BUILD_DIR)
	cd $(MPFR_BUILD_DIR) && \
	../configure $(MPFR_CONFIGURE_FLAGS) --prefix=$(MPFR_INSTALL_DIR)

$(MPFR_BUILD_DIR):
	mkdir $(MPFR_BUILD_DIR)

clean-mpfr:
	rm -rf $(MPFR_BUILD_DIR) $(MPFR_INSTALL_DIR)

.PHONY: build-mpfr clean-mpfr

#-------------------------------------------------------------------------
# gcc
#-------------------------------------------------------------------------

GCC_BUILD_DIR = $(GCC_DIR)/$(BUILD_DIR)
GCC_MAKEFILE = $(GCC_BUILD_DIR)/Makefile
GCC_CONFIGURE_FLAGS = $(COMMON_CONFIGURE_FLAGS) \
											--enable-languages=c,c++ --with-newlib \
											--with-headers=$(NEWLIB_LIBC_HEADER_DIR) \
											--with-gmp=$(GMP_INSTALL_DIR) \
											--with-mpfr=$(MPFR_INSTALL_DIR) \
											--with-arc=armv5 --with-float=soft \
											--enable-__cxa_atexit \
											--enable-target-optspace --disable-nls


build-gcc: build-binutils build-gmp build-mpfr $(GCC_MAKEFILE)
	cd $(GCC_BUILD_DIR) && \
	export LD_LIBRARY_PATH=$(GMP_INSTALL_DIR)/lib:$(MPFR_INSTALL_DIR)/lib:$$LD_LIBRARY_PATH && \
	make $(MAKEFLAGS) && \
	make $(MAKEFLAGS) install

$(GCC_MAKEFILE): build-binutils build-gmp build-mpfr | $(GCC_BUILD_DIR)
	cd $(GCC_BUILD_DIR) && \
	../configure $(GCC_CONFIGURE_FLAGS) --prefix=$(PREFIX)

$(GCC_BUILD_DIR):
	mkdir $(GCC_BUILD_DIR)

clean-gcc:
	rm -rf $(GCC_BUILD_DIR)

.PHONY: build-gcc clean-gcc

#-------------------------------------------------------------------------
# newlib
#-------------------------------------------------------------------------

NEWLIB_BUILD_DIR = $(NEWLIB_DIR)/$(BUILD_DIR)
NEWLIB_MAKEFILE = $(NEWLIB_BUILD_DIR)/Makefile

build-newlib: build-binutils build-gcc $(NEWLIB_MAKEFILE)
	cd $(NEWLIB_BUILD_DIR) && \
	export PATH=$(PREFIX)/bin:$$PATH && \
	make $(MAKEFLAGS) && \
	make $(MAKEFLAGS) install

$(NEWLIB_MAKEFILE): build-binutils build-gcc | $(NEWLIB_BUILD_DIR)
	cd $(NEWLIB_BUILD_DIR) && \
	export PATH=$(PREFIX)/bin:$$PATH && \
	../configure $(COMMON_CONFIGURE_FLAGS) --prefix=$(PREFIX)

$(NEWLIB_BUILD_DIR):
	mkdir $(NEWLIB_BUILD_DIR)

clean-newlib:
	rm -rf $(NEWLIB_BUILD_DIR)

.PHONY: build-newlib clean-newlib

