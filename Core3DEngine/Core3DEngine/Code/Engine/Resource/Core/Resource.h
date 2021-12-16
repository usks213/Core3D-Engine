/*****************************************************************//**
 * \file   Resource.h
 * \brief  ���\�[�X�I�u�W�F�N�g
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _RESOURCE_
#define _RESOURCE_

#include <Core\Object.h>
#include <memory>

 /// @brief �^���t��
#define DECLARE_RESOURCE_INFO(T)	\
DECLARE_OBJECT_INFO(T);				\
using T##ID = ResourceID

namespace Core
{
	class ResourceManager;

	/// @brief ���\�[�X�N���X
	class Resource : public Object
	{
	public:
		/// @brief �R���X�g���N�^
		/// @return 
		explicit Resource() noexcept :
			Object(),
			m_pResourceManager(nullptr)
		{
		}

		/// @brief �f�X�g���N�^
		/// @return 
		virtual ~Resource() noexcept = default;

		/// @brief ���\�[�XID�擾
		/// @return ���\�[�XID
		ResourceID GetResourceID() noexcept
		{
			return static_cast<ResourceID>(GetInstanceID());
		}

		/// @brief ���\�[�X���擾
		/// @return ���\�[�X��
		std::string_view GetName() { return m_name; }

		/// @brief �C���X�y�N�^�[�\��
		virtual void OnInspectorGUI() = 0;

	private:
		//--- none serialize param

		ResourceManager* m_pResourceManager;

		//--- serialize param

		std::string		m_name;	///< ���\�[�X��

	};
}


#endif // !_RESOURCE_
