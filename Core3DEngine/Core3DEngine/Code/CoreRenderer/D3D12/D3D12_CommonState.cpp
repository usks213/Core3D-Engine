/*****************************************************************//**
 * \file   D3D12_CommonState.h
 * \brief  DirectX12共通ステート
 *
 * \author USAMI KOSHI
 * \date   2021/10/13
 *********************************************************************/

#include "D3D12_CommonState.h"
using namespace d3d12;


/// @brief リソースフラグ取得
/// @param flags フラグ
/// @return D3D12リソースフラグ
D3D12_RESOURCE_FLAGS d3d12::getD3D12ResourceFlags(UINT bindFlags)
{
	if (bindFlags & core::BindFlags::RENDER_TARGET) return D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	else if (bindFlags & core::BindFlags::DEPTH_STENCIL) return D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	else if (bindFlags & core::BindFlags::UNORDERED_ACCESS) return D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	else return D3D12_RESOURCE_FLAG_NONE;
}

/// @brief ヒープフラグ取得
/// @param flags フラグ
/// @return D3D12ヒープフラグ
D3D12_DESCRIPTOR_HEAP_FLAGS d3d12::getD3D12HeapFlags(UINT bindFlags)
{
	if (bindFlags & core::BindFlags::SHADER_RESOURCE) return D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	else return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
}

/// @brief D3D12のプリミティブトポロジー取得
/// @param topology プリミティブトポロジー
/// @return D3D12プリミティブトポロジー
D3D12_PRIMITIVE_TOPOLOGY d3d12::getD3D12PrimitiveTopology(core::PrimitiveTopology topology) {
	static D3D12_PRIMITIVE_TOPOLOGY d3dTopologies[static_cast<size_t>(core::PrimitiveTopology::MAX)] = {
		D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
		//D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST
	};

	return d3dTopologies[static_cast<size_t>(topology)];
}

/// @brief DXGIのテクスチャフォーマット取得
/// @param format テクスチャフォーマット
/// @return DXGIフォーマット
DXGI_FORMAT d3d12::getDXGIFormat(core::TextureFormat format) {
	static DXGI_FORMAT d3dDXGIFormat[static_cast<size_t>(core::TextureFormat::MAX)] = {
	DXGI_FORMAT_UNKNOWN, // 不明

	DXGI_FORMAT_R32G32B32A32_TYPELESS,
	DXGI_FORMAT_R32G32B32A32_FLOAT,
	DXGI_FORMAT_R32G32B32A32_UINT,
	DXGI_FORMAT_R32G32B32A32_SINT,

	DXGI_FORMAT_R32G32B32_TYPELESS,
	DXGI_FORMAT_R32G32B32_FLOAT,
	DXGI_FORMAT_R32G32B32_UINT,
	DXGI_FORMAT_R32G32B32_SINT,

	DXGI_FORMAT_R16G16B16A16_TYPELESS,
	DXGI_FORMAT_R16G16B16A16_FLOAT,
	DXGI_FORMAT_R16G16B16A16_UNORM,
	DXGI_FORMAT_R16G16B16A16_UINT,
	DXGI_FORMAT_R16G16B16A16_SNORM,
	DXGI_FORMAT_R16G16B16A16_SINT,

	DXGI_FORMAT_R32G32_TYPELESS,
	DXGI_FORMAT_R32G32_FLOAT,
	DXGI_FORMAT_R32G32_UINT,
	DXGI_FORMAT_R32G32_SINT,

	DXGI_FORMAT_R11G11B10_FLOAT,

	DXGI_FORMAT_R8G8B8A8_TYPELESS,
	DXGI_FORMAT_R8G8B8A8_UNORM,
	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
	DXGI_FORMAT_R8G8B8A8_UINT,
	DXGI_FORMAT_R8G8B8A8_SNORM,
	DXGI_FORMAT_R8G8B8A8_SINT,

	DXGI_FORMAT_R16G16_TYPELESS,
	DXGI_FORMAT_R16G16_FLOAT,
	DXGI_FORMAT_R16G16_UNORM,
	DXGI_FORMAT_R16G16_UINT,
	DXGI_FORMAT_R16G16_SNORM,
	DXGI_FORMAT_R16G16_SINT,

	DXGI_FORMAT_R32_TYPELESS,
	DXGI_FORMAT_D32_FLOAT,
	DXGI_FORMAT_R32_FLOAT,
	DXGI_FORMAT_R32_UINT,
	DXGI_FORMAT_R32_SINT,

	DXGI_FORMAT_R24G8_TYPELESS,
	DXGI_FORMAT_D24_UNORM_S8_UINT,

	DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT,

	DXGI_FORMAT_R8G8_TYPELESS,
	DXGI_FORMAT_R8G8_UNORM,
	DXGI_FORMAT_R8G8_UINT,
	DXGI_FORMAT_R8G8_SNORM,
	DXGI_FORMAT_R8G8_SINT,

	DXGI_FORMAT_R16_TYPELESS,
	DXGI_FORMAT_R16_FLOAT,
	DXGI_FORMAT_D16_UNORM,
	DXGI_FORMAT_R16_UNORM,
	DXGI_FORMAT_R16_UINT,
	DXGI_FORMAT_R16_SNORM,
	DXGI_FORMAT_R16_SINT,

	DXGI_FORMAT_R8_TYPELESS,
	DXGI_FORMAT_R8_UNORM,
	DXGI_FORMAT_R8_UINT,
	DXGI_FORMAT_R8_SNORM,
	DXGI_FORMAT_R8_SINT,

	// ブロック圧縮テクスチャ
	DXGI_FORMAT_BC1_TYPELESS,
	DXGI_FORMAT_BC1_UNORM,
	DXGI_FORMAT_BC1_UNORM_SRGB,
	DXGI_FORMAT_BC2_TYPELESS,
	DXGI_FORMAT_BC2_UNORM,
	DXGI_FORMAT_BC2_UNORM_SRGB,
	DXGI_FORMAT_BC3_TYPELESS,
	DXGI_FORMAT_BC3_UNORM,
	DXGI_FORMAT_BC3_UNORM_SRGB,
	DXGI_FORMAT_BC4_TYPELESS,
	DXGI_FORMAT_BC4_UNORM,
	DXGI_FORMAT_BC4_SNORM,
	DXGI_FORMAT_BC5_TYPELESS,
	DXGI_FORMAT_BC5_UNORM,
	DXGI_FORMAT_BC5_SNORM,
	DXGI_FORMAT_BC6H_TYPELESS,
	DXGI_FORMAT_BC6H_UF16,
	DXGI_FORMAT_BC6H_SF16,
	DXGI_FORMAT_BC7_TYPELESS,
	DXGI_FORMAT_BC7_UNORM,
	DXGI_FORMAT_BC7_UNORM_SRGB,
	};

	return d3dDXGIFormat[static_cast<size_t>(format)];
}

/// @brief TypeLessフォーマットをDSVフォーマットに変換して返す
/// @param format TypeLessフォーマット
/// @return DSVフォーマット or そのまま
DXGI_FORMAT d3d12::getTypeLessToDSVFormat(core::TextureFormat format)
{
	auto f = getDXGIFormat(format);
	if (f == DXGI_FORMAT_R32_TYPELESS)
	{
		return DXGI_FORMAT_D32_FLOAT;
	}
	else if (f == DXGI_FORMAT_R24G8_TYPELESS)
	{
		return DXGI_FORMAT_D24_UNORM_S8_UINT;
	}
	else if (f == DXGI_FORMAT_R24_UNORM_X8_TYPELESS)
	{
		return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
	}
	else
	{
		return getDXGIFormat(format);
	}
}

/// @brief TypeLessフォーマットをSRVフォーマットに変換して返す
/// @param format TypeLessフォーマット
/// @return SRVフォーマット or そのまま
DXGI_FORMAT d3d12::getTypeLessToSRVFormat(core::TextureFormat format)
{
	auto f = getDXGIFormat(format);
	if (f == DXGI_FORMAT_R32_TYPELESS)
	{
		return DXGI_FORMAT_R32_FLOAT;
	}
	else
	{
		return getDXGIFormat(format);
	}
}
