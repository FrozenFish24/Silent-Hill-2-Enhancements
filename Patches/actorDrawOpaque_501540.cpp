#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstring>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"
#include "Specular.h"

#pragma optimize("", off)
void __cdecl actorDrawOpaque_501540(ModelMaterial* pModelMaterial)
{
    int v1; // edi
    bool cullMode; // zf
    float v3; // st7
    float ambientG; // edx
    float ambientB; // ecx
    float specularX; // edx
    float v7; // st7
    float diffuseG; // edx
    float diffuseB; // ecx
    float ambientX; // edx
    unsigned int pSamplerStateArray; // esi
    //DWORD v12; // edx
    ModelSamplerStates* samplerStateArray; // esi
    char materialType; // al
    unsigned __int16* unkU16Array0Offset; // eax
    char* v16; // edx
    unsigned int unkU16Count0; // esi
    int v18; // ecx
    unsigned int unkU16Count1; // ecx
    unsigned __int16* unkU16Array1Offset; // eax
    unsigned int v21; // ebx
    char* v22; // edx
    const void* v23; // esi
    unsigned int v24; // ecx
    IDirect3DVertexBuffer8* pStreamData; // ecx

    DWORD Stage; // [esp+17Ch] [ebp-E4h]
    D3DTEXTURESTAGESTATETYPE Type; // [esp+180h] [ebp-E0h]
    float v25; // [esp+198h] [ebp-C8h]
    float specularHighlightScale; // [esp+198h] [ebp-C8h]
    float vsConstants[4]; // [esp+19Ch] [ebp-C4h]
    unsigned int v27; // [esp+1ACh] [ebp-B4h]
    float vsConstants_1[4]; // [esp+1B0h] [ebp-B0h]
    float vsConstants_2[4]; // [esp+1C0h] [ebp-A0h]
    float vsConstants_3[4]; // [esp+1D0h] [ebp-90h]
    D3DMATRIX texture1Matrix; // [esp+1E0h] [ebp-80h]
    D3DMATRIX otherMatrix; // [esp+220h] [ebp-40h]

    v25 = sub_50C500();
    v1 = 0;
    cullMode = pModelMaterial->cullMode == 0;
    v27 = 0;

    if (cullMode)
        pD3DDevice_A32894->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    else
        pD3DDevice_A32894->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

    if (pModelMaterial->materialType == 1)
    {
        vsConstants_1[3] = 1.0;
        vsConstants_1[2] = 1.0;
        vsConstants_1[1] = 1.0;
        vsConstants_1[0] = 1.0;
    }
    else
    {
        v3 = v25 * pModelMaterial->unkAmbientFloat;
        ambientG = pModelMaterial->ambientG;
        vsConstants_1[0] = pModelMaterial->ambientR;
        ambientB = pModelMaterial->ambientB;
        vsConstants_1[1] = ambientG;
        specularX = pModelMaterial->specularX;
        vsConstants_1[0] = float_1F7D510 * vsConstants_1[0];
        vsConstants_1[1] = float_1F7D514 * vsConstants_1[1];
        vsConstants_1[2] = float_1F7D518 * ambientB;
        vsConstants_1[3] = float_1F7D51C * v3;
    }

    v7 = v25 * pModelMaterial->unkDiffuseFloat;
    diffuseG = pModelMaterial->diffuseG;
    vsConstants_3[0] = pModelMaterial->diffuseR;
    diffuseB = pModelMaterial->diffuseB;
    vsConstants_3[1] = diffuseG;
    ambientX = pModelMaterial->ambientX;
    vsConstants_3[3] = v7;
    vsConstants_3[2] = diffuseB;

    if (bUsePixelShaders_A33374)
    {
        pD3DDevice_A32894->SetVertexShaderConstant(43, vsConstants_3, 1);
        pD3DDevice_A32894->SetVertexShaderConstant(44, vsConstants_1, 1);
    }

    if (dword_1F7D718 && dword_A33370)
    {
        vsConstants[0] = float_1F7D65C * vsConstants_3[0];
        vsConstants[3] = float_1F7D668;
        vsConstants[1] = float_1F7D660 * vsConstants_3[1];
        vsConstants[2] = float_1F7D664 * vsConstants_3[2];
        pD3DDevice_A32894->SetPixelShaderConstant(2, vsConstants, 1);
    }

    pSamplerStateArray = pModelMaterial->samplerStatesOffset;
    //v12 = *((unsigned char*)&pModelMaterial->pNext + pSamplerStateArray);
    samplerStateArray = (ModelSamplerStates*)((unsigned int)&pModelMaterial + pSamplerStateArray);

    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ADDRESSU, samplerStateArray->addressu /*v12*/);
    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ADDRESSV, samplerStateArray->addressv);
    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_MAGFILTER, samplerStateArray->magfilter);
    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_MINFILTER, samplerStateArray->minfilter);

    if (pModelMaterial->materialType == 4)
    {
        specularHighlightScale = pModelMaterial->specularHighlightScale;
        if (bUsePixelShaders_A33374)
        {
            copyMatrixFromAAA634_50C570(&texture1Matrix);
            vsConstants[0] = texture1Matrix._11 * specularHighlightScale;
            vsConstants[3] = 0.5;
            vsConstants_2[3] = 0.5;
            vsConstants[1] = texture1Matrix._21 * specularHighlightScale;
            vsConstants[2] = texture1Matrix._31 * specularHighlightScale;
            vsConstants_2[0] = texture1Matrix._12 * specularHighlightScale;
            vsConstants_2[1] = texture1Matrix._22 * specularHighlightScale;
            vsConstants_2[2] = texture1Matrix._32 * specularHighlightScale;
            pD3DDevice_A32894->SetVertexShaderConstant(89, vsConstants, 1);
            pD3DDevice_A32894->SetVertexShaderConstant(90, vsConstants_2, 1);
        }
        else
        {
            copyMatrixFromAAA634_50C570(&texture1Matrix);
            vsConstants_2[0] = specularHighlightScale;
            vsConstants_2[1] = specularHighlightScale;
            vsConstants_2[2] = specularHighlightScale;
            vsConstants_2[3] = 1.0;

            // Arguments passed via register
            __asm
            {
                mov edx, vsConstants_2
                mov ecx, otherMatrix
            }
            sub_4FE750(/*vsConstants_2, &otherMatrix*/);
            otherMatrix._31 = 0.5;
            otherMatrix._32 = 0.5;
            D3DXMatrixTranspose_4199CA(&texture1Matrix, &otherMatrix);
            pD3DDevice_A32894->SetTransform(D3DTS_TEXTURE1, &texture1Matrix);
        }
    }

    // Sets the diffuse texture for rendering piece of current actor
    pD3DDevice_A32894->SetTexture(0, *(IDirect3DBaseTexture8**)(&pMoreUnkModelData_1F7D4AC->textureBase + *(signed __int16*)((char*)&pModelMaterial->materialLength + pModelMaterial->unkU16Array2Offset)));

    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

    if (dword_1F7D718 && dword_A33370)
        goto LABEL_24;

    if (!bUsePixelShaders_A33374)
    {
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_RESULTARG, D3DTA_CURRENT);
        materialType = (char)pModelMaterial->materialType;

        if (materialType != 1)
        {
            if (materialType == 4)
            {
                pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
                pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
                pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
                pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
                pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
                pD3DDevice_A32894->SetTexture(1, pMoreUnkModelData_1F7D4AC->specularTexture);
                pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1 | D3DTSS_TCI_CAMERASPACENORMAL);
                pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
                pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
                pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

                if (dword_A333C0)
                    pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDDIFFUSEALPHA);
                else
                    pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);

                pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
                pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
                pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
                pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
                goto LABEL_24;
            }

            pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
            pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
            pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
            pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
            pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
            pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

            Type = D3DTSS_COLOROP;
            goto LABEL_22;
        }

        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

    LABEL_21:
        pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        Type = D3DTSS_ALPHAOP;

    LABEL_22:
        Stage = 1;

    LABEL_23:
        pD3DDevice_A32894->SetTextureStageState(Stage, Type, D3DTOP_DISABLE);
        goto LABEL_24;
    }

    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_RESULTARG, D3DTA_CURRENT);

    if (pModelMaterial->materialType != 1)
    {
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

        if (pModelMaterial->unkMaterialSubtype)
        {
            pD3DDevice_A32894->SetTexture(1, pMoreUnkModelData_1F7D4AC->specularTexture);
            pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
            pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
            pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
            pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDCURRENTALPHA);
            pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
            pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
            pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

            Type = D3DTSS_ALPHAOP;
            Stage = 2;
            goto LABEL_23;
        }

        goto LABEL_21;
    }

    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

LABEL_24:

    if (dword_1F7D718 && dword_A33370)
    {
        pD3DDevice_A32894->SetTexture(1, pMoreUnkModelData_1F7D4AC->specularTexture);
        pD3DDevice_A32894->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
        pD3DDevice_A32894->SetTexture(2, cubeMapTexture_1F7D710);
        pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 2);
        pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
        pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
        pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
        pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
        pD3DDevice_A32894->SetTextureStageState(2, D3DTSS_MIPFILTER, D3DTEXF_NONE);

        if (pModelMaterial->materialType == 4)
        {
            vsConstants[0] = pModelMaterial->specularR * 0.0078125f;
            vsConstants[1] = pModelMaterial->specularG * 0.0078125f;
            vsConstants[2] = pModelMaterial->specularB * 0.0078125f;
        }
        else
        {
            vsConstants[0] = 0.0;
            vsConstants[1] = 0.0;
            vsConstants[2] = 0.0;
        }
        vsConstants[3] = 0.0;

        // Controls color and opacity of specular highlights
        pD3DDevice_A32894->SetPixelShaderConstant(3, vsConstants, 1); // Specular hack Part 3 happens here
    }
    unkU16Array0Offset = (unsigned short*)((char*)pModelMaterial + pModelMaterial->unkU16Array0Offset);

    if (pModelMaterial->unkU16Count0)
    {
        v16 = byte_A33590;

        do
        {
            std::memcpy(v16, &pMoreUnkModelData_1F7D4AC->matrices[*unkU16Array0Offset], 64);
            unkU16Count0 = pModelMaterial->unkU16Count0;
            ++unkU16Array0Offset;
            v18 = v27 + 1;
            v16 += 64;
            ++v27;
        } while (v27 < unkU16Count0);
        v1 = v18;
    }

    unkU16Count1 = pModelMaterial->unkU16Count1;
    unkU16Array1Offset = (unsigned short*)((char*)pModelMaterial + pModelMaterial->unkU16Array1Offset);
    v21 = 0;

    if (unkU16Count1)
    {
        v22 = &byte_A33590[64 * v1];

        do
        {
            v23 = &pMoreUnkModelData_1F7D4AC->matrices[*unkU16Array1Offset + 128];
            ++unkU16Array1Offset;
            std::memcpy(v22, v23, 64);
            unkU16Count1 = pModelMaterial->unkU16Count1;
            ++v21;
            v22 += 64;
        } while (v21 < unkU16Count1);
    }

    __asm
    {
        mov ecx, unkU16Count1
        mov edi, pModelMaterial
    }
    sub_5014C0(/*unkU16Count1, (int)pModelMaterial*/);
    pD3DDevice_A32894->SetIndices((IDirect3DIndexBuffer8*)pModelMaterial->reserved1[1].pIndexData, 0);
    v24 = 8;

    while (&pModelMaterial->reserved1->pIndexData[1] > (struct_dword38_dword0*)(1 << v24))
    {
        if (++v24 > 14)
        {
            pStreamData = NULL;
            goto LABEL_51;
        }
    }

    pStreamData = vertexBufferArray_A33540[v24];

LABEL_51:
    pD3DDevice_A32894->SetStreamSource(0, pStreamData, 32);
    pD3DDevice_A32894->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, (UINT)pModelMaterial->reserved1->pIndexData, 0, pModelMaterial->primCount - 2);
}
#pragma optimize("", on)
