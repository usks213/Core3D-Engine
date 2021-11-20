/*****************************************************************//**
 * \file   ComponentManager.h
 * \brief  �R���|�[�l���g�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _COMPONENT_MANAGER_
#define _COMPONENT_MANAGER_

#include "Component.h"

#include <memory>
#include <vector>
#include <unordered_map>

class Scene;

class ComponentManager final
{
public:
	/// @brief �R���X�g���N�^
	/// @param pScene �V�[���|�C���^
	explicit ComponentManager(Scene* pScene) noexcept :
		m_pScene(pScene)
	{
	}

	/// @brief �f�X�g���N�^
	~ComponentManager() noexcept = default;

	/// @brief �R���|�[�l���g�̐���
	/// @tparam T �R���|�[�l���g�^
	/// @param entityID �e�̃G���e�B�e�BID
	/// @param isEnable �L���t���O
	/// @return ���������R���|�[�l���g�^�|�C���^
	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* CreateComponent(const EntityID& entityID, bool isEnable)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ID����
		InstanceID id = NONE_INSTANCE_ID;
		// ����
		auto pCom = std::make_unique<T>();
		auto pResult = pCom.get();
		pResult->m_instanceID = id;
		pResult->m_entityID = entityID;
		pResult->m_isEnable = isEnable;
		// �i�[
		m_componentLookupTable[typeID].emplace(pCom->GetComponentID(), m_componentPool[typeID].size());
		m_componentPool[typeID].push_back(std::move(pCom));
		// �������R�[���o�b�N
		pCom->OnCreate();
		// �L���t���O
		SetComponentEnable(pCom, isEnable);

		return pResult;
	}

	/// @brief �R���|�[�l���g���폜���X�g�ɓo�^
	/// @param typeID �R���|�[�l���g�^�C�vID
	/// @param componentID �R���|�[�l���gID
	void DestroyComponent(const TypeID& typeID, const ComponentID& componentID);

	/// @brief �R���|�[�l���g�̌���
	/// @param typeID �R���|�[�l���g�^�C�vID
	/// @param componentID �R���|�[�l���gID
	/// @return �R���|�[�l���g�|�C���^ or nullptr
	Component* FindComponent(const TypeID& typeID, const ComponentID& componentID);

	/// @brief �R���|�[�l���g�̌���
	/// @tparam T �R���|�[�l���g�^
	/// @param componentID �R���|�[�l���gID
	/// @return �R���|�[�l���g�^�|�C���^ or nullptr
	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* FindComponent(const ComponentID& componentID)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		return static_cast<T*>(FindComponent(typeID, componentID));
	}

	/// @brief �R���|�[�l���g�̗L���w��
	/// @param pComponent �Ώۂ̃R���|�[�l���g�|�C���^
	/// @param isEnable �L���t���O
	void SetComponentEnable(Component* pComponent, bool isEnable);

	/// @brief �폜���X�g�̎��s
	void CleanupComponent();

	/// @brief �R���|�[�l���g�̃V���A���C�Y
	void Serialize();

	/// @brief �R���|�[�l���g�̃f�V���A���C�Y
	void Deserialize();

private:

	Component* RegisterComponent(const TypeID& typeID, const ComponentID& componentID, Component* pComponent);

private:
	/// @brief vectorIndex
	using Index = std::size_t;

	/// @brief �R���|�[�l���g���
	struct ComponentInfo
	{
		ComponentID	id;		///< �R���|�[�l���gID
		TypeID		type;	///< �R���|�[�l���g�^ID
	};

	//--- serialize param

	/// @brief �^���Ƃ̃R���|�[�l���g�v�[��
	std::unordered_map<TypeID, std::vector<std::unique_ptr<Component>>>		m_componentPool;

	//--- none serialize param

	/// @brief �����V�[��
	Scene* m_pScene;

	/// @brief �R���|�[�l���g�̃��b�N�A�b�v�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_componentLookupTable;

	/// @brief �������X�g
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_createList;
	/// @brief �폜���X�g
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_destroyList;

	/// @brief �L���R���|�[�l���g���X�g
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_enableComponents;
	/// @brief �L���R���|�[�l���g�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_enableComponentsTable;
	/// @brief �����R���|�[�l���g���X�g
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_disableComponents;
	/// @brief �����R���|�[�l���g�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_disableComponentsTable;

};

#endif // !_COMPONENT_MANAGER_
