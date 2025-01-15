#include "EnginePCH.h"
#include "TilemapEditorWindow.h"

#include <EngineBase/EngineIO.h>
#include <EnginePlatform/EngineInputSystem.h>
#include <EngineCore/Level.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/Resources/EngineSprite.h>


UTilemapEditorWindow::UTilemapEditorWindow(ULevel* _Level)
	:Level(_Level)
{
	SetName("TileMapEditor");
	PreviewTile = std::make_shared<URenderUnit>();
	PreviewTile->Init("Quad", "Tilemap");
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

	std::shared_ptr<UEngineSprite> Sprite = UResourceManager::Find<UEngineSprite>();
	std::vector<FSpriteData> SpriteData = Sprite->GetSpriteData();

	FTileData EditorSetting;

	for (size_t i = 0; i < Sprite->GetSpriteCount(); i++)
	{
		FSpriteData SpriteData = Sprite->GetSpriteByIndex(i);

		//SRV입니다
		ImTextureID SRV = reinterpret_cast<ImTextureID>(SpriteData.Texture->GetSRV());

		std::string Text = std::to_string(i);

		if (i != 0)
		{
			if (0 != (i % 10))
			{
				ImGui::SameLine();
			}
		}

		FSpriteRect Data = SpriteData.Rect;
		ImVec2 Pos = { Data.CuttingPos.X, Data.CuttingPos.Y };
		ImVec2 Size = { Data.CuttingPos.X + Data.CuttingSize.X, Data.CuttingPos.Y + Data.CuttingSize.Y };

		if (ImGui::ImageButton(Text.c_str(), SRV, { 30, 30 }, Pos, Size))
		{
			SelectItem = i;
		}
		// 엔터를 치지 않는개념.
	}

	//ImGui::ListBox("SpawnList", &SelectItem, &Arr[0], 2);

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
				TilemapComponent->SetTile(x, y, SelectItem);
			}
		}
	}

	FIntPoint WorldCoord = Level->GetCurrentCamera()->GetWorldMousePos();

	UCameraComponent* _Camera = Level->GetCurrentCamera()->GetCameraComponent().get();

	//if (TilemapComponent->GetTile(WorldCoord) == nullptr)
	{
		auto Index = TilemapComponent->WorldPosToTileIndex(WorldCoord);
		//Index.X *= TilemapComponent->ImageSize.X;
		//Index.Y *= TilemapComponent->ImageSize.X;
		Index.X *= 28;
		Index.Y *= 28;
		Index.X += 14;
		Index.Y += 14;

		FSpriteData SpriteData = Sprite->GetSpriteByIndex(SelectItem);
		//SpriteData.Rect.Pivot = { 0.0f, 0.0f };

		VertexConstant VC;
		FTransform Trans;
		VC.View = _Camera->GetViewMatrix();
		VC.View.MatrixTranspose();
		VC.Proj = _Camera->GetProjectionMatrix();
		VC.Proj.MatrixTranspose();

		PreviewTile->SetTexture("TilemapTexture", EShaderType::PS, SpriteData.Texture);
		PreviewTile->SetSampler("PSSampler", EShaderType::PS, UResourceManager::Find<UEngineSamplerState>("Default"));

		Trans.Location = FVector4(Index.X, Index.Y, 1.0f, 1.0f);
		if (true == IsFlip)
		{
			Trans.Rotation = FVector4(0.0f, 180.0f, 0.0f, 1.0f);
		}
		Trans.Rotation += FVector4(0.0f, 0.0f, 90.0f * Rotate, 1.0f);
		Trans.Scale = FVector4({ 28.0f, 28.0f, 1.0f });

		Trans.UpdateTransform();
		Trans.WorldMatrix.MatrixTranspose();
		VC.World = Trans.WorldMatrix;


		PreviewTile->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
		PreviewTile->SetConstantBufferData("SpriteData", EShaderType::VS, SpriteData.Rect);
		PreviewTile->SetConstantBufferData("PSColor", EShaderType::PS, FColor(1.0f, 1.0f, 1.0f, 0.5f));

		PreviewTile->Render(_Camera, 0.0f);
	}

	if (true == UEngineInputSystem::GetKey(EKey::Space))
	{
		//ESpawnList SelectMonster = static_cast<ESpawnList>(SelectItem);
		//std::shared_ptr<class ACameraActor> Camera = Level->GetMainCamera();
		//FVector4 Pos = Camera->ScreenMousePosToWorldPos();
		//Pos.Z = 0.0f;

		//std::shared_ptr<AActor> NewMonster;
		TilemapComponent->SetTile(FIntPoint(WorldCoord.X, WorldCoord.Y), SelectItem);
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

	if (true == UEngineInputSystem::GetKey(EKey::D))
	{
		TilemapComponent->RemoveTile(FIntPoint(WorldCoord.X, WorldCoord.Y));
	}
	if (true == UEngineInputSystem::GetKeyDown(EKey::R))
	{
		Rotate = (Rotate + 1) % 4;
	}

	if (true == UEngineInputSystem::GetKeyDown(EKey::F))
	{
		IsFlip = !IsFlip;
	}



	if (true == ImGui::Button("Save"))
	{
		//파일 입출력 기능으로 래핑
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
		ofn.lpstrDefExt = "Tmap";
		ofn.lpstrInitialDir = InitPath.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetSaveFileNameA(&ofn) == TRUE)
		{
			std::string FileName = ofn.lpstrFile;
			TilemapComponent->SaveTilemap(Dir, FileName);
		}
	}

	if (true == ImGui::Button("Load"))
	{
		//파일 입출력 기능으로 래핑
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
		ofn.lpstrFilter = ("All\0*.*\0Text\0*.Tmap\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = InitPath.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{

		}
	}
	ImGui::End();
}
