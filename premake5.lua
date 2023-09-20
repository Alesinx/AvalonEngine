workspace "Avalon"
	architecture "x64"
	startproject "AvalonEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Avalon/ThirdParty/GLFW/include"
IncludeDir["Glad"] = "Avalon/ThirdParty/Glad/include"
IncludeDir["ImGui"] = "Avalon/ThirdParty/ImGui"
IncludeDir["stb_image"] = "Avalon/ThirdParty/stb_image"
IncludeDir["glm"] = "Avalon/ThirdParty/glm"
IncludeDir["yaml_cpp"] = "Avalon/ThirdParty/yaml_cpp/include"

group "Dependencies"
	include "Avalon/ThirdParty/GLFW"
	include "Avalon/ThirdParty/Glad"
	include "Avalon/ThirdParty/ImGui"
	include "Avalon/ThirdParty/yaml_cpp"
group ""

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
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/ThirdParty/stb_image/**.h",
		"%{prj.name}/ThirdParty/stb_image/**.cpp",
		"%{prj.name}/ThirdParty/glm/glm/**.hpp",
		"%{prj.name}/ThirdParty/glm/glm/**.inl"
	}

	includedirs
	{
		"Avalon/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.yaml_cpp}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml_cpp",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "AVALON_DEBUG"
		runtime "Debug"
		symbols "On"
		optimize "Off"

	filter "configurations:Release"
		defines "AVALON_RELEASE"
		runtime "Release"
		symbols "On"
		optimize "On"

	filter "configurations:Dist"
		defines "AVALON_DIST"
		runtime "Release"
		symbols "Off"
		optimize "On"

project "AvalonEditor" ------------------------------------------------------------------------
	location "AvalonEditor"
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
		"Avalon/Source/",
		"Avalon/ThirdParty/",
		"%{IncludeDir.glm}",
		"%{IncludeDir.yaml_cpp}"
	}

	links
	{
		"Avalon"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "AVALON_DEBUG"
		runtime "Debug"
		symbols "On"
		optimize "Off"

	filter "configurations:Release"
		defines "AVALON_RELEASE"
		runtime "Release"
		symbols "On"
		optimize "On"

	filter "configurations:Dist"
		defines "AVALON_DIST"
		runtime "Release"
		symbols "Off"
		optimize "On"

project "Sandbox2D" ------------------------------------------------------------------------
	location "Sandbox2D"
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
		"Avalon/Source/",
		"Avalon/ThirdParty/",
		"%{IncludeDir.glm}",
		"%{IncludeDir.yaml_cpp}"
	}

	links
	{
		"Avalon"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "AVALON_DEBUG"
		runtime "Debug"
		symbols "On"
		optimize "Off"

	filter "configurations:Release"
		defines "AVALON_RELEASE"
		runtime "Release"
		symbols "On"
		optimize "On"

	filter "configurations:Dist"
		defines "AVALON_DIST"
		runtime "Release"
		symbols "Off"
		optimize "On"
