/*****************************************************************//**
 * \file   D3D12_Editor.h
 * \brief  DirectX12�G�f�B�^�[
 *
 * \author USAMI KOSHI
 * \date   2021/12/23
 *********************************************************************/
#ifndef _D3D12_EDITOR_
#define _D3D12_EDITOR_

#include <CoreEditor/Core_Editor.h>
#include <CoreRenderer\D3D12\D3D12_Device.h>

namespace d3d12
{
	class D3D12Editor final : public core::CoreEditor
	{
	public:

		/// @brief �R���X�g���N�^
		/// @param pEngine �G���W���|�C���^
		explicit D3D12Editor() noexcept
		{
		}

		/// @brief �f�X�g���N�^
		~D3D12Editor() noexcept = default;

		/// @brief ����������
		/// @param hWnd �E�B���h�E�n���h��
		/// @param pDevice �f�o�C�X
		/// @param pContext �C�~�f�B�G�C�g�R���e�L�X�g
		/// @return ���� TRUE / ���s FALSE
		bool initialize(HWND hWnd, D3D12Device* pDevice, int nBackBufferCount, DXGI_FORMAT backBufferFormat);

		/// @brief �I������
		void finalize() override;

		/// @brief �V�����`��t���[���쐬
		void NewFrame() override;

		/// @brief �`��
		/// @param cmdList �R�}���h���X�g
		void Render(core::CoreCommandList* cmdList) override;

	private:

		/// @brief ImGui�pGUP�q�[�v
		ID3D12DescriptorHeap*	 m_pTexHeap;

	};
}


#endif // !_D3D12_EDITOR_
