/*****************************************************************//**
 * \file   Resource.h
 * \brief  リソースオブジェクト
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _RESOURCE_
#define _RESOURCE_

#include <Core\Object.h>
#include <memory>

 /// @brief 型情報付加
#define DECLARE_RESOURCE_INFO(T)	\
DECLARE_OBJECT_INFO(T);				\
using T##ID = ResourceID

namespace Core
{
	class ResourceManager;

	/// @brief リソースクラス
	class Resource : public Object
	{
	public:
		/// @brief コンストラクタ
		/// @return 
		explicit Resource() noexcept :
			Object(),
			m_pResourceManager(nullptr)
		{
		}

		/// @brief デストラクタ
		/// @return 
		virtual ~Resource() noexcept = default;

		/// @brief リソースID取得
		/// @return リソースID
		ResourceID GetResourceID() noexcept
		{
			return static_cast<ResourceID>(GetInstanceID());
		}

		/// @brief リソース名取得
		/// @return リソース名
		std::string_view GetName() { return m_name; }

		/// @brief インスペクター表示
		virtual void OnInspectorGUI() = 0;

	private:
		//--- none serialize param

		ResourceManager* m_pResourceManager;

		//--- serialize param

		std::string		m_name;	///< リソース名

	};
}


#endif // !_RESOURCE_
