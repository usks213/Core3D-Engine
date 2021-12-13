/*****************************************************************//**
 * \file   D3D_ShaderCompiler.h
 * \brief  DirectX�V�F�[�_�[�R���p�C���[
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

#ifndef __d3d12_h__
#include <d3d11.h>
#endif // !__d3d12_h__

namespace Core::RHI::D3D
{
	class D3DShaderCompiler
	{
	public:

		/// @brief �V�F�[�_�[�t�@�C���̃R���p�C��
		/// @param filepath �t�@�C���p�X
		/// @param stage �V�F�[�_�[�X�e�[�W
		/// @param pOut �V�F�[�_�[�o�C�i���̏o�͐�(out)
		/// @return ���� TRUE / ���s FALSE
		bool CompileFromFile(std::string_view filepath, ShaderStage stage, ID3DBlob* pOut);

		/// @brief �V�F�[�_�[���t���N�V�����擾
		/// @param pBlob �V�F�[�_�[�o�C�i��(in)
		/// @param pRefletor ���t���N�V�����i�[��(out)
		/// @return ���� TRUE / ���s FALSE
		bool GetReflection(ID3DBlob* pBlob, void* pRefletor);

		/// @brief �C���v�b�g���C�A�E�g�쐬
		/// @param pReflection ���t���N�V�����f�[�^
		/// @param elementList �G�������g���X�g
		/// @param inputLayout �C���v�b�g���C�A�E�g(out)
		/// @return ���� TRUE / ���s FALSE
		bool CreateInputLayout(void* pReflection, 
#ifdef __d3d12_h__
			std::vector<D3D12_INPUT_ELEMENT_DESC>& elementList, 
#else __d3d11_h__
			std::vector<D3D11_INPUT_ELEMENT_DESC>& elementList,
#endif // __d3d12.h_
			ShaderInputLayout& inputLayout);

		/// @brief ���\�[�X���C�A�E�g�쐬
		/// @param pReflection ���t���N�V�����f�[�^
		/// @param resourceLayout ���\�[�X���C�A�E�g(out)
		/// @return ���� TRUE / ���s FALSE
		bool CreateResourceLayout(void* pReflection, ShaderResourceLayout& resourceLayout);

		/// @brief CBuffer���C�A�E�g�쐬
		/// @param pReflection ���t���N�V�����f�[�^
		/// @param resourceLayout ���\�[�X���C�A�E�g(in)
		/// @param cbufferLayouts CBuffer���C�A�E�g���X�g(out)
		/// @return ���� TRUE / ���s FALSE
		bool CreateCBufferLayouts(void* pReflection, ShaderResourceLayout& resourceLayout, 
			std::unordered_map<Slot, ShaderCBufferLayout>& cbufferLayouts);
	};
}

#endif // !_D3D_SHADER_COMPILER_

