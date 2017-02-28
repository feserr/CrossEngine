--
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

project ("crossengine")
	uuid ("C618B9EA-E27B-40FB-B97F-2E737BD35A8C")
	kind "StaticLib"

	includedirs {
		path.join(BX_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
	}

	files {
		path.join(BGFX_DIR, "3rdparty/ib-compress/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/ib-compress/**.h"),
		path.join(BGFX_DIR, "3rdparty/ocornut-imgui/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/ocornut-imgui/**.h"),
		path.join(MODULE_DIR, "src/**.cpp"),
		path.join(MODULE_DIR, "src/**.inl"),
		path.join(MODULE_DIR, "src/**.h"),
	}

	if _OPTIONS["with-scintilla"] then
		defines {
			"SCI_NAMESPACE",
			"SCI_LEXER",
		}

		buildoptions {
--			"-Wno-missing-field-initializers",
		}

		includedirs {
			path.join(BGFX_DIR, "3rdparty/scintilla/include"),
			path.join(BGFX_DIR, "3rdparty/scintilla/lexlib"),
		}

		files {
			path.join(BGFX_DIR, "3rdparty/scintilla/src/**.cxx"),
			path.join(BGFX_DIR, "3rdparty/scintilla/src/**.h"),
			path.join(BGFX_DIR, "3rdparty/scintilla/lexlib/**.cxx"),
			path.join(BGFX_DIR, "3rdparty/scintilla/lexlib/**.h"),
			path.join(BGFX_DIR, "3rdparty/scintilla/lexers/**.cxx"),
		}
	end

	if _OPTIONS["with-sdl"] then
		defines {
			"ENTRY_CONFIG_USE_SDL=1",
		}
		includedirs {
			"$(SDL2_DIR)/include",
		}
	end

	if _OPTIONS["with-glfw"] then
		defines {
			"ENTRY_CONFIG_USE_GLFW=1",
		}
	end

	configuration { "linux-steamlink" }
		defines {
			"EGL_API_FB",
		}

	configuration { "osx or ios* or tvos*" }
		files {
			path.join(MODULE_DIR, "src/**.mm"),
		}

	configuration { "winphone8* or winstore8* or durango"}
		files {
			path.join(MODULE_DIR, "src/**.cx"),
		}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}
		premake.vstudio.splashpath = "../../../runtime/images/SplashScreen.png"
