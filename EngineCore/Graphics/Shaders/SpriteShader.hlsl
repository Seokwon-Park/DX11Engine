struct VS_Input
{
    float4 Pos: POSITION;
    float4 Color : COLOR;
};

struct VS_Output
{
    float4 Pos: SV_POSITION;
    float4 Color : COLOR;
};

VS_Output vs_main(VS_Input _Input)
{
    VS_Output Output;
    Output.Pos = _Input.Pos;
    Output.Color = _Input.Color;    

    return Output;
}

struct PS_Output
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

float4 ps_main(VS_Output _Input) : SV_TARGET0
{
    return float4(1.0f,1.0f,0.0f,1.0f);
}