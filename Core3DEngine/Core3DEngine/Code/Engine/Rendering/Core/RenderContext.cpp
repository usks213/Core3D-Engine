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
	auto& resourceMgr = ResourceManager::get();
	// �V�F�[�_�[�̎擾
	auto pShader = resourceMgr.GetResource<GraphicsShader>(material.m_shaderID);
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

		// CBuffer�̎w��
		for (const auto& cbLayout : material.m_cbufferData[stageIndex])
		{
			m_pCmdList->SetConstantBuffer(stage, pRHIShader->GetResourceLayout(gsStage), 
				cbLayout.first, cbLayout.second, false);
		}

		// �e�N�X�`���̎w��
		for (const auto& texture : material.m_textureData[stageIndex])
		{
			auto pTex = resourceMgr.GetResource<Texture>(texture.second);
			if (pTex)
			{
				m_pCmdList->SetShaderResource(stage, pRHIShader->GetResourceLayout(gsStage),
					texture.first, pTex->GetRHITexture(), false);
			}
			else
			{
				m_pCmdList->SetShaderResource(stage, pRHIShader->GetResourceLayout(gsStage),
					texture.first, nullptr, false);
			}
		}

		// �T���v���[�̎w��
		for (const auto& sampler : material.m_samplerData[stageIndex])
		{
			m_pCmdList->SetSampler(stage, pRHIShader->GetResourceLayout(gsStage),
				sampler.first, sampler.second, false);
		}

	}
}

void RenderContext::SetMesh(const Mesh& mesh) const
{

}
