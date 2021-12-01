/*****************************************************************//**
 * \file   D3D12_CommonState.h
 * \brief  DirectX12共通ステート
 * 
 * \author USAMI KOSHI
 * \date   2021/10/13
 *********************************************************************/
#ifndef _D3D12_COMMON_STATE_
#define _D3D12_COMMON_STATE_

#include <CoreRenderer/Core/Core_CommonState.h>
#include "D3D12_Defines.h"

namespace d3d12
{
    /// @brief リソースフラグ取得
    /// @param flags フラグ
    /// @return D3D12リソースフラグ
    D3D12_RESOURCE_FLAGS getD3D12ResourceFlags(UINT bindFlags);

    /// @brief ヒープフラグ取得
    /// @param flags フラグ
    /// @return D3D12ヒープフラグ
    D3D12_DESCRIPTOR_HEAP_FLAGS getD3D12HeapFlags(UINT bindFlags);

    /// @brief D3D12のプリミティブトポロジー取得
    /// @param topology プリミティブトポロジー
    /// @return D3D12プリミティブトポロジー
    D3D12_PRIMITIVE_TOPOLOGY getD3D12PrimitiveTopology(core::PrimitiveTopology topology);

    /// @brief DXGIのテクスチャフォーマット取得
    /// @param format テクスチャフォーマット
    /// @return DXGIフォーマット
    DXGI_FORMAT getDXGIFormat(core::TextureFormat format);

    /// @brief TypeLessフォーマットをDSVフォーマットに変換して返す
    /// @param format TypeLessフォーマット
    /// @return DSVフォーマット or そのまま
    DXGI_FORMAT getTypeLessToDSVFormat(core::TextureFormat format);

    /// @brief TypeLessフォーマットをSRVフォーマットに変換して返す
    /// @param format TypeLessフォーマット
    /// @return SRVフォーマット or そのまま
    DXGI_FORMAT getTypeLessToSRVFormat(core::TextureFormat format);
}

#endif // !_D3D12_COMMON_STATE_

