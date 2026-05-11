#include "libuwp.h"
#include "d3dcompiler.h"

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
  _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs)
{
  return D3DCompile(pSrcData, SrcDataSize, pSourceName, pDefines, pInclude,
    pEntrypoint, pTarget, Flags1, Flags2, ppCode, ppErrorMsgs);
}

LIBAPI HRESULT WINAPI uwp_D3DDisassemble(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
  _In_ SIZE_T SrcDataSize,
  _In_ UINT Flags,
  _In_opt_ LPCSTR szComments,
  _Out_ ID3DBlob** ppDisassembly)
{
  return D3DDisassemble(pSrcData, SrcDataSize, Flags, szComments, ppDisassembly);
}
