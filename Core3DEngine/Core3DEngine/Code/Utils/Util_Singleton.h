/*****************************************************************//**
 * \file   Util_UtilSingleton.h
 * \brief  テンプレートシングルトン
 * 
 * \author USAMI KOSHI
 * \date   2021/06/14
 *********************************************************************/
#ifndef _UTIL_SINGLETON_
#define _UTIL_SINGLETON_

namespace util
{
    ///@class UtilSingleton
    ///@brief テンプレートシングルトン
    template <class T>
    class UtilSingleton
    {
    public:
        //------------------------------------------------------------------------------
        // public methods
        //------------------------------------------------------------------------------

        ///@brief インスタンス取得
        ///@return インスタンス
        static T& get() {
            static T instance;
            return instance;
        }

    protected:
        //------------------------------------------------------------------------------
        // protected methods
        //------------------------------------------------------------------------------

        /// @brief デフォルトコンストラクタ
        UtilSingleton() = default;

        /// @brief デフォルトデストラクタ
        virtual ~UtilSingleton() = default;

    private:
        //------------------------------------------------------------------------------
        // private methods
        //------------------------------------------------------------------------------

        UtilSingleton(const UtilSingleton&) = delete;
        UtilSingleton(const UtilSingleton&&) = delete;
        UtilSingleton& operator=(const UtilSingleton&) = delete;
        UtilSingleton& operator=(const UtilSingleton&&) = delete;
    };
}

#endif // !_UTIL_SINGLETON_
