// 2D用頂点シェーダ

// パラメータ
struct VS_INPUT {
	float3	Position	: POSITION;
	float2	TexCoord	: TEXCOORD0;
	uint		instID : SV_InstanceID;
};

struct VS_OUTPUT {
	float4	Position		: SV_Position;
	float2 TexCoord		: TEXCOORD0;
};

// トランスフォーム定数バッファ
cbuffer ViewProj : register(b0)
{
	float4x4 _mView;
	float4x4 _mProj;
}

cbuffer World : register(b8)
{
	float4x4 _mWorld[512];
}


VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	int n = input.instID % 512;
	float4x4 mWVP = mul(_mWorld[n], _mView);
	mWVP = mul(mWVP, _mProj);
	output.Position = mul(float4(input.Position, 1.0f), mWVP);
	//output.Position = mul(float4(input.Position, 1.0f), _mWorld);
	//output.TexCoord = mul(float4(input.TexCoord, 0.0f, 1.0f), _mTex).xy;
	output.TexCoord = input.TexCoord;
	return output;
}
