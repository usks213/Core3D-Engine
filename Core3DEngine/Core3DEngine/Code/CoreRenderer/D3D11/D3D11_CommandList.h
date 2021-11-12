/*****************************************************************//**
 * \file   D3D11_CommandList.h
 * \brief  DirectX11�����_�[�R�}���h���X�g�N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _D3D11_RENDER_CONTEXT_
#define _D3D11_RENDER_CONTEXT_

#include <CoreRenderer/Core/Core_CommandList.h>
#include <CoreRenderer/D3D11/D3D11_Shader.h>
#include <CoreRenderer/D3D11/D3D11_Material.h>


namespace d3d11
{
	// �O��`
	class D3D11Renderer;
	class D3D11Device;

	/// @class D3D11CommandList
	/// @brief DirectX11�����_�[�R�}���h���X�g
	class D3D11CommandList final : public core::CoreCommandList
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

		void setMaterial(const core::MaterialID& materialID) override;

		void setRenderBuffer(const core::RenderBufferID& renderBufferID)  override;

		//----- �Z�b�g���� -----

		void setBackBuffer() override;

		void setGraphicsPipelineState(const core::ShaderID& shaderID, const core::BlendState& bs,
			const core::RasterizeState& rs, const core::DepthStencilState& ds) override;

		void setRenderTarget(const core::RenderTargetID& rtID) override;
		void setRenderTarget(const std::uint32_t num, const core::RenderTargetID rtIDs[]) override;
		void setRenderTarget(const core::RenderTargetID& rtID, const core::DepthStencilID& dsID) override;
		void setRenderTarget(const std::uint32_t num, const core::RenderTargetID rtIDs[], const core::DepthStencilID& dsID) override;

		void setViewport(const Rect& rect) override;
		void setViewport(const Viewport& viewport) override;

		//----- �Q�b�g���� -----


		//----- �o�C���h���� -----

		void bindGlobalBuffer(const core::ShaderID& shaderID, const std::string& bindName, const core::BufferID& bufferID) override;

		void bindGlobalTexture(const core::ShaderID& shaderID, const std::string& bindName, const core::TextureID& textureID) override;

		void bindGlobalSampler(const core::ShaderID& shaderID, const std::string& bindName, const core::SamplerState& sampler) override;

		//----- �`�施��

		void render(const core::RenderBufferID& renderBufferID, std::uint32_t instanceCount = 1)  override;

		/// @brief 
		/// @param destID �Ώۂ̃����_�[�^�[�Q�b�g
		/// @param sourceID 
		/// @param matID 
		void blit(const core::RenderBufferID& destID, const core::TextureID& sourceID, const core::MaterialID& matID) override;


		//----- �N���A -----

		void clearCommand() override;		///< �R�}���h�̃N���A

		void clearBackBuffer(const Color& color) override;

		void clearRederTarget(const core::RenderTargetID& rtID, const Color& color) override;

		void clearDepthStencil(const core::DepthStencilID& dsID, float depth, std::uint8_t stencil) override;


		//----- �R�s�[ -----

		void copyBackBuffer(const core::TextureID& sourceID) override;

		void copyTexture(const core::TextureID& destID, const core::TextureID& sourceID) override;

	private:
		//------------------------------------------------------------------------------
		// private methods 
		//------------------------------------------------------------------------------

		void setCBufferResource(std::uint32_t slot, const core::BufferID& bufferID, core::ShaderStage stage);

		void setTextureResource(std::uint32_t slot, const core::TextureID& textureID, core::ShaderStage stage);

		void setSamplerResource(std::uint32_t slot, core::SamplerState state, core::ShaderStage stage);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		D3D11Renderer*					m_pRenderer;				///< �����_���[
		D3D11Device*						m_pDevice;				///< �f�o�C�X

		ComPtr<ID3D11DeviceContext1>		m_pDeferredContext;		///< �f�t�@�[�h�R���e�L�X�g
		ComPtr<ID3D11CommandList>			m_pCmdList;				///< �R�}���h���X�g

		core::DepthStencilID				m_curDepthStencilID;	///< ���݂̃f�v�X�X�e���V��

		static constexpr std::uint32_t MAX_RENDER_TARGET = 8;	///< �����_�[�^�[�Q�b�g�̍ő吔

	};
}

#endif // !_D3D11_RENDER_CONTEXT_
