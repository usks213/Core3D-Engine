/*****************************************************************//**
 * \file   D3D12_RenderBuffer.h
 * \brief  DirectX12���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@
 * 
 * \author USAMI KOSHI
 * \date   2021/10/12
 *********************************************************************/
#ifndef _D3D12_RENDER_BUFFER_
#define _D3D12_RENDER_BUFFER_

#include <CoreRenderer/Core/Core_RenderBuffer.h>
#include "D3D12_Defines.h"

namespace d3d12
{
	/// @class D3D12RenderBuffer
	/// @brief DirectX12�����_�[�o�b�t�@
	class D3D12RenderBuffer final : public core::CoreRenderBuffer
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
		explicit D3D12RenderBuffer(ID3D12Device* device, const core::RenderBufferID id, 
			const core::CoreShader& shader, const core::CoreMesh& mesh);

		/// @brief �f�X�g���N�^
		~D3D12RenderBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		ComPtr<ID3D12Resource>		m_pVertexBuffer;	///< ���_�o�b�t�@
		ComPtr<ID3D12Resource>		m_pIndexBuffer;		///< �C���f�b�N�X�o�b�t�@

		D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView;	///< ���_�o�b�t�@�r���[
		D3D12_INDEX_BUFFER_VIEW		m_indexBufferVew;	///< �C���f�b�N�X�o�b�t�@�r���[
	};
}

#endif // !_D3D12_RENDER_BUFFER_
