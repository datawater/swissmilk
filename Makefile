PROJECTNAME := $(shell basename $(shell pwd) | tr '[:upper:]' '[:lower:]')

SOURCEDIR := src
BUILDDIR :=
SOURCES := $(shell find . -type f -path "./**/$(PROJECTNAME)**/*.cpp" -not -path "./**/$(PROJECTNAME)-tests**/*.cpp" | cut -c 3-)
OBJECTS = $(foreach SOURCE,$(SOURCES),$(addprefix $(BUILDDIR)/,$(shell basename $(SOURCE:%.cpp=%.o))))
BINARY = $(addprefix $(BUILDDIR)/,$(PROJECTNAME))
HEADERDIR := $(SOURCEDIR)/
BINARYSOURCES := $(shell find src/ -type f -name "*.cpp" -not -path "src/$(PROJECTNAME)/*.cpp" -not -path "./**/$(PROJECTNAME)-tests/*.cpp")

RELEASE ?= false
AGGRESSIVE_OPTIMIZE ?= false
STRICT ?= false
BIT_WIDTH ?= $(shell getconf LONG_BIT)

CFLAGS = -Wall -Wextra -Werror -std=c++17 -Wno-error=cpp -Wno-error=format-security -Wno-error=deprecated-copy -m$(BIT_WIDTH)
LIBS =
CC_NAME =
ERROR =

HAS_LIBUNWIND := $(shell pkg-config --libs libunwind-generic 2> /dev/null > /dev/null && echo 1 || echo 0)

ifeq ($(HAS_LIBUNWIND),1)
	LIBS += $(shell pkg-config --libs libunwind-generic) 
endif

ifeq ($(RELEASE), false)
	CFLAGS += -g -Og -DDEBUG
	BUILDDIR = build/debug

	ifeq ($(AGGRESSIVE_OPTIMIZE), true)
		ERROR = AGGRESSIVE_OPTIMIZE is true without RELEASE being true
	endif
else
	BUILDDIR += build/release
	CFLAGS += -flto -O3

	ifneq ($(CC_NAME),clang)
		CFLAGS += -s
	endif

	ifeq ($(AGGRESSIVE_OPTIMIZE), true)
		CFLAGS += -mtune=native -march=native
		ifeq ($(CC_NAME), gnu)
			CFLAGS += -fmodulo-sched -fmodulo-sched-allow-regmoves \
					  -fgcse-las -fdevirtualize-speculatively -fira-hoist-pressure \
					  -floop-parallelize-all -ftree-parallelize-loops=4
		endif
	endif
endif

ifeq ($(CC_NAME), clang)
	CFLAGS += -Wno-unused-command-line-argument
endif

ifeq ($(STRICT), true)
	CFLAGS += -DSTRICT -Wstrict-aliasing -Wunreachable-code -Wcast-align -Wcast-qual \
					   -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs \
					   -Wredundant-decls -Wstrict-overflow=4 -Wswitch-default -Wundef -Wno-unused \
					   -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
endif

ifneq ($(LD),)
	ifneq ($(LD),ld)
		CFLAGS += -fuse-ld=$(LD)
	endif
endif

TESTEXECS := $(patsubst tests/%.cpp,$(BUILDDIR)/%.out,$(wildcard tests/*.cpp))

main: mac_clean help
build: check_errors init $(BINARY)

.PHONY: init
init:
	@-mkdir -p $(BUILDDIR) 2> /dev/null

.PHONY: clean
clean: mac_clean
	@-rm -fdr build/*
	@-rm -fdr tests/*.out

.PHONY: mac_clean
mac_clean:
	@-find . -type f -name ".DS_Store" -delete

.PHONY: check
check:
	infer capture -- make build -B -j$(shell nproc --ignore 8)
	infer -j $(shell nproc --ignore 2) run

.PHONY: check_errors
check_errors:
ifneq ($(ERROR),)
	$(error [ERROR] $(ERROR))
endif

$(BINARY): $(BINARYSOURCES) lib$(PROJECTNAME).so
	$(CXX) $(CFLAGS) $(BINARYSOURCES) -I$(HEADERDIR) -L$(BUILDDIR) -l$(PROJECTNAME) $(LIBS) -o $@.1

	echo -e '#!/bin/bash\nexport LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:$(shell pwd)/$(BUILDDIR)/"\n$(shell pwd)/$@.1' > $@
	chmod +x $@

$(OBJECTS): $(SOURCES)

$(BUILDDIR)/%.o: $(SOURCEDIR)/$(PROJECTNAME)/%.cpp
	$(CXX) $(CFLAGS) -fPIC -I$(HEADERDIR) -c $< -o $@

lib$(PROJECTNAME).so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $(BUILDDIR)/$@ $^ $(LIBS)

$(BUILDDIR)/%.out: tests/%.cpp $(BINARY)
	$(CXX) $(CFLAGS) -I$(HEADERDIR) -L $(BUILDDIR) -o $@.test.1 $< -l$(PROJECTNAME) $(LIBS)

	echo -e '#!/bin/bash\nexport LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:$(shell pwd)/$(BUILDDIR)/"\n$(shell pwd)/$@.test.1' > $@.test
	chmod +x $@.test

test: $(TESTEXECS)
	./test.sh $(BUILDDIR)
	rm -fdr *.tmp

SEPARATOR = "--------------------"

.PHONY: help
help:
	@echo -e $(SEPARATOR)
	@echo -e "Available subcommands:"
	@echo -e "\tbuild: Builds the project"
	@echo -e "\ttest:  Builds and tests the project"
	@echo -e "\tcheck: Statically analyzes the project with ccheck"
	@echo -e $(SEPARATOR)
	@echo -e "Available options:\n"
	@echo -e "RELEASE=(true | false):\n\t\tIf true, compiles in release mode, with optimizations,"
	@echo -e "\t\tif false compiles in debug mode, with debug info and minimal optimizations.\n\t\tDefault: false\n"
	@echo -e "AGGRESSIVE_OPTIMIZE=(true | false):\n\t\tIf true, compiles with \`-O3 -mtune=native -march=native\`,"
	@echo -e "\t\t!!!Only effective with RELEASE being true!!!. Default: false\n"
	@echo -e "STRICT=(true | false):\n\t\tIf true, compiles in strict mode (Extra warnings). Default: true\n"
	@echo -e "BIT_WIDTH=(16 | 32 | 64): Selects the bitwidth\n\t"
