/*****************************************************************//**
 * \file   D3D12_GPUBuffer.h
 * \brief  DirectX12Buffer
 *
 * \author USAMI KOSHI
 * \date   2021/10/20
 *********************************************************************/

#include "D3D12_GPUBuffer.h"
using namespace Core::D3D12;

 /// @brief コンストラクタ
 /// @param device デバイス
 /// @param id バッファID
 /// @param desc バッファDesc
 /// @param data 初期化データ
D3D12GPUBuffer::D3D12GPUBuffer(ID3D12Device* device, const Core::GPUBufferID& id, const Core::GPUBufferDesc& desc, const Core::GPUBufferData* pData) :
	Core::GPUBuffer(id, desc),
	m_pHeap(nullptr),
	m_pBuffer(nullptr),
	m_eState(D3D12_RESOURCE_STATE_GENERIC_READ)
{
	// ヒープの作成
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;		// ピープタイプ
	heapDesc.NumDescriptors = 1;					// バッファ数
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	// シェーダーリソースか
	heapDesc.NodeMask = 0;	// 今は0
	CHECK_FAILED(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_pHeap.GetAddressOf())));

	// ヒーププロパテェの設定
	D3D12_HEAP_PROPERTIES prop = {};
	prop.Type = D3D12_HEAP_TYPE_UPLOAD;					// ピープのタイプ
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;	// ページング設定
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;	// メモリプール設定
	prop.CreationNodeMask = 0;							// 今は0
	prop.VisibleNodeMask = 0;								// 今は0

	// リソースの設定
	D3D12_RESOURCE_DESC d3dDesc = {};
	d3dDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;	// リソースの種別
	d3dDesc.Alignment = 0;								// 配置指定？
	d3dDesc.Height = 1;								// 高さは１
	d3dDesc.DepthOrArraySize = 1;								// 3Dはリソースの深さ、1D,2Dの配列は配列サイズ
	d3dDesc.MipLevels = 1;								// バッファは１
	d3dDesc.Format = DXGI_FORMAT_UNKNOWN;				// バッファはUNKNOWN
	d3dDesc.SampleDesc = DXGI_SAMPLE_DESC{ 1, 0 };			// バッファはデフォルト
	d3dDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;	// とりあえずこれ！
	d3dDesc.Flags = D3D12_RESOURCE_FLAG_NONE;			// CBufferはなし

	// CBufferの場合は256アライメント
	auto width = desc.size * desc.count;
	if (desc.bindFlags & Core::BindFlags::CONSTANT_BUFFER)
	{
		const UINT64 MAX_SIZE = 256;
		d3dDesc.Width = (width / MAX_SIZE + 1) * MAX_SIZE;
	}
	else
	{
		d3dDesc.Width = width;
	}

	// CPUデータ作成
	m_aData.resize(d3dDesc.Width);
	if (pData)
	{
		std::memcpy(m_aData.data(), pData->pInitData, pData->size);
		m_isUpdate = false;
	}

	// リソース生成
	CHECK_FAILED(device->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&d3dDesc,
		m_eState,
		nullptr,
		IID_PPV_ARGS(m_pBuffer.GetAddressOf())
	));

	// 初期値代入
	if (pData)
	{
		void* pBuffer = nullptr;
		CHECK_FAILED(m_pBuffer->Map(0, nullptr, &pBuffer));
		if (pBuffer)
		{
			std::memcpy(pBuffer, pData->pInitData, pData->size);
			m_pBuffer->Unmap(0, nullptr);
		}
	}

	// ビューの作成
	if (desc.bindFlags & Core::BindFlags::CONSTANT_BUFFER)
	{
		// 定数バッファビューの作成
		m_type = BufferType::CBV;
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_pBuffer->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = d3dDesc.Width;
		device->CreateConstantBufferView(&cbvDesc, m_pHeap->GetCPUDescriptorHandleForHeapStart());
	}
	if (desc.bindFlags & Core::BindFlags::SHADER_RESOURCE)
	{
		// シェーダーリソースビューの作成
		m_type = BufferType::SRV;
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.NumElements = desc.count;
		if (desc.miscFlags & Core::MiscFlags::BUFFER_STRUCTURED)
		{
			srvDesc.Buffer.StructureByteStride = desc.size;
			srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
		}
		else if (desc.miscFlags & Core::MiscFlags::BUFFER_ALLOW_RAW_VIEWS)
		{
			srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;
		}
		device->CreateShaderResourceView(m_pBuffer.Get() ,&srvDesc, 
			m_pHeap->GetCPUDescriptorHandleForHeapStart());
	}
	if (desc.bindFlags & Core::BindFlags::UNORDERED_ACCESS)
	{
		// 順不同アクセスビューの作成
		m_type = BufferType::UAV;
		D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;

		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = desc.count;
		if (desc.miscFlags & Core::MiscFlags::BUFFER_STRUCTURED)
		{
			uavDesc.Buffer.StructureByteStride = desc.size;
			uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
			// UAVカウンター
			if(desc.uavFlag == Core::GPUBufferUAVFlag::COUNTER)
			{
				uavDesc.Buffer.CounterOffsetInBytes = 0; // よくわからない…
			}
		}
		else if (desc.miscFlags & Core::MiscFlags::BUFFER_ALLOW_RAW_VIEWS && 
				desc.uavFlag == Core::GPUBufferUAVFlag::RAW)
		{
			uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
			uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
		}

		device->CreateUnorderedAccessView(m_pBuffer.Get(), nullptr, &uavDesc, 
			m_pHeap->GetCPUDescriptorHandleForHeapStart());
	}
}
