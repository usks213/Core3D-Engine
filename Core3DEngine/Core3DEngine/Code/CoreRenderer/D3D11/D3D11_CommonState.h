/*****************************************************************//**
 * \file   D3D11_CommonState.h
 * \brief  DirectX11共通ステイト
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _D3D11_COMMON_STATE_
#define _D3D11_COMMON_STATE_

#include <CoreRenderer/Core/Core_CommonState.h>
#include "D3D11_Defines.h"

namespace d3d11
{
    /// @brief D3D11のリソース使用識別取得
    /// @param usage リソース使用識別
    /// @return D3D11リソース使用識別
    D3D11_USAGE getD3D11Usage(core::Usage usage);

    /// @brief D3D11のバインドフラグ取得
    /// @param flags バインドフラグ
    /// @return 符号なし整数型バインドフラグ
    UINT32 getD3D11BindFlags(UINT flags);

    /// @brief D3D11のCPUアクセスフラグ取得
    /// @param flags CPUアクセスフラグ
    /// @return 符号なし整数型CPUアクセスフラグ
    UINT32 getD3D11CPUAccessFlags(UINT flags);

    /// @brief D3D11のバッファフラグ取得
    /// @param flags バッファフラグ
    /// @return 符号なし整数型バッファフラグ
    UINT32 getD3D11MiscFlags(UINT flags);

    /// @brief D3D11のプリミティブトポロジー取得
    /// @param topology プリミティブトポロジー
    /// @return D3D11プリミティブトポロジー
    D3D11_PRIMITIVE_TOPOLOGY getD3D11PrimitiveTopology(core::PrimitiveTopology topology);

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

#endif // !_D3D11_COMMON_STATE_

