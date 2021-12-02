/*****************************************************************//**
 * \file   D3D12_CommandList.h
 * \brief  DiectX12�����_�[�R�}���h���X�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/13
 *********************************************************************/

#ifndef _D3D12_RENDER_CONTEXT_
#define _D3D12_RENDER_CONTEXT_

#include <Renderer/Core/CommandList.h>
#include <Resource\D3D12\D3D12_Shader.h>
#include <Resource\D3D12\D3D12_Material.h>

#include <tuple>
#include <map>

namespace Core::D3D12
{
	// �O��`
	class D3D12Renderer;
	class D3D12Device;

	/// @class D3D12CommandList
	/// @brief DirectX11�����_�[�R�}���h���X�g
	class D3D12CommandList final : public Core::CommandList
	{
		friend class D3D12Renderer;
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit D3D12CommandList();

		/// @brief �f�X�g���N�^(�f�t�H���g)
		~D3D12CommandList() noexcept = default;

		/// @brief ����������
		/// @param pRenderer D3D12�����_���[�|�C���^
		/// @param pDevice D3D12�f�o�C�X�|�C���^
		/// @return ������: ���� true | ���s false
		HRESULT initialize(D3D12Renderer* pRenderer, D3D12Device* pDevice);


		//----- ���\�[�X�w�薽�� -----

		void setMaterial(const Core::MaterialID& materialID) override;

		void setRenderBuffer(const Core::RenderBufferID& renderBufferID)  override;

		//----- �Z�b�g���� -----

		void setBackBuffer() override;

		void setGraphicsPipelineState(const Core::ShaderID& shaderID, const Core::BlendState& bs,
			const Core::RasterizeState& rs, const Core::DepthStencilState& ds) override;

		void setRenderTarget(const Core::RenderTargetID& rtID) override;
		void setRenderTarget(const std::uint32_t num, const Core::RenderTargetID rtIDs[]) override;
		void setRenderTarget(const Core::RenderTargetID& rtID, const Core::DepthStencilID& dsID) override;
		void setRenderTarget(const std::uint32_t num, const Core::RenderTargetID rtIDs[], const Core::DepthStencilID& dsID) override;

		void setViewport(const Rect& rect) override;
		void setViewport(const Viewport& viewport) override;

		//----- �Q�b�g���� -----

		//----- �o�C���h���� -----

		void bindGlobalBuffer(const Core::ShaderID& shaderID, const std::string& bindName, const Core::GPUBufferID& bufferID) override;

		void bindGlobalTexture(const Core::ShaderID& shaderID, const std::string& bindName, const Core::TextureID& textureID) override;

		void bindGlobalSampler(const Core::ShaderID& shaderID, const std::string& bindName, const Core::SamplerState& sampler) override;

		//----- �`�施�� -----

		void render(const Core::RenderBufferID& renderBufferID, std::uint32_t instanceCount = 1)  override;

		/// @brief 
		/// @param destID �Ώۂ̃����_�[�^�[�Q�b�g
		/// @param sourceID 
		/// @param matID 
		void blit(const Core::RenderBufferID& destID, const Core::TextureID& sourceID, const Core::MaterialID& matID) override;


		//----- �N���A -----

		void clearCommand() override;		///< �R�}���h�̃N���A

		void clearBackBuffer(const Color& color) override;

		void clearRederTarget(const Core::RenderTargetID& rtID, const Color& color) override;

		void clearDepthStencil(const Core::DepthStencilID& dsID, float depth, std::uint8_t stencil) override;


		//----- �R�s�[ -----

		void copyBackBuffer(const Core::TextureID& sourceID) override;

		void copyTexture(const Core::TextureID& destID, const Core::TextureID& sourceID) override;


	public:
		// native

		ID3D12GraphicsCommandList* GetD3D12GraphicsCommandList() { return m_pCmdList.Get(); }

	private:
		//------------------------------------------------------------------------------
		// private methods 
		//------------------------------------------------------------------------------

		void setTextureResource(Core::ShaderStage stage, std::uint32_t rootIndex, const Core::TextureID& textureID);

		void setSamplerResource(Core::ShaderStage stage, std::uint32_t rootIndex, Core::SamplerState state);

		void setTrasitionResourceBarrier(ID3D12Resource* pResource, 
			D3D12_RESOURCE_STATES& before, const D3D12_RESOURCE_STATES after);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		D3D12Renderer*					m_pRenderer;			///< �����_���[
		D3D12Device*						m_pDevice;			///< �f�o�C�X

		ComPtr<ID3D12CommandAllocator>		m_pCmdAllocator;		///< �R�}���h�A���P�[�^�[
		ComPtr<ID3D12GraphicsCommandList>	m_pCmdList;			///< �R�}���h���X�g

		Core::DepthStencilID				m_curDepthStencilID;	///< ���݂̃f�v�X�X�e���V��

		static constexpr std::uint32_t MAX_RENDER_TARGET = 8;	///< �����_�[�^�[�Q�b�g�̍ő吔
	};
}

#endif // !_D3D12_RENDER_CONTEXT_
