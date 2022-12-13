project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
	objdir "%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}"
	files {
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.h",
	}

	includedirs {
		"%{prj.location}/src",
		"%{wks.location}/GGL/src",
		"%{wks.location}/GGL/vendors/glfw/include",
		"%{wks.location}/GGL/vendors/glfw/include/GLFW",
		"%{wks.location}/GGL/vendors/glad/include",
		"%{wks.location}/GGL/vendors/glad/include/glad",
		"%{wks.location}/GGL/vendors/glad/include/KHR",
		"%{wks.location}/GGL/vendors/glm/src",
	}

	links {
		"opengl32",
		"gdi32",
		"GGL"
	}