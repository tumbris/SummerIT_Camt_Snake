workspace "Summet IT Snake"
    location "code/generated"
    configurations {"Debug", "Release"}
    architecture "x64"
    platforms {"Win64"}
    startproject "Snake"

    flags { "MultiProcessorCompile" , "FatalWarnings", "NoPCH"}

    CPPDIALECT = "C++20"

    WKS_ROOT = "%{wks.location}/../"

    TARGET_FORMAT = "%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}";

    INCLUDE_PATHS = 
    {
        SFML = WKS_ROOT .. "../dependencies/SFML/include",
        ROOT = WKS_ROOT,
    }

    LIB_PATHS = 
    {
        SFML = WKS_ROOT .. "../dependencies/SFML/lib",
    }

    filter "action:vs*"
        buildoptions {"/Zc:__cplusplus"}

    filter "system:windows"
        systemversion "latest"

    include "code/Snake"
