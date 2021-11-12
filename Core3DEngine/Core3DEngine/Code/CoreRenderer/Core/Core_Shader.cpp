/*****************************************************************//**
 * \file   Core_Shader.h
 * \brief  �V�F�[�_�[
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "Core_Shader.h"
using namespace core;

 /// @brief ���[�v�p�C���N�������g
ShaderStage core::operator++(ShaderStage& value) {
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
/// @brief ���[�v�p�C���N�������g
ShaderStage core::operator++(ShaderStage& value, int) {
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
/// @brief �V�F�[�_�[�X�e�[�W�t���O�p�_���a
std::uint32_t core::operator|(const ShaderStageFlags& l, const ShaderStageFlags& r) {
	return static_cast<std::uint32_t>(l) | static_cast<std::uint32_t>(r);
}
/// @brief �V�F�[�_�[�X�e�[�W�t���O�p�_���a
std::uint32_t core::operator|(const std::uint32_t& l, const ShaderStageFlags& r) {
	return l | static_cast<std::uint32_t>(r);
}

/// @brief 
/// @param shaderStage 
/// @return 
constexpr ShaderStageFlags core::ConvertShaderStage2Flags(const ShaderStage& shaderStage) {
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
/// @brief �V�F�[�_�[�X�e�[�W���t���O�Ɋ܂܂�Ă��邩
/// @details Flags��AND�����
/// @param shaderStageFlags �V�F�[�_�[�X�e�[�W�t���O
/// @param shaderStage �V�F�[�_�[�X�e�[�W
/// @return �܂܂�Ă���Ȃ�TRUE
bool core::hasStaderStage(const std::uint32_t& shaderStageFlags, const ShaderStage& shaderStage) {
	return shaderStageFlags & static_cast<std::uint32_t>(core::ConvertShaderStage2Flags(shaderStage));
}