/*****************************************************************//**
 * \file   RenderContext.h
 * \brief  �����_�[�R���e�L�X�g
 *
 * \author USAMI KOSHI
 * \date   2022/01/19
 *********************************************************************/
#include "RenderContext.h"

#include <RHI\Core\RHI_Device.h>
#include <RHI\Core\RHI_CommandList.h>

#include <Resource\Core\ResourceManager.h>
#include <Resource\Graphics\Material.h>
#include <Resource\Graphics\Mesh.h>

using namespace Core;


void RenderContext::SetMaterial(const Material& material) const
{
	// �V�F�[�_�[�̎擾
	auto pShader = ResourceManager::get().GetResource<GraphicsShader>(material.m_shaderID);
	auto pRHIShader = pShader->GetRHIGraphicsShader();
	if (!pRHIShader) return;

	// �p�C�v���C���̎w��
	m_pCmdList->SetGraphicsPipelineState(pRHIShader, material.m_blendState, 
		material.m_rasterizeState, material.m_depthStencilState);

	// �S�X�e�[�W
	for (auto gsStage = RHI::GraphicsShaderStage::VS; gsStage < RHI::GraphicsShaderStage::MAX; ++gsStage)
	{
		const auto stage = static_cast<RHI::ShaderStage>(gsStage);
		const auto stageIndex = static_cast<std::size_t>(gsStage);

		for (const auto& cbLayout : material.m_cbufferData[stageIndex])
		{
			m_pCmdList->SetConstantBuffer(stage, )
		}
	}
}

void RenderContext::SetMesh(const Mesh& mesh) const
{

}
