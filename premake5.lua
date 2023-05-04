workspace "Avalon"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Avalon/ThirdParty/GLFW/include"
IncludeDir["Glad"] = "Avalon/ThirdParty/Glad/include"
IncludeDir["ImGui"] = "Avalon/ThirdParty/ImGui"

include "Avalon/ThirdParty/GLFW"
include "Avalon/ThirdParty/Glad"
include "Avalon/ThirdParty/ImGui"

project "Avalon" -------------------------------------------------------------------------
    location "Avalon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "On"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "AvalonPch.h"
    pchsource "Avalon/Source/AvalonPch.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs
    {
        "Avalon/Source",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "AVALON_PLATFORM_WINDOWS",
            "AVALON_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "AVALON_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "AVALON_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "AVALON_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox" ------------------------------------------------------------------------
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
	staticruntime "On"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs
    {
        "Avalon/Source",
    }

    links
    {
        "Avalon"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "AVALON_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AVALON_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "AVALON_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "AVALON_DIST"
        runtime "Release"
        symbols "On"
