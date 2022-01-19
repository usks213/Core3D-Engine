/*****************************************************************//**
 * \file   Script.h
 * \brief  �X�N���v�g
 *
 * \author USAMI KOSHI
 * \date   2021/11/15
 *********************************************************************/
#ifndef _SCRIPT_
#define _SCRIPT_

#include "Component.h"

 /// @brief �^���t��
#define DECLARE_SCRIPT_INFO(T) 										\
public:																\
	static constexpr std::string_view GetScriptTypeString()			\
	{																\
		return #T;													\
	}																\
	static constexpr TypeHash GetScriptTypeHash()					\
	{																\
		return static_cast<TypeHash>(Util::stringHash(#T));			\
	}																\
[[nodiscard]] ScriptTypeID GetScriptTypeID() noexcept override {	\
	return static_cast<ScriptTypeID>(GetScriptTypeHash());			\
}																	\
[[nodiscard]] std::string_view GetScriptName() noexcept override {	\
	return GetScriptTypeString();									\
}																	\
using T##ID = Component::ID


namespace Core
{
	/// @brief �X�N���v�g�N���X
	class Script : public Component
	{
		friend class Entity;
	public:
		/// @brief �I�u�W�F�N�g���
		DECLARE_OBJECT_INFO(Script);
	public:

		/// @brief �R���X�g���N�^
		explicit Script() noexcept :
			Component()
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~Script() noexcept = default;

		/// @brief �X�N���v�g�^�C�v�̎擾
		[[nodiscard]] virtual ScriptTypeID GetScriptTypeID() noexcept = 0;

		/// @brief �X�N���v�g���̎擾
		[[nodiscard]] virtual std::string_view GetScriptName() noexcept = 0;

	private:

		/// @brief �R���|�[�l���g���̎擾(�X�N���v�g�p�����)
		/// @return �R���|�[�l���g��
		std::string_view GetComponentName() noexcept override
		{
			return GetScriptName();
		}

	public:
		//--- �R�[���o�b�N�֐�

		virtual void OnCreate() override {}		///< �������X�g�i�[��
		virtual void OnDestroy() override {}	///< �폜���X�g�i�[��

		virtual void OnEnable() override {}		///< �L����
		virtual void OnDisable() override {}	///< ������

		virtual void OnStart() override {}		///< ����X�V�O�Ɉ�x

		/// @brief �C���X�y�N�^�[�\��
		virtual void OnInspectorGUI() override {}

	private:

	};
}


#endif // !_SCRIPT_


