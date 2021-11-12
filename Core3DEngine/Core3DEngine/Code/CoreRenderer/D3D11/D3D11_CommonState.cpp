/*****************************************************************//**
 * \file   D3D11_CommonState.h
 * \brief  DirectX11���ʃX�e�C�g
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#include "D3D11_CommonState.h"
using namespace d3d11;


/// @brief D3D11�̃��\�[�X�g�p���ʎ擾
/// @param usage ���\�[�X�g�p����
/// @return D3D11���\�[�X�g�p����
D3D11_USAGE d3d11::getD3D11Usage(core::Usage usage) {
	switch (usage) {
	case core::Usage::STATIC:  return D3D11_USAGE_IMMUTABLE;
	case core::Usage::DEFAULT: return D3D11_USAGE_DEFAULT;
	case core::Usage::DYNAMIC: return D3D11_USAGE_DYNAMIC;
	case core::Usage::STAGING: return D3D11_USAGE_STAGING;
	default:             return D3D11_USAGE_DEFAULT;
	}
}

/// @brief D3D11�̃o�C���h�t���O�擾
/// @param flags �o�C���h�t���O
/// @return �����Ȃ������^�o�C���h�t���O
UINT32 d3d11::getD3D11BindFlags(UINT flags) {
	UINT32 d3d11BindFlags = 0;

	d3d11BindFlags = d3d11BindFlags | ((flags & core::BindFlags::VERTEX_BUFFER) ? D3D11_BIND_VERTEX_BUFFER : 0);
	d3d11BindFlags = d3d11BindFlags | ((flags & core::BindFlags::INDEX_BUFFER) ? D3D11_BIND_INDEX_BUFFER : 0);
	d3d11BindFlags = d3d11BindFlags | ((flags & core::BindFlags::CONSTANT_BUFFER) ? D3D11_BIND_CONSTANT_BUFFER : 0);
	d3d11BindFlags = d3d11BindFlags | ((flags & core::BindFlags::SHADER_RESOURCE) ? D3D11_BIND_SHADER_RESOURCE : 0);
	d3d11BindFlags = d3d11BindFlags | ((flags & core::BindFlags::STREAM_OUTPUT) ? D3D11_BIND_STREAM_OUTPUT : 0);
	d3d11BindFlags = d3d11BindFlags | ((flags & core::BindFlags::RENDER_TARGET) ? D3D11_BIND_RENDER_TARGET : 0);
	d3d11BindFlags = d3d11BindFlags | ((flags & core::BindFlags::DEPTH_STENCIL) ? D3D11_BIND_DEPTH_STENCIL : 0);
	d3d11BindFlags = d3d11BindFlags | ((flags & core::BindFlags::UNORDERED_ACCESS) ? D3D11_BIND_UNORDERED_ACCESS : 0);

	return d3d11BindFlags;
}

/// @brief D3D11��CPU�A�N�Z�X�t���O�擾
/// @param flags CPU�A�N�Z�X�t���O
/// @return �����Ȃ������^CPU�A�N�Z�X�t���O
UINT32 d3d11::getD3D11CPUAccessFlags(UINT flags) {
	UINT32 d3d11CPUAccessFlags = 0;

	d3d11CPUAccessFlags |= (flags & core::CPUAccessFlags::READ) ? D3D11_CPU_ACCESS_READ : 0;
	d3d11CPUAccessFlags |= (flags & core::CPUAccessFlags::WRITE) ? D3D11_CPU_ACCESS_WRITE : 0;

	return d3d11CPUAccessFlags;
}

/// @brief D3D11�̃o�b�t�@�t���O�擾
/// @param flags �o�b�t�@�t���O
/// @return �����Ȃ������^�o�b�t�@�t���O
UINT32 d3d11::getD3D11MiscFlags(UINT flags) {
	UINT32 d3d11MiscFlags = 0;

	d3d11MiscFlags |= (flags & core::MiscFlags::GENERATE_MIPS) ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::TEXTURECUBE) ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::DRAWINDIRECT_ARGS) ? D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::BUFFER_ALLOW_RAW_VIEWS) ? D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::BUFFER_STRUCTURED) ? D3D11_RESOURCE_MISC_BUFFER_STRUCTURED : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::RESOURCE_CLAMP) ? D3D11_RESOURCE_MISC_RESOURCE_CLAMP : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::BUFFER_STRUCTURED) ? D3D11_RESOURCE_MISC_BUFFER_STRUCTURED : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::SHARED_KEYEDMUTEX) ? D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::TILE_POOL) ? D3D11_RESOURCE_MISC_TILE_POOL : 0;
	d3d11MiscFlags |= (flags & core::MiscFlags::TILED) ? D3D11_RESOURCE_MISC_TILED : 0;

	return d3d11MiscFlags;
}

/// @brief D3D11�̃v���~�e�B�u�g�|���W�[�擾
/// @param topology �v���~�e�B�u�g�|���W�[
/// @return D3D11�v���~�e�B�u�g�|���W�[
D3D11_PRIMITIVE_TOPOLOGY d3d11::getD3D11PrimitiveTopology(core::PrimitiveTopology topology) {
	static D3D11_PRIMITIVE_TOPOLOGY d3dTopologies[static_cast<size_t>(core::PrimitiveTopology::MAX)] = {
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

/// @brief DXGI�̃e�N�X�`���t�H�[�}�b�g�擾
/// @param format �e�N�X�`���t�H�[�}�b�g
/// @return DXGI�t�H�[�}�b�g
DXGI_FORMAT d3d11::getDXGIFormat(core::TextureFormat format) {
	static DXGI_FORMAT d3dDXGIFormat[static_cast<size_t>(core::TextureFormat::MAX)] = {
	DXGI_FORMAT_UNKNOWN, // �s��

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

	// �u���b�N���k�e�N�X�`��
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

/// @brief TypeLess�t�H�[�}�b�g��DSV�t�H�[�}�b�g�ɕϊ����ĕԂ�
/// @param format TypeLess�t�H�[�}�b�g
/// @return DSV�t�H�[�}�b�g or ���̂܂�
DXGI_FORMAT d3d11::getTypeLessToDSVFormat(core::TextureFormat format)
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

/// @brief TypeLess�t�H�[�}�b�g��SRV�t�H�[�}�b�g�ɕϊ����ĕԂ�
/// @param format TypeLess�t�H�[�}�b�g
/// @return SRV�t�H�[�}�b�g or ���̂܂�
DXGI_FORMAT d3d11::getTypeLessToSRVFormat(core::TextureFormat format)
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
