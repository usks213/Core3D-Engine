/*****************************************************************//**
 * \file   D3D11_CommandList.h
 * \brief  DirectX11�����_�[�R�}���h���X�g�N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _D3D11_RENDER_CONTEXT_
#define _D3D11_RENDER_CONTEXT_

#include <Renderer/Core/CommandList.h>
#include <Resource/D3D11/D3D11_Shader.h>
#include <Resource/D3D11/D3D11_Material.h>


namespace Core::D3D11
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

		//----- �`�施��

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

		//----- Native -----

		D3D11Renderer* GetD3D11Renderer() { return m_pRenderer; }

	private:
		//------------------------------------------------------------------------------
		// private methods 
		//------------------------------------------------------------------------------

		void setCBufferResource(std::uint32_t slot, const Core::GPUBufferID& bufferID, Core::ShaderStage stage);

		void setTextureResource(std::uint32_t slot, const Core::TextureID& textureID, Core::ShaderStage stage);

		void setSamplerResource(std::uint32_t slot, Core::SamplerState state, Core::ShaderStage stage);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		D3D11Renderer*					m_pRenderer;				///< �����_���[
		D3D11Device*						m_pDevice;				///< �f�o�C�X

		ComPtr<ID3D11DeviceContext1>		m_pDeferredContext;		///< �f�t�@�[�h�R���e�L�X�g
		ComPtr<ID3D11CommandList>			m_pCmdList;				///< �R�}���h���X�g

		Core::DepthStencilID				m_curDepthStencilID;	///< ���݂̃f�v�X�X�e���V��

		static constexpr std::uint32_t MAX_RENDER_TARGET = 8;	///< �����_�[�^�[�Q�b�g�̍ő吔

	};
}

#endif // !_D3D11_RENDER_CONTEXT_
