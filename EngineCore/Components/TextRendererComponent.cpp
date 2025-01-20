#include "EnginePCH.h"
#include "TextRendererComponent.h"
#include <EngineCore/Structures/ShaderBufferDataStructure.h>

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
	Unit->Init("Quad", "Quad");
	GetOwner()->GetLevel()->PushRenderer(GetThis<UTextRendererComponent>());

}

void UTextRendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	const msdf_atlas::FontGeometry& FontGeometry = Font->GetMSDFData()->FontGeometry;
	const auto& metrics = FontGeometry.getMetrics();
	std::shared_ptr<UEngineTexture2D> FontAtlas = Font->GetFontAtlasTexture();

	double x = 0.0;
	double fsScale = 1.0 / (metrics.ascenderY - metrics.descenderY);
	double y = 0.0;

	const float spaceGlyphAdvance = FontGeometry.getGlyph(' ')->getAdvance();

	VertexConstant VC;
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View = _Camera->GetViewMatrix();
	VC.View.MatrixTranspose();

	//Data.Proj.MatrixOrthoFovLH(1.22, 1280.0f / 720.0f, 0.01f, 100.0f);
	VC.Proj = _Camera->GetProjectionMatrix();
	VC.Proj.MatrixTranspose();

	for (size_t i = 0; i < Text.size(); i++)
	{
		char character = Text[i];
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
				char nextCharacter = Text[i + 1];
				double dAdvance;
				FontGeometry.getAdvance(dAdvance, character, nextCharacter);
				advance = (float)dAdvance;
			}

			x += fsScale * advance + TextParam.Kerning;
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

		double pl, pb, pr, pt;
		glyph->getQuadPlaneBounds(pl, pb, pr, pt);
		FVector2 quadMin((float)pl, (float)pb);
		FVector2 quadMax((float)pr, (float)pt);

		quadMin *= fsScale, quadMax *= fsScale;
		quadMin += FVector2(x, y);
		quadMax += FVector2(x, y);

		float texelWidth = 1.0f / FontAtlas->GetTextureSize().X;
		float texelHeight = 1.0f / FontAtlas->GetTextureSize().Y;
		texCoordMin *= FVector2(texelWidth, texelHeight);
		texCoordMax *= FVector2(texelWidth, texelHeight);

		FSpriteRect Rect;

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
			char nextCharacter = Text[i + 1];
			FontGeometry.getAdvance(advance, character, nextCharacter);

			x += fsScale * advance + TextParam.Kerning;
		}

		
		auto test = FColor(0.0f, 0.0f, 0.0f, 1.0f);
		Unit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
		Unit->SetConstantBufferData("SpriteData", EShaderType::VS, Rect);
		Unit->SetConstantBufferData("PSColor", EShaderType::PS, test);
		Unit->SetTexture("SpriteTexture", EShaderType::PS, FontAtlas);
		Unit->SetSampler("PSSampler", EShaderType::PS, UResourceManager::Find<UEngineSamplerState>("Default"));

	}
	URenderer2DComponent::Render(_Camera, _DeltaTime);
}
