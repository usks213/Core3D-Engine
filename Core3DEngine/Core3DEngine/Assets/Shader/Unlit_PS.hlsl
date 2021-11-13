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
	float4 _Color;
}

Texture2D _Texture : register(t0);		// ���C���e�N�X�`��
SamplerState _Sampler : register(s0);	// ���C���T���v��

float4 PS(VS_OUTPUT input) : SV_Target0
{
	float4 Color = _Color;
	Color *= _Texture.Sample(_Sampler, input.TexCoord);
	
	return Color;
}
