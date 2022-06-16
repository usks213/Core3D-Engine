/*****************************************************************//**
 * \file   Util_Singleton.h
 * \brief  �e���v���[�g�V���O���g��
 * 
 * \author USAMI KOSHI
 * \date   2021/06/14
 *********************************************************************/
#ifndef _UTIL_SINGLETON_
#define _UTIL_SINGLETON_

namespace Util
{
    ///@class Singleton
    ///@brief �e���v���[�g�V���O���g��
    template <class T>
    class Singleton
    {
    public:
        //------------------------------------------------------------------------------
        // public methods
        //------------------------------------------------------------------------------

        ///@brief �C���X�^���X�擾
        ///@return �C���X�^���X
        static T& GetInstance() {
            static T instance;
            return instance;
        }

    protected:
        //------------------------------------------------------------------------------
        // protected methods
        //------------------------------------------------------------------------------

        /// @brief �f�t�H���g�R���X�g���N�^
        Singleton() = default;

        /// @brief �f�t�H���g�f�X�g���N�^
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
