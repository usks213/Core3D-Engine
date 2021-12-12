/*****************************************************************//**
 * \file   D3D_ShaderCompiler.h
 * \brief  DirectXシェーダーコンパイラー
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#include "D3D_ShaderCompiler.h"

using namespace Core::RHI;
using namespace Core::RHI::D3D;




bool D3DShaderCompiler::CompileFromFile(std::string_view filepath, ShaderStage stage, ID3DBlob* pOut)
{

}

bool D3DShaderCompiler::GetReflection(ID3DBlob* pBlob, void** ppRefletor)
{

}


/// @brief インプットレイアウト作成
/// @param pReflection リフレクションデータ
/// @param elementList エレメントリスト
/// @param inputLayout インプットレイアウト(out)
/// @return 成功 TRUE / 失敗 FALSE
bool D3DShaderCompiler::CreateInputLayout(void* pReflection,
#ifdef __d3d12_h__
	std::vector<D3D12_INPUT_ELEMENT_DESC>& elementList,
#elif __d3d11_h__
	std::vector<D3D11_INPUT_ELEMENT_DESC>& elementList,
#endif // __d3d12.h_
	ShaderInputLayout& inputLayout)
{

}

/// @brief リソースレイアウト作成
/// @param pReflection リフレクションデータ
/// @param resourceLayout リソースレイアウト(out)
/// @return 成功 TRUE / 失敗 FALSE
bool D3DShaderCompiler::CreateResourceLayout(void* pReflection, ShaderResourceLayout& resourceLayout)
{

}

/// @brief CBufferレイアウト作成
/// @param pReflection リフレクションデータ
/// @param resourceLayout リソースレイアウト(in)
/// @param cbufferLayouts CBufferレイアウトリスト(out)
/// @return 成功 TRUE / 失敗 FALSE
bool D3DShaderCompiler::CreateCBufferLayouts(void* pReflection, ShaderResourceLayout& resourceLayout,
	std::unordered_map<Slot, ShaderCBufferLayout>& cbufferLayouts)
{

}
