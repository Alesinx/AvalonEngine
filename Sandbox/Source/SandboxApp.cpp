#include <Avalon.h>

class Sandbox : public Avalon::Application
{
public:
	Sandbox() { }
	~Sandbox() { }
};

Avalon::Application* Avalon::CreateApplication()
{
	return new Sandbox();
}