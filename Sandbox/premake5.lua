include "../Dependencies.lua"

project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"%{wks.location}/resources/icon.rc",
	}

	includedirs
	{
		"src",
		"%{wks.location}/Calyx/src",
		"%{wks.location}/vendor/spdlog/include",
		"%{wks.location}/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.json}",
		"%{IncludeDir.box2d}"
	}

	links
	{
		"Calyx"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CALYX_PLATFORM_WINDOWS",
			"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING"
		}

	filter "configurations:Debug"
		defines "CALYX_DEBUG"
		runtime "Debug"
		symbols "on"

		postbuildcommands 
		{
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/Debug/GameNetworkingSockets.dll" "%{cfg.targetdir}"',
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/Debug/libcrypto-3-x64.dll" "%{cfg.targetdir}"',
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/Debug/libprotobufd.dll" "%{cfg.targetdir}"',
		}

	filter "configurations:Release"
		defines "CALYX_RELEASE"
		runtime "Release"
		optimize "on"

		postbuildcommands 
		{
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/RelWithDebInfo/GameNetworkingSockets.dll" "%{cfg.targetdir}"',
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/RelWithDebInfo/libcrypto-3-x64.dll" "%{cfg.targetdir}"',
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/RelWithDebInfo/libprotobuf.dll" "%{cfg.targetdir}"',
		}

	filter "configurations:Distribution"
		defines "CALYX_DISTRIBUTION"
		runtime "Release"
		optimize "on"
		kind "WindowedApp"

		postbuildcommands 
		{
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/Release/GameNetworkingSockets.dll" "%{cfg.targetdir}"',
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/Release/libcrypto-3-x64.dll" "%{cfg.targetdir}"',
		  '{COPY} "%{wks.location}/vendor/GameNetworkingSockets/bin/Windows/Release/libprotobuf.dll" "%{cfg.targetdir}"',
		}
	
	filter {"configurations:Distribution", "system:windows"}
		entrypoint "WinMainCRTStartup"
