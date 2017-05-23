UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin FreeBSD GNU/kFreeBSD))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
ifeq ($(UNAME),$(filter $(UNAME),FreeBSD GNU/kFreeBSD))
OS=bsd
else
OS=linux
endif
endif
else
OS=windows

help: projgen

endif

BX_DIR?=../bx
GENIE?=$(BX_DIR)/tools/bin/$(OS)/genie
NINJA?=$(BX_DIR)/tools/bin/$(OS)/ninja

.PHONY: help

help:
	@echo Available targets:

clean: ## Clean all intermediate files.
	@echo Cleaning...
	-@rm -rf .build
	@mkdir .build

projgen:
	$(GENIE) --with-shared-lib --gcc=osx gmake

.build/projects/gmake-osx:
	$(GENIE) --with-shared-lib --gcc=osx gmake
osx-debug32: .build/projects/gmake-osx ## Build - OSX x86 Debug
	$(MAKE) -C .build/projects/gmake-osx config=debug32 -j 6
osx-release32: .build/projects/gmake-osx ## Build - OSX x86 Release
	$(MAKE) -C .build/projects/gmake-osx config=release32 -j 6
osx-debug64: .build/projects/gmake-osx ## Build - OSX x64 Debug
	$(MAKE) -C .build/projects/gmake-osx config=debug64 -j 6
osx-release64: .build/projects/gmake-osx ## Build - OSX x64 Release
	$(MAKE) -C .build/projects/gmake-osx config=release64 -j6
osx: osx-debug32 osx-release32 osx-debug64 osx-release64 ## Build - OSX x86/x64 Debug and Release

build-darwin: osx

build: build-$(OS)

analyze:
	cppcheck src/
