#include "Drips.h"
#include <cstring>
#include <algorithm>
#include "Common\Utils.h"
#include "Logging\Logging.h"
#include "Patches\Patches.h"
#include "Common\Settings.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"

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

struct TransGeomTexture
{
    IDirect3DBaseTexture8* pTexture;
    int type;
    IDirect3DBaseTexture8* tex0;
    IDirect3DBaseTexture8* tex1;
    IDirect3DVertexBuffer8* vbuf0;
    IDirect3DBaseTexture8* tex2;
    unsigned __int16 primitiveCount;
    void* vertexStreamZeroData;
    unsigned __int16 unk_20;
    unsigned __int16 stride;
    unsigned __int8 unk_22;
    unsigned __int8 unk_23;
    int unknown_24[13];
};

struct TransGeom
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    TransGeomTexture* pTextures;
};

static auto originalDrawDrips = reinterpret_cast<void (*)(/* UINT primCount */)>(0x4EDE20);
static auto originalDrawTransGeom = reinterpret_cast<void (*)(TransGeom*)>(0x5AFEE0);

BYTE& flashlightAvailable = *reinterpret_cast<BYTE*>(0x942BF0);
IDirect3DDevice8*& g_d3d8Device_A32894 = *reinterpret_cast<IDirect3DDevice8**>(0xA32894);
float& g_jamesRotation_1FB1030 = *reinterpret_cast<float*>(0x1FB1030);
Line& vertexStreamZeroData_963880 = *reinterpret_cast<Line*>(0x963880);

inline D3DVECTOR normalize(const D3DVECTOR& vec)
{
    float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return { vec.x / magnitude, vec.y / magnitude, vec.z / magnitude };
}

inline D3DVECTOR cross(const D3DVECTOR& a, const D3DVECTOR& b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

Triangle DEBUG_flashlightBeam(float angle);

// BUG: Is the bottom vert billboarding correctly?
// TODO: Move billboarding into vertex shader
// TODO: Move lighting into pixel shader
// TODO: Angle based brightness fall-off
std::vector<Triangle> transformDrips(UINT primCount)
{
    if (primCount == 0)
        return {};

    std::vector<Triangle> triList;
    const float width = DropletSize;

    // TODO: This seems wrong
    float angle = -g_jamesRotation_1FB1030 + (3.1415927f * 0.5f);

    for (size_t i = 0; i < primCount; i++)
    {
        Line* line = &(&vertexStreamZeroData_963880)[i];
        const Vertex james = { GetJamesPosX(), GetJamesPosY(), GetJamesPosZ() };

        Vertex v0 = line->v0;
        Vertex v1 = line->v0;
        Vertex v2 = line->v0;
        Vertex v3 = line->v1;
        v0.diffuse = line->v1.diffuse;
        v2.diffuse = line->v1.diffuse;

        // James forward direction vector
        D3DVECTOR f = { std::cos(angle), 0.0f, std::sin(angle) };

        // Direction vector to raindrop
        D3DVECTOR d = { v0.x - james.x, 0.0f, v0.z - james.z };

        float dropAngle = (f.x * d.x + f.z * d.z) / std::sqrt(d.x * d.x + d.z * d.z);
        bool isLit = dropAngle >= std::sqrt(2) / 2;

        if (isLit && GetFlashlightSwitch() && flashlightAvailable != 1)
        {
            constexpr unsigned char litAlpha = 255;
            v0.diffuse = (v0.diffuse & 0x00FFFFFF) | (litAlpha << 24);
            v1.diffuse = (v1.diffuse & 0x00FFFFFF) | (litAlpha << 24);
            v2.diffuse = (v2.diffuse & 0x00FFFFFF) | (litAlpha << 24);
            v3.diffuse = (v3.diffuse & 0x00FFFFFF) | (litAlpha << 24);
        }

        if (DEBUG_RainColors)
        {
            if (isLit)
            {
                v0.diffuse = D3DCOLOR_ARGB(255, 0, 255, 0);
                v1.diffuse = D3DCOLOR_ARGB(255, 0, 255, 0);
                v2.diffuse = D3DCOLOR_ARGB(255, 0, 255, 0);
                v3.diffuse = D3DCOLOR_ARGB(255, 0, 255, 0);
            }
            else
            {
                v0.diffuse = D3DCOLOR_ARGB(255, 255, 0, 0);
                v1.diffuse = D3DCOLOR_ARGB(255, 255, 0, 0);
                v2.diffuse = D3DCOLOR_ARGB(255, 255, 0, 0);
                v3.diffuse = D3DCOLOR_ARGB(255, 255, 0, 0);
            }
        }

        // Build raindrop triangles
        // TODO: Move billboarding to a vertex shader?
        const Vertex center = { line->v0.x, (line->v0.y + line->v1.y) / 2, line->v0.z };
        constexpr D3DVECTOR upVec = { 0.0f, 1.0f, 0.0f };

        const Vertex camera = { GetInGameCameraPosX(), GetInGameCameraPosY(), GetInGameCameraPosZ() };
        D3DVECTOR toCam = { camera.x - center.x, camera.y - center.y, camera.z - center.z };
        toCam = normalize(toCam);

        const D3DVECTOR rightVec = normalize(cross(upVec, toCam));

        constexpr float DROP_SHOULDER_RATIO = 0.97f;
        float dropShoulder = (line->v1.y - line->v0.y) * DROP_SHOULDER_RATIO;

        v0.y += dropShoulder;
        v2.y += dropShoulder;

        v0.x -= rightVec.x * (width * 0.5f);
        v0.y -= rightVec.y * (width * 0.5f);
        v0.z -= rightVec.z * (width * 0.5f);
        
        v2.x += rightVec.x * (width * 0.5f);
        v2.y += rightVec.y * (width * 0.5f);
        v2.z += rightVec.z * (width * 0.5f);

        triList.push_back({ v0, v1, v2 });
        triList.push_back({ v0, v2, v3 });
    }

    if (DEBUG_DrawFlashlightBeam)
    {
        triList.push_back(DEBUG_flashlightBeam(angle));
    }

    return triList;
}

Triangle DEBUG_flashlightBeam(float angle)
{
    // TODO: Look into this var from Flashlight Reflection patch
    // g_FlashLightPos = reinterpret_cast<float*>(0x1FB7D18);

    constexpr float height = -680.0f;
    constexpr float range = 3000.0f;

    float leftAngle = angle - (3.1415927f / 4.0f);
    float rightAngle = angle + (3.1415927f / 4.0f);

    D3DVECTOR left = { std::cos(leftAngle), 0.0f, std::sin(leftAngle) };
    D3DVECTOR right = { std::cos(rightAngle), 0.0f, std::sin(rightAngle) };

    const Vertex origin = { GetJamesPosX(), GetJamesPosY() + height, GetJamesPosZ(), D3DCOLOR_ARGB(128, 0, 0, 255) };
    const Vertex leftPoint = { origin.x + left.x * range, origin.y, origin.z + left.z * range, D3DCOLOR_ARGB(128, 0, 0, 255) };
    const Vertex rightPoint = { origin.x + right.x * range, origin.y, origin.z + right.z * range, D3DCOLOR_ARGB(128, 0, 0, 255) };

    return { origin, leftPoint, rightPoint };
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

        // NEW CODE
        g_d3d8Device_A32894->DrawPrimitiveUP(D3DPT_TRIANGLELIST, triList.size(), triList.data(), 16);
        // END NEW CODE

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

    // Toggle me in debugger to switch between original and reimpl
    //static bool reimplDrips = true;

    //if (reimplDrips) {
    //    drawDrips(primCount, triList);
    //}
    //else
    //{
    //    __asm mov esi, primCount
    //    originalDrawDrips();
    //}
}

void __cdecl hookDrawTransGeom(TransGeom* pTransGeom)
{
    static bool skipDraw = false;
    if (!skipDraw)
        originalDrawTransGeom(pTransGeom);

    drawDrips(primCountBackup, triListBackup);
}

//void* addr = reinterpret_cast<void*>(0x5B0008);
//
//__declspec(naked) void __stdcall coolHook() noexcept
//{
//    drawDrips(primCountBackup, triListBackup);
//
//    __asm {
//        mov eax, [ebp+4]
//        cmp eax, 0x7FFFFFFF
//        jmp addr
//    }
//}

void PatchDrips()
{
    switch (GameVersion)
    {
    case SH2V_10:
        WriteCalltoMemory((BYTE*)0x4EE4C6, hookDrawDrips);
        WriteCalltoMemory((BYTE*)0x4EE8E0, hookDrawDrips);

        WriteCalltoMemory((BYTE*)0x4762A5, hookDrawTransGeom);
        //WriteJMPtoMemory((BYTE*)0x5B0000, coolHook, 8);
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
