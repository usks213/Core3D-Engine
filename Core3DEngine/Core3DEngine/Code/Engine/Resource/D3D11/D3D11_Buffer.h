/*****************************************************************//**
 * \file   D3D11_Buffer.h
 * \brief  DirectX11�o�b�t�@�[
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_Buffer_
#define _D3D11_Buffer_

#include <CoreRenderer/Core/Core_Buffer.h>
#include <CoreRenderer/D3D11/D3D11_Defines.h>

namespace d3d11
{
	/// @class D3D11Buffer
	/// @brief DirectX11�o�b�t�@-
	class D3D11Buffer final : public core::CoreBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param id �o�b�t�@ID
		/// @param desc �o�b�t�@Desc
		/// @param data �������f�[�^
		explicit D3D11Buffer(ID3D11Device1* device, const core::BufferID& id, 
			const core::BufferDesc& desc, const core::BufferData* pData = nullptr);

		/// @brief �f�X�g���N�^
		~D3D11Buffer() noexcept = default;

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
