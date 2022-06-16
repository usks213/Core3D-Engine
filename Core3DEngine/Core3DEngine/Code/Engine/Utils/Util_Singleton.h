/*****************************************************************//**
 * \file   Util_Singleton.h
 * \brief  テンプレートシングルトン
 * 
 * \author USAMI KOSHI
 * \date   2021/06/14
 *********************************************************************/
#ifndef _UTIL_SINGLETON_
#define _UTIL_SINGLETON_

namespace Util
{
    ///@class Singleton
    ///@brief テンプレートシングルトン
    template <class T>
    class Singleton
    {
    public:
        //------------------------------------------------------------------------------
        // public methods
        //------------------------------------------------------------------------------

        ///@brief インスタンス取得
        ///@return インスタンス
        static T& GetInstance() {
            static T instance;
            return instance;
        }

    protected:
        //------------------------------------------------------------------------------
        // protected methods
        //------------------------------------------------------------------------------

        /// @brief デフォルトコンストラクタ
        Singleton() = default;

        /// @brief デフォルトデストラクタ
        virtual ~Singleton() = default;

    private:
        //------------------------------------------------------------------------------
        // private methods
        //------------------------------------------------------------------------------

        Singleton(const Singleton&) = delete;
        Singleton(const Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(const Singleton&&) = delete;
    };
}

#endif // !_UTIL_SINGLETON_
