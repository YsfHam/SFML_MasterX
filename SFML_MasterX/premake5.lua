project "SFML_MasterX"

	kind "StaticLib"
	language "C++"
	cppdialect "c++2a"
	targetdir "%{wks.location}/bin/bin/%{cfg.name}_%{cfg.architecture}"
	objdir "%{wks.location}/bin/obj/%{cfg.name}_%{cfg.architecture}"

	files
	{
		"src/**.cpp",
		"src/**.hpp"

	}
	
	includedirs
	{
		"%{Includes.SFML}",
		"%{Includes.spdlog}",
		"src"
	}
	
	pchheader "PCH/sfmxpch.hpp"
	
	--[plateform dependece configurations]--
	filter "action:vs*"
		pchsource "PCH/sfmxpch.cpp"
		defines "MASTER_VS_COMPILER"

	filter "action:gmake*"
		removefiles "src/PCH/sfmxpch.cpp"

	filter "system:macosx"
		links
		{
			"sfml-graphics.framework",
			"sfml-system.framework",
			"sfml-window.framework",
			"sfml-audio.framework"
		}

		defines "MASTER_MACOSX"

	filter "system:windows"
		defines "MASTER_WINDOWS"

	filter "system:linux"
		defines "MASTER_LINUX"


	filter "configurations:Debug"
		symbols "On"
		defines "MASTER_DEBUG"
		
	filter "configurations:Release"
		optimize "On"