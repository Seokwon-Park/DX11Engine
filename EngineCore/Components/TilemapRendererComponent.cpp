#include "EnginePCH.h"
#include "TilemapRendererComponent.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"

UTilemapRendererComponent::UTilemapRendererComponent()
{
}

UTilemapRendererComponent::~UTilemapRendererComponent()
{
}

void UTilemapRendererComponent::SetTileSetting(std::string_view _Name, FVector2 _TileSize, FVector2 _ImageSize, FVector2 _Pivot)
{
	Sprite = UResourceManager::Find<UEngineSprite>(_Name).get();

	TileSize = _TileSize;
	ImageSize = _ImageSize;
	TilePivot = _Pivot;
}

void UTilemapRendererComponent::SetTile(FIntPoint _Pos, int _SpriteIndex)
{
	// 이공식이?????
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	SetTile(Index.X, Index.Y, _SpriteIndex);
}

void UTilemapRendererComponent::SetTile(int _X, int _Y, int _Spriteindex)
{
	FTileIndex Index = { _X,  _Y };

	FTileData& NewTile = Tiles[Index.Key];

	NewTile.SpriteIndex = _Spriteindex;
	NewTile.SpriteData.Rect.CuttingPos = { 0.0f, 0.0f };
	NewTile.SpriteData.Rect.CuttingSize = { 1.0f, 1.0f };
	NewTile.SpriteData.Rect.Pivot = { 0.5f, 0.5f };
}

FVector4 UTilemapRendererComponent::TileIndexToWorldPos(FTileIndex _Pos)
{
	FVector4 Result;
	Result.X = _Pos.X * ImageSize.X;
	Result.Y = _Pos.Y * ImageSize.X;
	return Result;
}

FTileIndex UTilemapRendererComponent::WorldPosToTileIndex(FIntPoint _Pos)
{
	FTileIndex Result = FTileIndex();
	FIntPoint ConvertVector = FIntPoint(_Pos.X / ImageSize.X , _Pos.Y / ImageSize.Y);
	Result.X = ConvertVector.X;
	Result.Y = ConvertVector.Y;

	return Result;
}

void UTilemapRendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	VertexConstant VC;
	auto& Test = Parent->GetTransformRef();
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View = _Camera->GetViewMatrix();
	VC.View.MatrixTranspose();
	VC.Proj = _Camera->GetProjMatrix();
	VC.Proj.MatrixTranspose();



	if (0 == Tiles.size())
	{
		return;
	}

	FTransform Trans;

	for (std::pair<const __int64, FTileData>& TilePair : Tiles)
	{
		//if (화면 바깥에 나간 타일은)
		//{
		//	continue;
		//}

		FTileData& Tile = TilePair.second;
		FTileIndex Index;

		Unit->SetTexture("TilemapTexture", EShaderType::PS, Sprite->GetSpriteData(Tile.SpriteIndex).Texture);
		Unit->SetSampler("PSSampler", EShaderType::PS, UEngineSamplerState::Create());

		Tile.SpriteData = Sprite->GetSpriteData(Tile.SpriteIndex);
		Tile.SpriteData.Rect.Pivot = { 0.0f, 0.0f };

		Index.Key = TilePair.first;

		FVector4 ConvertPos = TileIndexToWorldPos(Index);

		Trans.Location = FVector4({ ConvertPos.X, ConvertPos.Y, 0.0f, 1.0f });
		Trans.Scale = FVector4({ ImageSize.X, ImageSize.Y, 1.0f, 1.0f });

		Trans.UpdateTransform();
		Trans.WorldMatrix.MatrixTranspose();
		VC.World = Trans.WorldMatrix;

		Unit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
		Unit->SetConstantBufferData("SpriteData", EShaderType::VS, Tile.SpriteData.Rect);

		//Unit.ConstantBufferLinkData("ResultColor", Tile.ColorData);

		Unit->Render(_Camera, _DeltaTime);
	}

	URendererComponent::Render(_Camera, _DeltaTime);
}

void UTilemapRendererComponent::BeginPlay()
{
	URendererComponent::BeginPlay();
	GetOwner()->GetLevel()->PushTilemapRenderer(GetThis<UTilemapRendererComponent>());
	Unit = std::make_shared<URenderUnit>();
	Unit->Init("Quad", "Tilemap");
}

void UTilemapRendererComponent::TickComponent(float _DeltaTime)
{
	URendererComponent::TickComponent(_DeltaTime);
}
