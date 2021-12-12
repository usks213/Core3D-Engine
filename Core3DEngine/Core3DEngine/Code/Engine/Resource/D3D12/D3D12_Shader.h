/*****************************************************************//**
 * \file   D3D12_Shader.h
 * \brief  DirectX12シェーダークラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/11
 *********************************************************************/
#ifndef _D3D12_SHADER_
#define _D3D12_SHADER_

#include <Resource/Core/Shader.h>
#include <RHI\D3D12\D3D12_Device.h>
#include <d3d12shader.h>

namespace Core::D3D12
{
	/// @class D3D12Shader
	/// @brief DirectX11シェーダ
	class D3D12Shader final : public Core::CoreShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief  コンストラクタ
		/// @param device デバイス
		/// @param desc シェーダ情報
		explicit D3D12Shader(D3D12Device* device, 
			Core::ShaderDesc desc, const Core::ShaderID& id);

		/// @brief デストラクタ
		~D3D12Shader() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief シェーダデータ
		std::array < ComPtr<ID3DBlob>, 
			static_cast<std::size_t>(Core::GraphicsShaderStage::MAX)>	m_pShaderBlob;

		/// @brief 入力レイアウト
		std::vector<D3D12_INPUT_ELEMENT_DESC>					m_inputElementDesc;

		/// @brief ルートシグネチャー
		ComPtr<ID3D12RootSignature>	m_pRootSignature;	///< ルートシグネチャー

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief ルートシグネチャーの生成
		void CreateRootSignature(D3D12Device* device);

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_D3D12_SHADER_
