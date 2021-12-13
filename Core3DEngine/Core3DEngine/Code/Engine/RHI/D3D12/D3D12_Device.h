/*****************************************************************//**
 * \file   D3D12_Device.h
 * \brief  DirectX12�f�o�C�X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/13
 *********************************************************************/

#ifndef _D3D12_RENDER_DEVICE_
#define _D3D12_RENDER_DEVICE_

#include <RHI/Core/Device.h>
#include "D3D12_CommonState.h"
#include "D3D12_DescriptorPool.h"
#include <tuple>
#include <map>


namespace Core::D3D12
{
	// �O��`
	class D3D12Renderer;
	class D3D12Shader;
	class D3D12Material;
	class D3D12Texture;

	/// @class D3D12Device
	/// @brief D3D12�f�o�C�X
	class D3D12Device final : public Core::Device
	{
		friend class D3D12Renderer;
		friend class D3D12CommandList;
		friend class D3D12Shader;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit D3D12Device();

		/// @brief �f�X�g���N�^
		~D3D12Device() noexcept = default;

		/// @brief ����������
		/// @param pDevice D3D12�f�o�C�X�|�C���^
		/// @param hWnd �E�B���h�E�n���h��
		/// @param width �E�B���h�E�̕�
		/// @param height �E�B���h�E�̍���
		/// @return ������: ���� true | ���s false
		HRESULT initialize(ID3D12Device* pDevice, IDXGIFactory2* pFactory2, 
			HWND hWnd, UINT width, UINT height);

		//----- ���\�[�X���� -----

		Core::GPUBufferID		CreateBuffer(Core::GPUBufferDesc& desc, const Core::GPUBufferData* pData = nullptr) override;
		Core::DepthStencilID	CreateDepthStencil(Core::TextureDesc& desc, float depth = 1.0f, std::uint8_t stencil = 0) override;
		Core::MaterialID		CreateMaterial(std::string name, Core::ShaderID& shaderID) override;
		Core::MeshID			CreateMesh(std::string name) override;
		Core::RenderBufferID	CreateRenderBuffer(Core::ShaderID& shaderID, Core::MeshID& meshID) override;
		Core::RenderTargetID	CreateRenderTarget(Core::TextureDesc& desc, const Color& color = Color()) override;
		Core::ShaderID		CreateShader(Core::ShaderDesc& desc) override;
		Core::TextureID		CreateTexture(std::string filePath) override;
		Core::TextureID		CreateTexture(Core::TextureDesc& desc, const Core::TextureData* pData = nullptr) override;

		//----- Native DirectX12 -----

		ID3D12Device* GetD3D12Device() { return m_pD3DDevice; }
		UINT GetBackBufferCount() { return m_backBufferCount; }
		DXGI_FORMAT GetBackBufferFormat() { return m_backBufferFormat; }
		D3D12DescriptorPool* GetTextureDescriptor() { return m_pTexturePool.get(); }

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief ���ʃX�e�[�g�̐���
		/// @return HRESULT
		HRESULT CreateCommonState();

		/// @brief D3D12�e�N�X�`������(�N���A�l����)
		/// @param desc �e�N�X�`��Desc
		/// @param pClear �N���A�f�[�^
		/// @return D3D12�e�N�X�`���|�C���^
		D3D12Texture* CreateD3D12Texture(Core::TextureDesc& desc, D3D12_CLEAR_VALUE* pClear);

		/// @brief �p�C�v���C���X�e�[�g����
		/// @param d3d12Shader �V�F�[�_�[
		/// @param d3d12Mat �}�e���A��
		/// @return �p�C�v���C���X�e�[�g
		ID3D12PipelineState* CreateGraphicsPipelineState(D3D12Shader& d3d12Shader, const Core::BlendState& bs,
			const Core::RasterizeState& rs, const Core::DepthStencilState& ds);


		//--- �X�V���\�[�X ---
		
		/// @brief �X�V���\�[�X�����X�g�ɒǉ�
		/// @param pResource D3D12���\�[�X�|�C���^
		/// @param pData �f�[�^�|�C���^
		/// @param size �f�[�^�T�C�Y
		void AddUpdateResource(ID3D12Resource* pResource, void* pData, std::size_t size);

		/// @brief �X�V���\�[�X���X�g�̎��s
		void ExecuteUpdateResurce();

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		ID3D12Device*						m_pD3DDevice;			///< �f�o�C�X�|�C���^

		//ComPtr<IDXGISwapChain1>				m_swapChain;			///< �X���b�v�`�F�[��

		//ComPtr<ID3D12Texture2D>				m_backBufferRT;			///< �o�b�N�o�b�t�@
		//ComPtr<ID3D12RenderTargetView>		m_backBufferRTV;		///< �o�b�N�o�b�t�@�r���[
		DXGI_FORMAT							m_backBufferFormat;		///< �o�b�t�@�o�b�t�@�t�H�[�}�b�g

		//ComPtr<ID3D12Texture2D>				m_depthStencilTexture;	///< Z�o�b�t�@
		//ComPtr<ID3D12DepthStencilView>		m_depthStencilView;		///< Z�o�b�t�@�r���[
		DXGI_FORMAT							m_depthStencilFormat;	///< Z�o�b�t�@�t�H�[�}�b�g

		HWND									m_hWnd;					///< �E�B���h�E�n���h��
		D3D12_VIEWPORT						m_viewport;				///< �r���[�|�[�g

		UINT									m_backBufferCount;		///< �o�b�N�o�b�t�@��
		UINT									m_nOutputWidth;			///< �o�̓T�C�Y(��)
		UINT									m_nOutputHeight;		///< �o�̓T�C�Y(����)

		// �X�e�[�g
		D3D12_RASTERIZER_DESC              	m_rasterizeStates[(size_t)Core::RasterizeState::MAX];		///< ���X�^���C�U�X�e�[�g
		D3D12_BLEND_DESC                   	m_blendStates[(size_t)Core::BlendState::MAX];				///< �u�����h�X�e�[�g
		D3D12_DEPTH_STENCIL_DESC           	m_depthStencilStates[(size_t)Core::DepthStencilState::MAX];	///< �[�x�X�e���V���X�e�[�g

		// �T���v���[
		D3D12_STATIC_SAMPLER_DESC 			m_staticSamplers[(size_t)Core::SamplerState::MAX];			///< �ÓI�T���v���X�e�[�g
		D3D12_GPU_DESCRIPTOR_HANDLE			m_dynamicSamplers[(size_t)Core::SamplerState::MAX];			///< �_�C�i�b�N�T���v���[
		ComPtr<ID3D12DescriptorHeap>			m_pSamplerHeap;											///< �T���v���[�q�[�v

		// �O���t�B�N�X�p�C�v���C���X�e�[�g
		using GraphicsPipelineStateID = std::tuple<Core::ShaderID, Core::BlendState, Core::RasterizeState, Core::DepthStencilState>;
		std::map<GraphicsPipelineStateID, ComPtr<ID3D12PipelineState>>	m_pGraphicsPipelineState;

		//--- �X�V���\�[�X ---
		struct UpdateResourceData
		{
			ID3D12Resource*			pResource = nullptr;
			std::vector<std::byte>	data;
		};
		std::vector<UpdateResourceData>			m_updateResourceList;

		// �f�B�X�N���v�^�v�[��
		std::unique_ptr<D3D12DescriptorPool>	m_pTexturePool;
	};
}

#endif // !_D3D12_RENDER_DEVICE_