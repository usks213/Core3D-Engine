/*****************************************************************//**
 * \file   D3D12_Shader.h
 * \brief  DirectX12�V�F�[�_�[�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/11
 *********************************************************************/
#ifndef _D3D12_SHADER_
#define _D3D12_SHADER_

#include <CoreRenderer/Core/Core_Shader.h>
#include "D3D12_Device.h"
#include "D3D12_Defines.h"
#include <d3d12shader.h>

namespace d3d12
{
	/// @class D3D12Shader
	/// @brief DirectX11�V�F�[�_
	class D3D12Shader final : public core::CoreShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief  �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param desc �V�F�[�_���
		explicit D3D12Shader(D3D12Device* device, 
			core::ShaderDesc desc, const core::ShaderID& id);

		/// @brief �f�X�g���N�^
		~D3D12Shader() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_�f�[�^
		std::array < ComPtr<ID3DBlob>, 
			static_cast<std::size_t>(core::ShaderStage::MAX)>	m_pShaderBlob;

		/// @brief ���̓��C�A�E�g
		std::vector<D3D12_INPUT_ELEMENT_DESC>					m_inputElementDesc;

		/// @brief ���[�g�V�O�l�`���[
		ComPtr<ID3D12RootSignature>	m_pRootSignature;	///< ���[�g�V�O�l�`���[

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief ���[�g�V�O�l�`���[�̐���
		void CreateRootSignature(D3D12Device* device);

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_D3D12_SHADER_
