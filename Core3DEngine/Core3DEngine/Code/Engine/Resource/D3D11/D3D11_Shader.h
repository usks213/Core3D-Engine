/*****************************************************************//**
 * \file   D3D11_Shader.h
 * \brief  DirectX11�V�F�[�_�[
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
	/// @brief DirectX11�V�F�[�_
	class D3D11Shader final : public Core::CoreShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief  �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param desc �V�F�[�_���
		explicit D3D11Shader(ID3D11Device1* device, 
			Core::ShaderDesc desc, const Core::ShaderID& id);

		/// @brief �f�X�g���N�^
		~D3D11Shader() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_�f�[�^
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
		/// @brief ���̓��C�A�E�g
		ComPtr<ID3D11InputLayout>				m_inputLayout;

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_�I�u�W�F�N�g����
		/// @param device �f�o�C�X
		/// @param stage �V�F�[�_�X�e�[�W
		/// @param blob �R���p�C���f�[�^
		void CreateShaderObjct(ID3D11Device1* device, const Core::ShaderStage& stage, ComPtr<ID3DBlob>& blob);

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_�̃X�}�[�g�|�C���^(����p)
		std::vector<ComPtr<ID3D11DeviceChild>>	m_comShaders;

	};
}

#endif // !_D3D11_SHADER_
