/*****************************************************************//**
 * \file   D3D_ShaderCompiler.h
 * \brief  DirectXシェーダーコンパイラー
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D_SHADER_COMPILER_
#define _D3D_SHADER_COMPILER_

#include <RHI\Core\RHI_ShaderUtil.h>
#include <RHI\Core\RHI_ShaderCBufferLayout.h>
#include <RHI\Core\RHI_ShaderInputLayout.h>
#include <RHI\Core\RHI_ShaderResourceLayout.h>

#include <d3dcompiler.h>

#include <d3d12.h>

namespace Core::RHI::D3D
{
	class D3DShaderCompiler
	{
	public:

		bool CompileFromFile(std::string_view filepath, ShaderStage stage, ID3DBlob* pOut);

		bool GetReflection(ID3DBlob* pBlob, void** ppRefletor);


		/// @brief インプットレイアウト作成
		/// @param pReflection リフレクションデータ
		/// @param elementList エレメントリスト
		/// @param inputLayout インプットレイアウト(out)
		/// @return 成功 TRUE / 失敗 FALSE
		bool CreateInputLayout(void* pReflection, 
#ifdef __d3d12_h__
			std::vector<D3D12_INPUT_ELEMENT_DESC>& elementList, 
#elif __d3d11_h__
			std::vector<D3D11_INPUT_ELEMENT_DESC>& elementList,
#endif // __d3d12.h_
			ShaderInputLayout& inputLayout);

		/// @brief リソースレイアウト作成
		/// @param pReflection リフレクションデータ
		/// @param resourceLayout リソースレイアウト(out)
		/// @return 成功 TRUE / 失敗 FALSE
		bool CreateResourceLayout(void* pReflection, ShaderResourceLayout& resourceLayout);

		/// @brief CBufferレイアウト作成
		/// @param pReflection リフレクションデータ
		/// @param resourceLayout リソースレイアウト(in)
		/// @param cbufferLayouts CBufferレイアウトリスト(out)
		/// @return 成功 TRUE / 失敗 FALSE
		bool CreateCBufferLayouts(void* pReflection, ShaderResourceLayout& resourceLayout, 
			std::unordered_map<Slot, ShaderCBufferLayout>& cbufferLayouts);
	};
}

#endif // !_D3D_SHADER_COMPILER_

