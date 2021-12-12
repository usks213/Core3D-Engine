/*****************************************************************//**
 * \file   D3D12_Material.h
 * \brief  DirectX12�}�e���A��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/11
 *********************************************************************/
#ifndef _D3D12_MATERIAL_
#define _D3D12_MATERIAL_

#include <Resource/Core/Material.h>
#include <Resource/Core/ShaderResource.h>
#include <RHI/D3D12/D3D12_Defines.h>

namespace Core::D3D12
{
	/// @class D3D12Material
	/// @brief Directx11�}�e���A��
	class D3D12Material final :public Core::CoreMaterial
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
		explicit D3D12Material(ID3D12Device* device, const Core::MaterialID& id,
			const std::string& name, Core::CoreShader& shader);

		/// @brief �f�X�g���N�^
		~D3D12Material() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief �S�X�e�[�W�A�X���b�g���̃q�[�v�̈�
		std::array<ComPtr<ID3D12DescriptorHeap>, 
			static_cast<size_t>(Core::GraphicsShaderStage::MAX)>	m_pCBufferHeap;

		/// @brief �S�X�e�[�W�A�X���b�g����CBuffer���\�[�X�|�C���^
		std::array<std::unordered_map<std::uint32_t, ComPtr<ID3D12Resource>>,
			static_cast<size_t>(Core::GraphicsShaderStage::MAX)>	m_d3dCbuffer;

	};
}

#endif // !_D3D12_MATERIAL_
