/*****************************************************************//**
 * \file   RHI_CommandList.h
 * \brief  �����_�[�R�}���h���X�g�N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _RHI_RENDER_CONTEXT_
#define _RHI_RENDER_CONTEXT_

#include "RHI_DepthStencil.h"
#include "RHI_GPUBuffer.h"
#include "RHI_GraphicsShader.h"
#include "RHI_RenderTarget.h"
#include "RHI_Texture.h"


namespace Core::RHI
{
	/// @class CommandList
	/// @brief �����_�[�R�}���h���X�g
	class CommandList
	{
	public:

		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit CommandList()
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~CommandList() noexcept = default;


		//----- �^�[�Q�b�g�X�e�[�g���� -----

		virtual void SetBackBuffer() = 0;

		virtual void SetRenderTarget(std::shared_ptr<RenderTarget> pRT) = 0;
		virtual void SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[]) = 0;
		virtual void SetRenderTarget(std::shared_ptr<RenderTarget> pRT, std::shared_ptr<DepthStencil> pDS) = 0;
		virtual void SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[], std::shared_ptr<DepthStencil> pDS) = 0;

		virtual void SetViewport(const Rect& rect) = 0;
		virtual void SetViewport(const Viewport& viewport) = 0;


		//----- �p�C�v���C���X�e�[�g���� -----

		virtual void SetGraphicsPipelineState(std::shared_ptr<GraphicsShader> pShader, const BlendState& bs,
			const RasterizeState& rs, const DepthStencilState& ds) = 0;

		virtual void SetComputePipelineState() = 0;

		//----- ���\�[�X���� -----

		virtual void SetLocalBuffer(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, std::shared_ptr<GPUBuffer> pGPUBuffer) = 0;

		virtual void SetLocalTexture(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, std::shared_ptr<Texture> pTexture) = 0;

		virtual void SetLocalSampler(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, SamplerState samplerState) = 0;

		virtual void SetGlobalBuffer(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, std::shared_ptr<GPUBuffer> pGPUBuffer) = 0;

		virtual void SetGlobalTexture(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, std::shared_ptr<Texture> pTexture) = 0;

		virtual void SetGlobalSampler(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, SamplerState samplerState) = 0;


		//----- �W�I���g���[�X�e�[�g���� -----

		virtual void SetVertexBuffer() = 0;

		virtual void SetIndexBuffer() = 0;

		virtual void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) = 0;


		//----- �`��E���s���� -----

		virtual void DrawInstanced(std::uint32_t VertexCountPerInstance, std::uint32_t InstanceCount,
			std::uint32_t StartVertexLocation, std::uint32_t StartInstanceLocation) = 0;

		virtual void DrawIndexedInstanced(std::uint32_t IndexCountPerInstance, std::uint32_t InstanceCount,
			std::uint32_t StartIndexLocation, std::int32_t  BaseVertexLocation, std::uint32_t StartInstanceLocation) = 0;

		virtual void ExecuteIndirect() = 0;

		virtual void Dispatch() = 0;


		//----- �N���A���� -----

		virtual void ClearCommand() = 0;		///< �R�}���h�̃N���A

		virtual void ClearBackBuffer(const Color& color) = 0;

		virtual void ClearRederTarget(std::shared_ptr<RenderTarget> pRT, const Color& color) = 0;

		virtual void ClearDepthStencil(std::shared_ptr<DepthStencil> pDS, float depth, std::uint8_t stencil) = 0;


		//----- �R�s�[���� -----

		virtual void CopyBackBuffer(std::shared_ptr<Texture> pSource) = 0;

		virtual void CopyBuffer(std::shared_ptr<GPUBuffer> pDest, std::shared_ptr<GPUBuffer> pSource) = 0;

		virtual void CopyTexture(std::shared_ptr<Texture> pDest, std::shared_ptr<Texture> pSource) = 0;


		////----- �A�b�v���[�h���� -----

		//virtual void UpdateSubresources() = 0;

		//virtual void UploadBuffer() = 0;

		//virtual void UploadTexture() = 0;


	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------


	private:

	};
}

#endif // !_RHI_RENDER_CONTEXT_
