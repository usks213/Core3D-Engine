/*****************************************************************//**
 * \file   Component.h
 * \brief  �R���|�[�l���g
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _COMPONENT_
#define _COMPONENT_

#include "Object.h"

 /// @brief �^���t��
#define DECLARE_COMPONENT_INFO(T)	\
DECLARE_OBJECT_INFO(T);				\
using T##ID = ComponentID

class Entity;
class Transform;
class ComponentManager;

/// @brief �R���|�[�l���g
class Component : public Object
{
	friend class Entity;
	friend class ComponentManager;
public:

	/// @brief �R���X�g���N�^
	explicit Component() noexcept :
		Object(), 
		m_pComponentManager(nullptr),
		m_entityID(NONE_ENTITY_ID),
		m_isEnable(true)
	{
	}

	/// @brief �f�X�g���N�^
	virtual ~Component() noexcept = default;

	/// @brief �R���|�[�l���gID�擾
	/// @return �R���|�[�l���gID
	ComponentID GetComponentID() noexcept
	{
		return static_cast<ComponentID>(GetInstanceID()); 
	}

	/// @brief �e�G���e�B�e�B�̎擾
	/// @return �G���e�B�e�B�|�C���^
	Entity* entity() noexcept;

	/// @brief �g�����X�t�H�[���̎擾
	/// @return �g�����X�t�H�[���|�C���^
	Transform* transform() noexcept;

	/// @brief �g�p�t���O�w��
	/// @param isEnable �t���O
	void SetEnable(bool isEnable) noexcept;

	bool GetEnable() { return m_isEnable; }

public:
	//--- �R�[���o�b�N�֐�

	virtual void OnCreate() {}	///< �������X�g�i�[��
	virtual void OnDestroy() {}	///< �폜���X�g�i�[��

	virtual void OnEnable() {}	///< �L����
	virtual void OnDisable() {}	///< ������

	virtual void OnStart() {}	///< ����X�V�O�Ɉ�x

	/// @brief �C���X�y�N�^�[�\��
	virtual void OnInspectorGUI() override {}

protected:

	/// @brief �R���|�[�l���g���̎擾(�X�N���v�g�p�����)
	/// @return �R���|�[�l���g��
	virtual std::string_view GetComponentName() noexcept;

protected:

	/// @brief �C���X�y�N�^�[�\���̊J�n
	/// @return �m�[�h���J���Ă��邩
	bool BeginInspectorGUI();

	/// @brief �C���X�y�N�^�[�\���̏I��
	void EndInspectorGUI();

protected:
	//--- none serialize param

	ComponentManager* m_pComponentManager;

	//--- serialize param

	/// @brief �e�̃G���e�B�e�BID
	EntityID	m_entityID;
	/// @brief �A�N�e�B�u�t���O
	bool		m_isEnable;

};

#endif // !_COMPONENT_
