/*****************************************************************//**
 * \file   D3D11_Renderer.cpp
 * \brief  DirectX11�����_���[�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#include "D3D11_Renderer.h"
#include <vector>

using namespace d3d11;


/// @brief �R���X�g���N�^
D3D11Renderer::D3D11Renderer() :
	m_curBackBufferIndex(1),
	m_cmdLists(),
	m_useCmdListCnt{0,0},
	m_device(),
	m_d3dDevice(),
	m_d3dAnnotation(),
	m_d3dContext(),
	m_dxgiFactory()
{
}

 /// @brief ����������
 /// @param hWnd �E�B���h�E�n���h��
 /// @param width �E�B���h�E�̕�
 /// @param height �E�B���h�E�̍���
 /// @return ������: ���� true | ���s false
HRESULT D3D11Renderer::initialize(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr = S_OK;

	// �f�o�C�X�ƃR�}���h���X�g�̍쐬
	CHECK_FAILED(hr = createDiveceAndContext(hWnd));

	// �f�o�C�X�̏�����
	CHECK_FAILED(hr = m_device.initialize(m_d3dDevice.Get(), 
		m_dxgiFactory.Get(), hWnd, width, height, BACK_BUFFER_COUNT));

	return hr;
}

/// @brief �I������
void D3D11Renderer::finalize()
{

}

/// @brief �t���[���J�n
void D3D11Renderer::beginFrame()
{
	//--- ���\�[�X�̍X�V
	// GPU���̃o�b�t�@�A�e�N�X�`���ȂǍX�V
	// DirectX11�͂���Ȃ�����

	//--- �R�}���h���s
	// �O�t���[���Œ��߂��R�}���h�̔��s

	// �R�}���h�̎��s
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		m_d3dContext->ExecuteCommandList(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList.Get(), false);
	}

	//--- ���t���[���̃R�}���h����

	// �o�b�t�@�C���f�b�N�X�؂�ւ�
	m_curBackBufferIndex = (m_curBackBufferIndex + 1) % BACK_BUFFER_COUNT;

	// �R�}���h���X�g�̃N���A
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		CHECK_FAILED(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList.Reset());
	}
	m_useCmdListCnt[m_curBackBufferIndex] = 0;

}

/// @brief �t���[���I��
void D3D11Renderer::endFrame()
{
	// �R�}���h�̋L�^�I��
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		m_cmdLists[m_curBackBufferIndex][i]->m_pDeferredContext->FinishCommandList(true,
			m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList.GetAddressOf());
	}

	//--- �O�t���[���̃R�}���h������҂�

	// �X���b�v
	//m_swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);	// �e�B�A�����O���e�`��
	//m_swapChain->Present(0, 0);							// �񐂒������`��
	m_device.m_swapChain->Present(1, 0);					// ���������`��
}

/// @brief �R�}���h���X�g�̎擾
/// @return �R�}���h���X�g�̃|�C���^ 
core::CoreCommandList* D3D11Renderer::getCommandList()
{
	if (m_useCmdListCnt[m_curBackBufferIndex] >= m_cmdLists[m_curBackBufferIndex].size())
	{
		auto up = std::make_unique<D3D11CommandList>();
		auto* ptr = up.get();
		ptr->initialize(this, &m_device);
		m_cmdLists[m_curBackBufferIndex].push_back(std::move(up));
		++m_useCmdListCnt[m_curBackBufferIndex];
		return ptr;
	}

	return m_cmdLists[m_curBackBufferIndex][m_useCmdListCnt[m_curBackBufferIndex]++].get();
}

//------------------------------------------------------------------------------
// private methods
//------------------------------------------------------------------------------

/// @brief �f�o�C�X�ƃR�}���h���X�g�̐���
/// @return HRESULT
HRESULT D3D11Renderer::createDiveceAndContext(HWND hWnd)
{
	HRESULT hr = S_OK;

	D3D_FEATURE_LEVEL featureLevels[] = {
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
	D3D_FEATURE_LEVEL_9_3,
	D3D_FEATURE_LEVEL_9_2,
	D3D_FEATURE_LEVEL_9_1,
	};

	// �t�@�N�g���[�̎擾
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), (void**)(&m_dxgiFactory));
	if (FAILED(hr)) {
		MessageBoxW(hWnd, L"CreateDXGIFactory1", L"Err", MB_ICONSTOP);
		return hr;
	}
	// �A�_�v�^�[�̎擾
	IDXGIAdapter* iAdapter = NULL;
	std::vector<IDXGIAdapter*> aiAdapter;
	aiAdapter.push_back(iAdapter);
	for (unsigned int index = 0;; index++)
	{
		HRESULT	ret = m_dxgiFactory->EnumAdapters(index, &iAdapter);

		if (ret == DXGI_ERROR_NOT_FOUND)
		{
			break;
		}
		// �` �A�_�v�^�̑I��
		aiAdapter.push_back(iAdapter);
	}
	aiAdapter.pop_back();
	if (aiAdapter.size() <= 0)
	{
		aiAdapter.push_back(NULL);
	}


	//--- �f�o�C�X�̐��� ---
	ComPtr<ID3D11Device>				device;
	ComPtr<ID3D11DeviceContext>		context;

	// �f�o�C�X�B�R�}���h���X�g�̐���
	hr = D3D11CreateDevice(
		aiAdapter.back(),
		aiAdapter.back() ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		featureLevels,
		7,
		D3D11_SDK_VERSION,
		device.GetAddressOf(),
		NULL,
		context.GetAddressOf());
	if (FAILED(hr)) {
		MessageBoxW(hWnd, L"D3D11CreateDevice", L"Err", MB_ICONSTOP);
		return hr;
	}

	// �i�[
	hr = device.As(&m_d3dDevice);
	hr = context.As(&m_d3dContext);

	return hr;
}
