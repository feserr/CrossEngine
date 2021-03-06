project('crossengine')
uuid('C618B9EA-E27B-40FB-B97F-2E737BD35A8C')
kind 'StaticLib'

includedirs {
    EIGEN_DIR,
    path.join(BX_DIR, 'include'),
    path.join(BIMG_DIR, 'include'),
    path.join(BGFX_DIR, 'include'),
    path.join(BGFX_DIR, '3rdparty'),
    path.join(CROSSENGINE_DIR, 'deps/include')
}

files {
    path.join(BGFX_DIR, "3rdparty/meshoptimizer/src/**.cpp"),
	path.join(BGFX_DIR, "3rdparty/meshoptimizer/src/**.h"),
    path.join(BGFX_DIR, "3rdparty/dear-imgui/**.cpp"),
	path.join(BGFX_DIR, "3rdparty/dear-imgui/**.h"),
    path.join(CROSSENGINE_DIR, 'src/**.cpp'),
    path.join(CROSSENGINE_DIR, 'src/**.mm'),
    path.join(CROSSENGINE_DIR, 'src/**.inl'),
    path.join(CROSSENGINE_DIR, 'src/**.h')
}

removeflags {
    'NoExceptions'
}

if _OPTIONS['with-scintilla'] then
    defines {
        'SCI_NAMESPACE',
        'SCI_LEXER'
    }

    buildoptions {}

    includedirs {
        path.join(BGFX_DIR, '3rdparty/scintilla/include'),
        path.join(BGFX_DIR, '3rdparty/scintilla/lexlib')
    }

    files {
        path.join(BGFX_DIR, '3rdparty/scintilla/src/**.cxx'),
        path.join(BGFX_DIR, '3rdparty/scintilla/src/**.h'),
        path.join(BGFX_DIR, '3rdparty/scintilla/lexlib/**.cxx'),
        path.join(BGFX_DIR, '3rdparty/scintilla/lexlib/**.h'),
        path.join(BGFX_DIR, '3rdparty/scintilla/lexers/**.cxx')
    }
end

if _OPTIONS['with-sdl'] then
    defines {
        'ENTRY_CONFIG_USE_SDL=1'
    }
    includedirs {
        path.join(CROSSENGINE_DIR, 'deps/include/SDL')
    }
end

if _OPTIONS['with-glfw'] then
    defines {
        'ENTRY_CONFIG_USE_GLFW=1'
    }
end

configuration {'linux-steamlink'}
defines {
    'EGL_API_FB'
}

configuration {'osx or ios* or tvos*'}
files {
    path.join(CROSSENGINE, 'src/**.mm')
}

configuration {'winphone8* or winstore8* or durango'}
files {
    path.join(CROSSENGINE, 'src/**.cx')
}
linkoptions {
    '/ignore:4264' -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
}
premake.vstudio.splashpath = '../../../runtime/images/SplashScreen.png'
