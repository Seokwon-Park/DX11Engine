#pragma once
#include <EngineBase/EngineBase.h>
#include <EngineBase/EngineTimer.h>	
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInputSystem.h>
#include "Level.h"
#include "IContentsCore.h"
#include "EngineDeviceContext.h"

enum class ERendererAPI
{
	DirectX11,
	None
};

// Ό³Έν :
class UEngineCore
{
public:

	// constrcuter destructer
	ENGINE_API UEngineCore();
	ENGINE_API virtual ~UEngineCore() = 0;

	ENGINE_API static void EngineStart(HINSTANCE _Instance, std::string_view _DllName);
	

	template<typename GameModeType, typename MainPawnType>
	static class std::shared_ptr<class ULevel> CreateLevel(std::string_view _Name)
	{
		std::shared_ptr<ULevel> NewLevel = std::make_shared<ULevel>();

		NewLevel->Create<GameModeType, MainPawnType>();
		//NewLevel->SpawnActor<GameModeType>();
		//NewLevel->SpawnActor<MainPawnType>();

		AddLevel(_Name, NewLevel);

		return NewLevel;
	}

	ENGINE_API static void AddLevel(std::string_view _Name, std::shared_ptr<ULevel> _Level);

	ENGINE_API static void OpenLevel(std::string_view _Name);

	//ENGINE_API inline static float GetDeltaTime() { return Timer.GetDeltaTime(); }

	ENGINE_API inline static void SetRendererAPI(ERendererAPI _API) { RendererAPI = _API; }
	ENGINE_API inline static ERendererAPI GetRendererAPI() { return RendererAPI; }
	ENGINE_API static UEngineDeviceContext* GraphicsDevice;

protected:

private:
	inline static ERendererAPI RendererAPI;

	static UEngineWindow MainWindow;
	static HMODULE ContentsDLL;
	static std::shared_ptr<IContentsCore> Core;

	static UEngineTimer Timer;

	static void WindowInit(HINSTANCE _Instance);
	static void LoadContentsDll(std::string_view _DllName);

	static void EngineUpdate();
	static void CheckLevelChange();
	static void EngineShutdown();

	static inline std::map<std::string, std::shared_ptr<ULevel>> Levels;

	static std::shared_ptr<class ULevel> CurLevel;
	static std::shared_ptr<class ULevel> NextLevel;
};

