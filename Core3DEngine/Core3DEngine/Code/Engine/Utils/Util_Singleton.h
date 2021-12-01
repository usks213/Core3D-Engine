/*****************************************************************//**
 * \file   Util_UtilSingleton.h
 * \brief  �e���v���[�g�V���O���g��
 * 
 * \author USAMI KOSHI
 * \date   2021/06/14
 *********************************************************************/
#ifndef _UTIL_SINGLETON_
#define _UTIL_SINGLETON_

namespace util
{
    ///@class UtilSingleton
    ///@brief �e���v���[�g�V���O���g��
    template <class T>
    class UtilSingleton
    {
    public:
        //------------------------------------------------------------------------------
        // public methods
        //------------------------------------------------------------------------------

        ///@brief �C���X�^���X�擾
        ///@return �C���X�^���X
        static T& get() {
            static T instance;
            return instance;
        }

    protected:
        //------------------------------------------------------------------------------
        // protected methods
        //------------------------------------------------------------------------------

        /// @brief �f�t�H���g�R���X�g���N�^
        UtilSingleton() = default;

        /// @brief �f�t�H���g�f�X�g���N�^
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
