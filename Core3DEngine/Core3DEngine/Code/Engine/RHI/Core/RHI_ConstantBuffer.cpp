/*****************************************************************//**
 * \file   RHI_ConstantBuffer.h
 * \brief  �R���X�^���g�o�b�t�@
 *
 * \author USAMI KOSHI
 * \date   2021/12/04
 *********************************************************************/

#include "RHI_ConstantBuffer.h"

using namespace Core::RHI;

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief �R���X�g���N�^
/// @param layout �R���X�^���g�o�b�t�@���C�A�E�g
ConstantBuffer::ConstantBuffer(const ConstantBufferLayout& layout) :
	m_data(layout.m_size), m_layout(layout), m_isDitry(true)
{
	// �ϐ��f�[�^�i�[
	for (const auto& var : m_layout.m_variables)
	{
		// �������q�f�[�^������ꍇ�͏���������
		if (var.second.defaultVal.size() > 0)
		{
			std::memcpy(m_data.data() + var.second.offset,
				var.second.defaultVal.data(), var.second.size);	// �������c
		}
		else
		{
			std::memset(m_data.data() + var.second.offset, 0, var.second.size);
		}
	}
}


//------------------------------------------------------------------------------
// protected methods
//------------------------------------------------------------------------------

/// @brief �f�[�^�ݒ�
bool ConstantBuffer::SetData(const char* name, const void* data)
{
	auto itr = m_layout.m_variables.find(name);
	if (m_layout.m_variables.end() == itr) return false;

	std::memcpy(m_data.data() + itr->second.offset, data, itr->second.size);
	m_isDitry = true;

	return true;
}
