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

    vpaths {
        ["Include"] = {"Dough/**.h", "Dough/**.hpp"},
        ["Source"] = {"Dough/**.cpp", "Dough/**.c"},
    }

    files { "Dough/**.h", "Dough/**.hpp", "Dough/**.cpp", "Dough/**.c" }

    includedirs 
    { 
        "Dough/Vendor/spdlog/include",

        "Dough/Include"
    }

    filter "system:windows"
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/Sandbox/" .. outputDir)
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
        ["Headers"] = {"Sandbox/**.h", "Sandbox/**.hpp"},
        ["Source"] = {"Sandbox/**.cpp", "Sandbox/**.c"},
    }

    files { "Sandbox/**.h", "Sandbox/**.hpp", "Sandbox/**.cpp", "Sandbox/**.c" }
    includedirs 
    { 
        "Dough/Vendor/spdlog/include",

        "Dough/Include",
        "Sandbox/Include" 
    }

    links
    {
        "Hazel"
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
