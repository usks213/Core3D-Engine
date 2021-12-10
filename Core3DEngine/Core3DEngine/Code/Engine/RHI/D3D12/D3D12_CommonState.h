/*****************************************************************//**
 * \file   D3D12_CommonState.h
 * \brief  DirectX12���ʃX�e�[�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/13
 *********************************************************************/
#ifndef _D3D12_COMMON_STATE_
#define _D3D12_COMMON_STATE_

#include <RHI/Core/CommonState.h>
#include "D3D12_Defines.h"

namespace Core::D3D12
{
    /// @brief ���\�[�X�t���O�擾
    /// @param flags �t���O
    /// @return D3D12���\�[�X�t���O
    D3D12_RESOURCE_FLAGS getD3D12ResourceFlags(UINT bindFlags);

    /// @brief �q�[�v�t���O�擾
    /// @param flags �t���O
    /// @return D3D12�q�[�v�t���O
    D3D12_DESCRIPTOR_HEAP_FLAGS getD3D12HeapFlags(UINT bindFlags);

    /// @brief D3D12�̃v���~�e�B�u�g�|���W�[�擾
    /// @param topology �v���~�e�B�u�g�|���W�[
    /// @return D3D12�v���~�e�B�u�g�|���W�[
    D3D12_PRIMITIVE_TOPOLOGY getD3D12PrimitiveTopology(Core::PrimitiveTopology topology);

    /// @brief DXGI�̃e�N�X�`���t�H�[�}�b�g�擾
    /// @param format �e�N�X�`���t�H�[�}�b�g
    /// @return DXGI�t�H�[�}�b�g
    DXGI_FORMAT getDXGIFormat(Core::TextureFormat format);

    /// @brief TypeLess�t�H�[�}�b�g��DSV�t�H�[�}�b�g�ɕϊ����ĕԂ�
    /// @param format TypeLess�t�H�[�}�b�g
    /// @return DSV�t�H�[�}�b�g or ���̂܂�
    DXGI_FORMAT getTypeLessToDSVFormat(Core::TextureFormat format);

    /// @brief TypeLess�t�H�[�}�b�g��SRV�t�H�[�}�b�g�ɕϊ����ĕԂ�
    /// @param format TypeLess�t�H�[�}�b�g
    /// @return SRV�t�H�[�}�b�g or ���̂܂�
    DXGI_FORMAT getTypeLessToSRVFormat(Core::TextureFormat format);
}

#endif // !_D3D12_COMMON_STATE_

