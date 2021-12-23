/*****************************************************************//**
 * \file   D3D11_DepthStencil.h
 * \brief  DirectX11�f�v�X�X�e���V��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_DEPTH_STENCIL_
#define _D3D11_DEPTH_STENCIL_

#include <RHI/Core/RHI_DepthStencil.h>
#include "D3D11_Texture.h"
#include <memory>

namespace Core::RHI::D3D11
{
	/// @class D3D11DepthStencil
	/// @brief DreictX11�[�x�X�e���V��
	class D3D11DepthStencil final : public DepthStencil, public D3D11Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param pDevice �f�o�C�X
		/// @param desc �e�N�X�`�����
		/// @param pData �������f�[�^
		explicit D3D11DepthStencil(ID3D11Device1* pDevice, ResourceDesc& desc, const ResourceData* pData = nullptr);

		/// @brief �f�X�g���N�^
		~D3D11DepthStencil() noexcept = default;

		/// @brief �f�v�X�X�e���V���r���[�̎擾
		/// @return �ėp�|�C���^
		void* GetDSV() override { return m_dsv.Get(); }

	protected:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief D3D11�[�x�X�e���V���r���[
		ComPtr<ID3D11DepthStencilView>		m_dsv;
	};
}

#endif // !_D3D11_DEPTH_STENCIL_
