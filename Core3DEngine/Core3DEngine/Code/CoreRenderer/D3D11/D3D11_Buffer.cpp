/*****************************************************************//**
 * \file   D3D11_Buffer.h
 * \brief  DirectX11バッファー
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_Buffer.h"
#include "D3D11_CommonState.h"
using namespace d3d11;

 /// @brief コンストラクタ
 /// @param device デバイス
 /// @param id バッファID
 /// @param desc バッファDesc
 /// @param data 初期化データ
D3D11Buffer::D3D11Buffer(ID3D11Device1* device, const core::BufferID& id, const core::BufferDesc& desc, const core::BufferData* pData) :
	core::CoreBuffer(id, desc)
{
	// バッファの初期化
	D3D11_BUFFER_DESC d3dDesc = {};
	d3dDesc.ByteWidth = desc.size * desc.count;//Max:D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT
	d3dDesc.Usage = d3d11::getD3D11Usage(desc.usage);
	d3dDesc.BindFlags = d3d11::getD3D11BindFlags(desc.bindFlags);
	d3dDesc.CPUAccessFlags = d3d11::getD3D11CPUAccessFlags(desc.cpuAccessFlags);
	d3dDesc.MiscFlags = d3d11::getD3D11MiscFlags(desc.miscFlags);

	// CPUデータ作成
	m_aData.resize(d3dDesc.ByteWidth);
	if (pData)
	{
		std::memcpy(m_aData.data(), pData->pInitData, pData->size);
		m_isUpdate = false;
	}

	// コンスタントバッファ
	if (desc.bindFlags & core::BindFlags::CONSTANT_BUFFER)
	{
		m_type = BufferType::CBV;
	}

	// 構造体バッファ
	if (desc.miscFlags & core::MiscFlags::BUFFER_STRUCTURED)
	{
		d3dDesc.StructureByteStride = desc.size;
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
	if (desc.bindFlags & core::BindFlags::SHADER_RESOURCE)
	{
		// シェーダーリソースビュー
		m_type = BufferType::SRV;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;

		// RAW
		if (desc.miscFlags & core::MiscFlags::BUFFER_ALLOW_RAW_VIEWS)
		{
			// ByteAddressBuffer
			srvDesc.BufferEx.FirstElement = 0;
			srvDesc.BufferEx.NumElements = desc.count;
			srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		}
		else
		{
			// StructuredBuffer
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = desc.count;
		}

		CHECK_FAILED(device->CreateShaderResourceView(m_pBuffer.Get(), &srvDesc, m_pSRV.GetAddressOf()));
	}
	if (desc.bindFlags & core::BindFlags::UNORDERED_ACCESS)
	{
		// 順不同アクセスビュー
		m_type = BufferType::UAV;
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = desc.count;
		// RAW
		if (desc.miscFlags & core::MiscFlags::BUFFER_ALLOW_RAW_VIEWS && 
			desc.uavFlag == core::BufferUAVFlag::RAW)
		{
			uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		}
		else if(desc.miscFlags & core::MiscFlags::BUFFER_STRUCTURED && 
			desc.uavFlag == core::BufferUAVFlag::APPEND)
		{
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;
		}
		else if (desc.uavFlag == core::BufferUAVFlag::COUNTER)
		{
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;
		}

		CHECK_FAILED(device->CreateUnorderedAccessView(m_pBuffer.Get(), &uavDesc, m_pUAV.GetAddressOf()));
	}
}
