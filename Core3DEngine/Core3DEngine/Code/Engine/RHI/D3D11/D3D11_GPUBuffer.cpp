/*****************************************************************//**
 * \file   D3D11_GPUBuffer.h
 * \brief  DirectX11バッファー
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_GPUBuffer.h"
#include <RHI\D3D11\D3D11_CommonState.h>

using namespace Core::RHI::D3D11;

 /// @brief コンストラクタ
 /// @param device デバイス
 /// @param desc バッファDesc
 /// @param data 初期化データ
D3D11GPUBuffer::D3D11GPUBuffer(ID3D11Device1* device, const ResourceDesc& desc, const ResourceData* pData) :
	GPUBuffer(desc)
{
	// バッファの初期化
	D3D11_BUFFER_DESC d3dDesc = {};
	d3dDesc.ByteWidth = desc.buffer.size * desc.buffer.count;//Max:D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT
	d3dDesc.Usage = GetD3D11Usage(desc.usage);
	d3dDesc.BindFlags = GetD3D11BindFlags(desc.bindFlags);
	d3dDesc.CPUAccessFlags = GetD3D11CPUAccessFlags(desc.cpuAccessFlags);
	d3dDesc.MiscFlags = GetD3D11MiscFlags(desc.miscFlags);

	// CPUデータ作成
	m_aData.resize(d3dDesc.ByteWidth);
	if (pData)
	{
		std::memcpy(m_aData.data(), pData->pInitData, pData->size);
		m_isDirty = false;
	}

	// 構造体バッファ
	if (desc.miscFlags & MiscFlags::BUFFER_STRUCTURED)
	{
		d3dDesc.StructureByteStride = desc.buffer.size;
	}

	// 初期化データ
	if (pData)
	{
		// 初期化データ
		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = pData->pInitData;
		initData.SysMemPitch = static_cast<UINT>(pData->size);
		// 生成
		CHECK_FAILED(device->CreateBuffer(&d3dDesc, &initData, m_pBuffer.GetAddressOf()));
	}
	else
	{
		// 生成
		CHECK_FAILED(device->CreateBuffer(&d3dDesc, nullptr, m_pBuffer.GetAddressOf()));
	}

	// ビューの作成
	if (desc.bindFlags & BindFlags::SHADER_RESOURCE)
	{
		// シェーダーリソースビュー
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;

		// RAW
		if (desc.miscFlags & MiscFlags::BUFFER_ALLOW_RAW_VIEWS)
		{
			// ByteAddressBuffer
			srvDesc.BufferEx.FirstElement = 0;
			srvDesc.BufferEx.NumElements = desc.buffer.count;
			srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		}
		else
		{
			// StructuredBuffer
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = desc.buffer.count;
		}

		CHECK_FAILED(device->CreateShaderResourceView(m_pBuffer.Get(), &srvDesc, m_pSRV.GetAddressOf()));
	}
	if (desc.bindFlags & BindFlags::UNORDERED_ACCESS)
	{
		// 順不同アクセスビュー
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = desc.buffer.count;
		// RAW
		if (desc.miscFlags & MiscFlags::BUFFER_ALLOW_RAW_VIEWS && 
			desc.uavFlag == UAVFlag::RAW)
		{
			uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		}
		else if(desc.miscFlags & MiscFlags::BUFFER_STRUCTURED && 
			desc.uavFlag == UAVFlag::APPEND)
		{
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;
		}
		else if (desc.uavFlag == UAVFlag::COUNTER)
		{
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;
		}

		CHECK_FAILED(device->CreateUnorderedAccessView(m_pBuffer.Get(), &uavDesc, m_pUAV.GetAddressOf()));
	}
}
