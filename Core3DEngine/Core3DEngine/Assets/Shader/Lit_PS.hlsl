// ���C�g�s�N�Z���V�F�[�_

#include "Light.hlsli"

// �p�����[�^
struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float2 TexCoord : TEXCOORD0;
	float3 WorldPos : POSITION0;
	float3 Normal : NORMAL0;
};

// �}�e���A��
cbuffer Material : register(b0)
{
	float4 _Color;
	uint _PointLightNum;
	float3 _ViewPos;
}

// �e�N�X�`��
Texture2D _Texture : register(t0);		// ���C���e�N�X�`��
SamplerState _Sampler : register(s0);	// ���C���T���v��

// �|�C���g���C�g
StructuredBuffer<PointLightData> _PointLights : register(t8); // �|�C���g���C�g


float4 PS(VS_OUTPUT input) : SV_Target0
{
	float4 Color = _Color;
	Color *= _Texture.Sample(_Sampler, input.TexCoord);
	float3 Result = float3(0, 0, 0);

	// �p�����[�^
	float3 pos = input.WorldPos;
	float3 N = normalize(input.Normal);
	float3 V = normalize(_ViewPos - pos); // ���_�ւ̃x�N�g��
	float3 R = reflect(-V, N);
	
	// �|�C���g���C�g���C�g�v�Z
	uint i = 0;
	for (; i < _PointLightNum; ++i)
	{
		float3 L = normalize(_PointLights[i].position - pos);	// �����̃x�N�g��
		float3 H = normalize(L + V);							// �n�[�t�x�N�g��
		
		float3 dif = Color.rgb * saturate(dot(L, N));
		float3 spe = pow(saturate(dot(N, H)), 100.0f);
		float3 amb = float3(0.2f, 0.2f, 0.2f) * Color.rgb;
		
		Result += (dif + spe + amb) * PointLightColor(_PointLights[i], pos);
	}
	
	
	return float4(Result.rgb, Color.w);
}
