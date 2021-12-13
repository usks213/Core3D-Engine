/*****************************************************************//**
 * \file   RHI_ShaderUtil.h
 * \brief  �V�F�[�_�[���[�e�B���e�B
 *
 * \author USAMI KOSHI
 * \date   2021/12/10
 *********************************************************************/
#include "RHI_ShaderUtil.h"

namespace Core::RHI
{
	/// @brief ���[�v�p�C���N�������g
	GraphicsShaderStage operator++(GraphicsShaderStage& value) {
		int result = static_cast<int>(value) + 1;
		if (result > static_cast<int>(GraphicsShaderStage::MAX)) {
			value = GraphicsShaderStage::VS;
			return GraphicsShaderStage::VS;
		}
		else {
			value = static_cast<GraphicsShaderStage>(result);
			return value;
		}
	}
	/// @brief ���[�v�p�C���N�������g
	GraphicsShaderStage operator++(GraphicsShaderStage& value, int) {
		int result = static_cast<int>(value) + 1;
		if (result > static_cast<int>(GraphicsShaderStage::MAX)) {
			value = GraphicsShaderStage::VS;
			return GraphicsShaderStage::VS;
		}
		else {
			value = static_cast<GraphicsShaderStage>(result);
			return static_cast<GraphicsShaderStage>(result);
		}
	}
	/// @brief �V�F�[�_�[�X�e�[�W�t���O�p�_���a
	std::uint32_t operator|(const GraphicsShaderStageFlags& l, const GraphicsShaderStageFlags& r) {
		return static_cast<std::uint32_t>(l) | static_cast<std::uint32_t>(r);
	}
	/// @brief �V�F�[�_�[�X�e�[�W�t���O�p�_���a
	std::uint32_t operator|(const std::uint32_t& l, const GraphicsShaderStageFlags& r) {
		return l | static_cast<std::uint32_t>(r);
	}

	/// @brief 
	/// @param shaderStage 
	/// @return 
	constexpr GraphicsShaderStageFlags ConvertGraphicsShaderStage2Flags(const GraphicsShaderStage& shaderStage) {
		switch (shaderStage) {
		case GraphicsShaderStage::VS: return GraphicsShaderStageFlags::VS;
		case GraphicsShaderStage::GS: return GraphicsShaderStageFlags::GS;
		case GraphicsShaderStage::DS: return GraphicsShaderStageFlags::DS;
		case GraphicsShaderStage::HS: return GraphicsShaderStageFlags::HS;
		case GraphicsShaderStage::PS: return GraphicsShaderStageFlags::PS;
		case GraphicsShaderStage::CS: return GraphicsShaderStageFlags::CS;
		default:			   return GraphicsShaderStageFlags::NONE;
		}
	}
	/// @brief �V�F�[�_�[�X�e�[�W���t���O�Ɋ܂܂�Ă��邩
	/// @details Flags��AND�����
	/// @param shaderStageFlags �V�F�[�_�[�X�e�[�W�t���O
	/// @param shaderStage �V�F�[�_�[�X�e�[�W
	/// @return �܂܂�Ă���Ȃ�TRUE
	bool hasStaderStage(const std::uint32_t& shaderStageFlags, const GraphicsShaderStage& shaderStage) {
		return shaderStageFlags & static_cast<std::uint32_t>(ConvertGraphicsShaderStage2Flags(shaderStage));
	}
}