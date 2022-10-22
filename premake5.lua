workspace "Dough"
    configurations { "Debug", "Release", "Dist" }
    platforms { "Win64" }
    startproject "Sandbox"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Dough"
    kind "SharedLib"
    language "C++"
    location "Dough"
    targetdir ("Build/%{prj.name}/" .. outputDir)
    objdir ("Build/%{prj.name}/Intermediates/" .. outputDir)

    pchheader "dhpch.h"
    pchsource "Dough/Source/dhpch.cpp"

    vpaths {
        ["Include"] = {"Dough/Include/**.h", "Dough/Include/**.hpp"},
        ["Source"] = {"Dough/Source/**.cpp", "Dough/Source/**.c"},
    }

    files { "Dough/Include/**.h", "Dough/Include/**.hpp", "Dough/Source/**.cpp", "Dough/Source/**.c" }

    includedirs 
    { 
        "Dough/Vendor/spdlog/include",

        "Dough/Include"
    }

    filter "system:windows"
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../Build/Sandbox/" .. outputDir)
        }
        defines { "DH_BUILD_DLL" }

os.mkdir("Dough/Source")
os.mkdir("Dough/Include")

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    location "Sandbox"
    targetdir ("Build/%{prj.name}/" .. outputDir)
    objdir ("Build/%{prj.name}/Intermediates/" .. outputDir)

    vpaths {
        ["Headers"] = {"Sandbox/Include/**.h", "Sandbox/Include/**.hpp"},
        ["Source"] = {"Sandbox/Source/**.cpp", "Sandbox/Source/**.c"},
    }

    files { "Sandbox/Include/**.h", "Sandbox/Include/**.hpp", "Sandbox/Source/**.cpp", "Sandbox/Source/**.c" }
    includedirs 
    { 
        "Dough/Vendor/spdlog/include",

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
    defines { "DH_DEBUG" }
    runtime "Debug"
    symbols "On"

filter "configurations:Release"
    defines { "DH_RELEASE" }
    runtime "Release"
    optimize "On"
    symbols "On"

filter "configurations:Dist"
    defines { "DH_DIST" }
    runtime "Release"
    staticruntime "On"
    optimize "On"
    symbols "Off"

filter "system:windows"
    cppdialect "C++17"
    systemversion "latest"
    defines { "DH_PLATFORM_WINDOWS" }

filter "platforms:Win64"
    system "Windows"
    architecture "x64"
