#include "EnginePCH.h"
#include "TilemapEditorWindow.h"
#include <EngineBase/EngineIO.h>
#include <EnginePlatform/EngineInputSystem.h>
#include <EngineCore/Level.h>
#include "TitleLogo.h"

#include <EngineCore/EngineCore.h>

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

	// ���߿� ���� ����. ���콺 ��ǥ ��ȯ.
	auto pos = UEngineCore::GetMainWindow().GetMousePos();
	auto size = UEngineCore::GetMainWindow().GetWindowSize();
	// ���콺 Ŀ���� ��ġ�� NDC�� ��ȯ
	// ���콺 Ŀ���� ���� ��� (0, 0), ���� �ϴ�(width-1, height-1)
	// NDC�� ���� �ϴ��� (-1, -1), ���� ���(1, 1)
	float CursorX = pos.X * 2.0f / size.X - 1.0f;
	float CursorY = -pos.Y * 2.0f / size.Y + 1.0f;

	// Ŀ���� ȭ�� ������ ������ ��� ���� ����
	// ���ӿ����� Ŭ������ ���� ���� �ֽ��ϴ�.
	CursorX = FMath::Clamp(CursorX, -1.0f, 1.0f);
	CursorY = FMath::Clamp(CursorY, -1.0f, 1.0f);

	auto Viewmat = Level->GetMainCamera()->GetViewMatrix();
	auto Projmat = Level->GetMainCamera()->GetProjMatrix();

	auto VP = Viewmat * Projmat;
	VP.MatrixInverse();

	FVector4 WorldCoord = VP * FVector4(CursorX, CursorY, 0.0f, 1.0f);

	std::cout << WorldCoord.X << ", " << WorldCoord.Y << '\n';
	///////////////���߿� ���� ������

	ImGui::Begin(GetName().c_str());
	std::vector<const char*> Arr;
	Arr.push_back("Monster");
	Arr.push_back("Monster2");

	ImGui::ListBox("SpawnList", &SelectItem, &Arr[0], 2);

	ImGui::InputInt("TileStartX", &Start.X);
	ImGui::InputInt("TileStartY", &Start.Y);
	ImGui::InputInt("TileMapX", &TileSize.X);
	ImGui::InputInt("TileMapY", &TileSize.Y);

	if (ImGui::Button("Fill Tile"))
	{
		for (int y = Start.Y; y < TileSize.Y; y++)
		{
			for (int x = Start.X; x < TileSize.X; x++)
			{
				TilemapRenderer->SetTile(x, y, 0);
			}
		}
	}

	if (true == UEngineInputSystem::GetKey(EKey::Space))
	{
		//ESpawnList SelectMonster = static_cast<ESpawnList>(SelectItem);
		//std::shared_ptr<class ACameraActor> Camera = Level->GetMainCamera();
		//FVector4 Pos = Camera->ScreenMousePosToWorldPos();
		//Pos.Z = 0.0f;

		//std::shared_ptr<AActor> NewMonster;
		TilemapRenderer->SetTile(FIntPoint( WorldCoord.X, WorldCoord.Y ), 5);
		//Level->SpawnActor<ATitleLogo>("TileTest");

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
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
			//	// ���� ����ȴٴ� �̾߱�
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
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
