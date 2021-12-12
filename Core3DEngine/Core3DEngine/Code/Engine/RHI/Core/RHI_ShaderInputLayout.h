/*****************************************************************//**
 * \file   RHI_ShaderInputLayout.h
 * \brief  �V�F�[�_�[�C���v�b�g���C�A�E�g
 *
 * \author USAMI KOSHI
 * \date   2021/12/10
 *********************************************************************/
#ifndef _RHI_SHADER_INPUT_LAYOUT_
#define _RHI_SHADER_INPUT_LAYOUT_

#include <vector>
#include <string>

namespace Core::RHI
{
	class ShaderInputLayout
	{
	public:
		ShaderInputLayout();
		~ShaderInputLayout();

		/// @brief ���̓��C�A�E�g���\����
		struct InputLayoutVariable
		{
			std::string semanticName;		///< �Z�}���e�B�b�N��		��:TEXCOOD
			std::uint32_t semanticIndex;	///< �Z�}���e�B�b�N�ԍ�	��:TEXCOOD[0]��
			std::size_t offset;			///< �ϐ��I�t�Z�b�g
			std::size_t arrayNum;			///< �z��̐� ��:R32=1,R32B32=2,
			std::size_t formatWidth;		///< �t�H�[�}�b�g�̕� ��:r16=2,r32=4
			InputLayoutVariable() :
				semanticName(),
				semanticIndex(0),
				offset(0),
				arrayNum(0),
				formatWidth(0) {}
		};

		/// @brief �ϐ��̒ǉ�
		/// @param var ���̓��C�A�E�g�̕ϐ�
		void AddVariable(const InputLayoutVariable& var)
		{
			m_inputLayoutVariableList.push_back(var);
		}

		/// @brief ���̓��C�A�E�g�̕ϐ����X�g���擾
		/// @return �ϐ����X�g
		std::vector<InputLayoutVariable>& GetVariableList() 
		{
			return m_inputLayoutVariableList; 
		}

	protected:

		/// @brief ���̓��C�A�E�g��񃊃X�g
		std::vector<InputLayoutVariable> m_inputLayoutVariableList;

	};

}

#endif // !_RHI_SHADER_INPUT_LAYOUT_

