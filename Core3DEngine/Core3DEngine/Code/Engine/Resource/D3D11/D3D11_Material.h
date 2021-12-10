/*****************************************************************//**
 * \file   D3D11_Material.h
 * \brief  DirectX11�}�e���A��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_MATERIAL_
#define _D3D11_MATERIAL_

#include <Resource/Core/Material.h>
#include <Resource/Core/ShaderResource.h>
#include <RHI/D3D11/D3D11_Defines.h>

namespace Core::D3D11
{
	/// @class D3D11Material
	/// @brief Directx11�}�e���A��
	class D3D11Material final :public Core::CoreMaterial
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param id �}�e���A��ID
		/// @param name �}�e���A����
		/// @param shader �V�F�[�_
		explicit D3D11Material(ID3D11Device1* device, const Core::MaterialID& id,
			const std::string& name, const Core::CoreShader& shader);

		/// @brief �f�X�g���N�^
		~D3D11Material() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief �S�X�e�[�W�A�X���b�g����CBuffer�|�C���^
		std::array<std::unordered_map<std::uint32_t, ComPtr<ID3D11Buffer>>,
			static_cast<size_t>(Core::ShaderStage::MAX)>	m_d3dCbuffer;
	};
}

#endif // !_D3D11_MATERIAL_
