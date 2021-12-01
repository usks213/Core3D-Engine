/*****************************************************************//**
 * \file   D3D11_Defines.h
 * \brief  DirectX11’è‹`
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _D3D11_DEFINES_
#define _D3D11_DEFINES_

#include <tchar.h>
#include <wchar.h>
#include <comdef.h>
#include <Windows.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

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

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#ifdef _UNICODE
#define CHECK_FAILED(hr)													                                                                        \
    if (FAILED(hr)) {                                                                                                                               \
            static wchar_t szResult[256];                                                                                                           \
            static char szResult2[256];                                                                                                             \
            static size_t count;                                                                                                                    \
            _com_error  err(hr);                                                                                                                    \
            LPCTSTR     errMsg = err.ErrorMessage();                                                                                                \
            swprintf_s(szResult, sizeof(szResult), _T("[ERROR] HRESULT: %08X %s#L%d\n%s"), static_cast<UINT>(hr), _T(__FILE__), __LINE__, szResult);    \
            MessageBox(nullptr, szResult, _T("ERROR"), MB_OK | MB_ICONERROR);                                                                       \
            wcstombs_s(&count, szResult2, 256, szResult, 256);                                                                                      \
            throw std::exception(szResult2);                                                                                                        \
    }
#else
#define CHECK_FAILED(hr)													\
    if (FAILED(hr)) {                                                                                                                 \
        static char szResult[256];                                                                                                    \
        _com_error  err(hr);                                                                                                          \
        LPCTSTR     errMsg = err.ErrorMessage();                                                                                      \
        sprintf_s(szResult, sizeof(szResult), _T("[ERROR] HRESULT: %08X %s#L%d\n%s"), static_cast<UINT>(hr), __FILE__, __LINE__, errMsg); \
        MessageBox(nullptr, szResult, _T("ERROR"), MB_OK | MB_ICONERROR);                                                                 \
        throw std::exception(szResult);                                                                                               \
    }
#endif // _UNICODE




#endif // !_D3D11_DEFINES_

