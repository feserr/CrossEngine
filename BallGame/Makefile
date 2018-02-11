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
	$(GENIE) --with-shared-lib vs2012
	$(GENIE) --with-shared-lib vs2013
	$(GENIE) --with-shared-lib vs2015
	$(GENIE) --with-shared-lib vs2017
	$(GENIE) --with-shared-lib --gcc=osx gmake

.build/projects/vs2012:
	$(GENIE) --with-shared-lib vs2012
vs2012-debug32: .build/projects/vs2012 ## Build - VS2012 x86 Debug
	devenv .build/projects/vs2012/pong.sln /Build "Debug|Win32"
vs2012-release32: .build/projects/vs2012 ## Build - VS2012 x86 Release
	devenv .build/projects/vs2012/pong.sln /Build "Release|Win32"
vs2012-debug64: .build/projects/vs2012 ## Build - VS2012 x64 Debug
	devenv .build/projects/vs2012/pong.sln /Build "Debug|x64"
vs2012-release64: .build/projects/vs2012 ## Build - VS2012 x64 Release
	devenv .build/projects/vs2012/pong.sln /Build "Release|x64"
vs2012: vs2012-debug32 vs2012-release32 vs2012-debug64 vs2012-release64 ## Build - VS2012 x86/x64 Debug and Release

.build/projects/vs2013:
	$(GENIE) --with-shared-lib vs2013
vs2013-debug32: .build/projects/vs2013 ## Build - VS2013 x86 Debug
	devenv .build/projects/vs2013/pong.sln /Build "Debug|Win32"
vs2013-release32: .build/projects/vs2013 ## Build - VS2013 x86 Release
	devenv .build/projects/vs2013/pong.sln /Build "Release|Win32"
vs2013-debug64: .build/projects/vs2013 ## Build - VS2013 x64 Debug
	devenv .build/projects/vs2013/pong.sln /Build "Debug|x64"
vs2013-release64: .build/projects/vs2013 ## Build - VS2013 x64 Release
	devenv .build/projects/vs2013/pong.sln /Build "Release|x64"
vs2013: vs2013-debug32 vs2013-release32 vs2013-debug64 vs2013-release64 ## Build - VS2013 x86/x64 Debug and Release

.build/projects/vs2015:
	$(GENIE) --with-shared-lib vs2015
vs2015-debug32: .build/projects/vs2015 ## Build - VS2015 x86 Debug
	devenv .build/projects/vs2015/pong.sln /Build "Debug|Win32"
vs2015-release32: .build/projects/vs2015 ## Build - VS2015 x86 Release
	devenv .build/projects/vs2015/pong.sln /Build "Release|Win32"
vs2015-debug64: .build/projects/vs2015 ## Build - VS2015 x64 Debug
	devenv .build/projects/vs2015/pong.sln /Build "Debug|x64"
vs2015-release64: .build/projects/vs2015 ## Build - VS2015 x64 Release
	devenv .build/projects/vs2015/pong.sln /Build "Release|x64"
vs2015: vs2015-debug32 vs2015-release32 vs2015-debug64 vs2015-release64 ## Build - VS2015 x86/x64 Debug and Release

.build/projects/vs2017:
	$(GENIE) --with-shared-lib vs2017
vs2017-debug32: .build/projects/vs2017 ## Build - vs2017 x86 Debug
	devenv .build/projects/vs2017/pong.sln /Build "Debug|Win32"
vs2017-release32: .build/projects/vs2017 ## Build - vs2017 x86 Release
	devenv .build/projects/vs2017/pong.sln /Build "Release|Win32"
vs2017-debug64: .build/projects/vs2017 ## Build - vs2017 x64 Debug
	devenv .build/projects/vs2017/pong.sln /Build "Debug|x64"
vs2017-release64: .build/projects/vs2017 ## Build - vs2017 x64 Release
	devenv .build/projects/vs2017/pong.sln /Build "Release|x64"
vs2017: vs2017-debug32 vs2017-release32 vs2017-debug64 vs2017-release64 ## Build - vs2017 x86/x64 Debug and Release

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

.build/projects/gmake-ios-arm:
	$(GENIE) --gcc=ios-arm gmake
ios-arm-debug: .build/projects/gmake-ios-arm ## Build - iOS ARM Debug
     $(MAKE) -R -C .build/projects/gmake-ios-arm config=debug
ios-arm-release: .build/projects/gmake-ios-arm ## Build - iOS ARM Release
     $(MAKE) -R -C .build/projects/gmake-ios-arm config=release
ios-arm: ios-arm-debug ios-arm-release ## Build - iOS ARM Debug and Release

.build/projects/gmake-ios-arm64:
	$(GENIE) --gcc=ios-arm64 gmake
ios-arm64-debug: .build/projects/gmake-ios-arm64 ## Build - iOS ARM64 Debug
     $(MAKE) -R -C .build/projects/gmake-ios-arm64 config=debug
ios-arm64-release: .build/projects/gmake-ios-arm64 ## Build - iOS ARM64 Release
     $(MAKE) -R -C .build/projects/gmake-ios-arm64 config=release
ios-arm64: ios-arm64-debug ios-arm64-release ## Build - iOS ARM64 Debug and Release

.build/projects/gmake-ios-simulator:
	$(GENIE) --gcc=ios-simulator gmake
ios-simulator-debug: .build/projects/gmake-ios-simulator ## Build - iOS Simulator Debug
     $(MAKE) -R -C .build/projects/gmake-ios-simulator config=debug
ios-simulator-release: .build/projects/gmake-ios-simulator ## Build - iOS Simulator Release
     $(MAKE) -R -C .build/projects/gmake-ios-simulator config=release
ios-simulator: ios-simulator-debug ios-simulator-release ## Build - iOS Simulator Debug and Release

build-darwin: osx

build: build-$(OS)

analyze:
	cppcheck src/
