#include "EnginePCH.h"
#include "TilemapEditorWindow.h"
#include <EngineBase/EngineIO.h>
#include <EnginePlatform/EngineInputSystem.h>
#include <EngineCore/Level.h>
#include "TitleLogo.h"

UTilemapEditorWindow::UTilemapEditorWindow(ULevel* _Level)
	:Level(_Level)
{
	SetName("TileMapEditor");
}

UTilemapEditorWindow::~UTilemapEditorWindow()
{
}

void UTilemapEditorWindow::OnImGuiRender()
{
	ImGui::Begin(GetName().c_str());
	std::vector<const char*> Arr;
	Arr.push_back("Monster");
	Arr.push_back("Monster2");

	ImGui::ListBox("SpawnList", &SelectItem, &Arr[0], 2);

	if (true == UEngineInputSystem::GetKeyDown(EKey::MouseLeft) && true == UEngineInputSystem::GetKeyDown(EKey::LControl))
	{
		//ESpawnList SelectMonster = static_cast<ESpawnList>(SelectItem);
		//std::shared_ptr<class ACameraActor> Camera = Level->GetMainCamera();
		//FVector4 Pos = Camera->ScreenMousePosToWorldPos();
		//Pos.Z = 0.0f;

		//std::shared_ptr<AActor> NewMonster;

		Level->SpawnActor<ATitleLogo>("TileTest");

		//switch (SelectMonster)
		//{
		//case ESpawnList::Monster:
		//	NewMonster = GetWorld()->SpawnActor<AMonster>();
			//break;
		//case ESpawnList::Monster2:
		//	NewMonster = GetWorld()->SpawnActor<AMonster2>();
			//break;
		//default:
			//break;
		//}

		//NewMonster->SetActorLocation(Pos);
	}


	if (true == ImGui::Button("Save"))
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.AppendDirectory("TilemapData");
		std::string InitPath = Dir.ToString();

		OPENFILENAME ofn;       // common dialog box structure
		char szFile[260] = { 0 };       // if using TCHAR macros
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = ("All\0*.*\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrDefExt = "MapData";
		ofn.lpstrInitialDir = InitPath.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetSaveFileNameA(&ofn) == TRUE)
		{
			UEngineSerializer Ser;

			Ser << 1;

			//for (std::shared_ptr<AMon> Actor : AllMonsterList)
			//{

			//	Ser << static_cast<int>(Actor->MonsterTypeValue);
			//	// 여기 저장된다는 이야기
			//	Actor->Serialize(Ser);
			//}

			UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);

			NewFile.FileOpen("wb");
			NewFile.Write(Ser);
		}
	}

	if (true == ImGui::Button("Load"))
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.AppendDirectory("Data");
		std::string InitPath = Dir.ToString();

		OPENFILENAME ofn;       // common dialog box structure
		char szFile[260] = { 0 };       // if using TCHAR macros
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = ("All\0*.*\0Text\0*.MapData\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = InitPath.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);
			UEngineSerializer Ser;

			NewFile.FileOpen("rb");
			NewFile.Read(Ser);


			int MonsterCount = 0;

			Ser >> MonsterCount;

			std::cout << MonsterCount;
			/*for (size_t i = 0; i < MonsterCount; i++)
			{

			}*/

		}
	}
	ImGui::End();
}
