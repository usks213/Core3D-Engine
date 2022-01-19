/*****************************************************************//**
 * \file   GraphicsShader.h
 * \brief  グラフィックスシェーダー
 *
 * \author USAMI KOSHI
 * \date   2021/12/16
 *********************************************************************/
#include "GraphicsShader.h"
#include <Resource\Core\ResourceManager.h>
#include <Engine\Core\Engine.h>
#include <RHI\Core\RHI_Device.h>

using namespace Core;


/// @brief シェーダーデータ作成
/// @param desc RHIシェーダーDesc
/// @return 成功 TRUE / 失敗 FALSE
bool GraphicsShader::CreateShaderData(RHI::GraphicsShaderDesc& desc)
{
	auto pRenderer = GetResourceManager()->GetEngine()->GetRenderer();
	m_pRHIGraphicsShader = pRenderer->GetDevice()->CreateGraphicsShader(desc);
	if (!m_pRHIGraphicsShader) return false;

	return true;
}

