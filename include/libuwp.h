#pragma once

#include <windows.h>
#include <d3dcommon.h>

#define LIBAPI extern "C" __declspec(dllexport)

// :: Screen information
LIBAPI void  uwp_GetActualSize(int* x, int* y); // Gets the display resolution
LIBAPI void  uwp_GetScreenSize(int* x, int* y); // Gets the display resolution OR override from user
LIBAPI float uwp_GetRefreshRate();
LIBAPI void* uwp_GetActualWindowReference();
LIBAPI void* uwp_GetWindowReference();

// By default GetScreenSize will return display resolution, but this will allow apps to override those values
LIBAPI void  uwp_SetScreenSize(int x, int y);

// :: Filepaths
LIBAPI void uwp_GetBundlePath(char* buffer);
LIBAPI void uwp_GetBundleFilePath(char* buffer, const char* filename);

 // MT dlls can be finnicky about loading other DLL's, call back here to workaround.
LIBAPI HMODULE uwp_LoadLibrary(LPCWSTR path);

// :: Events

// If not using SDL or other helper you must occasionally call this to get anything to show on screen
LIBAPI void uwp_ProcessEvents();

// If not using SDL or other helper you must register event callbacks to read controller input
LIBAPI void uwp_RegisterGamepadCallbacks(void (*callback)(void));

// :: Basic app support
extern int (*UWPAppEntryPoint)();
LIBAPI int uwp_main(int mainFunc());

// :: D3DCompile hooks
LIBAPI HRESULT WINAPI uwp_D3DCompile(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
  _In_ SIZE_T SrcDataSize,
  _In_opt_ LPCSTR pSourceName,
  _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) CONST D3D_SHADER_MACRO* pDefines,
  _In_opt_ ID3DInclude* pInclude,
  _In_opt_ LPCSTR pEntrypoint,
  _In_ LPCSTR pTarget,
  _In_ UINT Flags1,
  _In_ UINT Flags2,
  _Out_ ID3DBlob** ppCode,
  _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs);

LIBAPI HRESULT WINAPI uwp_D3DDisassemble(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
  _In_ SIZE_T SrcDataSize,
  _In_ UINT Flags,
  _In_opt_ LPCSTR szComments,
  _Out_ ID3DBlob** ppDisassembly);
