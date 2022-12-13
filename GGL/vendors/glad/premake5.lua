PROJECT_VENDORS = "%{wks.location}/vendors"

project "Glad"
	kind "StaticLib"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
	objdir "%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}"

	includedirs {
		"%{prj.location}/include/glad",
		"%{prj.location}/include/KHR",
		"%{prj.location}/include",
	}

	files {
		"%{prj.location}/src/glad.c"
	}

	libdirs {

	}
	
	links {
		"opengl32",
		"gdi32",
		"user32",
		"kernel32",
		"mingw32",
		"dwmapi"
	}