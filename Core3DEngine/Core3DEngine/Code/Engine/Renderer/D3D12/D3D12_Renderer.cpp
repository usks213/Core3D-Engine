/*****************************************************************//**
 * \file   D3D12_Renderer.h
 * \brief  DirectX12�����_���[
 *
 * \author USAMI KOSHI
 * \date   2021/10/08
 *********************************************************************/

#include "D3D12_Renderer.h"
using namespace d3d12;


//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief �R���X�g���N�^
D3D12Renderer::D3D12Renderer() :
	m_eBackBufferSate{ D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_PRESENT }
{

}

/// @brief ����������
/// @param hWnd �E�B���h�E�n���h��
/// @param width �E�B���h�E�̕�
/// @param height �E�B���h�E�̍���
/// @return ������: ���� true | ���s false
HRESULT D3D12Renderer::initialize(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr = S_OK;

	//----- �f�o�b�O���C���[�E�t�@�N�g���[ -----

#ifdef _DEBUG
	// �f�o�b�O���C���[
	{
		hr = D3D12GetDebugInterface(IID_PPV_ARGS(m_pDebugLater.ReleaseAndGetAddressOf()));
		CHECK_FAILED(hr);
		m_pDebugLater->EnableDebugLayer();
	}
#endif // _DEBUG

	// �t�@�N�g���[�̐���
	{
#ifdef _DEBUG
		hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_pDXGIFactory.ReleaseAndGetAddressOf()));
#else
		hr = CreateDXGIFactory1(IID_PPV_ARGS(m_pDXGIFactory.ReleaseAndGetAddressOf()));
#endif // _DEBUG
		CHECK_FAILED(hr);
	}

	//----- �A�_�v�^�E�f�o�C�X -----

	// �f�o�C�X����
	hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(m_pD3DDevice.ReleaseAndGetAddressOf()));
	CHECK_FAILED(hr);


	//----- �R�}���h�L���[ -----
	D3D12_COMMAND_LIST_TYPE cmdType = D3D12_COMMAND_LIST_TYPE_DIRECT;
	UINT nodeMask = 0;

	// �R�}���h�L���[�̐���
	{
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = cmdType;									// �R�}���h�o�b�t�@�̎��
		desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;	// �R�}���h�L���[�̗D��x
		desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;				// ??? GPUTimeOut
		desc.NodeMask = nodeMask;								// GPU���ʃ}�X�N(1��0)

		hr = m_pD3DDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(m_pCmdQueue.ReleaseAndGetAddressOf()));
		CHECK_FAILED(hr);
	}

	//----- �X���b�v�`�F�C���E�t�F���X�E�����_�[�^�[�Q�b�g -----

	// �X���b�v�`�F�C���̐���
	{
		DXGI_SWAP_CHAIN_DESC1 desc = {};
		desc.Width = width;
		desc.Height = height;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Stereo = false;								// �t���X�N���[���w��
		desc.SampleDesc = DXGI_SAMPLE_DESC{ 1,0 };	
		desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;			// �o�b�t�@����
		desc.BufferCount = BACK_BUFFER_COUNT;				// �o�b�N�o�b�t�@��
		desc.Scaling = DXGI_SCALING_STRETCH;				// �o�b�N�o�b�t�@�̃X�P�[�����O�w��
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// �X���b�v���̃o�b�t�@�̈���
		desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;		// �A���t�@���[�h??
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;// ����I�v�V���� (�t���X�N���[���؂�ւ���)

		IDXGISwapChain1* pTempSwapChain1;
		hr = m_pDXGIFactory->CreateSwapChainForHwnd(
			m_pCmdQueue.Get(),
			hWnd,
			&desc,
			nullptr,
			nullptr,
			&pTempSwapChain1
		);
		CHECK_FAILED(hr);
		
		// �X���b�v�`�F�C���S�ɕϊ�
		hr = pTempSwapChain1->QueryInterface(IID_PPV_ARGS(m_pSwapChain.ReleaseAndGetAddressOf()));
		CHECK_FAILED(hr);
		
		// �t���[���o�b�t�@�ԍ��擾

	}

	// �t�F���X�̐���
	{
		m_nFenceVal = 0;
		hr = m_pD3DDevice->CreateFence(m_nFenceVal, D3D12_FENCE_FLAG_NONE,
			IID_PPV_ARGS(m_pFence.ReleaseAndGetAddressOf()));
		CHECK_FAILED(hr);
	}

	// �����_�[�^�[�Q�b�g�q�[�v�̐���
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// �s�[�v�^�C�v
		desc.NumDescriptors = BACK_BUFFER_COUNT;		// �o�b�t�@��
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// �V�F�[�_�[���\�[�X��
		desc.NodeMask = nodeMask;

		hr = m_pD3DDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_pBackBufferHeap.ReleaseAndGetAddressOf()));
	}

	// �����_�[�^�[�Q�b�g�r���[�̐���
	{
		// �擪�A�h���X�ƃI�t�Z�b�g�T�C�Y���擾
		auto handle = m_pBackBufferHeap->GetCPUDescriptorHandleForHeapStart();
		m_nBackBufferSize = m_pD3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_RENDER_TARGET_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;	// MSAA off

		// �o�b�N�o�b�t�@���烌���_�[�^�[�Q�b�g�𐶐�
		for (UINT i = 0; i < BACK_BUFFER_COUNT; ++i)
		{
			// �o�b�N�o�b�t�@�擾
			hr = m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(m_pBackBuffer[i].ReleaseAndGetAddressOf()));
			CHECK_FAILED(hr);

			// �����_�[�^�[�Q�b�g�r���[�̐���
			m_pD3DDevice->CreateRenderTargetView(m_pBackBuffer[i].Get(), &desc, handle);
			// �n���h���̃|�C���^��i�߂�
			handle.ptr += m_nBackBufferSize;
		}
	}

	//�[�x�o�b�t�@�쐬
	{
		//�[�x�o�b�t�@�̎d�l
		D3D12_RESOURCE_DESC depthResDesc = {};
		depthResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;//2�����̃e�N�X�`���f�[�^�Ƃ���
		depthResDesc.Width = width;//���ƍ����̓����_�[�^�[�Q�b�g�Ɠ���
		depthResDesc.Height = height;//��ɓ���
		depthResDesc.DepthOrArraySize = 1;//�e�N�X�`���z��ł��Ȃ���3D�e�N�X�`���ł��Ȃ�
		depthResDesc.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�������ݗp�t�H�[�}�b�g
		depthResDesc.SampleDesc.Count = 1;//�T���v����1�s�N�Z��������1��
		depthResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;//���̃o�b�t�@�͐[�x�X�e���V���Ƃ��Ďg�p���܂�
		depthResDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		depthResDesc.MipLevels = 1;

		//�f�v�X�p�q�[�v�v���p�e�B
		D3D12_HEAP_PROPERTIES depthHeapProp = {};
		depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;//DEFAULT��������UNKNOWN�ł悵
		depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		//���̃N���A�o�����[���d�v�ȈӖ�������
		D3D12_CLEAR_VALUE _depthClearValue = {};
		_depthClearValue.DepthStencil.Depth = 1.0f;//�[���P(�ő�l)�ŃN���A
		_depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;//32bit�[�x�l�Ƃ��ăN���A

		m_pD3DDevice->CreateCommittedResource(
			&depthHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthResDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE, //�f�v�X�������݂Ɏg�p
			&_depthClearValue,
			IID_PPV_ARGS(m_pDepthStencil.ReleaseAndGetAddressOf()));

		//�[�x�̂��߂̃f�X�N���v�^�q�[�v�쐬
		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};//�[�x�Ɏg����Ƃ��������킩��΂���
		dsvHeapDesc.NumDescriptors = 1;//�[�x�r���[1�̂�
		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//�f�v�X�X�e���V���r���[�Ƃ��Ďg��
		dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		m_pD3DDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_pDepthStencilHeap.ReleaseAndGetAddressOf()));

		//�[�x�r���[�쐬
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//�f�v�X�l��32bit�g�p
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;//�t���O�͓��ɂȂ�
		m_pD3DDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &dsvDesc, 
			m_pDepthStencilHeap->GetCPUDescriptorHandleForHeapStart());
	}


	// �f�o�C�X�̐���
	m_device.initialize(m_pD3DDevice.Get(), m_pDXGIFactory.Get(), hWnd, width, height);

	return hr;
}

/// @brief �I������
void D3D12Renderer::finalize()
{
	HRESULT hr = S_OK;

	// �R�}���h�����҂�
	hr = m_pCmdQueue->Signal(m_pFence.Get(), ++m_nFenceVal);
	CHECK_FAILED(hr);

	// �t�F���X����
	if (m_pFence->GetCompletedValue() != m_nFenceVal)
	{
		// �C�x���g���s
		auto hEvent = CreateEvent(nullptr, false, false, nullptr);
		hr = m_pFence->SetEventOnCompletion(m_nFenceVal, hEvent);
		CHECK_FAILED(hr);
		// �C�x���g�I���҂�
		WaitForSingleObject(hEvent, INFINITE);
		// �C�x���g�����
		CloseHandle(hEvent);
	}

	// �\��
	m_pSwapChain->Present(1, 0);
}

/// @brief �t���[���J�n
void D3D12Renderer::beginFrame()
{
	HRESULT hr = S_OK;

	//--- ���\�[�X�̍X�V
	// GPU���̃o�b�t�@�A�e�N�X�`���ȂǍX�V

	// ���\�[�X�X�V
	m_device.ExecuteUpdateResurce();


	//--- �R�}���h���s
	// �O�t���[���Œ��߂��R�}���h�̔��s

	// �R�}���h���X�g���i�[
	std::vector<ID3D12CommandList*> ppCmdList;
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		ppCmdList.push_back(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList.Get());
	}

	// �R�}���h�̎��s
	m_pCmdQueue->ExecuteCommandLists(ppCmdList.size(), ppCmdList.data());


	//--- ���t���[���̃R�}���h����
	// �o�b�N�o�b�t�@����ւ�

	// ���݂̃o�b�N�o�b�t�@�C���f�b�N�X
	m_curBackBufferIndex = (m_pSwapChain->GetCurrentBackBufferIndex() + 1) % BACK_BUFFER_COUNT;

	// �R�}���h�A���P�[�^�[�ƃR�}���h���X�g�����Z�b�g
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		CHECK_FAILED(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdAllocator->Reset());
		CHECK_FAILED(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList->
			Reset(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdAllocator.Get(), nullptr));
	}
	m_useCmdListCnt[m_curBackBufferIndex] = 0;

}

/// @brief �t���[���I��
void D3D12Renderer::endFrame()
{
	HRESULT hr = S_OK;

	if (m_eBackBufferSate[m_curBackBufferIndex] != D3D12_RESOURCE_STATE_PRESENT && 
		m_cmdLists[m_curBackBufferIndex].size() > 0)
	{
		// �����_�[�^�[�Q�b�g�̃o���A�w��
		D3D12_RESOURCE_BARRIER barrierDesc = {};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;					// �o���A���(�J��)
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;						// �o���A�����p
		barrierDesc.Transition.pResource = m_pBackBuffer[m_curBackBufferIndex].Get();	// ���\�[�X�|�C���^
		barrierDesc.Transition.Subresource = 										// �T�u���\�[�X�̐�
			D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;								// ���\�[�X���̂��ׂẴT�u���\�[�X�𓯎��Ɉڍs
		barrierDesc.Transition.StateBefore = m_eBackBufferSate[m_curBackBufferIndex];	// �J�ڑO�̃��\�[�X���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			// �J�ڌ�̃��\�[�X���

		// �Ō�̃R�}���h�Ƀ��\�[�X�o���A
		m_cmdLists[m_curBackBufferIndex].back()->m_pCmdList->ResourceBarrier(1, &barrierDesc);
		m_eBackBufferSate[m_curBackBufferIndex] = D3D12_RESOURCE_STATE_PRESENT;
	}

	// �R�}���h�̋L�^�I��
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		CHECK_FAILED(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList->Close());
	}

	//--- �O�t���[���̃R�}���h������҂�

	// �R�}���h�����҂�
	hr = m_pCmdQueue->Signal(m_pFence.Get(), ++m_nFenceVal);
	CHECK_FAILED(hr);

	// �t�F���X����
	if (m_pFence->GetCompletedValue() != m_nFenceVal)
	{
		// �C�x���g���s
		auto hEvent = CreateEvent(nullptr, false, false, nullptr);
		hr = m_pFence->SetEventOnCompletion(m_nFenceVal, hEvent);
		CHECK_FAILED(hr);
		// �C�x���g�I���҂�
		WaitForSingleObject(hEvent, INFINITE);
		// �C�x���g�����
		CloseHandle(hEvent);
	}

	// �\��
	m_pSwapChain->Present(1, 0);
}

/// @brief �R�}���h���X�g�̎擾
/// @return �R�}���h���X�g�̃|�C���^ 
core::CoreCommandList* D3D12Renderer::getCommandList()
{
	if (m_useCmdListCnt[m_curBackBufferIndex] >= m_cmdLists[m_curBackBufferIndex].size())
	{
		auto up = std::make_unique<D3D12CommandList>();
		auto* ptr = up.get();
		ptr->initialize(this, &m_device);
		m_cmdLists[m_curBackBufferIndex].push_back(std::move(up));
		++m_useCmdListCnt[m_curBackBufferIndex];
		return ptr;
	}

	return m_cmdLists[m_curBackBufferIndex][m_useCmdListCnt[m_curBackBufferIndex]++].get();
}