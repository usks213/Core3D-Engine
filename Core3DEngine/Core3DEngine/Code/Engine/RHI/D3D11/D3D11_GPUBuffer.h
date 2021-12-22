/*****************************************************************//**
 * \file   D3D11_GPUBuffer.h
 * \brief  DirectX11�o�b�t�@�[
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_Buffer_
#define _D3D11_Buffer_

#include <RHI/Core/RHI_GPUBuffer.h>
#include <RHI/D3D11/D3D11_Defines.h>

namespace Core::RHI::D3D11
{
	/// @class D3D11GPUBuffer
	/// @brief DirectX11�o�b�t�@-
	class D3D11GPUBuffer final : public GPUBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param desc �o�b�t�@Desc
		/// @param data �������f�[�^
		explicit D3D11GPUBuffer(ID3D11Device1* device, const ResourceDesc& desc, const ResourceData* pData = nullptr);

		/// @brief �f�X�g���N�^
		~D3D11GPUBuffer() noexcept = default;

		/// @brief ���\�[�X�|�C���^�̎擾
		/// @return ���\�[�X�^
		void* GetResource() override { return m_pBuffer.Get(); }

		/// @brief CBV�|�C���^�̎擾
		/// @return CBV�^
		void* GetCBV() override { return m_pBuffer.Get(); }

		/// @brief SRV�|�C���^�̎擾
		/// @return SRV�^
		void* GetSRV() override { return m_pSRV.Get(); }

		/// @brief UAV�|�C���^�̎擾
		/// @return UAV�^
		void* GetUAV() override { return m_pUAV.Get(); }

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief �o�b�t�@
		ComPtr<ID3D11Buffer>				m_pBuffer;

		/// @brief �V�F�[�_�[���\�[�X�r���[
		ComPtr<ID3D11ShaderResourceView>	m_pSRV;

		/// @brief ���s���A�N�Z�X�r���[
		ComPtr<ID3D11UnorderedAccessView>	m_pUAV;
	};
}

#endif // !_D3D11_Buffer_
