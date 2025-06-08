#include "Drips.h"
#include <cstring>
#include "Common\Utils.h"
#include "Logging\Logging.h"
#include "Patches\Patches.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"

IDirect3DDevice8*& g_d3d8Device_A32894 = *reinterpret_cast<IDirect3DDevice8**>(0xA32894);

using originalDrawDripsFunc = void (*)(/* UINT primCount */);
static originalDrawDripsFunc originalDrawDrips = reinterpret_cast< originalDrawDripsFunc>(0x4EDE20);

struct Point {
    float x;
    float y;
    float z;
    D3DCOLOR diffuse;
};

struct Line {
    Point p0;
    Point p1;
};

Line& vertexStreamZeroData_963880 = *reinterpret_cast<Line*>(0x963880);

void drawDrips(UINT primCount)
{
    D3DMATRIX worldMatrix;

    if (primCount > 0)
    {
        g_d3d8Device_A32894->SetRenderState(D3DRS_LIGHTING, FALSE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_FOGENABLE, FALSE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        g_d3d8Device_A32894->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        g_d3d8Device_A32894->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_COLORVERTEX, TRUE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
        g_d3d8Device_A32894->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
        
        g_d3d8Device_A32894->SetTexture(0, NULL);
        g_d3d8Device_A32894->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        g_d3d8Device_A32894->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        g_d3d8Device_A32894->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
        g_d3d8Device_A32894->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        g_d3d8Device_A32894->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        g_d3d8Device_A32894->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        
        std::memset(&worldMatrix.m[2][3], 0, 16);
        std::memset(&worldMatrix.m[1][2], 0, 16);
        std::memset(&worldMatrix.m[0][1], 0, 16);
        worldMatrix._44 = 1.0;
        worldMatrix._33 = 1.0;
        worldMatrix._22 = 1.0;
        worldMatrix._11 = 1.0;

        g_d3d8Device_A32894->SetTransform(D3DTS_WORLD, &worldMatrix);
        g_d3d8Device_A32894->SetVertexShader(D3DFVF_XYZ | D3DFVF_DIFFUSE);

        // NEW CODE
        //std::vector<Line> lineList;
        //lineList.assign(&vertexStreamZeroData_963880, &vertexStreamZeroData_963880 + primCount);

        for (size_t i = 0; i < primCount; i++) {
            Line* line = &(&vertexStreamZeroData_963880)[i];
            line->p0.diffuse = D3DCOLOR_ARGB(255, 255, 0 ,0);
            line->p1.diffuse = D3DCOLOR_ARGB(255, 0, 0, 255);
        }
        // END NEW CODE

        g_d3d8Device_A32894->DrawPrimitiveUP(D3DPT_LINELIST, primCount, &vertexStreamZeroData_963880, 16);

        g_d3d8Device_A32894->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_FOGENABLE, TRUE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    }
}

void hookDrawDrips()
{
    UINT primCount;
    __asm mov primCount, esi

    // Toggle me in debugger to switch between original and reimpl
    static bool reimplDrips = true;

    if (reimplDrips) {
        drawDrips(primCount);
    }
    else
    {
        __asm mov esi, primCount
        originalDrawDrips();
    }
}

void PatchDrips()
{
    switch (GameVersion)
    {
    case SH2V_10:
        WriteCalltoMemory((BYTE*)0x4EE4C6, hookDrawDrips);
        WriteCalltoMemory((BYTE*)0x4EE8E0, hookDrawDrips);
        break;
    case SH2V_11:
        Logging::Log() << __FUNCTION__ << " Error: not implemented for v1.1!";
        break;
    case SH2V_DC:
        Logging::Log() << __FUNCTION__ << " Error: not implemented for DC!";
        break;
    case SH2V_UNKNOWN:
        Logging::Log() << __FUNCTION__ << " Error: unknown game version!";
        return;
    }
}
