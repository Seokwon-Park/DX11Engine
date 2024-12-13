#include <EngineCore/Core.h>

class EngineEditor : public Application
{
public:
	EngineEditor()
	{
	}

	~EngineEditor()
	{

	}
};

Application* CreateApplication()
{
	return new EngineEditor();
}