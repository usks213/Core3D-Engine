/*****************************************************************//**
 * \file   D3D11_Defines.h
 * \brief  DirectX11’è‹`
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _D3D11_DEFINES_
#define _D3D11_DEFINES_

#include <RHI\D3D\D3D_Defines.h>

#define D3D11_VERSION_1

#ifdef D3D11_VERSION_1
#include <d3d11_1.h>
#endif
#ifdef D3D11_VERSION_2
#include <d3d11_2.h>
#endif
#ifdef D3D11_VERSION_3
#include <d3d11_3.h>
#endif
#ifdef D3D11_VERSION_4
#include <d3d11_4.h>
#endif


#endif // !_D3D11_DEFINES_

