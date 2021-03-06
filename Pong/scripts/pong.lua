
project ("pong")
    uuid (os.uuid("pong"))
    kind "WindowedApp"

configuration {}

debugdir (path.join(MODULE_DIR, "runtime"))

includedirs {
    EIGEN_DIR,
    path.join(BX_DIR,   "include"),
    path.join(BIMG_DIR, "include"),
    path.join(BGFX_DIR, "include"),
    path.join(BGFX_DIR, "3rdparty"),
    path.join(CROSSENGINE_DIR, "deps/include"),
    path.join(CROSSENGINE_DIR, "src"),
    path.join(CROSSENGINE_DIR, "src/crossengine"),
}

files {
    path.join(MODULE_DIR, "**.c"),
    path.join(MODULE_DIR, "**.cpp"),
    path.join(MODULE_DIR, "**.h"),
    path.join(MODULE_DIR, "runtime/images"),
    path.join(MODULE_DIR, "runtime/shaders"),
}

removefiles {
    path.join(MODULE_DIR, "**.bin.h"),
}

flags {
--    "FatalWarnings",
}

removeflags {
    "NoExceptions",
}

links {
    "crossengine",
    "bgfx",
    "bimg_decode",
    "bimg",
    "bx",
    "SDL2",
    "SDL2main",
    "SDL2_ttf",
    "SDL2_mixer",
}

libdirs { path.join(CROSSENGINE_DIR, "deps/lib/SDL") }

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
        "d3d12",
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
        path.join(MODULE_DIR, "runtime/iOS-Info.plist"),
    }

configuration { "xcode4", "tvos" }
    kind "WindowedApp"
    files {
        path.join(MODULE_DIR, "runtime/tvOS-Info.plist"),
    }

configuration { "qnx*" }
    targetextension ""
    links {
        "EGL",
        "GLESv2",
    }

configuration {}

strip()
