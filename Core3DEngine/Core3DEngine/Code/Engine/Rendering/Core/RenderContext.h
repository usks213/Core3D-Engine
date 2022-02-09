/*****************************************************************//**
 * \file   RenderContext.h
 * \brief  �����_�[�R���e�L�X�g
 *
 * \author USAMI KOSHI
 * \date   2022/01/19
 *********************************************************************/
#ifndef _RENDER_CONTEXT_
#define _RENDER_CONTEXT_

namespace Core
{
	namespace RHI
	{
		class Device;
		class CommandList;
	}

	class GraphicsShader;
	class Material;
	class Mesh;

	class RenderContext final
	{
	public:
		/// @brief �R���X�g���N�^
		/// @param pDevice RHI�f�o�C�X
		/// @param pCmdList RHI�R�}���h���X�g
		explicit RenderContext(RHI::Device* pDevice, RHI::CommandList* pCmdList) noexcept :
			m_pDevice(pDevice), m_pCmdList(pCmdList)
		{
		}

		/// @brief �f�X�g���N�^
		~RenderContext() noexcept = default;

		void SetCamera();

		void SetLight();

		void SetShadow();

		void SetTransform();

		void SetAnimation();

		void SetMaterial(const Material& material) const;

		void SetMesh(Mesh& mesh, const GraphicsShader& shader) const;

		void Draw();

		/// @brief RHI�f�o�C�X�̎擾
		/// @return RHI�f�o�C�X�|�C���^
		const RHI::Device* GetRHIDevice() { return m_pDevice; }

		/// @brief RHI�R�}���h���X�g�̎擾
		/// @return RHI�R�}���h���X�g�|�C���^
		const RHI::CommandList* GetRHICommandList() { return m_pCmdList; }

	private:
		RHI::Device*		m_pDevice;	///< RHI�f�o�C�X
		RHI::CommandList*	m_pCmdList;	///< RHI�R�}���h���X�g
	};
}

#endif // !_RENDER_CONTEXT_

