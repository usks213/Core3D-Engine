// ライトピクセルシェーダ

#include "Light.hlsli"

// パラメータ
struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float2 TexCoord : TEXCOORD0;
	float3 WorldPos : POSITION0;
	float3 Normal : NORMAL0;
};

// マテリアル
cbuffer Material : register(b0)
{
	float4 _Color;
	uint _PointLightNum;
	float3 _ViewPos;
}

// テクスチャ
Texture2D _Texture : register(t0);		// メインテクスチャ
SamplerState _Sampler : register(s0);	// メインサンプラ

// ポイントライト
StructuredBuffer<PointLightData> _PointLights : register(t8); // ポイントライト


float4 PS(VS_OUTPUT input) : SV_Target0
{
	float4 Color = _Color;
	Color *= _Texture.Sample(_Sampler, input.TexCoord);
	float3 Result = float3(0, 0, 0);

	// パラメータ
	float3 pos = input.WorldPos;
	float3 N = normalize(input.Normal);
	float3 V = normalize(_ViewPos - pos); // 視点へのベクトル
	float3 R = reflect(-V, N);
	
	// ポイントライトライト計算
	uint i = 0;
	for (; i < _PointLightNum; ++i)
	{
		float3 L = normalize(_PointLights[i].position - pos);	// 光源のベクトル
		float3 H = normalize(L + V);							// ハーフベクトル
		
		float3 dif = Color.rgb * saturate(dot(L, N));
		float3 spe = pow(saturate(dot(N, H)), 100.0f);
		float3 amb = float3(0.2f, 0.2f, 0.2f) * Color.rgb;
		
		Result += (dif + spe + amb) * PointLightColor(_PointLights[i], pos);
	}
	
	
	return float4(Result.rgb, Color.w);
}
