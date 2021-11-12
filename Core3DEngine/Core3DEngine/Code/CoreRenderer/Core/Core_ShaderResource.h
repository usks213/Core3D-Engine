/*****************************************************************//**
 * \file   Core_ShaderResource.h
 * \brief  シェーダーリソース情報
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_SHADER_RESOURCE_
#define _CORE_SHADER_RESOURCE_

#include "Core_Light.h"
#include <string_view>

#define SHADER_ENUM_SLOT_OP(EnumType, MIN, MAX)		\
EnumType operator++(EnumType& value) {		\
	int result = static_cast<int>(value) + 1;		\
	if (result > static_cast<int>(MAX)) {			\
		value = MIN;								\
		return MIN;									\
	}												\
	else {											\
		value = static_cast<EnumType>(result);		\
		return value;								\
	}												\
}													\
EnumType operator++(EnumType& value, int) {	\
	int result = static_cast<int>(value) + 1;		\
	if (result > static_cast<int>(MAX)) {			\
		value = MIN;								\
		return MIN;									\
	}												\
	else {											\
		value = static_cast<EnumType>(result);		\
		return static_cast<EnumType>(result);		\
	}												\
}													

namespace core
{ 
	namespace SHADER 
	{
		constexpr std::uint32_t MAX_SLOT_COUNT = 14;

		// Light
		constexpr std::uint32_t MAX_POINT_LIGHT_COUNT = 128;
		constexpr std::uint32_t MAX_SPOT_LIGHT_COUNT = 128;

		// AnimationCB Bone
		constexpr std::uint32_t MAX_ANIMATION_BONE_COUNT = 512;

		// システム定数バッファ
		struct SystemBuffer
		{
			Matrix	_mView;
			Matrix	_mProj;
			Matrix	_mProj2D;
			Matrix	_mViewInv;
			Matrix	_mProjInv;
			Vector4 _viewPos;

			CoreDirectionalLight _directionalLit;

			std::uint32_t _pointLightNum;
			std::uint32_t _spotLightNum;

			Vector2 _padding2;
		};

		// トランスフォーム定数バッファ
		struct TransformBuffer
		{
			Matrix _mWorld;
		};

		// アニメーション定数バッファ
		struct AnimationBuffer
		{
			Matrix _mBone[MAX_ANIMATION_BONE_COUNT];
		};
	}
}

#endif // !_CORE_SHADER_RESOURCE_
