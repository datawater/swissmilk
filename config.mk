CXXFLAGS_WARNINGS = -Wall -Wextra -pedantic -Wstrict-aliasing -Wno-pointer-arith \
					-Wno-variadic-macros -Wno-unused-command-line-argument \
					-Wno-write-strings -Wno-unknown-warning-option
CXXFLAGS = $(CXXFLAGS_WARNINGS) -std=c++17
LIBS = -lunwind

GLIBC_VERSION := $(shell getconf GNU_LIBC_VERSION | tail -c +7)
LRT_REQUIRED_VERSION := 2.17
LRT_IS_REQUIRED := $(shell printf "%s\n" $(LRT_REQUIRED_VERSION) $(GLIBC_VERSION) | sort | head -n1)

PROFILE_DEBUG_CXXFLAGS := -ggdb -O0
PROFILE_RELEASE_CXXFLAGS := -O3 -s -flto -mtune=native -march=native -fgraphite-identity
PROFILE_SIZE_CXXFLAGS := -Oz -s

USE_MOLD = $(shell which mold)
ifneq ($(USE_MOLD),)
	CXXLAGS += -fuse-ld=$(USE_MOLD)
endif

PROFILE ?=debug

IS_ERROR = 0
ERROR_TEXT = ok

ifeq ($(LRT_IS_REQUIRED),$(GLIBC_VERSION))
	LIBS += -lrt
endif

ifeq ($(PROFILE),debug)
	CXXFLAGS += $(PROFILE_DEBUG_CXXFLAGS)
else
	ifeq ($(PROFILE),release)
		CXXFLAGS += $(PROFILE_RELEASE_CXXFLAGS)
	else
		ifeq ($(PROFILE),size)
			CXXFLAGS += $(PROFILE_SIZE_CXXFLAGS)
		else
			IS_ERROR =1
			ERROR_TEXT = [ERROR] Unknown profile "$(PROFILE)".
		endif
	endif
endif
