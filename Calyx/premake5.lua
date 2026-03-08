include "../Dependencies.lua"

project "Calyx"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	pchheader "cxpch.h"
	pchsource "src/cxpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"%{wks.location}/vendor/stb/**.h",
		"%{wks.location}/vendor/stb/**.cpp",
		"%{wks.location}/vendor/json/**.hpp",
		"%{wks.location}/vendor/Crc32/**.h",
		"%{wks.location}/vendor/Crc32/**.cpp"
	}

	includedirs
	{
		"src",
		"%{wks.location}/vendor/spdlog/include",
		"%{wks.location}/vendor/Crc32",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.msdfgen}",
		"%{IncludeDir.msdf_atlas_gen}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.json}",
		"%{IncludeDir.box2d}",
		"%{IncludeDir.GameNetworkingSockets}"
	}

	links
	{
		"glad",
		"GLFW",
		"ImGui",
		"opengl32.lib",
		"msdf-atlas-gen",
		"box2d"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CALYX_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
  

	filter "configurations:Debug"
		defines "CALYX_DEBUG"
		symbols "on"

		links
		{
			"%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/Debug/GameNetworkingSockets.lib"
		}

	filter "configurations:Release"
		defines "CALYX_RELEASE"
		optimize "on"

		links
		{
			"%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/RelWithDebInfo/GameNetworkingSockets.lib"
		}

	filter "configurations:Distribution"
		defines "CALYX_DISTRIBUTION"
		runtime "Release"
		optimize "on"

		links
		{
			"%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/Release/GameNetworkingSockets.lib"
		}

		removeincludedirs { "%{IncludeDir.ImGui}" }