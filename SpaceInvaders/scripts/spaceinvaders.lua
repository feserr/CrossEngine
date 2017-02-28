
project ("spaceinvaders")
    uuid (os.uuid("spaceinvaers"))
    kind "WindowedApp"

configuration {}

debugdir (path.join(BGFX_DIR, "examples/runtime"))

includedirs {
    path.join(BX_DIR,   "include"),
    path.join(BGFX_DIR, "include"),
    path.join(BGFX_DIR, "3rdparty"),
    path.join(CROSSENGINE_DIR, "src"),
}

files {
    path.join(MODULE_DIR, "**.c"),
    path.join(MODULE_DIR, "**.cpp"),
    path.join(MODULE_DIR, "**.h"),
}

removefiles {
    path.join(MODULE_DIR, "**.bin.h"),
}

links {
    "crossengine",
    "bgfx",
    "bx",
}

if _OPTIONS["with-sdl"] then
    defines { "ENTRY_CONFIG_USE_SDL=1" }
    links   { "SDL2" }

    configuration { "osx" }
        libdirs { "$(SDL2_DIR)/lib" }

    configuration {}
end

if _OPTIONS["with-glfw"] then
    defines { "ENTRY_CONFIG_USE_GLFW=1" }
    links   { "glfw3" }

    configuration { "linux or freebsd" }
        links {
            "Xrandr",
            "Xinerama",
            "Xi",
            "Xxf86vm",
            "Xcursor",
        }

    configuration { "osx" }
        linkoptions {
            "-framework CoreVideo",
            "-framework IOKit",
        }

    configuration {}
end

if _OPTIONS["with-ovr"] then
    configuration { "x32" }
        libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/Win32/Release", _ACTION) }

    configuration { "x64" }
        libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/x64/Release", _ACTION) }

    configuration { "x32 or x64" }
        links { "libovr" }

    configuration {}
end

configuration { "vs*", "x32 or x64" }
    linkoptions {
        "/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
    }
    links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
        "DelayImp",
    }

configuration { "vs201*", "x32 or x64" }
    linkoptions { -- this is needed only for testing with GLES2/3 on Windows with VS201x
        "/DELAYLOAD:\"libEGL.dll\"",
        "/DELAYLOAD:\"libGLESv2.dll\"",
    }

configuration { "mingw*" }
    targetextension ".exe"
    links {
        "gdi32",
        "psapi",
    }

configuration { "vs20*", "x32 or x64" }
    links {
        "gdi32",
        "psapi",
    }

configuration { "durango" }
    links {
        "d3d11_x",
        "d3d12_x",
        "combase",
        "kernelx",
    }

configuration { "winphone8* or winstore8*" }
    removelinks {
        "DelayImp",
        "gdi32",
        "psapi"
    }
    links {
        "d3d11",
        "dxgi"
    }
    linkoptions {
        "/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
    }

-- WinRT targets need their own output directories or build files stomp over each other
configuration { "x32", "winphone8* or winstore8*" }
    targetdir (path.join(BGFX_BUILD_DIR, "win32_" .. _ACTION, "bin", _name))
    objdir (path.join(BGFX_BUILD_DIR, "win32_" .. _ACTION, "obj", _name))

configuration { "x64", "winphone8* or winstore8*" }
    targetdir (path.join(BGFX_BUILD_DIR, "win64_" .. _ACTION, "bin", _name))
    objdir (path.join(BGFX_BUILD_DIR, "win64_" .. _ACTION, "obj", _name))

configuration { "ARM", "winphone8* or winstore8*" }
    targetdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "bin", _name))
    objdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "obj", _name))

configuration { "mingw-clang" }
    kind "ConsoleApp"

configuration { "android*" }
    kind "ConsoleApp"
    targetextension ".so"
    linkoptions {
        "-shared",
    }
    links {
        "EGL",
        "GLESv2",
    }

configuration { "nacl*" }
    kind "ConsoleApp"
    targetextension ".nexe"
    links {
        "ppapi",
        "ppapi_gles2",
        "pthread",
    }

configuration { "pnacl" }
    kind "ConsoleApp"
    targetextension ".pexe"
    links {
        "ppapi",
        "ppapi_gles2",
        "pthread",
    }

configuration { "asmjs" }
    kind "ConsoleApp"
    targetextension ".bc"

configuration { "linux-* or freebsd", "not linux-steamlink" }
    links {
        "X11",
        "GL",
        "pthread",
    }

configuration { "linux-steamlink" }
    links {
        "EGL",
        "GLESv2",
        "SDL2",
        "pthread",
    }

configuration { "rpi" }
    links {
        "X11",
        "GLESv2",
        "EGL",
        "bcm_host",
        "vcos",
        "vchiq_arm",
        "pthread",
    }

configuration { "osx" }
    linkoptions {
        "-framework Cocoa",
        "-framework QuartzCore",
        "-framework OpenGL",
        "-weak_framework Metal",
    }

configuration { "ios* or tvos*" }
    kind "ConsoleApp"
    linkoptions {
        "-framework CoreFoundation",
        "-framework Foundation",
        "-framework OpenGLES",
        "-framework UIKit",
        "-framework QuartzCore",
        "-weak_framework Metal",
    }

configuration { "xcode4", "ios" }
    kind "WindowedApp"
    files {
        path.join(BGFX_DIR, "examples/runtime/iOS-Info.plist"),
    }

configuration { "xcode4", "tvos" }
    kind "WindowedApp"
    files {
        path.join(BGFX_DIR, "examples/runtime/tvOS-Info.plist"),
    }

configuration { "qnx*" }
    targetextension ""
    links {
        "EGL",
        "GLESv2",
    }

configuration {}

strip()
