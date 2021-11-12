/*****************************************************************//**
 * \file   D3D11_Device.h
 * \brief  DirectX11�f�o�C�X�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _D3D11_RENDER_DEVICE_
#define _D3D11_RENDER_DEVICE_

#include <CoreRenderer/Core/Core_Device.h>
#include "D3D11_CommonState.h"

namespace d3d11
{
	// �O��`
	class D3D11Renderer;

	/// @class D3D11Device
	/// @brief D3D11�f�o�C�X
	class D3D11Device final : public core::CoreDevice
	{
		friend class D3D11Renderer;
		friend class D3D11CommandList;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit D3D11Device();

		/// @brief �f�X�g���N�^
		~D3D11Device() noexcept = default;

		/// @brief ����������
		/// @param pDevice D3D11�f�o�C�X�|�C���^
		/// @param hWnd �E�B���h�E�n���h��
		/// @param width �E�B���h�E�̕�
		/// @param height �E�B���h�E�̍���
		/// @return ������: ���� true | ���s false
		HRESULT initialize(ID3D11Device1* pDevice, IDXGIFactory2* pFactory2, 
			HWND hWnd, UINT width, UINT height, UINT backBufferCount);

		//----- ���\�[�X���� -----

		core::BufferID		createBuffer(core::BufferDesc& desc, const core::BufferData* pData = nullptr) override;
		core::DepthStencilID	createDepthStencil(core::TextureDesc& desc, float depth = 1.0f, std::uint8_t stencil = 0) override;
		core::MaterialID		createMaterial(std::string name, core::ShaderID& shaderID) override;
		core::MeshID			createMesh(std::string name) override;
		core::RenderBufferID	createRenderBuffer(core::ShaderID& shaderID, core::MeshID& meshID) override;
		core::RenderTargetID	createRenderTarget(core::TextureDesc& desc, const Color& color = Color()) override;
		core::ShaderID		createShader(core::ShaderDesc& desc) override;
		core::TextureID		createTexture(std::string filePath) override;
		core::TextureID		createTexture(core::TextureDesc& desc, const core::TextureData* pData = nullptr) override;

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief �X���b�v�`�F�[���ƃo�b�t�@�̐���
		/// @return HRESULT
		HRESULT createSwapChainAndBuffer(IDXGIFactory2* pFactory2);

		/// @brief ���ʃX�e�[�g�̐���
		/// @return HRESULT
		HRESULT createCommonState();

		//--- �X�V���\�[�X ---

		/// @brief �X�V���\�[�X�����X�g�ɒǉ�
		/// @param pResource D3D11���\�[�X�|�C���^
		/// @param pData �f�[�^�|�C���^
		/// @param size �f�[�^�T�C�Y
		void AddUpdateResource(ID3D11Resource* pResource, void* pData, std::size_t size);

		/// @brief �X�V���\�[�X���X�g�̎��s
		void ExecuteUpdateResurce(ID3D11DeviceContext1* pContext);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		ID3D11Device1*					m_pD3DDevice;			///< �f�o�C�X�|�C���^

		ComPtr<IDXGISwapChain1>			m_swapChain;			///< �X���b�v�`�F�[��

		ComPtr<ID3D11Texture2D>			m_backBufferRT;			///< �o�b�N�o�b�t�@
		ComPtr<ID3D11RenderTargetView>		m_backBufferRTV;		///< �o�b�N�o�b�t�@�r���[
		DXGI_FORMAT						m_backBufferFormat;		///< �o�b�t�@�o�b�t�@�t�H�[�}�b�g

		ComPtr<ID3D11Texture2D>			m_depthStencilTexture;	///< Z�o�b�t�@
		ComPtr<ID3D11DepthStencilView>		m_depthStencilView;		///< Z�o�b�t�@�r���[
		DXGI_FORMAT						m_depthStencilFormat;	///< Z�o�b�t�@�t�H�[�}�b�g

		HWND								m_hWnd;					///< �E�B���h�E�n���h��
		D3D11_VIEWPORT					m_viewport;				///< �r���[�|�[�g

		UINT								m_backBufferCount;		///< �o�b�N�o�b�t�@��
		UINT								m_nOutputWidth;			///< �o�̓T�C�Y(��)
		UINT								m_nOutputHeight;		///< �o�̓T�C�Y(����)

		ComPtr<ID3D11RasterizerState>		m_rasterizeStates[(size_t)core::RasterizeState::MAX];		///< ���X�^���C�U�X�e�[�g
		ComPtr<ID3D11SamplerState>		m_samplerStates[(size_t)core::SamplerState::MAX];			///< �T���v���X�e�[�g
		ComPtr<ID3D11BlendState>			m_blendStates[(size_t)core::BlendState::MAX];				///< �u�����h�X�e�[�g
		ComPtr<ID3D11DepthStencilState>	m_depthStencilStates[(size_t)core::DepthStencilState::MAX];	///< �[�x�X�e���V���X�e�[�g

		//--- �X�V���\�[�X ---
		struct UpdateResourceData
		{
			ID3D11Resource* pResource = nullptr;
			std::vector<std::byte>	data;
		};
		std::vector<UpdateResourceData>		m_updateResourceList;

	};
}

#endif // !_D3D11_RENDER_DEVICE_
