/*****************************************************************//**
 * \file   RHI_ShaderUtil.h
 * \brief  シェーダーユーティリティ
 *
 * \author USAMI KOSHI
 * \date   2021/12/10
 *********************************************************************/
#include "RHI_ShaderUtil.h"

namespace Core::RHI
{
	/// @brief ループ用インクリメント
	ShaderStage operator++(ShaderStage& value) {
		int result = static_cast<int>(value) + 1;
		if (result > static_cast<int>(ShaderStage::MAX)) {
			value = ShaderStage::VS;
			return ShaderStage::VS;
		}
		else {
			value = static_cast<ShaderStage>(result);
			return value;
		}
	}
	/// @brief ループ用インクリメント
	ShaderStage operator++(ShaderStage& value, int) {
		int result = static_cast<int>(value) + 1;
		if (result > static_cast<int>(ShaderStage::MAX)) {
			value = ShaderStage::VS;
			return ShaderStage::VS;
		}
		else {
			value = static_cast<ShaderStage>(result);
			return static_cast<ShaderStage>(result);
		}
	}
	/// @brief シェーダーステージフラグ用論理和
	std::uint32_t operator|(const ShaderStageFlags& l, const ShaderStageFlags& r) {
		return static_cast<std::uint32_t>(l) | static_cast<std::uint32_t>(r);
	}
	/// @brief シェーダーステージフラグ用論理和
	std::uint32_t operator|(const std::uint32_t& l, const ShaderStageFlags& r) {
		return l | static_cast<std::uint32_t>(r);
	}

	/// @brief 
	/// @param shaderStage 
	/// @return 
	constexpr ShaderStageFlags ConvertShaderStage2Flags(const ShaderStage& shaderStage) {
		switch (shaderStage) {
		case ShaderStage::VS: return ShaderStageFlags::VS;
		case ShaderStage::GS: return ShaderStageFlags::GS;
		case ShaderStage::DS: return ShaderStageFlags::DS;
		case ShaderStage::HS: return ShaderStageFlags::HS;
		case ShaderStage::PS: return ShaderStageFlags::PS;
		case ShaderStage::CS: return ShaderStageFlags::CS;
		default:			   return ShaderStageFlags::NONE;
		}
	}
	/// @brief シェーダーステージがフラグに含まれているか
	/// @details FlagsとANDを取る
	/// @param shaderStageFlags シェーダーステージフラグ
	/// @param shaderStage シェーダーステージ
	/// @return 含まれているならTRUE
	bool hasStaderStage(const std::uint32_t& shaderStageFlags, const ShaderStage& shaderStage) {
		return shaderStageFlags & static_cast<std::uint32_t>(ConvertShaderStage2Flags(shaderStage));
	}
}
