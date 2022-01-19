/*****************************************************************//**
 * \file   GraphicsShader.h
 * \brief  �O���t�B�b�N�X�V�F�[�_�[
 *
 * \author USAMI KOSHI
 * \date   2021/12/16
 *********************************************************************/
#include "GraphicsShader.h"
#include <Resource\Core\ResourceManager.h>
#include <Engine\Core\Engine.h>
#include <RHI\Core\RHI_Device.h>

using namespace Core;


/// @brief �V�F�[�_�[�f�[�^�쐬
/// @param desc RHI�V�F�[�_�[Desc
/// @return ���� TRUE / ���s FALSE
bool GraphicsShader::CreateShaderData(RHI::GraphicsShaderDesc& desc)
{
	auto pRenderer = GetResourceManager()->GetEngine()->GetRenderer();
	m_pRHIGraphicsShader = pRenderer->GetDevice()->CreateGraphicsShader(desc);
	if (!m_pRHIGraphicsShader) return false;

	return true;
}

