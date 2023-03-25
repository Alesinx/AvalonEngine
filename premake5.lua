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

-- group "Dependencies"
--     include "Avalon/thirdParty/GLFW"
--     include "Avalon/thirdParty/Glad"
--     include "Avalon/thirdParty/ImGui"

project "Avalon" ----------------------------------------------------------------------
    location "Avalon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "AvalonPch.h"
    pchsource "Avalon/Source/AvalonPch.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        -- "%{prj.name}/thirdParty/glm/glm/**.hpp",
        -- "%{prj.name}/thirdParty/glm/glm/**.inl"
    }

    includedirs
    {
        "Avalon/Source"
        -- "%{prj.name}/thirdParty/spdlog/include",
        -- "%{prj.name}/thirdParty/GLFW/include",
        -- "%{prj.name}/thirdParty/Glad/include",
        -- "%{prj.name}/thirdParty/ImGui",
        -- "%{prj.name}/thirdParty/glm"
    }

    -- links
    -- {
    --     "GLFW",
    --     "Glad",
    --     "ImGui",
    --     "opengl32.lib"
    -- }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "AVALON_PLATFORM_WINDOWS",
            "AVALON_BUILD_DLL"
            -- "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "AVALON_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AVALON_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AVALON_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox" ------------------------------------------------------------------------
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
	staticruntime "on"

    targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs
    {
        "Avalon/Source",
        "Avalon/thirdParty/spdlog/include",
        "Avalon/thirdParty/glm",
        "Avalon/thirdParty/ImGui"
    }

    links
    {
        "Avalon"
        -- "ImGui"
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
        symbols "on"

    filter "configurations:Release"
        defines "AVALON_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AVALON_DIST"
        runtime "Release"
        symbols "on"
