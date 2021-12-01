/*****************************************************************//**
 * \file   D3D11_RenderBuffer.h
 * \brief  DirectX11�`��o�b�t�@
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_RENDER_BUFFER_
#define _D3D11_RENDER_BUFFER_

#include <CoreRenderer/Core/Core_RenderBuffer.h>
#include "D3D11_Defines.h"

namespace d3d11
{
	/// @class D3D11RenderBuffer
	/// @brief DirectX11�����_�[�o�b�t�@
	class D3D11RenderBuffer final : public core::CoreRenderBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param id �����_�[�o�b�t�@ID
		/// @param shader �V�F�[�_�[
		/// @param mesh ���b�V��
		explicit D3D11RenderBuffer(ID3D11Device1* device, const core::RenderBufferID id, 
			const core::CoreShader& shader, const core::CoreMesh& mesh);

		/// @brief �f�X�g���N�^
		~D3D11RenderBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		ComPtr<ID3D11Buffer> m_vertexBuffer;	///< ���_�o�b�t�@
		ComPtr<ID3D11Buffer> m_indexBuffer;		///< �C���f�b�N�X�o�b�t�@
	};
}

#endif // !_D3D11_RENDER_BUFFER_