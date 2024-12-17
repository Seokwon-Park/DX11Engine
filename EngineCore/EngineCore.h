#pragma once
#include <EngineBase/EngineBase.h>
#include <EnginePlatform/EngineWindow.h>
#include "Level.h"
#include "IContentsCore.h"


// Ό³Έν :
class UEngineCore
{
public:
	// constrcuter destructer
	ENGINE_API UEngineCore();
	ENGINE_API virtual ~UEngineCore() = 0;

	ENGINE_API static void EngineStart(HINSTANCE _Instance, std::string_view _DllName);

	template<typename GameMode, typename MainPawn>
	ENGINE_API static std::shared_ptr<class ULevel> CreateLevel(std::string_view _Name)
	{
		std::shared_ptr<ULevel> NewLevel = std::make_shared<ULevel>();

		NewLevel->SpawnActor<GameMode>();
		NewLevel->SpawnActor<MainPawn>();

		return NewLevel;
	}

	ENGINE_API static void OpenLevel(std::string_view _Name);

protected:

private:
	static UEngineWindow MainWindow;
	static HMODULE ContentsDLL;
	static std::shared_ptr<IContentsCore> Core;

	static void WindowInit(HINSTANCE _Instance);
	static void LoadContents(std::string_view _DllName);

	static void Shutdown();

	static std::map<std::string, std::shared_ptr<class ULevel>> Levels;

	static std::shared_ptr<class ULevel> CurLevel;
	static std::shared_ptr<class ULevel> NextLevel;
};

