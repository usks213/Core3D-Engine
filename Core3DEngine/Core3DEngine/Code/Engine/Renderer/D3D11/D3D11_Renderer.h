/*****************************************************************//**
 * \file   D3D11_Renderer.h
 * \brief  DirectX11�����_���[�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _D3D11_RENDERER_
#define _D3D11_RENDERER_

#include <Renderer/Core/Renderer.h>
#include <Renderer/D3D11/D3D11_Device.h>
#include <Renderer/D3D11/D3D11_CommandList.h>

namespace Core::D3D11
{
	class D3D11Device;
	class D3D11CommandList;

	/// @brief D3D11�����_���[
	/// @class D3D11Renderer
	class D3D11Renderer final : public Renderer
	{
		friend class D3D11Device;
		friend class D3D11CommandList;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit D3D11Renderer();
		/// @brief �f�X�g���N�^
		~D3D11Renderer() noexcept = default;

		/// @brief ����������
		/// @param hWnd �E�B���h�E�n���h��
		/// @param width �E�B���h�E�̕�
		/// @param height �E�B���h�E�̍���
		/// @return ������: ���� true | ���s false
		HRESULT initialize(HWND hWnd, UINT width, UINT height);

		/// @brief �I������
		void finalize() override;

		/// @brief �t���[���J�n
		void beginFrame() override;
		/// @brief �t���[���I��
		void endFrame() override;

		/// @brief �f�o�C�X�̎擾
		/// @return �f�o�C�X�̃|�C���^
		Core::Device* getDevice() override
		{
			return &m_device;
		}

		/// @brief �R�}���h���X�g�̎擾
		/// @return �R�}���h���X�g�̃|�C���^ 
		Core::CommandList* getCommandList() override;

		/// @brief �R�s�[�R���X�g���N�^�폜
		D3D11Renderer(const D3D11Renderer&) = delete;
		/// @brief ���[�u�R���X�g���N�^�폜
		D3D11Renderer(D3D11Renderer&&) = delete;

	public:

		//--- Native ---

		/// @brief DirectX11�f�o�C�X�̎擾
		/// @return DirectX11�f�o�C�X
		ID3D11Device1* GetD3D11Device() const noexcept { return m_d3dDevice.Get(); }

		/// @brief DirectX11�C�~�f�B�G�C�g�R���e�L�X�g�̎擾
		/// @return DirectX11�f�o�C�X�R���e�L�X�g
		ID3D11DeviceContext* GetD3D11Context() const noexcept { return m_d3dContext.Get(); }

		/// @brief �C�~�f�B�G�C�g�R���e�L�X�g�Ńo�b�t�@�w��
		void SetD3D11BackBuffer();

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief �f�o�C�X�ƃR�}���h���X�g�̐���
		/// @return HRESULT
		HRESULT CreateDiveceAndContext(HWND hWnd);


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------
		static constexpr std::uint32_t BACK_BUFFER_COUNT = 2;

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		D3D11Device						m_device;					///< �f�o�C�X�N���X
		
		std::uint32_t m_curBackBufferIndex;

		std::vector<std::unique_ptr<D3D11CommandList>>	m_cmdLists[BACK_BUFFER_COUNT];			///< �R�}���h���X�g�z��
		std::uint32_t								m_useCmdListCnt[BACK_BUFFER_COUNT];	///< �g�p����Ă���R�}���h���X�g��

		ComPtr<ID3D11Device1>				m_d3dDevice;					///< �f�o�C�X
		ComPtr<ID3D11DeviceContext1>		m_d3dContext;				///< �C�~�f�B�G�C�g�R���e�L�X�g
		ComPtr<ID3DUserDefinedAnnotation>	m_d3dAnnotation;				///< �A�m�e�[�V����

		ComPtr<IDXGIFactory2>				m_dxgiFactory;				///< �t�@�N�g���[

	};
}

#endif // !_D3D11_RENDERER_
