#include <Calyx.h>
#include <Calyx/Core/EntryPoint.h>

class Sandbox : public Calyx::Application
{
public:
	Sandbox(Calyx::ApplicationSpecification& spec) 
		: Calyx::Application(spec)
	{
	}
};

Calyx::Application* Calyx::CreateApplication(Calyx::ApplicationCommandLineArgs args)
{
	Calyx::ApplicationSpecification spec;
	spec.Name = "Calyx: Sandbox App";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}
