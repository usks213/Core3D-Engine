// 2D�p�s�N�Z���V�F�[�_

// �p�����[�^
struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float2 TexCoord : TEXCOORD0;
};

// �}�e���A��
cbuffer Material : register(b0)
{
	float3 _Color;
	float _Time;
}

Texture2D _RT			: register(t0);	// �����_�[�^�[�Q�b�g
SamplerState _Sampler		: register(s0);	// ���C���T���v��

float4 PS(VS_OUTPUT input) : SV_Target0
{
	float3 Color = _Color;
	Color *= _RT.Sample(_Sampler, input.TexCoord).rgb;
	
	// �|�X�g�G�t�F�N�g
	//Color.r *= saturate(sin(_Time));
	
	// �F����
	float size = sin(_Time) * 0.075f;
	float2 uvBase = input.TexCoord - 0.5f;
	// R�l
	float2 uvR = uvBase * (1.0f - size * 2.0f) + 0.5f;
	Color.r = _RT.Sample(_Sampler, uvR).r;
	// G�l
	float2 uvG = uvBase * (1.0f - size) + 0.5f;
	Color.g = _RT.Sample(_Sampler, uvG).g;
	
	return float4(Color, 1.0f);
}
