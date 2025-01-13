cbuffer WorldViewProjection : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Proj;
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
    float4 PosWorld : POSITION;
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
    

    Output.PosWorld = mul(_Input.Pos, World);
    // Output.PosWorld = mul(Output.PosWorld, View);
    
    
    Output.UV = _Input.UV;
    //Output.UV.x = (_Input.UV.x * CuttingSize.x) + CuttingPos.x;
    //Output.UV.y = (_Input.UV.y * CuttingSize.y) + CuttingPos.y;

    return Output;
}

cbuffer PSColor : register(b0)
{
    float4 Color;
};

struct PS_Output
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

float4 ps_main(VS_Output _Input) : SV_TARGET0
{
    int GridX = abs(_Input.PosWorld.x) % 28;
    int GridY = abs(_Input.PosWorld.y) % 28;
    
    if (GridX != 0 && GridY != 0)
    {
        // return Color;
        clip(-1);
    }
    return Color;
    
}