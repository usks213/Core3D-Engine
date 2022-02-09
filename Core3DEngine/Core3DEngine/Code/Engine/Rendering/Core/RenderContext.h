/*****************************************************************//**
 * \file   RenderContext.h
 * \brief  レンダーコンテキスト
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
		/// @brief コンストラクタ
		/// @param pDevice RHIデバイス
		/// @param pCmdList RHIコマンドリスト
		explicit RenderContext(RHI::Device* pDevice, RHI::CommandList* pCmdList) noexcept :
			m_pDevice(pDevice), m_pCmdList(pCmdList)
		{
		}

		/// @brief デストラクタ
		~RenderContext() noexcept = default;

		void SetCamera();

		void SetLight();

		void SetShadow();

		void SetTransform();

		void SetAnimation();

		void SetMaterial(const Material& material) const;

		void SetMesh(Mesh& mesh, const GraphicsShader& shader) const;

		void Draw();

		/// @brief RHIデバイスの取得
		/// @return RHIデバイスポインタ
		const RHI::Device* GetRHIDevice() { return m_pDevice; }

		/// @brief RHIコマンドリストの取得
		/// @return RHIコマンドリストポインタ
		const RHI::CommandList* GetRHICommandList() { return m_pCmdList; }

	private:
		RHI::Device*		m_pDevice;	///< RHIデバイス
		RHI::CommandList*	m_pCmdList;	///< RHIコマンドリスト
	};
}

#endif // !_RENDER_CONTEXT_

