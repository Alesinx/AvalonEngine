#pragma once

#ifdef AVALON_PLATFORM_WINDOWS

#include "Avalon/Application.h"

extern Avalon::Application* Avalon::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Avalon::CreateApplication();
	app->Run();
	delete app;
}

#endif