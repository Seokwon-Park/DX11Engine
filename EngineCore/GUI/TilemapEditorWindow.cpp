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
	SetName("TilemapEditor");
	PreviewTile = std::make_shared<URenderUnit>();
	PreviewTile->Init("Quad", "Tilemap");
	PreviewTile->SetSampler("PSSampler", EShaderType::PS, UResourceManager::Find<UEngineSamplerState>("Default"));
}

UTilemapEditorWindow::~UTilemapEditorWindow()
{
}

bool VectorOfStringGetter(void* data, int n, const char** out_text)
{
	const std::vector<std::string>* v = (std::vector<std::string>*)data;
	*out_text = v->at(n).c_str();
	return true;
}

void UTilemapEditorWindow::OnImGuiRender()
{
	ImGui::Begin(GetName().c_str());

	auto Sprites = UResourceManager::GetAllResources<UEngineSprite>();
	

	std::vector<std::string> Temp;
	for (auto S : Sprites)
	{
		Temp.push_back(S->GetName());
	}

	std::vector<const char*> SpriteNames;
	for (auto& Str : Temp)
	{
		SpriteNames.push_back(Str.c_str());
		//SpriteNames.push_back(c);
	}

	// ListBox 생성
	ImGui::ListBox("SpawnList", &SelectSprite, SpriteNames.data(), (int)SpriteNames.size());

	ImGui::Text("Current Selection: %d", SelectSprite);

	std::shared_ptr<UEngineSprite> Sprite = UResourceManager::Find<UEngineSprite>(Temp[SelectSprite]);
	std::vector<FSpriteData> SpriteData = Sprite->GetSpriteData();

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
			EditorSetting.SpriteRect = Data;
			EditorSetting.SpriteIndex = SelectItem;

		}
		// 엔터를 치지 않는개념.
	}

	EditorSetting.IsBlock = false;

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
				TilemapComponent->SetTile(x, y, EditorSetting);
			}
		}
	}

	ImGui::Checkbox("Flip Tile", &IsFlip);

	FIntPoint WorldCoord = Level->GetCurrentCamera()->GetWorldMousePos();

	UCameraComponent* _Camera = Level->GetCurrentCamera()->GetCameraComponent().get();

	//if (TilemapComponent->GetTile(WorldCoord) == nullptr)
	{
		FTileIndex Index = TilemapComponent->WorldPosToTileIndex(WorldCoord);
		FVector4 RenderPos = TilemapComponent->TileIndexToWorldPos(Index);

		FSpriteData SpriteData = Sprite->GetSpriteByIndex(SelectItem);
		//SpriteData.Rect.Pivot = { 0.0f, 0.0f };

		VertexConstant VC;
		FTransform Trans;
		VC.View = _Camera->GetViewMatrixTranspose();
		VC.Proj = _Camera->GetProjectionMatrixTranspose();


		Trans.Location = FVector4(RenderPos.X, RenderPos.Y, 1.0f, 1.0f);
		if (true == IsFlip)
		{
			Trans.Rotation = FVector4(0.0f, 180.0f, 0.0f, 1.0f);
		}
		Trans.Rotation += FVector4(0.0f, 0.0f, 90.0f * Rotate, 1.0f);
		Trans.Scale = FVector4({ SpriteData.Texture->GetTextureSize().X, SpriteData.Texture->GetTextureSize().Y,1.0f});

		Trans.UpdateTransform();
		Trans.WorldMatrix.MatrixTranspose();
		VC.World = Trans.WorldMatrix;

		PreviewTile->SetTexture("TilemapTexture", EShaderType::PS, SpriteData.Texture);
		PreviewTile->SetConstantBufferData("PSColor", EShaderType::PS, FColor(1.0f, 1.0f, 1.0f, 0.5f));
		PreviewTile->SetConstantBufferData("SpriteData", EShaderType::VS, SpriteData.Rect);
		PreviewTile->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);

		PreviewTile->Render(_Camera, 0.0f);
	}

	if (true == UEngineInputSystem::GetKey(EKey::Space))
	{
		//ESpawnList SelectMonster = static_cast<ESpawnList>(SelectItem);
		//std::shared_ptr<class ACameraActor> Camera = Level->GetMainCamera();
		//FVector4 Pos = Camera->ScreenMousePosToWorldPos();
		//Pos.Z = 0.0f;

		//std::shared_ptr<AActor> NewMonster;
		TilemapComponent->SetTile(FIntPoint(WorldCoord.X, WorldCoord.Y), EditorSetting);
		TilemapColliderComponent->UpdateCollider();
	}

	if (true == UEngineInputSystem::GetKey(EKey::D))
	{
		TilemapComponent->RemoveTile(FIntPoint(WorldCoord.X, WorldCoord.Y));
		TilemapColliderComponent->UpdateCollider();

	}
	if (true == UEngineInputSystem::GetKeyDown(EKey::R))
	{
		Rotate = (Rotate + 1) % 4;
		EditorSetting.RotatedCount = Rotate;
	}

	if (true == UEngineInputSystem::GetKeyDown(EKey::F))
	{
		IsFlip = !IsFlip;
		EditorSetting.IsFlip = IsFlip;
	}


	// Enum 값에 대응하는 문자열 배열
	const char* enumNames[] = { "Quad", "Slope1", "Slope2", "Slope3", "Slope4", "Slope5", "Slope6" };
	// 현재 선택된 항목의 인덱스를 가져옵니다.

	// ImGui::Combo를 사용하여 드롭다운 리스트 생성
	if (ImGui::Combo("Enum Selector", &currentIndex, enumNames, static_cast<int>(ETilePolygon::Slope6) + 1)) {
		// 선택이 변경되면 currentSelection 값을 업데이트
		EditorSetting.PolygonType = static_cast<ETilePolygon>(currentIndex);
	}

	//// 현재 선택된 값을 표시
	ImGui::Text("Current Selection: %s", enumNames[currentIndex]);

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
		ofn.lpstrFilter = ("All\0*.*\0Text\0*.Tmap\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = InitPath.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			UEnginePath Path = std::string_view(ofn.lpstrFile);
			TilemapComponent->Load(Path.GetFileNameWithoutExtension());
		}
		TilemapColliderComponent->UpdateCollider();
	}
	ImGui::End();
}
