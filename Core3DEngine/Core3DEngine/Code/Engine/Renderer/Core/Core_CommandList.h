/*****************************************************************//**
 * \file   Core_CommandList.h
 * \brief  �����_�[�R�}���h���X�g�N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _CORE_RENDER_CONTEXT_
#define _CORE_RENDER_CONTEXT_

#include "Core_Buffer.h"
#include "Core_Material.h"
#include "Core_RenderBuffer.h"
#include "Core_RenderTarget.h"
#include "Core_DepthStencil.h"
#include "Core_ShaderResource.h"


namespace core
{
	/// @class CoreCommandList
	/// @brief �����_�[�R�}���h���X�g
	class CoreCommandList
	{
		friend class CoreRenderer;
	public:

		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit CoreCommandList()
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~CoreCommandList() noexcept = default;


		//----- ���\�[�X�w�薽�� -----

		/// @brief �}�e���A���w��
		/// @param materialID �}�e���A��ID
		virtual void setMaterial(const MaterialID& materialID) = 0;

		/// @brief �����_�[�o�b�t�@�w��
		/// @param renderBufferID �����_�[�o�b�t�@ID
		virtual void setRenderBuffer(const RenderBufferID& renderBufferID) = 0;


		//----- �Z�b�g���� -----

		virtual void setBackBuffer() = 0;

		virtual void setGraphicsPipelineState(const ShaderID& shaderID, const BlendState& bs,
			const RasterizeState& rs, const DepthStencilState& ds) = 0;

		virtual void setRenderTarget(const RenderTargetID& rtID) = 0;
		virtual void setRenderTarget(const std::uint32_t num, const RenderTargetID rtIDs[]) = 0;
		virtual void setRenderTarget(const RenderTargetID& rtID, const DepthStencilID& dsID) = 0;
		virtual void setRenderTarget(const std::uint32_t num, const RenderTargetID rtIDs[], const DepthStencilID& dsID) = 0;

		virtual void setViewport(const Rect& rect) = 0;
		virtual void setViewport(const Viewport& viewport) = 0;

		//----- �Q�b�g���� -----


		//----- �o�C���h���� -----

		virtual void bindGlobalBuffer(const core::ShaderID& shaderID, const std::string& bindName, const core::BufferID& bufferID) = 0;

		virtual void bindGlobalTexture(const core::ShaderID& shaderID, const std::string& bindName, const core::TextureID& textureID) = 0;

		virtual void bindGlobalSampler(const core::ShaderID& shaderID, const std::string& bindName, const core::SamplerState& sampler) = 0;


		//----- �`�施�� -----

		/// @brief �`�施��
		/// @param renderBufferID �����_�[�o�b�t�@ID
		virtual void render(const RenderBufferID& renderBufferID, const std::uint32_t instanceCount = 1) = 0;

		/// @brief 
		/// @param destID �Ώۂ̃����_�[�^�[�Q�b�g
		/// @param sourceID 
		/// @param matID 
		virtual void blit(const RenderBufferID& destID, const TextureID& sourceID, const MaterialID& matID) = 0;


		//----- �N���A -----

		virtual void clearCommand() = 0;		///< �R�}���h�̃N���A

		virtual void clearBackBuffer(const Color& color) = 0;

		virtual void clearRederTarget(const RenderTargetID& rtID, const Color& color) = 0;

		virtual void clearDepthStencil(const DepthStencilID& dsID, float depth, std::uint8_t stencil) = 0;


		//----- �R�s�[ -----

		virtual void copyBackBuffer(const TextureID& sourceID) = 0;

		virtual void copyTexture(const TextureID& destID, const TextureID& sourceID) = 0;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------


	private:

	};
}

#endif // !_CORE_RENDER_CONTEXT_
