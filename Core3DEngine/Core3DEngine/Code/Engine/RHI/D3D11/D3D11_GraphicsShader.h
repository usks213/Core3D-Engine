/*****************************************************************//**
 * \file   D3D11_GraphicsShader.h
 * \brief  DirectX11�O���t�B�b�N�X�V�F�[�_�[
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
	/// @brief DirectX11�V�F�[�_
	class D3D11GraphicsShader final : public GraphicsShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief  �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param desc �V�F�[�_���
		explicit D3D11GraphicsShader(ID3D11Device1* device, const GraphicsShaderDesc& desc);

		/// @brief �f�X�g���N�^
		~D3D11GraphicsShader() noexcept = default;

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
			};
			ID3D11DeviceChild* shaders[static_cast<size_t>(GraphicsShaderStage::MAX)];
		};
		/// @brief ���̓��C�A�E�g
		ComPtr<ID3D11InputLayout>				m_pInputLayout;

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_�I�u�W�F�N�g����
		/// @param device �f�o�C�X
		/// @param stage �V�F�[�_�X�e�[�W
		/// @param blob �R���p�C���f�[�^
		void CreateGraphicsShaderObjct(ID3D11Device1* device, const GraphicsShaderStage& stage, ComPtr<ID3DBlob>& blob);

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_�̃X�}�[�g�|�C���^(����p)
		std::vector<ComPtr<ID3D11DeviceChild>>	m_comGraphicsShaders;

	};
}

#endif // !_D3D11_GRAPHICS_SHADER_
