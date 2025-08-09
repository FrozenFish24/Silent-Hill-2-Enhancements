#include "Drips.h"
#include <cstring>
#include "Common\Utils.h"
#include "Logging\Logging.h"
#include "Patches\Patches.h"
#include "Common\Settings.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"

IDirect3DDevice8*& g_d3d8Device_A32894 = *reinterpret_cast<IDirect3DDevice8**>(0xA32894);

using originalDrawDripsFunc = void (*)(/* UINT primCount */);
static originalDrawDripsFunc originalDrawDrips = reinterpret_cast< originalDrawDripsFunc>(0x4EDE20);

struct Vertex {
    float x, y, z;
    D3DCOLOR diffuse;
};

struct Line {
    Vertex v0, v1;
};

struct Triangle {
    Vertex v0, v1, v2;
};

Line& vertexStreamZeroData_963880 = *reinterpret_cast<Line*>(0x963880);

inline D3DVECTOR normalize(const D3DVECTOR& vec)
{
    float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return { vec.x / magnitude, vec.y / magnitude, vec.z / magnitude };
}

inline D3DVECTOR cross(const D3DVECTOR& a, const D3DVECTOR& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

std::vector<Triangle> transformDrips(UINT primCount)
{
    std::vector<Triangle> triList;
    const float width = DropletSize;

    for (size_t i = 0; i < primCount; i++) {
        Line* line = &(&vertexStreamZeroData_963880)[i];

        // TODO: Move to vertex shader
        const Vertex center = { line->v0.x, (line->v0.y + line->v1.y) / 2, line->v0.z };
        constexpr D3DVECTOR upVec = { 0,1,0 };

        const Vertex camera = { GetInGameCameraPosX(), GetInGameCameraPosY(), GetInGameCameraPosZ() };
        D3DVECTOR toCam = { camera.x - center.x, camera.y - center.y, camera.z - center.z };
        toCam = normalize(toCam);

        const D3DVECTOR rightVec = normalize(cross(upVec, toCam));

        Vertex v0 = line->v0;
        Vertex v1 = line->v0;
        Vertex v2 = line->v1;
        Vertex v3 = line->v1;

        v0.x += rightVec.x * (width / 2);
        v0.y += rightVec.y * (width / 2);
        v0.z += rightVec.z * (width / 2);

        v1.x -= rightVec.x * (width / 2);
        v1.y -= rightVec.y * (width / 2);
        v1.z -= rightVec.z * (width / 2);

        v2.x += rightVec.x * (width / 2);
        v2.y += rightVec.y * (width / 2);
        v2.z += rightVec.z * (width / 2);

        v3.x -= rightVec.x * (width / 2);
        v3.y -= rightVec.y * (width / 2);
        v3.z -= rightVec.z * (width / 2);

        triList.push_back({ v3, v1, v0 });
        triList.push_back({ v0, v2, v3 });
    }

    return triList;
}

void drawDrips(UINT primCount, std::vector<Triangle> triList)
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

        g_d3d8Device_A32894->DrawPrimitiveUP(D3DPT_TRIANGLELIST, triList.size(), triList.data(), 16);
        //g_d3d8Device_A32894->DrawPrimitiveUP(D3DPT_LINELIST, primCount, &vertexStreamZeroData_963880, 16);

        g_d3d8Device_A32894->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_FOGENABLE, TRUE);
        g_d3d8Device_A32894->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    }
}

UINT primCountBackup = 0;
std::vector<Triangle> triListBackup;

void hookDrawDrips()
{
    UINT primCount;
    __asm mov primCount, esi

    primCountBackup = primCount;
    triListBackup = transformDrips(primCount);
}

auto originalDrawTransGeom = reinterpret_cast<void(*)(void*)>(0x5AFEE0);

void __cdecl hookDrawTransGeom(void* pTransGeom)
{
    originalDrawTransGeom(pTransGeom);
    drawDrips(primCountBackup, triListBackup);
}

void PatchDrips()
{
    switch (GameVersion)
    {
    case SH2V_10:
        WriteCalltoMemory((BYTE*)0x4EE4C6, hookDrawDrips);
        WriteCalltoMemory((BYTE*)0x4EE8E0, hookDrawDrips);

        WriteCalltoMemory((BYTE*)0x4762A5, hookDrawTransGeom);
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
