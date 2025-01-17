#include "EnginePCH.h"
#include "TextRendererComponent.h"

UTextRendererComponent::UTextRendererComponent()
{
}

UTextRendererComponent::~UTextRendererComponent()
{
}

void UTextRendererComponent::TickComponent(float _DeltaTime)
{
}

void UTextRendererComponent::BeginPlay()
{
}

void UTextRendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	//const auto& fontGeometry = Font->GetMSDFData()->FontGeometry;
	//const auto& metrics = fontGeometry.getMetrics();
	//Ref<Texture2D> fontAtlas = font->GetAtlasTexture();

	//s_Data.FontAtlasTexture = fontAtlas;

	//double x = 0.0;
	//double fsScale = 1.0 / (metrics.ascenderY - metrics.descenderY);
	//double y = 0.0;

	//const float spaceGlyphAdvance = fontGeometry.getGlyph(' ')->getAdvance();

	//for (size_t i = 0; i < string.size(); i++)
	//{
	//	char character = string[i];
	//	if (character == '\r')
	//		continue;

	//	if (character == '\n')
	//	{
	//		x = 0;
	//		y -= fsScale * metrics.lineHeight + textParams.LineSpacing;
	//		continue;
	//	}

	//	if (character == ' ')
	//	{
	//		float advance = spaceGlyphAdvance;
	//		if (i < string.size() - 1)
	//		{
	//			char nextCharacter = string[i + 1];
	//			double dAdvance;
	//			fontGeometry.getAdvance(dAdvance, character, nextCharacter);
	//			advance = (float)dAdvance;
	//		}

	//		x += fsScale * advance + textParams.Kerning;
	//		continue;
	//	}

	//	if (character == '\t')
	//	{
	//		// NOTE(Yan): is this right?
	//		x += 4.0f * (fsScale * spaceGlyphAdvance + textParams.Kerning);
	//		continue;
	//	}

	//	auto glyph = fontGeometry.getGlyph(character);
	//	if (!glyph)
	//		glyph = fontGeometry.getGlyph('?');
	//	if (!glyph)
	//		return;

	//	double al, ab, ar, at;
	//	glyph->getQuadAtlasBounds(al, ab, ar, at);
	//	glm::vec2 texCoordMin((float)al, (float)ab);
	//	glm::vec2 texCoordMax((float)ar, (float)at);

	//	double pl, pb, pr, pt;
	//	glyph->getQuadPlaneBounds(pl, pb, pr, pt);
	//	glm::vec2 quadMin((float)pl, (float)pb);
	//	glm::vec2 quadMax((float)pr, (float)pt);

	//	quadMin *= fsScale, quadMax *= fsScale;
	//	quadMin += glm::vec2(x, y);
	//	quadMax += glm::vec2(x, y);

	//	float texelWidth = 1.0f / fontAtlas->GetWidth();
	//	float texelHeight = 1.0f / fontAtlas->GetHeight();
	//	texCoordMin *= glm::vec2(texelWidth, texelHeight);
	//	texCoordMax *= glm::vec2(texelWidth, texelHeight);

	//	// render here
	//	s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMin, 0.0f, 1.0f);
	//	s_Data.TextVertexBufferPtr->Color = textParams.Color;
	//	s_Data.TextVertexBufferPtr->TexCoord = texCoordMin;
	//	s_Data.TextVertexBufferPtr->EntityID = entityID;
	//	s_Data.TextVertexBufferPtr++;

	//	s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMin.x, quadMax.y, 0.0f, 1.0f);
	//	s_Data.TextVertexBufferPtr->Color = textParams.Color;
	//	s_Data.TextVertexBufferPtr->TexCoord = { texCoordMin.x, texCoordMax.y };
	//	s_Data.TextVertexBufferPtr->EntityID = entityID;
	//	s_Data.TextVertexBufferPtr++;

	//	s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMax, 0.0f, 1.0f);
	//	s_Data.TextVertexBufferPtr->Color = textParams.Color;
	//	s_Data.TextVertexBufferPtr->TexCoord = texCoordMax;
	//	s_Data.TextVertexBufferPtr->EntityID = entityID;
	//	s_Data.TextVertexBufferPtr++;

	//	s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMax.x, quadMin.y, 0.0f, 1.0f);
	//	s_Data.TextVertexBufferPtr->Color = textParams.Color;
	//	s_Data.TextVertexBufferPtr->TexCoord = { texCoordMax.x, texCoordMin.y };
	//	s_Data.TextVertexBufferPtr->EntityID = entityID;
	//	s_Data.TextVertexBufferPtr++;

	//	s_Data.TextIndexCount += 6;
	//	s_Data.Stats.QuadCount++;

	//	if (i < string.size() - 1)
	//	{
	//		double advance = glyph->getAdvance();
	//		char nextCharacter = string[i + 1];
	//		fontGeometry.getAdvance(advance, character, nextCharacter);

	//		x += fsScale * advance + textParams.Kerning;
	//	}
	//}
}
