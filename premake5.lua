include "Dependencies.lua"

workspace "CalyxEngine"
	architecture "x64"
    startproject "sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
	}

  outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/GLFW"
	include "vendor/glad"
	include "vendor/imgui"
	include "vendor/box2d"
	include "vendor/msdf-atlas-gen"
group ""

group "Core"
  include "Calyx"
group ""

group "Misc"
  include "Sandbox"
group ""
