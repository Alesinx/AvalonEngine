#include <Avalon.h>

#include <iostream>

class Sandbox : public Avalon::Application
{
public:
	Sandbox() { }
	~Sandbox() { }
};

Avalon::Application* Avalon::CreateApplication()
{
	int n = 42;
	AVALON_LOG_INFO("Example info log.");
	AVALON_LOG_TRACE("Example trace log with a paramter: {}", n);
	AVALON_LOG_WARNING("Example warning log with a parameter: {}", n);
	AVALON_LOG_ERROR("Example error log with a parameter: {}", n);

	return new Sandbox();
}