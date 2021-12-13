/*****************************************************************//**
 * \file   D3D_Defines.h
 * \brief  DirectX’è‹`
 *
 * \author USAMI KOSHI
 * \date   2021/12/13
 *********************************************************************/
#ifndef _D3D_DEFINES_
#define _D3D_DEFINES_

#include <tchar.h>
#include <wchar.h>
#include <comdef.h>
#include <Windows.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

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




#endif // !_D3D_DEFINES_

