#include "EnginePCH.h"
#include "TextRendererComponent.h"
#include <EngineCore/Structures/ShaderBufferDataStructure.h>

struct FTextColorData
{
	FColor bgColor;
	FColor fgColor;
};
UTextRendererComponent::UTextRendererComponent()
{
}

UTextRendererComponent::~UTextRendererComponent()
{
}

void UTextRendererComponent::SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer)
{
	URenderer2DComponent::SetOrder(_SortingLayer, _OrderInLayer);
	int SortingLayerInt = static_cast<int>(_SortingLayer);
	std::shared_ptr<UTextRendererComponent> RendererPtr = GetThis<UTextRendererComponent>();
	ULevel* Level = GetOwner()->GetLevel();

	//처음 렌더러 생성시에는 Level이 Null일 수 있으므로 미루고 BeginPlay에서 처리.
	if (Level == nullptr)
	{
		return;
	}
	Level->ChangeRenderOrder(PrevOrder, RendererPtr);
}

void UTextRendererComponent::SetFont(std::string_view _FontName)
{
	Font = UResourceManager::Find<UEngineFont>(_FontName);
}

void UTextRendererComponent::TickComponent(float _DeltaTime)
{
	URenderer2DComponent::TickComponent(_DeltaTime);

}

void UTextRendererComponent::BeginPlay()
{
	URenderer2DComponent::BeginPlay();
	Unit = std::make_shared<URenderUnit>();
	Unit->Init("Quad", "Text");
	GetOwner()->GetLevel()->PushRenderer(GetThis<UTextRendererComponent>());

}

void UTextRendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	if (Font == nullptr) { return; }
	const msdf_atlas::FontGeometry& FontGeometry = Font->GetMSDFData()->FontGeometry;
	const auto& metrics = FontGeometry.getMetrics();
	std::shared_ptr<UEngineTexture2D> FontAtlas = Font->GetFontAtlasTexture();
	//std::shared_ptr<UEngineTexture2D> FontAtlas = UResourceManager::Find<UEngineTexture2D>("tevi_n_01.png");

	double x = 0.0;
	double fsScale = 1.0 / (metrics.ascenderY - metrics.descenderY);
	double y = 0.0;
	
	const float spaceGlyphAdvance = FontGeometry.getGlyph(' ')->getAdvance();

	for (size_t i = 0; i < Text.size(); i++)
	{
		wchar_t character = Text[i];
		if (character == '\r')
			continue;

		if (character == '\n')
		{
			x = 0;
			y -= fsScale * metrics.lineHeight + TextParam.LineSpacing;
			continue;
		}

		if (character == ' ')
		{
			float advance = spaceGlyphAdvance;
			if (i < Text.size() - 1)
			{
				wchar_t nextCharacter = Text[i + 1];
				double dAdvance;
				FontGeometry.getAdvance(dAdvance, character, nextCharacter);
				advance = (float)dAdvance;
			}

			x += fsScale * advance * FontSize + TextParam.Kerning;
			continue;
		}

		if (character == '\t')
		{
			x += 4.0f * (fsScale * spaceGlyphAdvance + TextParam.Kerning);
			continue;
		}

		auto glyph = FontGeometry.getGlyph(character);
		if (!glyph)
			glyph = FontGeometry.getGlyph('?');
		if (!glyph)
			return;

		double al, ab, ar, at;
		glyph->getQuadAtlasBounds(al, ab, ar, at);
		FVector2 texCoordMin((float)al, (float)ab);
		FVector2 texCoordMax((float)ar, (float)at);

		float MaxY = texCoordMax.Y;
		texCoordMax.Y = FontAtlas->GetTextureSize().Y - texCoordMin.Y;
		texCoordMin.Y = FontAtlas->GetTextureSize().Y - MaxY;

		double pl, pb, pr, pt;
		glyph->getQuadPlaneBounds(pl, pb, pr, pt);
		FVector2 quadMin((float)pl, (float)pb);
		FVector2 quadMax((float)pr, (float)pt);

		quadMin *= fsScale, quadMax *= fsScale;
		quadMin += FVector2(x, y);
		quadMax += FVector2(x, y);

		float Width = (quadMax.X - quadMin.X);
		float Height = (quadMax.Y - quadMin.Y);
		VertexConstant VC;
		FTransform& Trans = GetTransformRef();
		Trans.Location = { (float)x, (float)y+ quadMax.Y * FontSize,1.0f };
		Trans.Scale = { FontSize * Width , FontSize * Height, 1.0f, 1.0f};
		UpdateTransform();
		VC.World = Trans.WorldMatrix;
		VC.World.MatrixTranspose();
		VC.View = _Camera->GetViewMatrix();
		VC.View.MatrixTranspose();

		//Data.Proj.MatrixOrthoFovLH(1.22, 1280.0f / 720.0f, 0.01f, 100.0f);
		VC.Proj = _Camera->GetProjectionMatrix();
		VC.Proj.MatrixTranspose();

		float texelWidth = 1.0f / FontAtlas->GetTextureSize().X;
		float texelHeight = 1.0f / FontAtlas->GetTextureSize().Y;
		texCoordMin *= FVector2(texelWidth, texelHeight);
		texCoordMax *= FVector2(texelWidth, texelHeight);

		//texCoordMin.X = 1.0 - texCoordMin.X;
		//texCoordMin.Y = 1.0 - texCoordMin.Y;

		//texCoordMax.X = 1.0 - texCoordMax.X;
		//texCoordMax.Y = 1.0 - texCoordMax.Y;
		FSpriteRect Rect;

		Rect.CuttingPos = texCoordMin;
		Rect.CuttingSize= texCoordMax - texCoordMin;
		Rect.Pivot = { 0.0f,1.0f };
		//// render here
		//s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMin, 0.0f, 1.0f);
		//s_Data.TextVertexBufferPtr->Color = textParams.Color;
		//s_Data.TextVertexBufferPtr->TexCoord = texCoordMin;
		//s_Data.TextVertexBufferPtr->EntityID = entityID;
		//s_Data.TextVertexBufferPtr++;

		//s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMin.x, quadMax.y, 0.0f, 1.0f);
		//s_Data.TextVertexBufferPtr->Color = textParams.Color;
		//s_Data.TextVertexBufferPtr->TexCoord = { texCoordMin.x, texCoordMax.y };
		//s_Data.TextVertexBufferPtr->EntityID = entityID;
		//s_Data.TextVertexBufferPtr++;

		//s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMax, 0.0f, 1.0f);
		//s_Data.TextVertexBufferPtr->Color = textParams.Color;
		//s_Data.TextVertexBufferPtr->TexCoord = texCoordMax;
		//s_Data.TextVertexBufferPtr->EntityID = entityID;
		//s_Data.TextVertexBufferPtr++;

		//s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMax.x, quadMin.y, 0.0f, 1.0f);
		//s_Data.TextVertexBufferPtr->Color = textParams.Color;
		//s_Data.TextVertexBufferPtr->TexCoord = { texCoordMax.x, texCoordMin.y };
		//s_Data.TextVertexBufferPtr->EntityID = entityID;
		//s_Data.TextVertexBufferPtr++;

		//s_Data.TextIndexCount += 6;
		//s_Data.Stats.QuadCount++;

		if (i < Text.size() - 1)
		{
			double advance = glyph->getAdvance();
			wchar_t nextCharacter = Text[i + 1];
			FontGeometry.getAdvance(advance, character, nextCharacter);

			x += fsScale * advance * FontSize + TextParam.Kerning;
		}

		
		FTextColorData test = { FColor(1.0f, 1.0f, 1.0f, 1.0f), TextParam.Color };
		Unit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
		Unit->SetConstantBufferData("SpriteData", EShaderType::VS, Rect);
		Unit->SetConstantBufferData("TextColor", EShaderType::PS, test);
		Unit->SetTexture("SpriteTexture", EShaderType::PS, FontAtlas);
		Unit->SetSampler("PSSampler", EShaderType::PS, UResourceManager::Find<UEngineSamplerState>("Default"));

		Unit->Render(_Camera, _DeltaTime);
	}
	URenderer2DComponent::Render(_Camera, _DeltaTime);
}
