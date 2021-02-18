project "Sandbox"

	kind "ConsoleApp"
	language "C++"
	cppdialect "c++2a"
	targetdir "%{wks.location}/bin/bin/%{cfg.name}_%{cfg.architecture}"
	objdir "%{wks.location}/bin/obj/%{cfg.name}_%{cfg.architecture}"

	includedirs
	{
		"%{wks.location}/SFML_MasterX/src",
		"%{Includes.SFML}",
		"%{Includes.spdlog}",
	}

	files
	{
		"src/**.cpp",
		"src/**.hpp"
	}

	links 
	{
		"SFML_MasterX",
		"sfml-graphics.framework",
		"sfml-system.framework",
		"sfml-window.framework",
		"sfml-audio.framework"
	}

	filter "configurations:Debug"
		defines "MASTER_DEBUG"
		symbols "On"
	filter "configurations:Release"
		optimize "On"
