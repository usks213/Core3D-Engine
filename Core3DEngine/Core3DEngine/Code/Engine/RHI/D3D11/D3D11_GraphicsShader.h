/*****************************************************************//**
 * \file   D3D11_GraphicsShader.h
 * \brief  DirectX11グラフィックスシェーダー
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_GRAPHICS_SHADER_
#define _D3D11_GRAPHICS_SHADER_

#include <RHI/Core/RHI_GraphicsShader.h>
#include "D3D11_Defines.h"


namespace Core::RHI::D3D11
{
	/// @class D3D11GraphicsShader
	/// @brief DirectX11シェーダ
	class D3D11GraphicsShader final : public GraphicsShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief  コンストラクタ
		/// @param device デバイス
		/// @param desc シェーダ情報
		explicit D3D11GraphicsShader(ID3D11Device1* device, const GraphicsShaderDesc& desc);

		/// @brief デストラクタ
		~D3D11GraphicsShader() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief シェーダデータ
		union {
			struct {
				ID3D11VertexShader* vs;
				ID3D11GeometryShader* gs;
				ID3D11DomainShader* ds;
				ID3D11HullShader* hs;
				ID3D11PixelShader* ps;
			};
			ID3D11DeviceChild* shaders[static_cast<size_t>(GraphicsShaderStage::MAX)];
		};
		/// @brief 入力レイアウト
		ComPtr<ID3D11InputLayout>				m_pInputLayout;

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief シェーダオブジェクト生成
		/// @param device デバイス
		/// @param stage シェーダステージ
		/// @param blob コンパイルデータ
		void CreateGraphicsShaderObjct(ID3D11Device1* device, const GraphicsShaderStage& stage, ComPtr<ID3DBlob>& blob);

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		/// @brief シェーダのスマートポインタ(解放用)
		std::vector<ComPtr<ID3D11DeviceChild>>	m_comGraphicsShaders;

	};
}

#endif // !_D3D11_GRAPHICS_SHADER_
