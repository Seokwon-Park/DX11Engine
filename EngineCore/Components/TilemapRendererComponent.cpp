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

void UTilemapRendererComponent::SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer)
{
	URenderer2DComponent::SetOrder(_SortingLayer, _OrderInLayer);
	int SortingLayerInt = static_cast<int>(_SortingLayer);
	std::shared_ptr<USpriteRendererComponent> RendererPtr = GetThis<USpriteRendererComponent>();
	ULevel* Level = GetOwner()->GetLevel();

	//처음 렌더러 생성시에는 Level이 Null일 수 있으므로 미루고 BeginPlay에서 처리.
	if (Level == nullptr)
	{
		return;
	}
	Level->ChangeRenderOrder(PrevOrder, RendererPtr);
}

FVector4 UTilemapRendererComponent::TileIndexToWorldPos(FTileIndex _Pos)
{
	FVector4 Result;
	Result.X = _Pos.X * TilemapComponent->ImageSize.X;
	Result.Y = _Pos.Y * TilemapComponent->ImageSize.Y;
	return Result;
}

void UTilemapRendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	VertexConstant VC;
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View = _Camera->GetViewMatrix();
	VC.View.MatrixTranspose();
	VC.Proj = _Camera->GetProjectionMatrix();
	VC.Proj.MatrixTranspose();

	if (0 == TilemapComponent->Tiles.size())
	{
		return;
	}

	FTransform Trans;

	for (std::pair<const __int64, FTileData>& TilePair : TilemapComponent->Tiles)
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index;

		Tile.SpriteRect = TilemapComponent->Sprite->GetSpriteByIndex(Tile.SpriteIndex).Rect;
		Tile.SpriteRect.Pivot = { 0.0f, 0.0f };

		Index.Key = TilePair.first;

		FVector4 ConvertPos = TileIndexToWorldPos(Index);

		//if ()
		//{
		//	continue;
		//}

		Unit->SetTexture("TilemapTexture", EShaderType::PS, TilemapComponent->Sprite->GetSpriteByIndex(Tile.SpriteIndex).Texture);
		Unit->SetSampler("PSSampler", EShaderType::PS, UEngineSamplerState::Create());

		Trans.Location = FVector4({ ConvertPos.X, ConvertPos.Y, 0.0f, 1.0f });
		Trans.Scale = FVector4({ TilemapComponent->ImageSize.X, TilemapComponent->ImageSize.Y, 1.0f, 1.0f });

		Trans.UpdateTransform();
		Trans.WorldMatrix.MatrixTranspose();
		VC.World = Trans.WorldMatrix;
		

		Unit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
		Unit->SetConstantBufferData("SpriteData", EShaderType::VS, Tile.SpriteRect);
		Unit->SetConstantBufferData("PSColor", EShaderType::PS, FColor(1.0f,1.0f,1.0f, 1.0f));

		//Unit.ConstantBufferLinkData("ResultColor", Tile.ColorData);

		Unit->Render(_Camera, _DeltaTime);
	}

	URendererComponent::Render(_Camera, _DeltaTime);
}

void UTilemapRendererComponent::BeginPlay()
{
	URendererComponent::BeginPlay();
	GetOwner()->GetLevel()->PushRenderer(GetThis<UTilemapRendererComponent>());
	Unit = std::make_shared<URenderUnit>();
	Unit->Init("Quad", "Tilemap");
}

void UTilemapRendererComponent::TickComponent(float _DeltaTime)
{
	URendererComponent::TickComponent(_DeltaTime);
}
