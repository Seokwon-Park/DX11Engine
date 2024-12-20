struct VS_Input
{
    float4 Pos: POSITION;
    float4 Color : COLOR;
<<<<<<< HEAD
=======
    //float2 UV : TEXCOORD0;
>>>>>>> 59ac2f97383e839d272725f1a70258eafd232c81
};

struct VS_Output
{
    float4 Pos: SV_POSITION;
    float4 Color : COLOR;
<<<<<<< HEAD
=======
    //float2 UV : TEXCOORD0;
>>>>>>> 59ac2f97383e839d272725f1a70258eafd232c81
};

VS_Output vs_main(VS_Input _Input)
{
    VS_Output Output;
<<<<<<< HEAD
    Output.Pos = _Input.Pos;
    Output.Color = _Input.Color;    
=======
    Output.Position = _Input.Position;
    Output.Color = _Input.Color;
    //Output.UV = _Input.UV;
>>>>>>> 59ac2f97383e839d272725f1a70258eafd232c81

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