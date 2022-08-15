include(FetchContent)

FetchContent_Declare(
	imgui.cmake
  	GIT_REPOSITORY https://github.com/pr0g/imgui.cmake.git
  	GIT_TAG 6cf719bdde34bfbcad7914210875bcf78edd2c1c
)

FetchContent_Declare(
	volk
	GIT_REPOSITORY https://github.com/zeux/volk
	GIT_TAG 1.3.215
)

FetchContent_Declare(
	glslang
	GIT_REPOSITORY https://github.com/KhronosGroup/glslang.git
	GIT_TAG master-tot
)

add_subdirectory(imgui)
add_subdirectory(volk)
add_subdirectory(glslang)
