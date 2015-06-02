#=========================================================================
# Pydgin ARM Cross-Compiler Makefile
#=========================================================================

# the name to be used to create a directory for gcc, binutils and newlib
# compilation
BUILD_DIR = build

PWD = $(shell pwd)

# the prefix for the produced xcc toolchain
PREFIX = $(PWD)/xcc

# we usually need to specify the directory of gmp
GMP_DIR = $$STOW_PKGS_PREFIX

COMMON_CONFIGURE_FLAGS = --target=arm-none-eabi --disable-interwork \
												 --disable-multilib

BINUTILS_DIR = $(PWD)/src/binutils-2.19.1
GCC_DIR = $(PWD)/src/gcc-4.3.3
NEWLIB_DIR = $(PWD)/src/newlib-2.1.0
NEWLIB_LIBC_HEADER_DIR = $(NEWLIB_DIR)/newlib/libc/include

build-all: build-binutils build-gcc build-newlib

clean: clean-binutils clean-gcc clean-newlib

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
# gcc
#-------------------------------------------------------------------------

GCC_BUILD_DIR = $(GCC_DIR)/$(BUILD_DIR)
GCC_MAKEFILE = $(GCC_BUILD_DIR)/Makefile
GCC_CONFIGURE_FLAGS = $(COMMON_CONFIGURE_FLAGS) \
											--enable-languages=c,c++ --with-newlib \
											--with-headers=$(NEWLIB_LIBC_HEADER_DIR) \
											--with-gmp=$(GMP_DIR) \
											--with-arc=armv5 --with-float=soft \
											--enable-__cxa_atexit \
											--enable-target-optspace --disable-nls


build-gcc: build-binutils $(GCC_MAKEFILE)
	cd $(GCC_BUILD_DIR) && \
	make $(MAKEFLAGS) && \
	make $(MAKEFLAGS) install

$(GCC_MAKEFILE): | $(GCC_BUILD_DIR)
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

$(NEWLIB_MAKEFILE): | $(NEWLIB_BUILD_DIR)
	cd $(NEWLIB_BUILD_DIR) && \
	export PATH=$(PREFIX)/bin:$$PATH && \
	../configure $(COMMON_CONFIGURE_FLAGS) --prefix=$(PREFIX)

$(NEWLIB_BUILD_DIR):
	mkdir $(NEWLIB_BUILD_DIR)

clean-newlib:
	rm -rf $(NEWLIB_BUILD_DIR)

.PHONY: build-newlib clean-newlib

