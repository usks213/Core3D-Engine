/*****************************************************************//**
 * \file   Mesh.h
 * \brief  ���b�V���N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#include "Mesh.h"
#include <Resource\Core\ResourceManager.h>

using namespace Core;

/// @brief �V�F�[�_�[�ɑΉ����郌���_�[�o�b�t�@�̎擾
/// @param shaderID �O���t�B�b�N�X�V�F�[�_�[ID
/// @return �����_�[�o�b�t�@�Q��
std::shared_ptr<RenderBuffer> Mesh::GetRenderBuffer(const GraphicsShader::ID& shaderID)
{
	// ���Ɋi�[�ς�
	auto itr = m_renderBuffers.find(shaderID);
	if (m_renderBuffers.end() != itr)
	{
		return itr->second;
	}

	// �V�F�[�_�[�擾
	auto pShader = ResourceManager::get().GetResource<GraphicsShader>(shaderID);
	if (pShader == nullptr) return nullptr;
	auto pRHIShader = pShader->GetRHIGraphicsShader();
	if (!pRHIShader) return nullptr;

	// �V�K����
	m_renderBuffers[shaderID] = std::make_shared<RenderBuffer>(
		pRHIShader->GetInputLayout(), m_vertex, m_index);

	return m_renderBuffers[shaderID];
}
