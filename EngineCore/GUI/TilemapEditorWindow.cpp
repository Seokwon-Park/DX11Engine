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

	{	// ������ Ÿ�ϸ� �����ϴ� �κ�
		std::vector<std::string> NameList;
		for (auto Tilemap : TilemapList)
		{
			NameList.push_back(Tilemap->GetName());
		}

		std::vector<const char*> TilemapNames;
		for (std::string& Ptr : NameList)
		{
			TilemapNames.push_back(Ptr.c_str());
		}

		ImGui::ListBox("TilemapList", &SelectTilemap, TilemapNames.data(), (int)TilemapNames.size());

		TilemapComponent = TilemapList[SelectTilemap]->GetTilmapComponent();
		if (TilemapList[SelectTilemap]->GetTilemapColliderComponent() != nullptr)
		{
			TilemapColliderComponent = TilemapList[SelectTilemap]->GetTilemapColliderComponent();
		}
	}

	std::shared_ptr<UEngineSprite> Sprite = UResourceManager::Find<UEngineSprite>(TilemapComponent->SpriteName);
	std::vector<FSpriteData> SpriteData = Sprite->GetSpriteData();

	for (size_t i = 0; i < Sprite->GetSpriteCount(); i++)
	{
		FSpriteData SpriteData = Sprite->GetSpriteByIndex(i);

		//SRV�Դϴ�
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
			EditorSetting.Multiplier = SpriteData.Texture->GetTextureSize() / TilemapComponent->GetTileSize();
			EditorSetting.SpriteRect = Data;
			EditorSetting.SpriteIndex = SelectItem;

		}
		// ���͸� ġ�� �ʴ°���.
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


		Trans.Location = FVector4(RenderPos.X + (TilemapComponent->GetTileSize().X / 2.0f) * (EditorSetting.Multiplier.X - 1), RenderPos.Y + (TilemapComponent->GetTileSize().Y / 2.0f) * (EditorSetting.Multiplier.Y - 1), 1.0f, 1.0f);
		if (true == IsFlip)
		{
			Trans.Rotation = FVector4(0.0f, 180.0f, 0.0f, 1.0f);
		}
		Trans.Rotation += FVector4(0.0f, 0.0f, 90.0f * Rotate, 1.0f);
		Trans.Scale = FVector4({ SpriteData.Texture->GetTextureSize().X, SpriteData.Texture->GetTextureSize().Y,1.0f });

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
		TilemapComponent->SetTile(FIntPoint(WorldCoord.X, WorldCoord.Y), EditorSetting);
		if (TilemapColliderComponent != nullptr)
			TilemapColliderComponent->UpdateCollider();
	}

	if (true == UEngineInputSystem::GetKey(EKey::D))
	{
		TilemapComponent->RemoveTile(FIntPoint(WorldCoord.X, WorldCoord.Y));
		if (TilemapColliderComponent != nullptr)
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


	// Enum ���� �����ϴ� ���ڿ� �迭
	const char* enumNames[] = { "Quad", "Slope1", "Slope2", "Slope3", "Slope4", "Slope5", "Slope6", "Large"};
	// ���� ���õ� �׸��� �ε����� �����ɴϴ�.

	// ImGui::Combo�� ����Ͽ� ��Ӵٿ� ����Ʈ ����
	if (ImGui::Combo("Enum Selector", &currentIndex, enumNames, static_cast<int>(ETilePolygon::End))) {
		// ������ ����Ǹ� currentSelection ���� ������Ʈ
		EditorSetting.PolygonType = static_cast<ETilePolygon>(currentIndex);
	}

	//// ���� ���õ� ���� ǥ��
	ImGui::Text("Current Selection: %s", enumNames[currentIndex]);

	if (true == ImGui::Button("Save"))
	{
		//���� ����� ������� ����
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
		//���� ����� ������� ����
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
		if (TilemapColliderComponent != nullptr)
			TilemapColliderComponent->UpdateCollider();
	}
	ImGui::End();
}
