#pragma once
#include <EngineBase/EngineBase.h>
#include <EngineBase/EngineTimer.h>	
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInputSystem.h>
#include "Level.h"
#include "TimerManager.h"
#include "IContentsCore.h"


// 설명 :
class UEngineCore
{
	friend class UDevTestWindow;
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

	template<typename GameModeType, typename MainPawnType>
	void ResetLevel(std::string_view _LevelName)
	{
		//std::string UpperName = UEngineString::ToUpper(_LevelName);

		// 지금 당장 이녀석을 지우면 안된다.
		//if (CurLevel->GetName() != UpperName)
		//{
		//	DestroyLevel(UpperName);
		//}
		//else
		//{
		//	Levels.erase(UpperName);
		//}
		//NextLevel = CreateLevel<GameModeType, MainPawnType>(UpperName);
	}

	void DestroyLevel(std::string_view _LevelName)
	{
		//std::string UpperName = UEngineString::ToUpper(_LevelName);

		//if (false == Levels.contains(UpperName))
		//{
		//	// MSGASSERT("존재하지 않는 레벨을 리셋할수 없습니다." + UpperName);
		//	return;
		//}

		//Levels.erase(UpperName);
	}


	ENGINE_API static void AddLevel(std::string_view _Name, std::shared_ptr<ULevel> _Level);

	ENGINE_API static void OpenLevel(std::string_view _Name);

	//ENGINE_API inline static float GetDeltaTime() { return Timer.GetDeltaTime(); }
	ENGINE_API static class UEngineDeviceContext* GetGraphicsDeviceContext();
	ENGINE_API static class FTimerManager& GetTimerManager();
	ENGINE_API static class UEngineWindow& GetMainWindow() { return MainWindow; };
	ENGINE_API static float GetEngineDeltaTime() { return Timer.GetDeltaTime(); }
protected:

private:
	static UEngineInitData Data;
	static class UEngineDeviceContext* GraphicsDeviceContext;

	static UEngineWindow MainWindow;
	static HMODULE ContentsDLL;
	static std::shared_ptr<IContentsCore> ContentsCore;

	static UEngineTimer Timer;
	static FTimerManager TimerManager;

	static void WindowInit(HINSTANCE _Instance);
	static void LoadContentsDll(std::string_view _DllName);

	static void EngineUpdate();
	static void CheckLevelChange();
	static void EngineShutdown();

	static inline std::map<std::string, std::shared_ptr<ULevel>> Levels;

	static std::shared_ptr<class ULevel> CurLevel;
	static std::shared_ptr<class ULevel> NextLevel;
};

