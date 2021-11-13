// ライトシェーダー

struct DirectionalLightData
{
	float4 color;		// 色
	float4 ambient;		// 環境光
	float4 direction;	// 方向
};

struct PointLightData
{
	float4 color;		// 色
	float3 position;	// 位置
	float range;		// 範囲
};

struct SpotLightData
{
	float4 color;		// 色
	float3 position;	// 位置
	float range;		// 範囲
	float3 direction;	// 方向
	float spot;			// スポット
};

float3 DirectionalLightColor(DirectionalLightData data)
{
	return data.color.rgb * data.color.w;
}

float3 PointLightColor(PointLightData data, float3 worldPos)
{
	float3 lightVec = data.position - worldPos;
	float d = length(lightVec) + 0.001f;

	if (d > data.range)
		return float3(0, 0, 0);

	//float att = 1.0f / dot(data.attenuation.rgb, float3(1.0f, d, d * d));
	float att = data.range / (d * d);
	
	return data.color.rgb * att * data.color.w;
}

float3 SpotLightColor(SpotLightData data, float3 worldPos)
{
	float3 lightVec = data.position - worldPos;
	float d = length(lightVec) + 0.001f;

	if (d > data.range)
		return float3(0, 0, 0);

	lightVec /= d;
	float spot = pow(max(dot(-lightVec, data.direction), 0.0f), data.spot);
	//float att = spot / dot(data.attenuation.rgb, float3(1.0f, d, d * d));
	float att = data.range / (d * d);
	
	return data.color.rgb * att * spot * data.color.w;
}