project "Snake"
    location "%{wks.location}"
    language "C++"
    cppdialect (CPPDIALECT)

    TARGET_DIR = WKS_ROOT .. "../bin/" .. TARGET_FORMAT
    targetdir (TARGET_DIR)
    objdir (WKS_ROOT .. "../bin/obj/" .. TARGET_FORMAT .. "/%{prj.name}")

    files { 
        WKS_ROOT .. "Snake/**.hpp", WKS_ROOT .. "Snake/**.cpp",
        WKS_ROOT .. "Utility/**.hpp", WKS_ROOT .. "Utility/**.cpp"
    }

    includedirs
    {
        INCLUDE_PATHS.ROOT,
        INCLUDE_PATHS.SFML
    }

    libdirs
    {
        LIB_PATHS.SFML
    }

    links
    {
        "opengl32",
        "freetype",
        "winmm",
        "gdi32",
        "flac",
        "vorbisenc",
        "vorbisfile",
        "vorbis",
        "ogg",
        "ws2_32",
    }

    defines 
    {
        "SFML_STATIC",
    }


    filter "configurations:Debug"
        kind "ConsoleApp"
        defines { "DEBUG" , "DATA_ROOT=\"" .. WKS_ROOT .. "../data/\""}
        symbols "On"
        runtime "Debug"

        links 
        {
            "sfml-graphics-s-d",
            "sfml-window-s-d",
            "sfml-system-s-d",
            "sfml-audio-s-d",
            "sfml-network-s-d"
        }

    filter "configurations:Release"
        kind "WindowedApp"
        defines { "NDEBUG", "RELEASE", "DATA_ROOT=\"data/\"" }
        optimize "On"
        runtime "Release"
        debugdir ("../../bin/" .. TARGET_FORMAT)

        links
        {
            "sfml-graphics-s",
            "sfml-window-s",
            "sfml-system-s",
            "sfml-audio-s",
            "sfml-network-s",
            "sfml-main"
        }

        postbuildcommands {
            "{DELETE} \"" .. TARGET_DIR .. "/data\"",
            "{COPYDIR} " .. WKS_ROOT .. "../data \"" .. TARGET_DIR .. "/data\""
        }