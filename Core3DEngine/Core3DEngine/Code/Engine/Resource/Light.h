/*****************************************************************//**
 * \file   Light.h
 * \brief  ライト情報
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_LIGHT_
#define _CORE_LIGHT_

#include <Utils/Util_Mathf.h>

namespace Core
{
	/// @brief ディレクショナルライト
	struct CoreDirectionalLight
	{
		Vector4 color = Vector4(1, 1, 1, 1);				///< 色+強さ
		Vector4 ambient = Vector4(0.1f, 0.1f, 0.1f, 1);		///< 環境光
		Vector4 direction = Vector4(1.0f, -1.0f, 1.0f, 1);	///< 方向
	};

	/// @brief ポインタライト
	struct CorePointLight
	{
		Vector4 color = Vector4(1, 1, 1, 1);	///< 色+強さ
		Vector3 position;						///< 位置
		float	range = 1.0f;					///< 範囲
	};

	/// @brief スポットライト
	struct CoreSpotLight
	{
		Vector4 color = Vector4(1, 1, 1, 1);	///< 色+強さ
		Vector3 position;						///< 位置
		float	range = 2.0f;					///< 範囲
		Vector3 direction = Vector3(0, -1, 0);;	///< 方向
		float	spot = 0.5f;					///< 円錐の大きさ(0.0f~1.0f)
	};
}

#endif // !_CORE_LIGHT_

