/*****************************************************************//**
 * \file   D3D_ShaderCompiler.h
 * \brief  DirectX�V�F�[�_�[�R���p�C���[
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#include "D3D_ShaderCompiler.h"

using namespace Core::RHI;
using namespace Core::RHI::D3D;




bool D3DShaderCompiler::CompileFromFile(std::string_view filepath, ShaderStage stage, ID3DBlob* pOut)
{

}

bool D3DShaderCompiler::GetReflection(ID3DBlob* pBlob, void** ppRefletor)
{

}


/// @brief �C���v�b�g���C�A�E�g�쐬
/// @param pReflection ���t���N�V�����f�[�^
/// @param elementList �G�������g���X�g
/// @param inputLayout �C���v�b�g���C�A�E�g(out)
/// @return ���� TRUE / ���s FALSE
bool D3DShaderCompiler::CreateInputLayout(void* pReflection,
#ifdef __d3d12_h__
	std::vector<D3D12_INPUT_ELEMENT_DESC>& elementList,
#elif __d3d11_h__
	std::vector<D3D11_INPUT_ELEMENT_DESC>& elementList,
#endif // __d3d12.h_
	ShaderInputLayout& inputLayout)
{

}

/// @brief ���\�[�X���C�A�E�g�쐬
/// @param pReflection ���t���N�V�����f�[�^
/// @param resourceLayout ���\�[�X���C�A�E�g(out)
/// @return ���� TRUE / ���s FALSE
bool D3DShaderCompiler::CreateResourceLayout(void* pReflection, ShaderResourceLayout& resourceLayout)
{

}

/// @brief CBuffer���C�A�E�g�쐬
/// @param pReflection ���t���N�V�����f�[�^
/// @param resourceLayout ���\�[�X���C�A�E�g(in)
/// @param cbufferLayouts CBuffer���C�A�E�g���X�g(out)
/// @return ���� TRUE / ���s FALSE
bool D3DShaderCompiler::CreateCBufferLayouts(void* pReflection, ShaderResourceLayout& resourceLayout,
	std::unordered_map<Slot, ShaderCBufferLayout>& cbufferLayouts)
{

}
