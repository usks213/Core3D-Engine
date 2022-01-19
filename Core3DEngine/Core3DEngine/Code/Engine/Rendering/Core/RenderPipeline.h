/*****************************************************************//**
 * \file   RenderPipeline.h
 * \brief  �����_�[�p�C�v���C���N���X
 *
 * \author USAMI KOSHI
 * \date   2022/01/19
 *********************************************************************/
#ifndef _RENDER_PIPELINE_
#define _RENDER_PIPELINE_

#include "RenderPass.h"
#include <type_traits>
#include <vector>
#include <memory>

namespace Core
{
	class RenderingManager;
	class RenderPass;
	class RenderContext;
	class RenderingData;

	/// @class RenderPipeline
	/// @brief �����_�[�p�C�v���C���N���X
	class RenderPipeline
	{
		friend class RenderingManager;
	public:

		/// @brief �R���X�g���N�^
		RenderPipeline() noexcept :
			m_pRenderManager(nullptr)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~RenderPipeline() = default;

		virtual void OnCreate() = 0;

		virtual void OnDestroy() = 0;

		virtual void BeginFrame(const RenderContext& context) = 0;

		virtual void EndFrame(const RenderContext& context) = 0;

		/// @brief �p�X�̎��s
		/// @param context �����_�[�R���e�L�X�g
		/// @param renderingData �����_�����O�f�[�^
		void Execute(const RenderContext& context, const RenderingData& renderingData);

		template<class T, bool isPassBase = std::is_base_of_v<RenderPass, T>>
		T* AddPass()
		{
			auto pPass = std::make_unique<T>();
			T* pResult = pPass.get();
			m_renderPassList.push_back(std::move(pPass));
			return pResult;
		}

	private:
		RenderingManager*							m_pRenderManager;	///< �����_�����O�}�l�[�W���[�̃|�C���^
		std::vector<std::unique_ptr<RenderPass>>	m_renderPassList;	///< �����_�[�p�X���X�g
	};
}

#endif // !_RENDER_PIPELINE_

