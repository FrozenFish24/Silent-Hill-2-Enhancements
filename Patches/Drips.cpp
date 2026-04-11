#include "Drips.h"
#include "DripTypes.h"
#include <vector>
#include "Common\Utils.h"
#include "Logging\Logging.h"
#include "Patches\Patches.h"
#include "Common\Settings.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"
#include "Wrappers\d3d8\DirectX81SDK\include\d3dx8.h"

static std::vector<Triangle> triListBackup;

// Original SH2 functions
static auto originalDrawDrips = reinterpret_cast<void (*)(/* UINT primCount */)>(0x4EDE20);
static auto originalDrawTransGeom = reinterpret_cast<void (*)(DrawCalls*)>(0x5AFEE0);

// Original SH2 variables
static BYTE& flashlightAvailable_942BF0 = *reinterpret_cast<BYTE*>(0x942BF0);
static Line* vertexStreamZeroData_963880 = reinterpret_cast<Line*>(0x963880);
static IDirect3DDevice8*& g_d3d8Device_A32894 = *reinterpret_cast<IDirect3DDevice8**>(0xA32894);
static D3DVECTOR& forwardVec_1FB7D28 = *reinterpret_cast<D3DVECTOR*>(0x1FB7D28);

Triangle DEBUG_flashlightBeam(const D3DVECTOR& fwd)
{
    constexpr float height = -680.0f;
    constexpr float range = 3000.0f;

    constexpr float halfFOV = 3.1415927f / 4.0f;

    D3DVECTOR left = { fwd.x * std::cos(-halfFOV) - fwd.z * std::sin(-halfFOV), 0.0f, fwd.x * std::sin(-halfFOV) + fwd.z * std::cos(-halfFOV) };
    D3DVECTOR right = { fwd.x * std::cos(halfFOV) - fwd.z * std::sin(halfFOV), 0.0f, fwd.x * std::sin(halfFOV) + fwd.z * std::cos(halfFOV) };

    const Vertex origin = { GetJamesPosX(), GetJamesPosY() + height, GetJamesPosZ(), D3DCOLOR_ARGB(128, 0, 0, 255) };
    const Vertex leftPoint = { origin.x + left.x * range, origin.y, origin.z + left.z * range, D3DCOLOR_ARGB(128, 0, 0, 255) };
    const Vertex rightPoint = { origin.x + right.x * range, origin.y, origin.z + right.z * range, D3DCOLOR_ARGB(128, 0, 0, 255) };

    return { origin, leftPoint, rightPoint };
}

// TODO: Move billboarding into vertex shader
// TODO: Move lighting into vertex shader
// TODO: Angle based brightness fall-off
static std::vector<Triangle> transformDrips(UINT primCount)
{
    if (primCount == 0)
        return {};

    std::vector<Triangle> triList;
    const float width = DropletSize;

    for (size_t i = 0; i < primCount; i++)
    {
        Line line = vertexStreamZeroData_963880[i];
        const Vertex james = { GetJamesPosX(), GetJamesPosY(), GetJamesPosZ() };

        Vertex v0 = line.v0;
        Vertex v1 = line.v0;
        Vertex v2 = line.v0;
        Vertex v3 = line.v1;
        v0.diffuse = line.v1.diffuse;
        v2.diffuse = line.v1.diffuse;

        // James forward direction vector
        D3DVECTOR f = { forwardVec_1FB7D28.x, 0.0f, forwardVec_1FB7D28.z };

        // Direction vector to raindrop
        D3DVECTOR d = { v0.x - james.x, 0.0f, v0.z - james.z };

        float dropAngle = (f.x * d.x + f.z * d.z) / std::sqrt(d.x * d.x + d.z * d.z);
        bool isLit = dropAngle >= std::sqrt(2) / 2;

        if (isLit && GetFlashlightSwitch() && flashlightAvailable_942BF0 != 1)
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
        const Vertex center = { line.v0.x, (line.v0.y + line.v1.y) / 2, line.v0.z };
        const D3DXVECTOR3 upVec = { 0.0f, 1.0f, 0.0f };

        const Vertex camera = { GetInGameCameraPosX(), GetInGameCameraPosY(), GetInGameCameraPosZ() };
        D3DXVECTOR3 toCam = { camera.x - center.x, camera.y - center.y, camera.z - center.z };
        D3DXVec3Normalize(&toCam, &toCam);

        D3DXVECTOR3 rightVec;
        D3DXVec3Normalize(&rightVec, D3DXVec3Cross(&rightVec, &upVec, &toCam));

        constexpr float DROP_SHOULDER_RATIO = 0.97f;
        float dropShoulder = (line.v1.y - line.v0.y) * DROP_SHOULDER_RATIO;

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
        triList.push_back(DEBUG_flashlightBeam({ forwardVec_1FB7D28.x, 0.0f, forwardVec_1FB7D28.z }));
    }

    return triList;
}

static void drawDrips(std::vector<Triangle>& triList)
{
    D3DMATRIX worldMatrix;

    if (triList.size() > 0)
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
        
        worldMatrix = {};
        worldMatrix._44 = 1.0;
        worldMatrix._33 = 1.0;
        worldMatrix._22 = 1.0;
        worldMatrix._11 = 1.0;

        g_d3d8Device_A32894->SetTransform(D3DTS_WORLD, &worldMatrix);
        g_d3d8Device_A32894->SetVertexShader(D3DFVF_XYZ | D3DFVF_DIFFUSE);

        g_d3d8Device_A32894->DrawPrimitiveUP(D3DPT_TRIANGLELIST, triList.size(), triList.data(), 16);
        //g_d3d8Device_A32894->DrawPrimitiveUP(D3DPT_LINELIST, primCount, &vertexStreamZeroData_963880, 16);
    }

    triListBackup.clear();
}

static void hookDrawDrips()
{
    UINT primCount;
    __asm mov primCount, esi
    
    // Accumulate rain in case of multiple calls (e.g. Hospital Courtyard after Flesh Lips)
    auto rain = transformDrips(primCount);
    triListBackup.insert(triListBackup.end(), rain.begin(), rain.end());
    
    // Toggle me in debugger to switch between original and reimpl
    //static bool reimplDrips = true;

    //if (reimplDrips) {
    //    drawDrips();
    //}
    //else
    //{
    //    __asm mov esi, primCount
    //    originalDrawDrips();
    //}
}

static void __cdecl hookDrawTransGeom(DrawCalls* pDrawCalls)
{
    DrawCallNode rain = {};
    rain.type = DrawCallType::Custom;
    rain.typeCustom.func = reinterpret_cast<void(*)(DWORD)>(drawDrips);
    rain.typeCustom.arg = reinterpret_cast<DWORD>(&triListBackup);

    // Insert rain NODES_FROM_TAIL nodes from the end of the draw call list
    constexpr int NODES_FROM_TAIL = 9;
    DrawCallNode* slow = pDrawCalls->head;
    DrawCallNode* fast = pDrawCalls->head;

    // Move fast pointer NODES_FROM_TAIL nodes ahead
    for (int i = 0; fast->pNext && i < NODES_FROM_TAIL; i++)
        fast = fast->pNext;

    while (fast->pNext) {
        slow = slow->pNext;
        fast = fast->pNext;
    }

    rain.pNext = slow->pNext;
    slow->pNext = &rain;

    originalDrawTransGeom(pDrawCalls);

    // Remove rain from the linked-list in case the game tries to free it later
    slow->pNext = rain.pNext;
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
