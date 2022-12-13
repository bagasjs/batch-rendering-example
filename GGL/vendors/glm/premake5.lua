project "Glad"
	kind "StaticLib"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
	objdir "%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}"

	includedirs {
		"%{prj.location}/glm",
	}

	files {
		"%{prj.location}/glm/**.cpp"
	}