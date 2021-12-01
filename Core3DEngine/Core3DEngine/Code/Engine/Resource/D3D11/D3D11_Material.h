/*****************************************************************//**
 * \file   D3D11_Material.h
 * \brief  DirectX11マテリアル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_MATERIAL_
#define _D3D11_MATERIAL_

#include <CoreRenderer/Core/Core_Material.h>
#include <CoreRenderer/Core/Core_ShaderResource.h>
#include <CoreRenderer/D3D11/D3D11_Defines.h>

namespace d3d11
{
	/// @class D3D11Material
	/// @brief Directx11マテリアル
	class D3D11Material final :public core::CoreMaterial
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id マテリアルID
		/// @param name マテリアル名
		/// @param shader シェーダ
		explicit D3D11Material(ID3D11Device1* device, const core::MaterialID& id,
			const std::string& name, const core::CoreShader& shader);

		/// @brief デストラクタ
		~D3D11Material() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief 全ステージ、スロット分のCBufferポインタ
		std::array<std::unordered_map<std::uint32_t, ComPtr<ID3D11Buffer>>,
			static_cast<size_t>(core::ShaderStage::MAX)>	m_d3dCbuffer;
	};
}

#endif // !_D3D11_MATERIAL_
