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
DECLARE_OBJECT_INFO(T)				
//enum class ID : BaseID {};			\
//T::ID Get##T##ID() { return static_cast<T::ID>(GetResourceID()); }

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

		/// @brief リソースマネージャーの取得
		/// @return リソースマネージャーポインタ
		ResourceManager* GetResourceManager() const noexcept 
		{
			return m_pResourceManager; 
		}

		/// @brief リソースID取得
		/// @return リソースID
		ResourceID GetResourceID() const noexcept
		{
			return static_cast<ResourceID>(GetInstanceID());
		}

		/// @brief リソース名取得
		/// @return リソース名
		std::string_view GetName() const { return m_name; }

		/// @brief リソース名変更
		/// @param name リソース名
		void SetName(const std::string& name) { m_name = name; }

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
