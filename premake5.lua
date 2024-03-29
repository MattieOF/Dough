workspace "Dough"
	configurations { "Debug", "Release", "Dist" }
	platforms { "Win64" }
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "Dough/Vendor/spdlog/include"
IncludeDir["GLFW"] = "Dough/Vendor/GLFW/include"
IncludeDir["PPK_ASSERT"] = "Dough/Vendor/PPK_ASSERT"
IncludeDir["GLAD"] = "Dough/Vendor/GLAD/include"
IncludeDir["ImGui"] = "Dough/Vendor/ImGui/"
IncludeDir["glm"] = "Dough/Vendor/glm/"

group "Vendor"
	include "Dough/Vendor/GLFW"
	include "Dough/Vendor/GLAD"
	include "Dough/Vendor/ImGui"
group ""

project "Dough"
	kind "StaticLib"
	staticruntime "On"
	language "C++"
	location "Dough"
	targetdir ("Build/%{prj.name}/" .. outputdir)
	objdir ("Build/%{prj.name}/Intermediates/" .. outputdir)

	pchheader "dhpch.h"
	pchsource "Dough/Source/dhpch.cpp"

	vpaths {
		["Include"] = {"Dough/Include/**.h", "Dough/Include/**.hpp"},
		["Source"] = {"Dough/Source/**.cpp", "Dough/Source/**.c"},
	}

	files { 
		"Dough/Include/**.h", "Dough/Include/**.hpp", 
		"Dough/Source/**.cpp", "Dough/Source/**.c",
		"Dough/Vendor/PPK_ASSERT/ppk_assert.cpp"
	}

	includedirs 
	{ 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.PPK_ASSERT}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",

		"Dough/Include"
	}

	links 
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	defines { 
		"PPK_ASSERT_DISABLE_IGNORE_LINE", 
		"GLFW_INCLUDE_NONE",
		"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
		"_CRT_SECURE_NO_WARNINGS"
	}

os.mkdir("Dough/Source")
os.mkdir("Dough/Include")

project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	location "Sandbox"
	staticruntime "On"
	targetdir ("Build/%{prj.name}/" .. outputdir)
	objdir ("Build/%{prj.name}/Intermediates/" .. outputdir)

	vpaths {
		["Headers"] = {"Sandbox/Include/**.h", "Sandbox/Include/**.hpp"},
		["Source"] = {"Sandbox/Source/**.cpp", "Sandbox/Source/**.c"},
	}

	files { "Sandbox/Include/**.h", "Sandbox/Include/**.hpp", "Sandbox/Source/**.cpp", "Sandbox/Source/**.c" }
	includedirs 
	{ 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.PPK_ASSERT}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",

		"Dough/Include",
		"Sandbox/Include" 
	}

	links
	{
		"Dough"
	}

	filter "configurations:Dist"
		kind "WindowedApp"

os.mkdir("Sandbox/Source")
os.mkdir("Sandbox/Include")

project "*"

filter "configurations:Debug"
	defines { "DH_DEBUG", "DH_ENABLE_ASSERTS" }
	symbols "On"
	runtime "Debug"

filter "configurations:Release"
	defines { "DH_RELEASE", "DH_ENABLE_ASSERTS" }
	optimize "On"
	symbols "On"
	runtime "Release"

filter "configurations:Dist"
	defines { "DH_DIST" }
	optimize "On"
	symbols "Off"
	runtime "Release"

filter "system:windows"
	cppdialect "C++17"
	systemversion "latest"
	defines { "DH_PLATFORM_WINDOWS" }

filter "platforms:Win64"
	system "Windows"
	architecture "x64"
