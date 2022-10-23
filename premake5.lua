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

include "Dough/Vendor/GLFW"
include "Dough/Vendor/GLAD"
include "Dough/Vendor/ImGui"

project "Dough"
    kind "SharedLib"
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
        "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
    }

    filter "system:windows"
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../Build/Sandbox/" .. outputdir)
        }
        defines { "DH_BUILD_DLL" }

os.mkdir("Dough/Source")
os.mkdir("Dough/Include")

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    location "Sandbox"
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

        "Dough/Include",
        "Sandbox/Include" 
    }

    links
    {
        "Dough"
    }

os.mkdir("Sandbox/Source")
os.mkdir("Sandbox/Include")

project "*"

filter "configurations:Debug"
    defines { "DH_DEBUG", "DH_ENABLE_ASSERTS" }
    runtime "Debug"
    symbols "On"

filter "configurations:Release"
    defines { "DH_RELEASE", "DH_ENABLE_ASSERTS" }
    runtime "Release"
    optimize "On"
    symbols "On"

filter "configurations:Dist"
    defines { "DH_DIST" }
    runtime "Release"
    optimize "On"
    symbols "Off"

filter "system:windows"
    cppdialect "C++17"
    systemversion "latest"
    defines { "DH_PLATFORM_WINDOWS" }

filter "platforms:Win64"
    system "Windows"
    architecture "x64"
