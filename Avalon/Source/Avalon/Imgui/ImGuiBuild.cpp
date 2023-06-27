#include "AvalonPch.h"

// These files need to be compiled in order to bind inputs to Imgui. To achieve that they should be
// included files in premake, but doing that makes the compile complain of them not including AvalonPch.
// This is an ugly workaround for now.

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "backends/imgui_impl_opengl3.cpp"
#include "backends/imgui_impl_glfw.cpp"
