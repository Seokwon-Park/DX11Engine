struct VS_Input
{
    float4 Position : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD0;
};

struct VS_Output
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD0;
};

VS_Output vs_main(VS_Input _Input)
{
    VS_Output Output;
    Output.Position = _Input.Position;
    Output.Color = _Input.Color;
    Output.UV = _Input.UV;

    return Output;
}

struct PS_Output
{
    float4 Position : SV_POSITION;
    float3 Color : COLOR;
};




float4 ps_main(VS_Output _Input) : SV_TARGET
{
    return float4(_Input.Color);
}