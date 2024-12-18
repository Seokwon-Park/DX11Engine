#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE _hInstance,
	_In_opt_ HINSTANCE _hPrevInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	UEngineCore::EngineStart(_hInstance, "TeviContents.dll");

	return 0;
}