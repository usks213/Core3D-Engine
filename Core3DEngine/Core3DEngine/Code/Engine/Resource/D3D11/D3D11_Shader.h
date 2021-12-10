/*****************************************************************//**
 * \file   D3D11_Shader.h
 * \brief  DirectX11シェーダー
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_SHADER_
#define _D3D11_SHADER_

#include <Resource/Core/Shader.h>
#include <RHI\D3D11\D3D11_Defines.h>
#include <d3d11shader.h>

namespace Core::D3D11
{
	/// @class D3D11Shader
	/// @brief DirectX11シェーダ
	class D3D11Shader final : public Core::CoreShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief  コンストラクタ
		/// @param device デバイス
		/// @param desc シェーダ情報
		explicit D3D11Shader(ID3D11Device1* device, 
			Core::ShaderDesc desc, const Core::ShaderID& id);

		/// @brief デストラクタ
		~D3D11Shader() noexcept = default;

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
				ID3D11ComputeShader* cs;
			};
			ID3D11DeviceChild* shaders[static_cast<size_t>(Core::ShaderStage::MAX)];
		};
		/// @brief 入力レイアウト
		ComPtr<ID3D11InputLayout>				m_inputLayout;

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief シェーダオブジェクト生成
		/// @param device デバイス
		/// @param stage シェーダステージ
		/// @param blob コンパイルデータ
		void CreateShaderObjct(ID3D11Device1* device, const Core::ShaderStage& stage, ComPtr<ID3DBlob>& blob);

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		/// @brief シェーダのスマートポインタ(解放用)
		std::vector<ComPtr<ID3D11DeviceChild>>	m_comShaders;

	};
}

#endif // !_D3D11_SHADER_
