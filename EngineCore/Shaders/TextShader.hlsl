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

cbuffer TextColor : register(b0)
{
    float4 bgColor;
    float4 fgColor;
};

struct PS_Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

float median(float r, float g, float b)
{
    return max(min(r, g), min(max(r, g), b));
}

float screenPxRange(float2 _uv)
{
    uint width, height;
    SpriteTexture.GetDimensions(width, height);
    float pxRange = 4.0f; // set to distance field's pixel range
    float2 unitRange = float2(pxRange / width, pxRange / height);
    float2 screenTexSize = float2(1.0f / fwidth(_uv).x, 1.0f / fwidth(_uv).y);
    return max(0.5 * dot(unitRange, screenTexSize), 1.0);
}

float4 ps_main(VS_Output _Input) : SV_TARGET0
{
	float3 msd = SpriteTexture.Sample(PSSampler, _Input.UV).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange(_Input.UV) * (sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5f, 0.0f, 1.0f);
    if (opacity == 0.0)
    {
        clip(-1);
    }
		
    float4 Color = lerp(bgColor, fgColor, float4(opacity, opacity, opacity, opacity));
    return Color;
    //return float4(msd, 1.0f);

}

