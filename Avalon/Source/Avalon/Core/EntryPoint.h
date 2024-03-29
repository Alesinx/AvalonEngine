#pragma once

#ifdef AVALON_PLATFORM_WINDOWS

#include "Avalon/Core/Application.h"

extern Avalon::Application* Avalon::CreateApplication();

int main(int argc, char** argv)
{

	Avalon::Application* app = Avalon::CreateApplication();
	app->Run();
	delete app;
}

#endif
