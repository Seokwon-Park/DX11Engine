cbuffer WorldViewProjection : register(b0)
{
	float4x4 World;
	float4x4 View;
	float4x4 Proj;
};

cbuffer SpriteData : register(b1)
{
	float2 CuttingPos;
	float2 CuttingSize;
	float2 Pivot;
	float2 Dummy;
};

struct VS_Input
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD0;
};

struct VS_Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD0;
};

VS_Output vs_main(VS_Input _Input)
{
	VS_Output Output;
	_Input.Pos.x += (1.0f - Pivot.x) - 0.5f;
	_Input.Pos.y += (1.0f - Pivot.y) - 0.5f;
	Output.Pos = mul(_Input.Pos, World);
	Output.Pos = mul(Output.Pos, View);
	Output.Pos = mul(Output.Pos, Proj);
	Output.Color = _Input.Color;
    
	Output.UV.x = (_Input.UV.x * CuttingSize.x) + CuttingPos.x;
	Output.UV.y = (_Input.UV.y * CuttingSize.y) + CuttingPos.y;

	return Output;
}

Texture2D SpriteTexture : register(t0);

SamplerState PSSampler : register(s0);

cbuffer PSColor : register(b0)
{
	float4 Albedo;
};

struct PS_Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

float4 ps_main(VS_Output _Input) : SV_TARGET0
{
	float4 Color = SpriteTexture.Sample(PSSampler, _Input.UV.xy) * Albedo;
    //float4 Color = float4(1.0f, 0.0f, 1.0f, 1.0f);
	return Color;
}