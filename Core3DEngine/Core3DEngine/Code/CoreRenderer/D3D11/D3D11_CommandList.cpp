/*****************************************************************//**
 * \file   D3D11_CommandList.h
 * \brief  DirectX11�����_�[�R�}���h���X�g�N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#include "D3D11_CommandList.h"
#include "D3D11_Renderer.h"

#include "D3D11_Buffer.h"
#include "D3D11_RenderBuffer.h"
#include "D3D11_Texture.h"
#include "D3D11_RenderTarget.h"
#include "D3D11_DepthStencil.h"

#include <CoreRenderer/Core/Core_SubResource.h>

#include <functional>

using namespace core;
using namespace d3d11;


//------------------------------------------------------------------------------
// local methods 
//------------------------------------------------------------------------------
namespace {
	// CBuffer
	static std::function<void(ID3D11DeviceContext1*, UINT, UINT, ID3D11Buffer* const*)>
		setCBuffer[static_cast<std::size_t>(ShaderStage::MAX)] = {
		&ID3D11DeviceContext1::VSSetConstantBuffers,
		&ID3D11DeviceContext1::GSSetConstantBuffers,
		&ID3D11DeviceContext1::DSSetConstantBuffers,
		&ID3D11DeviceContext1::HSSetConstantBuffers,
		&ID3D11DeviceContext1::PSSetConstantBuffers,
		&ID3D11DeviceContext1::CSSetConstantBuffers, };
	// SRV
	static std::function<void(ID3D11DeviceContext1*, UINT, UINT, ID3D11ShaderResourceView* const*)>
		setShaderResource[static_cast<std::size_t>(ShaderStage::MAX)] = {
		&ID3D11DeviceContext1::VSSetShaderResources,
		&ID3D11DeviceContext1::GSSetShaderResources,
		&ID3D11DeviceContext1::DSSetShaderResources,
		&ID3D11DeviceContext1::HSSetShaderResources,
		&ID3D11DeviceContext1::PSSetShaderResources,
		&ID3D11DeviceContext1::CSSetShaderResources, };
	// Sampler
	static std::function<void(ID3D11DeviceContext1*, UINT, UINT, ID3D11SamplerState* const*)>
		setSamplers[static_cast<std::size_t>(ShaderStage::MAX)] = {
		&ID3D11DeviceContext1::VSSetSamplers,
		&ID3D11DeviceContext1::GSSetSamplers,
		&ID3D11DeviceContext1::DSSetSamplers,
		&ID3D11DeviceContext1::HSSetSamplers,
		&ID3D11DeviceContext1::PSSetSamplers,
		&ID3D11DeviceContext1::CSSetSamplers, };
}

//------------------------------------------------------------------------------
// public methods 
//------------------------------------------------------------------------------

/// @brief �R���X�g���N�^
D3D11CommandList::D3D11CommandList() :
	m_pRenderer(nullptr),
	m_pDevice(nullptr),
	m_pDeferredContext(nullptr),
	m_pCmdList(nullptr),
	m_curDepthStencilID(NONE_DEPTH_STENCIL_ID)
{
}

/// @brief ����������
/// @param pRenderer D3D11�����_���[�|�C���^
/// @param pDevice D3D11�f�o�C�X�|�C���^
/// @return ������: ���� true | ���s false
HRESULT D3D11CommandList::initialize(D3D11Renderer* pRenderer, D3D11Device* pDevice)
{
	//--- ������
	m_pRenderer = pRenderer;
	m_pDevice = pDevice;

	// �f�t�@�[�h�R���e�L�X�g�̍쐬
	m_pDevice->m_pD3DDevice->CreateDeferredContext1(0, m_pDeferredContext.ReleaseAndGetAddressOf());
	//m_pDeferredContext->FinishCommandList(true, m_pCmdList.ReleaseAndGetAddressOf());
	//m_pCmdList.Reset();

	return S_OK;
}

//----- ���\�[�X�w�薽�� -----

void D3D11CommandList::setMaterial(const core::MaterialID& materialID)
{
	// �}�e���A���̎擾
	auto* d3dMat = static_cast<D3D11Material*>(m_pDevice->getMaterial(materialID));
	if (d3dMat == nullptr) return;

	// �p�C�v���C���X�e�[�g�̐ݒ�
	setGraphicsPipelineState(d3dMat->m_shaderID, d3dMat->m_blendState, 
		d3dMat->m_rasterizeState, d3dMat->m_depthStencilState);

	// �}�e���A�����\�[�X�w��E�X�V
		// �X�e�[�W����
	for (auto stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<std::size_t>(stage);

		// �R���X�^���g�o�b�t�@
		for (const auto& cbuffer : d3dMat->m_d3dCbuffer[stageIndex])
		{
			// �X�V
			if (d3dMat->m_cbufferData[stageIndex][cbuffer.first].isUpdate)
			{
				m_pDeferredContext->UpdateSubresource(cbuffer.second.Get(), 0, nullptr,
					d3dMat->m_cbufferData[stageIndex][cbuffer.first].data.get(), 0, 0);
				d3dMat->m_cbufferData[stageIndex][cbuffer.first].isUpdate = false;
			}
			// �w��
			setCBuffer[stageIndex](m_pDeferredContext.Get(), cbuffer.first, 1, cbuffer.second.GetAddressOf());
		}

		// �e�N�X�`���X�V
		for (const auto& tex : d3dMat->m_textureData[stageIndex])
		{
			setTextureResource(tex.first, tex.second.id, stage);
		}

		// �T���v���X�V
		for (const auto& sam : d3dMat->m_samplerData[stageIndex])
		{
			setSamplerResource(sam.first, sam.second.state, stage);
		}
	}
}

void D3D11CommandList::setRenderBuffer(const core::RenderBufferID& renderBufferID)
{
	auto* cmdList = m_pDeferredContext.Get();

	// �f�[�^�̎擾
	auto* renderBuffer = static_cast<D3D11RenderBuffer*>(m_pDevice->getRenderBuffer(renderBufferID));

	// ���_�o�b�t�@���Z�b�g
	UINT stride = static_cast<UINT>(renderBuffer->m_vertexData.size);
	UINT offset = 0;
	cmdList->IASetVertexBuffers(0, 1, renderBuffer->m_vertexBuffer.GetAddressOf(), &stride, &offset);
	// �C���f�b�N�X�o�b�t�@���Z�b�g
	if (renderBuffer->m_indexData.count > 0) {
		cmdList->IASetIndexBuffer(renderBuffer->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	// �v���~�e�B�u�w��
	m_pDeferredContext->IASetPrimitiveTopology(getD3D11PrimitiveTopology(renderBuffer->m_topology));

}

//----- �Z�b�g���� -----

void D3D11CommandList::setBackBuffer()
{
	m_pDeferredContext->OMSetRenderTargets(1, m_pDevice->m_backBufferRTV.GetAddressOf(),
		m_pDevice->m_depthStencilView.Get());
}

void D3D11CommandList::setGraphicsPipelineState(const ShaderID& shaderID, const BlendState& bs,
	const RasterizeState& rs, const DepthStencilState& ds)
{
	// �V�F�[�_�[�̎w��
	auto* d3dShader = static_cast<D3D11Shader*>(m_pDevice->getShader(shaderID));
	if (d3dShader)
	{
		// �V�F�[�_�[�f�[�^�w��
		if (d3dShader->vs) m_pDeferredContext->VSSetShader(d3dShader->vs, nullptr, 0);
		if (d3dShader->gs) m_pDeferredContext->GSSetShader(d3dShader->gs, nullptr, 0);
		if (d3dShader->ds) m_pDeferredContext->DSSetShader(d3dShader->ds, nullptr, 0);
		if (d3dShader->hs) m_pDeferredContext->HSSetShader(d3dShader->hs, nullptr, 0);
		if (d3dShader->ps) m_pDeferredContext->PSSetShader(d3dShader->ps, nullptr, 0);
		if (d3dShader->cs) m_pDeferredContext->CSSetShader(d3dShader->cs, nullptr, 0);
		// ���̓��C�A�E�g�w��
		m_pDeferredContext->IASetInputLayout(d3dShader->m_inputLayout.Get());
	}

	// �u�����h�X�e�[�g
	constexpr float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pDeferredContext->OMSetBlendState(m_pDevice->m_blendStates[
		static_cast<std::size_t>(bs)].Get(), blendFactor, 0xffffffff);

	// ���X�^���C�U�X�e�[�g
	m_pDeferredContext->RSSetState(m_pDevice->m_rasterizeStates[
		static_cast<std::size_t>(rs)].Get());

	// �[�x�X�e���V���X�e�[�g
	m_pDeferredContext->OMSetDepthStencilState(m_pDevice->m_depthStencilStates[
		static_cast<std::size_t>(ds)].Get(), 0);

}

void D3D11CommandList::setRenderTarget(const RenderTargetID& rtID)
{
	RenderTargetID rtIDs[] = { rtID };
	setRenderTarget(1, rtIDs);
}

void D3D11CommandList::setRenderTarget(const std::uint32_t num, const RenderTargetID rtIDs[])
{
	setRenderTarget(num, rtIDs, m_curDepthStencilID);
}

void D3D11CommandList::setRenderTarget(const RenderTargetID& rtID, const DepthStencilID& dsID)
{
	RenderTargetID rtIDs[] = { rtID };
;	setRenderTarget(1, rtIDs, dsID);
}

void D3D11CommandList::setRenderTarget(std::uint32_t num, const RenderTargetID rtIDs[], const DepthStencilID& dsID)
{
	// ���S����
	if (num >= MAX_RENDER_TARGET || num <= 0) return;

	// �����_�[�^�[�Q�b�g�擾
	std::vector<ID3D11RenderTargetView*> rtvs;
	rtvs.resize(num);
	for (int i = 0; i < num; ++i)
	{
		auto* pRT = static_cast<D3D11RenderTarget*>(m_pDevice->getRenderTarget(rtIDs[i]));
		if (pRT) rtvs[i] = pRT->m_rtv.Get();
		else rtvs[i] = nullptr;
	}

	// ���݂̃f�v�X�X�e���V���擾
	ID3D11DepthStencilView* pDSV = nullptr;
	auto* pDS = static_cast<D3D11DepthStencil*>(m_pDevice->getDepthStencil(dsID));
	if (pDS) pDSV = pDS->m_dsv.Get();
	m_curDepthStencilID = dsID;

	// �����_�[�^�[�Q�b�g�w��
	m_pDeferredContext->OMSetRenderTargets(num, rtvs.data(), pDSV);
}

void D3D11CommandList::setViewport(const Rect& rect)
{
	D3D11_VIEWPORT d3d11View = {
		rect.left, rect.top, rect.right, rect.bottom, 0.0f, 1.0f
	};
	m_pDeferredContext->RSSetViewports(1, &d3d11View);
}

void D3D11CommandList::setViewport(const Viewport& viewport)
{
	D3D11_VIEWPORT d3d11View = { viewport.left, viewport.top, 
		viewport.right, viewport.bottom, viewport.minDepth, viewport.maxDepth 
	};
	m_pDeferredContext->RSSetViewports(1, &d3d11View);
}

//----- �Q�b�g���� -----


//----- �o�C���h���� -----

void D3D11CommandList::bindGlobalBuffer(const core::ShaderID& shaderID, const std::string& bindName, const core::BufferID& bufferID)
{
	auto pShader = static_cast<D3D11Shader*>(m_pDevice->getShader(shaderID));
	auto* pBuffer = static_cast<D3D11Buffer*>(m_pDevice->getBuffer(bufferID));
	auto type = static_cast<std::size_t>(pBuffer->m_type);

	// �X�e�[�W����
	for (auto stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
	{
		if (!hasStaderStage(pShader->m_desc.m_stages, stage)) continue;
		auto stageIndex = static_cast<std::size_t>(stage);

		auto itr = pShader->m_staticBindData[stageIndex][type].find(bindName.data());
		if (pShader->m_staticBindData[stageIndex][type].end() != itr)
		{
			// GPU�o�b�t�@�X�V
			if (pBuffer->m_isUpdate)
			{
				if (pBuffer->m_desc.usage == core::Usage::DYNAMIC || 
					pBuffer->m_desc.usage == core::Usage::STAGING)
				{
					D3D11_MAPPED_SUBRESOURCE subData = {};
					CHECK_FAILED(m_pDeferredContext->Map(pBuffer->m_pBuffer.Get(), 0,
						D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subData));
					std::memcpy(subData.pData, pBuffer->m_aData.data(), pBuffer->m_aData.size());
					m_pDeferredContext->Unmap(pBuffer->m_pBuffer.Get(), 0);
				}
				else if(pBuffer->m_desc.usage == core::Usage::DEFAULT)
				{
					m_pDeferredContext->UpdateSubresource(pBuffer->m_pBuffer.Get(), 0, nullptr,
						pBuffer->m_aData.data(), 0, 0);
				}
				pBuffer->m_isUpdate = false;
			}

			// CBV,SRV,UAV
			if (pBuffer->m_type == CoreBuffer::BufferType::CBV)
			{
				setCBuffer[stageIndex](m_pDeferredContext.Get(), itr->second.slot,
					1, pBuffer->m_pBuffer.GetAddressOf());
			}
			else if (pBuffer->m_type == CoreBuffer::BufferType::SRV)
			{
				setShaderResource[stageIndex](m_pDeferredContext.Get(), itr->second.slot,
					1, pBuffer->m_pSRV.GetAddressOf());
			}
			else if (pBuffer->m_type == CoreBuffer::BufferType::UAV)
			{
				if (stage == ShaderStage::CS)
				{
					m_pDeferredContext->CSGetUnorderedAccessViews(itr->second.slot,
						1, pBuffer->m_pUAV.GetAddressOf());
				}
			}
			break;
		}
	}
}

void D3D11CommandList::bindGlobalTexture(const core::ShaderID& shaderID, const std::string& bindName, const core::TextureID& textureID)
{
	constexpr auto type = static_cast<std::size_t>(BindType::TEXTURE);
	auto* pShader = static_cast<D3D11Shader*>(m_pDevice->getShader(shaderID));
	auto* pTexture = static_cast<D3D11Texture*>(m_pDevice->getTexture(textureID));

	for (auto stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
	{
		if (!hasStaderStage(pShader->m_desc.m_stages, stage)) continue;
		auto stageIndex = static_cast<std::size_t>(stage);

		auto itr = pShader->m_staticBindData[stageIndex][type].find(bindName.data());
		if (pShader->m_staticBindData[stageIndex][type].end() != itr)
		{
			setTextureResource(itr->second.slot, textureID, stage);
			break;
		}
	}
}

void D3D11CommandList::bindGlobalSampler(const core::ShaderID& shaderID, const std::string& bindName, const core::SamplerState& sampler)
{
	constexpr auto type = static_cast<std::size_t>(BindType::SAMPLER);
	auto* pShader = static_cast<D3D11Shader*>(m_pDevice->getShader(shaderID));
	const auto& samplerState = m_pDevice->m_samplerStates[static_cast<size_t>(sampler)];

	for (auto stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
	{
		if (!hasStaderStage(pShader->m_desc.m_stages, stage)) continue;
		auto stageIndex = static_cast<std::size_t>(stage);

		auto itr = pShader->m_staticBindData[stageIndex][type].find(bindName.data());
		if (pShader->m_staticBindData[stageIndex][type].end() != itr)
		{
			setSamplerResource(itr->second.slot, sampler, stage);
			break;
		}
	}
}


//----- �`�施��

void D3D11CommandList::render(const core::RenderBufferID& renderBufferID, std::uint32_t instanceCount)
{
	auto* cmdList = m_pDeferredContext.Get();

	// �f�[�^�̎擾
	auto* renderBuffer = static_cast<D3D11RenderBuffer*>(m_pDevice->getRenderBuffer(renderBufferID));

	// �|���S���̕`��
	if (renderBuffer->m_indexData.count > 0)
	{
		cmdList->DrawIndexedInstanced(renderBuffer->m_indexData.count, instanceCount, 0, 0, 0);
	}
	else
	{
		cmdList->DrawInstanced(renderBuffer->m_vertexData.count, instanceCount, 0, 0);
	}
}

/// @brief 
/// @param destID �Ώۂ̃����_�[�^�[�Q�b�g
/// @param sourceID 
/// @param matID 
void D3D11CommandList::blit(const RenderBufferID& destID, const TextureID& sourceID, const MaterialID& matID)
{

}

//----- �N���A -----

void D3D11CommandList::clearCommand()
{
	// �R�}���h�̃N���A
}

void D3D11CommandList::clearBackBuffer(const Color& color)
{
	// �o�b�t�@�̃N���A
	float ClearColor[4] = {};
	std::memcpy(ClearColor, &color, sizeof(Color));
	m_pDeferredContext->ClearRenderTargetView(m_pDevice->m_backBufferRTV.Get(), ClearColor);
	m_pDeferredContext->ClearDepthStencilView(m_pDevice->m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3D11CommandList::clearRederTarget(const RenderTargetID& rtID, const Color& color)
{
	// �����_�[�^�[�Q�b�g�擾
	auto* pRT = static_cast<D3D11RenderTarget*>(m_pDevice->getRenderTarget(rtID));
	if (pRT == nullptr) return;

	FLOAT ColorRGBA[4];
	std::memcpy(ColorRGBA, &color, sizeof(Color));

	// �N���A�R�}���h
	m_pDeferredContext->ClearRenderTargetView(pRT->m_rtv.Get(), ColorRGBA);
}

void D3D11CommandList::clearDepthStencil(const DepthStencilID& dsID, float depth, std::uint8_t stencil)
{
	// ���݂̃f�v�X�X�e���V���擾
	auto* pDS = static_cast<D3D11DepthStencil*>(m_pDevice->getDepthStencil(dsID));
	if (pDS == nullptr) return;

	// �N���A�R�}���h
	m_pDeferredContext->ClearDepthStencilView(pDS->m_dsv.Get(), 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
}

//----- �R�s�[ -----

void D3D11CommandList::copyBackBuffer(const core::TextureID& sourceID)
{
	// �e�N�X�`���擾
	auto* pTex = static_cast<D3D11Texture*>(m_pDevice->getTexture(sourceID));
	if (pTex == nullptr) return;

	// ���\�[�X
	auto* pDest = m_pDevice->m_backBufferRT.Get();
	auto* pSource = pTex->m_tex.Get();

	// ���\�[�X�R�s�[
	m_pDeferredContext->CopyResource(pDest, pSource);
}

void D3D11CommandList::copyTexture(const core::TextureID& destID, const core::TextureID& sourceID)
{
	// �e�N�X�`���擾
	auto* pTexA = static_cast<D3D11Texture*>(m_pDevice->getTexture(destID));
	if (pTexA == nullptr) return;
	auto* pTexB = static_cast<D3D11Texture*>(m_pDevice->getTexture(sourceID));
	if (pTexB == nullptr) return;

	// ���\�[�X
	auto* pDest = pTexA->m_tex.Get();
	auto* pSource = pTexB->m_tex.Get();

	// ���\�[�X�R�s�[
	m_pDeferredContext->CopyResource(pDest, pSource);
}

//------------------------------------------------------------------------------
// private methods 
//------------------------------------------------------------------------------

void D3D11CommandList::setCBufferResource(std::uint32_t slot, const core::BufferID& bufferID, core::ShaderStage stage)
{

}

void D3D11CommandList::setTextureResource(std::uint32_t slot, const core::TextureID& textureID, core::ShaderStage stage)
{
	auto stageIndex = static_cast<std::size_t>(stage);

	if (textureID == NONE_TEXTURE_ID)
	{
		// �e�N�X�`���Ȃ�
		ID3D11ShaderResourceView* nullView = nullptr;
		setShaderResource[stageIndex](m_pDeferredContext.Get(), slot, 1, &nullView);
	}
	else
	{
		D3D11Texture* pD3DTex = static_cast<D3D11Texture*>(m_pDevice->getTexture(textureID));
		ID3D11ShaderResourceView* pTex = pD3DTex ? pD3DTex->m_srv.Get() : nullptr;
		setShaderResource[stageIndex](m_pDeferredContext.Get(), slot, 1, &pTex);
	}
}

void D3D11CommandList::setSamplerResource(std::uint32_t slot, core::SamplerState state, core::ShaderStage stage)
{
	auto stageIndex = static_cast<size_t>(stage);
	setSamplers[stageIndex](m_pDeferredContext.Get(), slot, 1, 
		m_pDevice->m_samplerStates[static_cast<size_t>(state)].GetAddressOf());
}