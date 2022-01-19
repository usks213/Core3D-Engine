/*****************************************************************//**
 * \file   RenderingData.h
 * \brief  レンダリングデータ
 *
 * \author USAMI KOSHI
 * \date   2022/01/19
 *********************************************************************/
#ifndef _RENDERING_DATA_
#define _RENDERING_DATA_

namespace Core
{
	struct CameraData
	{

	};

	struct CullingData
	{

	};

	struct LightData
	{

	};

	struct PostProcessingData
	{

	};

	struct ShadowData
	{

	};
	
	/// @brief レンダリングデータ
	struct RenderingData
	{
		CameraData cameraData;
		CullingData cullingData;
		LightData lightData;
		PostProcessingData postProcessingData;
		ShadowData shadowData;
	};

}

#endif // !_RENDERING_DATA_

