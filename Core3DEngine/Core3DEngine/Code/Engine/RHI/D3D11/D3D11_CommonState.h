/*****************************************************************//**
 * \file   D3D11_CommonState.h
 * \brief  DirectX11���ʃX�e�C�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _D3D11_COMMON_STATE_
#define _D3D11_COMMON_STATE_

#include <RHI/Core/RHI_CommonState.h>
#include "D3D11_Defines.h"

namespace Core::RHI::D3D11
{
    /// @brief D3D11�̃��\�[�X�g�p���ʎ擾
    /// @param usage ���\�[�X�g�p����
    /// @return D3D11���\�[�X�g�p����
    D3D11_USAGE GetD3D11Usage(Usage usage);

    /// @brief D3D11�̃o�C���h�t���O�擾
    /// @param flags �o�C���h�t���O
    /// @return �����Ȃ������^�o�C���h�t���O
    UINT32 GetD3D11BindFlags(UINT flags);

    /// @brief D3D11��CPU�A�N�Z�X�t���O�擾
    /// @param flags CPU�A�N�Z�X�t���O
    /// @return �����Ȃ������^CPU�A�N�Z�X�t���O
    UINT32 GetD3D11CPUAccessFlags(UINT flags);

    /// @brief D3D11�̃o�b�t�@�t���O�擾
    /// @param flags �o�b�t�@�t���O
    /// @return �����Ȃ������^�o�b�t�@�t���O
    UINT32 GetD3D11MiscFlags(UINT flags);

    /// @brief D3D11�̃v���~�e�B�u�g�|���W�[�擾
    /// @param topology �v���~�e�B�u�g�|���W�[
    /// @return D3D11�v���~�e�B�u�g�|���W�[
    D3D11_PRIMITIVE_TOPOLOGY GetD3D11PrimitiveTopology(PrimitiveTopology topology);

    /// @brief DXGI�̃e�N�X�`���t�H�[�}�b�g�擾
    /// @param format �e�N�X�`���t�H�[�}�b�g
    /// @return DXGI�t�H�[�}�b�g
    DXGI_FORMAT GetDXGIFormat(TextureFormat format);

    /// @brief TypeLess�t�H�[�}�b�g��DSV�t�H�[�}�b�g�ɕϊ����ĕԂ�
    /// @param format TypeLess�t�H�[�}�b�g
    /// @return DSV�t�H�[�}�b�g or ���̂܂�
    DXGI_FORMAT getTypeLessToDSVFormat(TextureFormat format);

    /// @brief TypeLess�t�H�[�}�b�g��SRV�t�H�[�}�b�g�ɕϊ����ĕԂ�
    /// @param format TypeLess�t�H�[�}�b�g
    /// @return SRV�t�H�[�}�b�g or ���̂܂�
    DXGI_FORMAT getTypeLessToSRVFormat(TextureFormat format);
}

#endif // !_D3D11_COMMON_STATE_

