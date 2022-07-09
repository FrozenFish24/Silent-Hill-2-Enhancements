/**
* Copyright (C) 2022 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#define WIN32_LEAN_AND_MEAN
#include "d3dx9.h"
#include "External\MemoryModule\MemoryModule.h"
#include "Common\Utils.h"
#include "Logging\Logging.h"
#include "Resource.h"

typedef interface ID3DXConstantTable ID3DXConstantTable;
typedef interface ID3DXConstantTable *LPD3DXCONSTANTTABLE;

typedef HRESULT(WINAPI *PFN_D3DXAssembleShader)(LPCSTR pSrcData, UINT SrcDataLen, const D3DXMACRO *pDefines, LPD3DXINCLUDE pInclude, DWORD Flags, LPD3DXBUFFER *ppShader, LPD3DXBUFFER *ppErrorMsgs);
typedef HRESULT(WINAPI *PFN_D3DXDisassembleShader)(const DWORD *pShader, BOOL EnableColorCode, LPCSTR pComments, LPD3DXBUFFER *ppDisassembly);
typedef HRESULT(WINAPI *PFN_D3DXLoadSurfaceFromSurface)(LPDIRECT3DSURFACE9 pDestSurface, const PALETTEENTRY *pDestPalette, const RECT *pDestRect, LPDIRECT3DSURFACE9 pSrcSurface, const PALETTEENTRY *pSrcPalette, const RECT *pSrcRect, DWORD Filter, D3DCOLOR ColorKey);
typedef HRESULT(WINAPI *PFN_D3DAssemble)(const void *pSrcData, SIZE_T SrcDataSize, const char *pFileName, const D3D_SHADER_MACRO *pDefines, ID3DInclude *pInclude, UINT Flags, ID3DBlob **ppShader, ID3DBlob **ppErrorMsgs);
typedef HRESULT(WINAPI *PFN_D3DCompile)(LPCVOID pSrcData, SIZE_T SrcDataSize, LPCSTR pSourceName, const D3D_SHADER_MACRO *pDefines, ID3DInclude *pInclude, LPCSTR pEntrypoint, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob **ppCode, ID3DBlob **ppErrorMsgs);
typedef HRESULT(WINAPI *PFN_D3DDisassemble)(LPCVOID pSrcData, SIZE_T SrcDataSize, UINT Flags, LPCSTR szComments, ID3DBlob **ppDisassembly);

HMEMORYMODULE d3dx9Module = nullptr;
HMEMORYMODULE d3dCompile43Module = nullptr;
HMEMORYMODULE d3dCompileModule = nullptr;

PFN_D3DXAssembleShader p_D3DXAssembleShader = nullptr;
PFN_D3DXDisassembleShader p_D3DXDisassembleShader = nullptr;
PFN_D3DXLoadSurfaceFromSurface p_D3DXLoadSurfaceFromSurface = nullptr;
// Some operating systems, like Windows XP, won't work with d3dcompile_47, so failover to d3dcompile_43 for these cases
PFN_D3DAssemble p_D3DAssemble43 = nullptr;
PFN_D3DCompile p_D3DCompile43 = nullptr;
PFN_D3DDisassemble p_D3DDisassemble43 = nullptr;
// These use d3dcompile_47
PFN_D3DAssemble p_D3DAssemble = nullptr;
PFN_D3DCompile p_D3DCompile = nullptr;
PFN_D3DDisassemble p_D3DDisassemble = nullptr;

PFN_D3DXAssembleShader f_D3DXAssembleShader = *D3DXAssembleShader;
PFN_D3DXDisassembleShader f_D3DXDisassembleShader = *D3DXDisassembleShader;
PFN_D3DXLoadSurfaceFromSurface f_D3DXLoadSurfaceFromSurface = *D3DXLoadSurfaceFromSurface;

void LoadD3dx9()
{
	static bool RunOnce = true;
	if (RunOnce)
	{
		RunOnce = false;

		d3dx9Module = LoadResourceToMemory(IDR_D3DX9_DLL);
		d3dCompile43Module = LoadResourceToMemory(IDR_D3DCOMPI43_DLL);
		d3dCompileModule = LoadResourceToMemory(IDR_D3DCOMPILE_DLL);

		if (d3dx9Module)
		{
			p_D3DXAssembleShader = reinterpret_cast<PFN_D3DXAssembleShader>(MemoryGetProcAddress(d3dx9Module, "D3DXAssembleShader"));
			p_D3DXDisassembleShader = reinterpret_cast<PFN_D3DXDisassembleShader>(MemoryGetProcAddress(d3dx9Module, "D3DXDisassembleShader"));
			p_D3DXLoadSurfaceFromSurface = reinterpret_cast<PFN_D3DXLoadSurfaceFromSurface>(MemoryGetProcAddress(d3dx9Module, "D3DXLoadSurfaceFromSurface"));
		}
		if (d3dCompile43Module)
		{
			p_D3DAssemble43 = reinterpret_cast<PFN_D3DAssemble>(MemoryGetProcAddress(d3dCompile43Module, "D3DAssemble"));
			p_D3DCompile43 = reinterpret_cast<PFN_D3DCompile>(MemoryGetProcAddress(d3dCompile43Module, "D3DCompile"));
			p_D3DDisassemble43 = reinterpret_cast<PFN_D3DDisassemble>(MemoryGetProcAddress(d3dCompile43Module, "D3DDisassemble"));
		}
		if (d3dCompileModule)
		{
			p_D3DAssemble = reinterpret_cast<PFN_D3DAssemble>(MemoryGetProcAddress(d3dCompileModule, "D3DAssemble"));
			p_D3DCompile = reinterpret_cast<PFN_D3DCompile>(MemoryGetProcAddress(d3dCompileModule, "D3DCompile"));
			p_D3DDisassemble = reinterpret_cast<PFN_D3DDisassemble>(MemoryGetProcAddress(d3dCompileModule, "D3DDisassemble"));
		}
	}
}

HRESULT WINAPI D3DXAssembleShader(LPCSTR pSrcData, UINT SrcDataLen, const D3DXMACRO *pDefines, LPD3DXINCLUDE pInclude, DWORD Flags, LPD3DXBUFFER *ppShader, LPD3DXBUFFER *ppErrorMsgs)
{
	Logging::LogDebug() << __FUNCTION__;

	return D3DAssemble(pSrcData, SrcDataLen, nullptr, pDefines, (ID3DInclude*)pInclude, Flags, ppShader, ppErrorMsgs);
}

HRESULT WINAPI D3DXDisassembleShader(const DWORD *pShader, BOOL EnableColorCode, LPCSTR pComments, LPD3DXBUFFER *ppDisassembly)
{
	Logging::LogDebug() << __FUNCTION__;

	UINT Flags = (EnableColorCode) ? D3D_DISASM_ENABLE_COLOR_CODE : 0;

	// ToDo: Update to get correct shader size
	SIZE_T SrcDataSize = 0;
	DWORD x = 0;
	while (TRUE)
	{
		if (pShader[x] != 0)
		{
			SrcDataSize += 4;
		}
		else
		{
			break;
		}
		x++;
	}

	return D3DDisassemble(pShader, SrcDataSize, Flags, pComments, ppDisassembly);
}

HRESULT WINAPI D3DXLoadSurfaceFromSurface(LPDIRECT3DSURFACE9 pDestSurface, const PALETTEENTRY *pDestPalette, const RECT *pDestRect, LPDIRECT3DSURFACE9 pSrcSurface, const PALETTEENTRY *pSrcPalette, const RECT *pSrcRect, DWORD Filter, D3DCOLOR ColorKey)
{
	Logging::LogDebug() << __FUNCTION__;

	LoadD3dx9();

	if (p_D3DXLoadSurfaceFromSurface)
	{
		return p_D3DXLoadSurfaceFromSurface(pDestSurface, pDestPalette, pDestRect, pSrcSurface, pSrcPalette, pSrcRect, Filter, ColorKey);
	}

	return D3DERR_INVALIDCALL;
}

HRESULT WINAPI D3DAssemble(const void *pSrcData, SIZE_T SrcDataSize, const char *pFileName, const D3D_SHADER_MACRO *pDefines, ID3DInclude *pInclude, UINT Flags, ID3DBlob **ppShader, ID3DBlob **ppErrorMsgs)
{
	Logging::LogDebug() << __FUNCTION__;

	LoadD3dx9();

	HRESULT hr = D3DERR_INVALIDCALL;

	if (p_D3DAssemble)
	{
		hr = p_D3DAssemble(pSrcData, SrcDataSize, pFileName, pDefines, pInclude, Flags, ppShader, ppErrorMsgs);
	}

	if (p_D3DAssemble43 && FAILED(hr))
	{
		hr = p_D3DAssemble43(pSrcData, SrcDataSize, pFileName, pDefines, pInclude, Flags, ppShader, ppErrorMsgs);
	}

	return hr;
}

HRESULT WINAPI D3DCompile(LPCVOID pSrcData, SIZE_T SrcDataSize, LPCSTR pSourceName, const D3D_SHADER_MACRO *pDefines, ID3DInclude *pInclude, LPCSTR pEntrypoint, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob **ppCode, ID3DBlob **ppErrorMsgs)
{
	Logging::LogDebug() << __FUNCTION__;

	LoadD3dx9();

	HRESULT hr = D3DERR_INVALIDCALL;

	if (p_D3DCompile)
	{
		hr = p_D3DCompile(pSrcData, SrcDataSize, pSourceName, pDefines, pInclude, pEntrypoint, pTarget, Flags1, Flags2, ppCode, ppErrorMsgs);
	}

	if (p_D3DCompile43 && FAILED(hr))
	{
		hr = p_D3DCompile43(pSrcData, SrcDataSize, pSourceName, pDefines, pInclude, pEntrypoint, pTarget, Flags1, Flags2, ppCode, ppErrorMsgs);
	}

	return hr;
}

HRESULT WINAPI D3DDisassemble(LPCVOID pSrcData, SIZE_T SrcDataSize, UINT Flags, LPCSTR szComments, ID3DBlob **ppDisassembly)
{
	Logging::LogDebug() << __FUNCTION__;

	LoadD3dx9();

	HRESULT hr = D3DERR_INVALIDCALL;

	if (p_D3DDisassemble)
	{
		hr = p_D3DDisassemble(pSrcData, SrcDataSize, Flags, szComments, ppDisassembly);
	}

	if (p_D3DDisassemble43 && FAILED(hr))
	{
		hr = p_D3DDisassemble43(pSrcData, SrcDataSize, Flags, szComments, ppDisassembly);
	}

	return hr;
}
