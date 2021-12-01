/*****************************************************************//**
 * \file   D3D11_Material.h
 * \brief  DirectX11�}�e���A��
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_Material.h"
using namespace d3d11;

/// @brief �R���X�g���N�^
/// @param device �f�o�C�X
/// @param id �}�e���A��ID
/// @param name �}�e���A����
/// @param shader �V�F�[�_
D3D11Material::D3D11Material(ID3D11Device1* device, const core::MaterialID& id,
	const std::string& name, const core::CoreShader& shader) :
	core::CoreMaterial(id,name,shader)
{
	// �R���X�^���g�o�b�t�@�̏�����
	D3D11_BUFFER_DESC d3dDesc = {};
	d3dDesc.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;
	d3dDesc.Usage			= D3D11_USAGE_DEFAULT;
	d3dDesc.CPUAccessFlags	= 0;
	d3dDesc.MiscFlags		= 0; // STRUCTURED_BUFFER�Ȃ�D3D11_RESOURCE_MISC_BUFFER_STRUCTURED
	//d3dDesc.StructureByteStride = 0;
	// Map()/Unmap()�Ń��\�[�X���X�V����ꍇ�́���p����
	//d3dDesc.Usage = D3D11_USAGE_DYNAMIC;
	//d3dDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// �������f�[�^
	D3D11_SUBRESOURCE_DATA initData = {};

	// �R���X�^���g�o�b�t�@�̊m��(GPU)
	for (core::ShaderStage stage = core::ShaderStage::VS; stage < core::ShaderStage::MAX; ++stage)
	{
		//--- CBuffer�m��
		auto stageIndex = static_cast<size_t>(stage);
		for (auto& cbData : m_cbufferData[stageIndex])
		{
			// CBuffer�T�C�Y
			d3dDesc.ByteWidth	= cbData.second.size;
			// �������f�[�^
			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = cbData.second.data.get();
			// ����
			CHECK_FAILED(device->CreateBuffer(&d3dDesc, &initData,
				m_d3dCbuffer[stageIndex][cbData.first].GetAddressOf()));
		}
	}
}
