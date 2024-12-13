#include <EngineCore/Core.h>

class TeviApp : public Application
{
public:
	TeviApp()
		:Application("Tevi")

	{
	}

	~TeviApp()
	{

	}
};

Application* CreateApplication()
{
	return new TeviApp();
}