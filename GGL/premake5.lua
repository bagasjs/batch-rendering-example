project "GGL"
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
	objdir "%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}"
	files {
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.h",
		"%{prj.location}/vendors/glad/src/glad.c",
		"%{prj.location}/vendors/glad/src/glad.c",
		"%{prj.location}/vendors/glfw/include/GLFW/glfw3.h",
		"%{prj.location}/vendors/glfw/include/GLFW/glfw3native.h",
		"%{prj.location}/vendors/glfw/src/glfw_config.h",
		"%{prj.location}/vendors/glfw/src/context.c",
		"%{prj.location}/vendors/glfw/src/init.c",
		"%{prj.location}/vendors/glfw/src/input.c",
		"%{prj.location}/vendors/glfw/src/monitor.c",
		"%{prj.location}/vendors/glfw/src/null_init.c",
		"%{prj.location}/vendors/glfw/src/null_joystick.c",
		"%{prj.location}/vendors/glfw/src/null_monitor.c",
		"%{prj.location}/vendors/glfw/src/null_window.c",
		"%{prj.location}/vendors/glfw/src/platform.c",
		"%{prj.location}/vendors/glfw/src/vulkan.c",
		"%{prj.location}/vendors/glfw/src/window.c",
		"%{prj.location}/vendors/stb/src/stb_image.cpp",
	}

	includedirs {
		"%{prj.location}/src",
		"%{prj.location}/src/GGL",
		"%{prj.location}/vendors/glfw/include",
		"%{prj.location}/vendors/glfw/include/GLFW",
		"%{prj.location}/vendors/glad/include",
		"%{prj.location}/vendors/glad/include/glad",
		"%{prj.location}/vendors/glad/include/KHR",
		"%{prj.location}/vendors/glm/src",
		"%{prj.location}/vendors/glm/src/glm",
		"%{prj.location}/vendors/stb/src",
	}

	links {
		"opengl32"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files {
			"%{prj.location}/vendors/glfw/src/x11_init.c",
			"%{prj.location}/vendors/glfw/src/x11_monitor.c",
			"%{prj.location}/vendors/glfw/src/x11_window.c",
			"%{prj.location}/vendors/glfw/src/xkb_unicode.c",
			"%{prj.location}/vendors/glfw/src/posix_time.c",
			"%{prj.location}/vendors/glfw/src/posix_thread.c",
			"%{prj.location}/vendors/glfw/src/glx_context.c",
			"%{prj.location}/vendors/glfw/src/egl_context.c",
			"%{prj.location}/vendors/glfw/src/osmesa_context.c",
			"%{prj.location}/vendors/glfw/src/linux_joystick.c"
		}

		defines {
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"

		files {
			"%{prj.location}/vendors/glfw/src/win32_init.c",
			"%{prj.location}/vendors/glfw/src/win32_joystick.c",
			"%{prj.location}/vendors/glfw/src/win32_module.c",
			"%{prj.location}/vendors/glfw/src/win32_monitor.c",
			"%{prj.location}/vendors/glfw/src/win32_time.c",
			"%{prj.location}/vendors/glfw/src/win32_thread.c",
			"%{prj.location}/vendors/glfw/src/win32_window.c",
			"%{prj.location}/vendors/glfw/src/wgl_context.c",
			"%{prj.location}/vendors/glfw/src/egl_context.c",
			"%{prj.location}/vendors/glfw/src/osmesa_context.c"
		}

		defines { 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

		links
		{
			"Dwmapi"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		optimize "off"