#pragma once
#include <EngineBase/EngineBase.h>
#include <EnginePlatform/EngineWindow.h>
#include "Level.h"
#include "IContentsCore.h"


// 설명 :
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
		// 1 유지하고 있겠죠.
		// shared_ptr을 사용하므로 new UEngineLevel()
		std::shared_ptr<ULevel> NewLevel = NewLevelCreate(_Name);
		// std::make_shared
		// new UEngineLevel();

		NewLevel->SpawnActor<GameModeType>();
		NewLevel->SpawnActor<MainPawnType>();

		// 2가 됩니다
		return NewLevel;
	}

	ENGINE_API static std::shared_ptr<ULevel> NewLevelCreate(std::string_view _Name);

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

