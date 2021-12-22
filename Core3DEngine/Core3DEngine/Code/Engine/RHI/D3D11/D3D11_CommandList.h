/*****************************************************************//**
 * \file   D3D11_CommandList.h
 * \brief  DirectX11�����_�[�R�}���h���X�g�N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _D3D11_COMMAND_LSIT_
#define _D3D11_COMMAND_LSIT_

#include <RHI/Core/RHI_CommandList.h>
#include "D3D11_Defines.h"

namespace Core::RHI::D3D11
{
	// �O��`
	class D3D11Renderer;
	class D3D11Device;

	/// @class D3D11CommandList
	/// @brief DirectX11�����_�[�R�}���h���X�g
	class D3D11CommandList final : public CommandList
	{
		friend class D3D11Renderer;
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit D3D11CommandList();

		/// @brief �f�X�g���N�^(�f�t�H���g)
		~D3D11CommandList() noexcept = default;

		/// @brief ����������
		/// @param pRenderer D3D11�����_���[�|�C���^
		/// @param pDevice D3D11�f�o�C�X�|�C���^
		/// @return ������: ���� true | ���s false
		HRESULT initialize(D3D11Renderer* pRenderer, D3D11Device* pDevice);


		//----- �^�[�Q�b�g�X�e�[�g���� -----

		void SetBackBuffer() override;

		void SetRenderTarget(std::shared_ptr<RenderTarget> pRT) override;
		void SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[]) override;
		void SetRenderTarget(std::shared_ptr<RenderTarget> pRT, std::shared_ptr<DepthStencil> pDS) override;
		void SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[], std::shared_ptr<DepthStencil> pDS) override;

		void SetViewport(const Rect& rect) override;
		void SetViewport(const Viewport& viewport) override;


		//----- �p�C�v���C���X�e�[�g���� -----

		void SetGraphicsPipelineState(std::shared_ptr<GraphicsShader> pShader, const BlendState& bs,
			const RasterizeState& rs, const DepthStencilState& ds) override;

		void SetComputePipelineState() override;

		//----- ���\�[�X���� -----

		void SetConstantBuffer(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal) override;

		void SetShaderResource(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal) override;

		void SetUnorderedAccess(ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal) override;

		void SetSampler(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, SamplerState samplerState, bool isGlobal) override;

		
		//----- �W�I���g���[�X�e�[�g���� -----

		void SetVertexBuffer(std::shared_ptr<GPUBuffer> pVertexBuffer, const std::uint32_t offset) override;

		void SetIndexBuffer(std::shared_ptr<GPUBuffer> pIndexBuffer, const std::uint32_t offset) override;

		void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) override;


		//----- �`��E���s���� -----

		void DrawInstanced(std::uint32_t VertexCountPerInstance, std::uint32_t InstanceCount,
			std::uint32_t StartVertexLocation, std::uint32_t StartInstanceLocation) override;

		void DrawIndexedInstanced(std::uint32_t IndexCountPerInstance, std::uint32_t InstanceCount,
			std::uint32_t StartIndexLocation, std::int32_t  BaseVertexLocation, std::uint32_t StartInstanceLocation) override;

		void ExecuteIndirect() override;

		void Dispatch() override;


		//----- �N���A���� -----

		void ClearCommand() override;		///< �R�}���h�̃N���A

		void ClearBackBuffer(const Color& color) override;

		void ClearRederTarget(std::shared_ptr<RenderTarget> pRT, const Color& color) override;

		void ClearDepthStencil(std::shared_ptr<DepthStencil> pDS, float depth, std::uint8_t stencil) override;


		//----- �R�s�[���� -----

		void CopyToBackBuffer(std::shared_ptr<Resource> pSource) override;

		void CopyFromBackBuffer(std::shared_ptr<Resource> pDest) override;

		void CopyResource(std::shared_ptr<Resource> pDest, std::shared_ptr<Resource> pSource) override;

		//----- Native -----

		D3D11Renderer* GetD3D11Renderer() { return m_pRenderer; }

		D3D11Device* GetD3D11Device() { return m_pDevice; }

	private:
		//------------------------------------------------------------------------------
		// private methods 
		//------------------------------------------------------------------------------

		void UpdateSubResource(std::shared_ptr<Resource> pResource);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		D3D11Renderer*					m_pRenderer;				///< �����_���[
		D3D11Device*						m_pDevice;				///< �f�o�C�X

		ComPtr<ID3D11DeviceContext1>		m_pDeferredContext;		///< �f�t�@�[�h�R���e�L�X�g
		ComPtr<ID3D11CommandList>			m_pCmdList;				///< �R�}���h���X�g

		static constexpr std::uint32_t MAX_RENDER_TARGET = 8;	///< �����_�[�^�[�Q�b�g�̍ő吔

	};
}

#endif // !_D3D11_COMMAND_LSIT_
