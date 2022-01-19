/*****************************************************************//**
 * \file   D3D11_CommandList.h
 * \brief  DirectX11�����_�[�R�}���h���X�g�N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#include "D3D11_CommandList.h"
#include "D3D11_Renderer.h"

#include <RHI/D3D11/D3D11_GraphicsShader.h>
#include <RHI/D3D11/D3D11_GPUBuffer.h>
#include <RHI/D3D11/D3D11_Texture.h>
#include <RHI/D3D11/D3D11_RenderTarget.h>
#include <RHI/D3D11/D3D11_DepthStencil.h>

#include <functional>

using namespace Core::RHI;
using namespace Core::RHI::D3D11;


//------------------------------------------------------------------------------
// local methods 
//------------------------------------------------------------------------------
namespace {
	// CBuffer
	static std::function<void(ID3D11DeviceContext1*, UINT, UINT, ID3D11Buffer* const*)>
		SetCBufferView[static_cast<std::size_t>(ShaderStage::MAX)] = {
		&ID3D11DeviceContext1::VSSetConstantBuffers,
		&ID3D11DeviceContext1::GSSetConstantBuffers,
		&ID3D11DeviceContext1::DSSetConstantBuffers,
		&ID3D11DeviceContext1::HSSetConstantBuffers,
		&ID3D11DeviceContext1::PSSetConstantBuffers, 
		&ID3D11DeviceContext1::CSSetConstantBuffers, 
	};
	// SRV
	static std::function<void(ID3D11DeviceContext1*, UINT, UINT, ID3D11ShaderResourceView* const*)>
		SetShaderResourceView[static_cast<std::size_t>(ShaderStage::MAX)] = {
		&ID3D11DeviceContext1::VSSetShaderResources,
		&ID3D11DeviceContext1::GSSetShaderResources,
		&ID3D11DeviceContext1::DSSetShaderResources,
		&ID3D11DeviceContext1::HSSetShaderResources,
		&ID3D11DeviceContext1::PSSetShaderResources,
		&ID3D11DeviceContext1::CSSetShaderResources,
	};
	// Sampler
	static std::function<void(ID3D11DeviceContext1*, UINT, UINT, ID3D11SamplerState* const*)>
		SetSamplers[static_cast<std::size_t>(ShaderStage::MAX)] = {
		&ID3D11DeviceContext1::VSSetSamplers,
		&ID3D11DeviceContext1::GSSetSamplers,
		&ID3D11DeviceContext1::DSSetSamplers,
		&ID3D11DeviceContext1::HSSetSamplers,
		&ID3D11DeviceContext1::PSSetSamplers, 
		&ID3D11DeviceContext1::CSSetSamplers, 
	};
}

//------------------------------------------------------------------------------
// public methods 
//------------------------------------------------------------------------------

/// @brief �R���X�g���N�^
D3D11CommandList::D3D11CommandList() :
	m_pRenderer(nullptr),
	m_pDevice(nullptr),
	m_pDeferredContext(nullptr),
	m_pCmdList(nullptr)
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

//----- �^�[�Q�b�g�X�e�[�g���� -----

void D3D11CommandList::SetBackBuffer()
{
	m_pDeferredContext->OMSetRenderTargets(1, m_pDevice->m_backBufferRTV.GetAddressOf(),
		m_pDevice->m_depthStencilView.Get());
}

void D3D11CommandList::SetRenderTarget(std::shared_ptr<RenderTarget> pRT)
{
	std::shared_ptr<RenderTarget> pRts[] = { pRT };
	SetRenderTarget(1, pRts);
}

void D3D11CommandList::SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[])
{
	SetRenderTarget(num, pRTs, m_pCurDSV);
}

void D3D11CommandList::SetRenderTarget(std::shared_ptr<RenderTarget> pRT, std::shared_ptr<DepthStencil> pDS)
{
	std::shared_ptr<RenderTarget> pRts[] = { pRT };
	;	SetRenderTarget(1, pRts, pDS);
}

void D3D11CommandList::SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[], std::shared_ptr<DepthStencil> pDS)
{
	// ���S����
	if (num >= MAX_RENDER_TARGET || num <= 0) return;

	// �����_�[�^�[�Q�b�g�擾
	std::vector<ID3D11RenderTargetView*> rtvs;
	rtvs.resize(num);
	for (int i = 0; i < num; ++i)
	{
		if (pRTs[i]) rtvs[i] = static_cast<ID3D11RenderTargetView*>(pRTs[i]->GetRTV());
		else rtvs[i] = nullptr;
	}

	// �f�v�X�X�e���V���擾
	ID3D11DepthStencilView* pDSV = nullptr;
	if (pDS) pDSV = static_cast<ID3D11DepthStencilView*>(pDS->GetDSV());
	m_pCurDSV = pDS;

	// �����_�[�^�[�Q�b�g�w��
	m_pDeferredContext->OMSetRenderTargets(num, rtvs.data(), pDSV);
}

void D3D11CommandList::SetViewport(const Rect& rect)
{
	D3D11_VIEWPORT d3d11View = {
		rect.left, rect.top, rect.right, rect.bottom, 0.0f, 1.0f
	};
	m_pDeferredContext->RSSetViewports(1, &d3d11View);
}

void D3D11CommandList::SetViewport(const Viewport& viewport)
{
	D3D11_VIEWPORT d3d11View = { viewport.left, viewport.top, 
		viewport.right, viewport.bottom, viewport.minDepth, viewport.maxDepth 
	};
	m_pDeferredContext->RSSetViewports(1, &d3d11View);
}

//----- �p�C�v���C���X�e�[�g���� -----

void D3D11CommandList::SetGraphicsPipelineState(std::shared_ptr<GraphicsShader> pShader, const BlendState& bs,
	const RasterizeState& rs, const DepthStencilState& ds)
{
	// �V�F�[�_�[�̎w��
	if (pShader)
	{
		auto d3dShader = std::static_pointer_cast<D3D11GraphicsShader>(pShader);
		// �V�F�[�_�[�f�[�^�w��
		if (d3dShader->vs) m_pDeferredContext->VSSetShader(d3dShader->vs, nullptr, 0);
		if (d3dShader->gs) m_pDeferredContext->GSSetShader(d3dShader->gs, nullptr, 0);
		if (d3dShader->ds) m_pDeferredContext->DSSetShader(d3dShader->ds, nullptr, 0);
		if (d3dShader->hs) m_pDeferredContext->HSSetShader(d3dShader->hs, nullptr, 0);
		if (d3dShader->ps) m_pDeferredContext->PSSetShader(d3dShader->ps, nullptr, 0);
		// ���̓��C�A�E�g�w��
		m_pDeferredContext->IASetInputLayout(d3dShader->m_pInputLayout.Get());
		// �g�p���\�[�X�֒ǉ�
		m_usedShaderList.push_back(pShader);
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

void D3D11CommandList::SetComputePipelineState()
{

}

//----- ���\�[�X���� -----

void D3D11CommandList::SetConstantBuffer(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal)
{
	auto stageIndex = static_cast<std::size_t>(stage);
	ID3D11Buffer* pView = nullptr;

	// ���\�[�X�̍X�V
	if (pResource)
	{
		UpdateSubResource(pResource);
		pView = static_cast<ID3D11Buffer*>(pResource->GetCBV());
	}

	// �O���[�o�����\�[�X��
	if (isGlobal)
	{
		auto& resources = resourceLayout.m_globalResource[static_cast<std::size_t>(ShaderResourceType::CBV)];
		auto itr = resources.find(name.data());
		if (resources.end() != itr)
		{
			SetCBufferView[stageIndex](m_pDeferredContext.Get(), itr->second.slot, 1, &pView);
		}
	}
	else
	{
		auto& resources = resourceLayout.m_localResource[static_cast<std::size_t>(ShaderResourceType::CBV)];
		auto itr = resources.find(name.data());
		if (resources.end() != itr)
		{
			SetCBufferView[stageIndex](m_pDeferredContext.Get(), itr->second.slot, 1, &pView);
		}
	}
}

void D3D11CommandList::SetShaderResource(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal)
{
	auto stageIndex = static_cast<std::size_t>(stage);
	ID3D11ShaderResourceView* pView = nullptr;

	// ���\�[�X�̍X�V
	if (pResource)
	{
		UpdateSubResource(pResource);
		pView = static_cast<ID3D11ShaderResourceView*>(pResource->GetSRV());
	}

	// �O���[�o�����\�[�X��
	if (isGlobal)
	{
		auto& resources = resourceLayout.m_globalResource[static_cast<std::size_t>(ShaderResourceType::SRV)];
		auto itr = resources.find(name.data());
		if (resources.end() != itr)
		{
			SetShaderResourceView[stageIndex](m_pDeferredContext.Get(), itr->second.slot, 1, &pView);
		}
	}
	else
	{
		auto& resources = resourceLayout.m_localResource[static_cast<std::size_t>(ShaderResourceType::SRV)];
		auto itr = resources.find(name.data());
		if (resources.end() != itr)
		{
			SetShaderResourceView[stageIndex](m_pDeferredContext.Get(), itr->second.slot, 1, &pView);
		}
	}
}

void D3D11CommandList::SetUnorderedAccess(ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal)
{
	ID3D11UnorderedAccessView* pView = nullptr;

	// ���\�[�X�̍X�V
	if (pResource)
	{
		UpdateSubResource(pResource);
		pView = static_cast<ID3D11UnorderedAccessView*>(pResource->GetUAV());
	}

	// �O���[�o�����\�[�X��
	if (isGlobal)
	{
		auto& resources = resourceLayout.m_globalResource[static_cast<std::size_t>(ShaderResourceType::UAV)];
		auto itr = resources.find(name.data());
		if (resources.end() != itr)
		{
			m_pDeferredContext->CSSetUnorderedAccessViews(itr->second.slot, 1, &pView, nullptr);
		}
	}
	else
	{
		auto& resources = resourceLayout.m_localResource[static_cast<std::size_t>(ShaderResourceType::UAV)];
		auto itr = resources.find(name.data());
		if (resources.end() != itr)
		{
			m_pDeferredContext->CSSetUnorderedAccessViews(itr->second.slot, 1, &pView, nullptr);
		}
	}
}

void D3D11CommandList::SetSampler(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, SamplerState samplerState, bool isGlobal)
{
	auto stageIndex = static_cast<std::size_t>(stage);
	// �O���[�o�����\�[�X��
	if (isGlobal)
	{
		auto& resources = resourceLayout.m_globalResource[static_cast<std::size_t>(ShaderResourceType::SAMPLER)];
		auto itr = resources.find(name.data());
		if (resources.end() != itr)
		{
			SetSamplers[stageIndex](m_pDeferredContext.Get(), itr->second.slot,
				1, m_pDevice->m_samplerStates[static_cast<size_t>(samplerState)].GetAddressOf());
		}
	}
	else
	{
		auto& resources = resourceLayout.m_localResource[static_cast<std::size_t>(ShaderResourceType::SAMPLER)];
		auto itr = resources.find(name.data());
		if (resources.end() != itr)
		{
			SetSamplers[stageIndex](m_pDeferredContext.Get(), itr->second.slot,
				1, m_pDevice->m_samplerStates[static_cast<size_t>(samplerState)].GetAddressOf());
		}
	}
}

//----- �W�I���g���[�X�e�[�g���� -----

void D3D11CommandList::SetVertexBuffer(std::shared_ptr<GPUBuffer> pVertexBuffer, const std::uint32_t offset)
{
	ID3D11Buffer* pBuffer = nullptr;
	UINT strides = 0;

	// ���\�[�X�X�V
	if (pVertexBuffer)
	{
		UpdateSubResource(pVertexBuffer);
		strides = pVertexBuffer->GetDesc().buffer.size;
		pBuffer = static_cast<ID3D11Buffer*>(pVertexBuffer->GetResource());
	}

	// ���_�o�b�t�@�w��
	m_pDeferredContext->IASetVertexBuffers(0, 1, &pBuffer, &strides, &offset);

}

void D3D11CommandList::SetIndexBuffer(std::shared_ptr<GPUBuffer> pIndexBuffer, const std::uint32_t offset)
{
	ID3D11Buffer* pBuffer = nullptr;
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;

	// ���\�[�X�X�V
	if (pIndexBuffer)
	{
		UpdateSubResource(pIndexBuffer);
		pBuffer = static_cast<ID3D11Buffer*>(pIndexBuffer->GetResource());
		// �C���f�b�N�X�t�H�[�}�b�g�I��
		switch (pIndexBuffer->GetDesc().buffer.size)
		{
		case 2:
			format = DXGI_FORMAT_R16_UINT;
			break;
		case 4:
			format = DXGI_FORMAT_R32_UINT;
			break;
		}
	}

	// �C���f�b�N�X�o�b�t�@�w��
	m_pDeferredContext->IASetIndexBuffer(pBuffer, format, offset);

}

void D3D11CommandList::SetPrimitiveTopology(PrimitiveTopology primitiveTopology)
{
	m_pDeferredContext->IASetPrimitiveTopology(GetD3D11PrimitiveTopology(primitiveTopology));
}


//----- �`��E���s���� -----

void D3D11CommandList::DrawInstanced(std::uint32_t VertexCountPerInstance, std::uint32_t InstanceCount,
	std::uint32_t StartVertexLocation, std::uint32_t StartInstanceLocation)
{
	m_pDeferredContext->DrawInstanced(VertexCountPerInstance, InstanceCount,
		StartVertexLocation, StartInstanceLocation);
}

void D3D11CommandList::DrawIndexedInstanced(std::uint32_t IndexCountPerInstance, std::uint32_t InstanceCount,
	std::uint32_t StartIndexLocation, std::int32_t  BaseVertexLocation, std::uint32_t StartInstanceLocation)
{
	m_pDeferredContext->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, 
		StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void D3D11CommandList::ExecuteIndirect()
{

}

void D3D11CommandList::Dispatch()
{
	//m_pDeferredContext->Dispatch();
}

//----- �N���A -----

void D3D11CommandList::ClearCommand()
{
	// �R�}���h�̃N���A
	CHECK_FAILED(m_pCmdList.Reset());

	// �g�p���\�[�X���X�g�̃N���A
	m_pCurDSV.reset();
	m_usedResourceList.clear();
	m_usedShaderList.clear();
}

void D3D11CommandList::ClearBackBuffer(const Color& color)
{
	// �o�b�t�@�̃N���A
	float ClearColor[4] = {};
	std::memcpy(ClearColor, &color, sizeof(Color));
	m_pDeferredContext->ClearRenderTargetView(m_pDevice->m_backBufferRTV.Get(), ClearColor);
	m_pDeferredContext->ClearDepthStencilView(m_pDevice->m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3D11CommandList::ClearRederTarget(std::shared_ptr<RenderTarget> pRT, const Color& color)
{
	FLOAT ColorRGBA[4];
	std::memcpy(ColorRGBA, &color, sizeof(Color));
	// �N���A�R�}���h
	m_pDeferredContext->ClearRenderTargetView(static_cast<ID3D11RenderTargetView*>(pRT->GetRTV()), ColorRGBA);
}

void D3D11CommandList::ClearDepthStencil(std::shared_ptr<DepthStencil> pDS, float depth, std::uint8_t stencil)
{
	// �N���A�R�}���h
	m_pDeferredContext->ClearDepthStencilView(static_cast<ID3D11DepthStencilView*>(pDS->GetDSV()),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
}

//----- �R�s�[ -----

void D3D11CommandList::CopyToBackBuffer(std::shared_ptr<Resource> pSource)
{
	// ���\�[�X�R�s�[
	m_pDeferredContext->CopyResource(m_pDevice->m_backBufferRT.Get(), 
		static_cast<ID3D11Resource*>(pSource->GetResource()));
}

void D3D11CommandList::CopyFromBackBuffer(std::shared_ptr<Resource> pDest)
{
	// ���\�[�X�R�s�[
	m_pDeferredContext->CopyResource(static_cast<ID3D11Resource*>(pDest->GetResource()),
		m_pDevice->m_backBufferRT.Get());
}

void D3D11CommandList::CopyResource(std::shared_ptr<Resource> pDest, std::shared_ptr<Resource> pSource)
{
	// ���\�[�X�R�s�[
	m_pDeferredContext->CopyResource(static_cast<ID3D11Resource*>(pDest->GetResource()),
		static_cast<ID3D11Resource*>(pSource->GetResource()));
}


//------------------------------------------------------------------------------
// private methods 
//------------------------------------------------------------------------------

void D3D11CommandList::UpdateSubResource(std::shared_ptr<Resource> pResource)
{
	// �g�p���\�[�X�֊i�[
	m_usedResourceList.push_back(pResource);

	// ���\�[�X�̍X�V
	if (pResource->GetDirty())
	{
		auto pD3DResource = static_cast<ID3D11Resource*>(pResource->GetResource());
		auto desc = pResource->GetDesc();

		if (desc.usage == Usage::DYNAMIC ||
			desc.usage == Usage::STAGING)
		{
			D3D11_MAPPED_SUBRESOURCE subData = {};
			CHECK_FAILED(m_pRenderer->m_d3dContext->Map(pD3DResource, 0,
				D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subData));
			std::memcpy(subData.pData, pResource->GetData(), pResource->GetDataSize());
			m_pRenderer->m_d3dContext->Unmap(pD3DResource, 0);
		}
		else if (desc.usage == Usage::DEFAULT)
		{
			m_pDeferredContext->UpdateSubresource(pD3DResource, 0, nullptr,
				pResource->GetData(), 0, 0);
		}
		pResource->ReSetDirty();
	}
}
