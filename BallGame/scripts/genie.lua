
newoption {
	trigger = "with-amalgamated",
	description = "Enable amalgamated build.",
}

newoption {
	trigger = "with-ovr",
	description = "Enable OculusVR integration.",
}

newoption {
	trigger = "with-sdl",
	description = "Enable SDL entry.",
}

newoption {
	trigger = "with-glfw",
	description = "Enable GLFW entry.",
}

newoption {
	trigger = "with-profiler",
	description = "Enable build with intrusive profiler.",
}

newoption {
	trigger = "with-scintilla",
	description = "Enable building with Scintilla editor.",
}

newoption {
	trigger = "with-shared-lib",
	description = "Enable building shared library.",
}

newoption {
	trigger = "with-tools",
	description = "Enable building tools.",
}

newoption {
	trigger = "with-examples",
	description = "Enable building examples.",
}

solution "ballgame"
	configurations {
		"Debug",
		"Release",
	}

	if _ACTION == "xcode4" then
		platforms {
			"Universal",
		}
	else
		platforms {
			"x32",
			"x64",
--			"Xbox360",
			"Native", -- for targets where bitness is not specified
		}
	end

	language "C++"
	startproject "ballgame"

MODULE_DIR = path.getabsolute("../")
EXTERNAL_DIR = path.getabsolute("../../external/")
BGFX_DIR   = path.getabsolute(path.join(EXTERNAL_DIR, "bgfx"))
BIMG_DIR   = path.getabsolute(path.join(EXTERNAL_DIR, "bimg"))
BX_DIR     = os.getenv("BX_DIR")
EIGEN_DIR  = path.getabsolute(path.join(EXTERNAL_DIR, "eigen"))
CROSSENGINE_DIR = path.getabsolute("../../CrossEngine")

local BGFX_BUILD_DIR = path.join(MODULE_DIR, "build")
local BGFX_THIRD_PARTY_DIR = path.join(BGFX_DIR, "3rdparty")
if not BX_DIR then
	BX_DIR = path.getabsolute(path.join(EXTERNAL_DIR, "bx"))
end

if not os.isdir(BX_DIR) then
	print("bx not found at " .. BX_DIR)
	print("For more info see: https://bkaradzic.github.io/bgfx/build.html")
	os.exit()
end

dofile (path.join(BX_DIR, "scripts/toolchain.lua"))
if not toolchain(BGFX_BUILD_DIR, BGFX_THIRD_PARTY_DIR) then
	return -- no action specified
end

function copyLib()
end

if _OPTIONS["with-sdl"] then
	if os.is("windows") then
		if not os.getenv("SDL2_DIR") then
			print("Set SDL2_DIR enviroment variable.")
		end
	end
end

if _OPTIONS["with-profiler"] then
	defines {
		"ENTRY_CONFIG_PROFILER=1",
		"BGFX_CONFIG_PROFILER_REMOTERY=1",
        "_WINSOCKAPI_"
	}
end

dofile(path.join(BGFX_DIR, "scripts/bgfx.lua"))

group "libs"
bgfxProject("", "StaticLib", {})

dofile(path.join(BX_DIR, "scripts/bx.lua"))

dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_decode.lua"))

dofile(path.join(CROSSENGINE_DIR, "scripts/crossengine.lua"))

if _OPTIONS["with-tools"] then
    group "tools"
    dofile(path.join(BIMG_DIR, "scripts/bimg_encode.lua"))
end

group "ballgame"
dofile(path.join(MODULE_DIR, "scripts/ballgame.lua"))

if _OPTIONS["with-shared-lib"] then
	group "libs"
	bgfxProject("-shared-lib", "SharedLib", {})
end
