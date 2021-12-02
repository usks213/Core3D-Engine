/*****************************************************************//**
 * \file   D3D11_Editor.h
 * \brief  DirectX11�G�f�B�^�[
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _D3D11_EDITOR_
#define _D3D11_EDITOR_

#include <Editor/Core/Editor.h>
#include <Renderer/D3D11/D3D11_Defines.h>

namespace Core::D3D11
{
	class D3D11Editor final : public Core::Editor
	{
	public:

		/// @brief �R���X�g���N�^
		/// @param pEngine �G���W���|�C���^
		explicit D3D11Editor() noexcept 
		{
		}

		/// @brief �f�X�g���N�^
		~D3D11Editor() noexcept = default;

		/// @brief ����������
		/// @param hWnd �E�B���h�E�n���h��
		/// @param pDevice �f�o�C�X
		/// @param pContext �C�~�f�B�G�C�g�R���e�L�X�g
		/// @return ���� TRUE / ���s FALSE
		bool initialize(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

		/// @brief �I������
		void finalize() override;

		/// @brief �V�����`��t���[���쐬
		void NewFrame() override;

		/// @brief �`��
		/// @param cmdList �R�}���h���X�g
		void Render(Core::CommandList* cmdList) override;

	private:

	};
}


#endif // !_D3D11_EDITOR_
