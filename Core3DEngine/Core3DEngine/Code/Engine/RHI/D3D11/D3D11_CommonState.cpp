/*****************************************************************//**
 * \file   D3D11_CommonState.h
 * \brief  DirectX11共通ステイト
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#include "D3D11_CommonState.h"

namespace Core::RHI::D3D11
{
	/// @brief D3D11のリソース使用識別取得
	/// @param usage リソース使用識別
	/// @return D3D11リソース使用識別
	D3D11_USAGE GetD3D11Usage(Usage usage) {
		switch (usage) {
		case Usage::STATIC:  return D3D11_USAGE_IMMUTABLE;
		case Usage::DEFAULT: return D3D11_USAGE_DEFAULT;
		case Usage::DYNAMIC: return D3D11_USAGE_DYNAMIC;
		case Usage::STAGING: return D3D11_USAGE_STAGING;
		default:             return D3D11_USAGE_DEFAULT;
		}
	}

	/// @brief D3D11のバインドフラグ取得
	/// @param flags バインドフラグ
	/// @return 符号なし整数型バインドフラグ
	UINT32 GetD3D11BindFlags(UINT flags) {
		UINT32 d3d11BindFlags = 0;

		d3d11BindFlags = d3d11BindFlags | ((flags & BindFlags::VERTEX_BUFFER) ? D3D11_BIND_VERTEX_BUFFER : 0);
		d3d11BindFlags = d3d11BindFlags | ((flags & BindFlags::INDEX_BUFFER) ? D3D11_BIND_INDEX_BUFFER : 0);
		d3d11BindFlags = d3d11BindFlags | ((flags & BindFlags::CONSTANT_BUFFER) ? D3D11_BIND_CONSTANT_BUFFER : 0);
		d3d11BindFlags = d3d11BindFlags | ((flags & BindFlags::SHADER_RESOURCE) ? D3D11_BIND_SHADER_RESOURCE : 0);
		d3d11BindFlags = d3d11BindFlags | ((flags & BindFlags::STREAM_OUTPUT) ? D3D11_BIND_STREAM_OUTPUT : 0);
		d3d11BindFlags = d3d11BindFlags | ((flags & BindFlags::RENDER_TARGET) ? D3D11_BIND_RENDER_TARGET : 0);
		d3d11BindFlags = d3d11BindFlags | ((flags & BindFlags::DEPTH_STENCIL) ? D3D11_BIND_DEPTH_STENCIL : 0);
		d3d11BindFlags = d3d11BindFlags | ((flags & BindFlags::UNORDERED_ACCESS) ? D3D11_BIND_UNORDERED_ACCESS : 0);

		return d3d11BindFlags;
	}

	/// @brief D3D11のCPUアクセスフラグ取得
	/// @param flags CPUアクセスフラグ
	/// @return 符号なし整数型CPUアクセスフラグ
	UINT32 GetD3D11CPUAccessFlags(UINT flags) {
		UINT32 d3d11CPUAccessFlags = 0;

		d3d11CPUAccessFlags |= (flags & CPUAccessFlags::READ) ? D3D11_CPU_ACCESS_READ : 0;
		d3d11CPUAccessFlags |= (flags & CPUAccessFlags::WRITE) ? D3D11_CPU_ACCESS_WRITE : 0;

		return d3d11CPUAccessFlags;
	}

	/// @brief D3D11のバッファフラグ取得
	/// @param flags バッファフラグ
	/// @return 符号なし整数型バッファフラグ
	UINT32 GetD3D11MiscFlags(UINT flags) {
		UINT32 d3d11MiscFlags = 0;

		d3d11MiscFlags |= (flags & MiscFlags::GENERATE_MIPS) ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;
		d3d11MiscFlags |= (flags & MiscFlags::TEXTURECUBE) ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0;
		d3d11MiscFlags |= (flags & MiscFlags::DRAWINDIRECT_ARGS) ? D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS : 0;
		d3d11MiscFlags |= (flags & MiscFlags::BUFFER_ALLOW_RAW_VIEWS) ? D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS : 0;
		d3d11MiscFlags |= (flags & MiscFlags::BUFFER_STRUCTURED) ? D3D11_RESOURCE_MISC_BUFFER_STRUCTURED : 0;
		d3d11MiscFlags |= (flags & MiscFlags::RESOURCE_CLAMP) ? D3D11_RESOURCE_MISC_RESOURCE_CLAMP : 0;
		d3d11MiscFlags |= (flags & MiscFlags::BUFFER_STRUCTURED) ? D3D11_RESOURCE_MISC_BUFFER_STRUCTURED : 0;
		d3d11MiscFlags |= (flags & MiscFlags::SHARED_KEYEDMUTEX) ? D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX : 0;
		d3d11MiscFlags |= (flags & MiscFlags::TILE_POOL) ? D3D11_RESOURCE_MISC_TILE_POOL : 0;
		d3d11MiscFlags |= (flags & MiscFlags::TILED) ? D3D11_RESOURCE_MISC_TILED : 0;

		return d3d11MiscFlags;
	}

	/// @brief D3D11のプリミティブトポロジー取得
	/// @param topology プリミティブトポロジー
	/// @return D3D11プリミティブトポロジー
	D3D11_PRIMITIVE_TOPOLOGY GetD3D11PrimitiveTopology(PrimitiveTopology topology) {
		static D3D11_PRIMITIVE_TOPOLOGY d3dTopologies[static_cast<size_t>(PrimitiveTopology::MAX)] = {
			D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
			D3D_PRIMITIVE_TOPOLOGY_LINELIST,
			D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
			D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST
		};

		return d3dTopologies[static_cast<size_t>(topology)];
	}

	/// @brief DXGIのテクスチャフォーマット取得
	/// @param format テクスチャフォーマット
	/// @return DXGIフォーマット
	DXGI_FORMAT GetDXGIFormat(TextureFormat format) {
		static DXGI_FORMAT d3dDXGIFormat[static_cast<size_t>(TextureFormat::MAX)] = {
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
	DXGI_FORMAT getTypeLessToDSVFormat(TextureFormat format)
	{
		auto f = GetDXGIFormat(format);
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
			return GetDXGIFormat(format);
		}
	}

	/// @brief TypeLessフォーマットをSRVフォーマットに変換して返す
	/// @param format TypeLessフォーマット
	/// @return SRVフォーマット or そのまま
	DXGI_FORMAT getTypeLessToSRVFormat(TextureFormat format)
	{
		auto f = GetDXGIFormat(format);
		if (f == DXGI_FORMAT_R32_TYPELESS)
		{
			return DXGI_FORMAT_R32_FLOAT;
		}
		else
		{
			return GetDXGIFormat(format);
		}
	}
}
