-- Copyright 2020 Elías Serrano. All rights reserved.
-- License: https://github.com/feserr/crossengine#license

solution "pong"
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
			"x64",
		}
	end

	language "C++"
	startproject "pong"

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

group "pong"
dofile(path.join(MODULE_DIR, "scripts/pong.lua"))
