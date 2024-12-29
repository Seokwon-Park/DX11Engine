cbuffer MVP : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Proj;
};

struct VS_Input
{
    float4 Pos: POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD0;
};

struct VS_Output
{
    float4 Pos: SV_POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD0;
};

VS_Output vs_main(VS_Input _Input)
{
    VS_Output Output;
    Output.Pos = mul(_Input.Pos, World);
    Output.Pos = mul(Output.Pos, View);
    Output.Pos = mul(Output.Pos, Proj);
    Output.Color = _Input.Color;    
    Output.UV = _Input.UV;

    return Output;
}

Texture2D ImageTexture : register(t0);

SamplerState ImageSampler : register(s0);

struct PS_Output
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

float4 ps_main(VS_Output _Input) : SV_TARGET0
{
    float4 Color = ImageTexture.Sample(ImageSampler, _Input.UV.xy);
    return Color;
}