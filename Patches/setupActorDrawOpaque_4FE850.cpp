#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cmath>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"
#include "Specular.h"

#pragma optimize("", off)
void __cdecl setupActorDrawOpaque_4FE850()
{
    signed int lightIndex; // esi
    int modelId; // eax
    signed int matrixIndex; // ebp
    signed int v3; // ebx
    float* v4; // edi
    float v5; // ecx
    float v6; // edx
    double v7; // st7
    int v8; // edi
    signed int v9; // ebx
    LightSourceStruct* pLightStruct; // eax
    LightSourceStruct* pLightStruct_1; // edi
    int lightType; // eax
    float v13; // ecx
    DWORD v14; // ebx
    float ambientR; // ecx
    float ambientG; // edx
    float lightDirX; // ecx
    float lightDirZ; // eax
    int v19; // eax
    int v20; // ecx
    double v21; // st7
    long double v22; // st6
    long double v23; // st6
    double v24; // st7
    double v25; // st7
    float v26; // ST8C_4
    float v27; // ST8C_4
    double v28; // st7
    double v29; // st7
    DWORD v30; // edi
    signed int v31; // esi
    DWORD v32; // edi
    signed int v33; // esi
    double v34; // st7
    float v35; // edx
    float v36; // eax
    double v37; // st7
    //IDirect3DDevice8Vtbl* lpVtbl_1; // ecx
    double v39; // st7
    DWORD vsHandle; // ecx
    //IDirect3DDevice8* pD3DDevice_1; // eax
    //IDirect3DDevice8Vtbl* lpVtbl; // edx
    float vsConstants_12[4]; // [esp+A0h] [ebp-2B4h]
    float vsConstants[4]; // [esp+B0h] [ebp-2A4h]
    float vsConstants_9[4]; // [esp+C0h] [ebp-294h]
    int dword_AAA418Plus3Div4; // [esp+D0h] [ebp-284h]
    float v47; // [esp+D4h] [ebp-280h]
    int v48; // [esp+D8h] [ebp-27Ch]
    float vsConstants_10[4]; // [esp+DCh] [ebp-278h]
    float vsConstants_11[4]; // [esp+ECh] [ebp-268h]
    float vsConstants_1[4]; // [esp+FCh] [ebp-258h]
    DWORD vsRegister; // [esp+10Ch] [ebp-248h]
    int lightSourceCount; // [esp+110h] [ebp-244h]
    int vsRegister_1; // [esp+114h] [ebp-240h]
    int v55; // [esp+118h] [ebp-23Ch]
    int index; // [esp+11Ch] [ebp-238h]
    DWORD fogColor; // [esp+120h] [ebp-234h]
    float v58; // [esp+124h] [ebp-230h]
    float psConstants[4]; // [esp+128h] [ebp-22Ch]
    D3DMATRIX projMatrixTranspose; // [esp+138h] [ebp-21Ch]
    int v61; // [esp+178h] [ebp-1DCh]
    int v62; // [esp+17Ch] [ebp-1D8h]
    int v63; // [esp+180h] [ebp-1D4h]
    int v64; // [esp+184h] [ebp-1D0h]
    float v65; // [esp+188h] [ebp-1CCh]
    float v66; // [esp+18Ch] [ebp-1C8h]
    float v67; // [esp+190h] [ebp-1C4h]
    int v68; // [esp+194h] [ebp-1C0h]
    int v69; // [esp+198h] [ebp-1BCh]
    int v70; // [esp+19Ch] [ebp-1B8h]
    float v71; // [esp+1A0h] [ebp-1B4h]
    int v72; // [esp+1A4h] [ebp-1B0h]
    int v73; // [esp+1A8h] [ebp-1ACh]
    int v74; // [esp+1ACh] [ebp-1A8h]
    float v75; // [esp+1B0h] [ebp-1A4h]
    float v76; // [esp+1B4h] [ebp-1A0h]
    float v77; // [esp+1B8h] [ebp-19Ch]
    float v78; // [esp+1BCh] [ebp-198h]
    float v79; // [esp+1C0h] [ebp-194h]
    float v80[4]; // [esp+1C4h] [ebp-190h]
    D3DLIGHT8 light; // [esp+1D4h] [ebp-180h]
    float vsConstants_2[4]; // [esp+23Ch] [ebp-118h]
    D3DLIGHT8 light_1; // [esp+24Ch] [ebp-108h]
    D3DMATRIX someMatrix; // [esp+2B4h] [ebp-A0h]
    float vsConstants_4[4]; // [esp+2F4h] [ebp-60h]
    float vsConstants_5[4]; // [esp+304h] [ebp-50h]
    float vsConstants_8[4]; // [esp+314h] [ebp-40h]
    float vsConstants_6[4]; // [esp+324h] [ebp-30h]
    float vsConstants_3[4]; // [esp+334h] [ebp-20h]
    float vsConstants_7[4]; // [esp+344h] [ebp-10h]

    fogColor = fogColor_1F7D634;
    lightIndex = 0;
    vsConstants_1[0] = 0.0f;
    vsConstants_1[1] = 0.0f;
    vsConstants_1[2] = 0.0f;
    vsConstants_1[3] = 0.0f;

    if (!dword_A3FD90)
        dword_A3FD90 = 1;

    dword_1F7D718 = 0;

    if (bUsePixelShaders_A33374)
    {
        vsConstants[0] = 0.0f;
        vsConstants[1] = 1.0f;
        vsConstants[2] = 768.0f;
        vsConstants[3] = 0.5f;

        pD3DDevice_A32894->SetVertexShaderConstant(0, vsConstants, 1);
        pD3DDevice_A32894->SetVertexShaderConstant(45, &vsConstant_1F7D500, 1);
        D3DXMatrixTranspose_4199CA(&projMatrixTranspose, &projMatrix_1F7D570);
        pD3DDevice_A32894->SetVertexShaderConstant(39, &projMatrixTranspose, 4);
    }
    else
    {
        pD3DDevice_A32894->SetTransform(D3DTS_WORLD, &worldMatrix0_1F7D5F0);
        pD3DDevice_A32894->SetTransform(D3DTS_VIEW, &viewMatrix_1F7D530);
        pD3DDevice_A32894->SetTransform(D3DTS_PROJECTION, &projMatrix_1F7D570);
    }

    v47 = 9999.0f;
    modelId = getModelId_50B6C0();

    if (isCertainValues_50DE10(modelId))
    {
      v47 = -1.0f;
      dword_1F7D720 = 1;
    }
    else
    {
      dword_1F7D720 = 0;
    }

    matrixIndex = 0;
    dword_AAA418Plus3Div4 = getDword_AAA418Plus3Div4_50C480();

    if (dword_AAA418Plus3Div4 > 0)
    {
        do
        {
            if (bUsePixelShaders_A33374)
                copyMatrixFromAAA4A8AtIndex_50C4C0(&projMatrixTranspose, matrixIndex);
            else
                copyMatrixFromAAA428AtIndex_50C4A0(&projMatrixTranspose, matrixIndex);

            copyMatrixFromAAA528AtIndex_50C4E0(&someMatrix, matrixIndex);
            v3 = 0;
            v4 = &someMatrix._12;

            do
            {
                vsConstants_10[0] = *(&projMatrixTranspose._11 + v3);
                vsConstants_10[1] = *(&projMatrixTranspose._21 + v3);
                vsConstants_10[2] = *(&projMatrixTranspose._31 + v3);

                if (v4[2] == v47)
                {
                    vsConstants_9[0] = vsConstants_1[0];
                    vsConstants_9[1] = vsConstants_1[1];
                    vsConstants_9[2] = vsConstants_1[2];
                    vsConstants_9[3] = vsConstants_1[3];
                }
                else
                {
                    v5 = *v4;
                    v6 = v4[1];
                    vsConstants_9[0] = *(v4 - 1);
                    vsConstants_9[1] = v5;
                    vsConstants_9[2] = v6;
                }

                if (bUsePixelShaders_A33374)
                {
                    pD3DDevice_A32894->SetVertexShaderConstant(lightIndex + 47, vsConstants_10, 1);
                    pD3DDevice_A32894->SetVertexShaderConstant(lightIndex++ + 55, vsConstants_9, 1);
                }
                else
                {
                    v7 = v4[2];
                    light.Direction.x = vsConstants_10[0];
                    vsConstants_11[0] = 0.0f;
                    light.Ambient.r = 0.0f;
                    light.Direction.y = vsConstants_10[1];
                    light.Direction.z = vsConstants_10[2];
                    vsConstants_11[3] = 1.0f;
                    light.Ambient.a = 1.0f;
                    vsConstants_11[1] = 0.0f;
                    vsConstants_11[2] = 0.0f;
                    light.Ambient.g = 0.0f;
                    light.Ambient.b = 0.0f;
                    light.Diffuse.b = vsConstants_9[2];
                    vsConstants_12[1] = 0.0f;
                    light.Diffuse.r = vsConstants_9[0];
                    light.Diffuse.g = vsConstants_9[1];
                    vsConstants_12[0] = 0.0f;
                    light.Specular.g = 0.0f;
                    light.Diffuse.a = vsConstants_9[3];
                    vsConstants_12[2] = 0.0f;
                    vsConstants_12[3] = 1.0f;
                    light.Specular.r = 0.0f;
                    light.Type = D3DLIGHT_DIRECTIONAL;
                    light.Specular.b = 0.0f;
                    light.Specular.a = 1.0f;
                    light.Range = 10000000.0f;

                    if (v7 == v47 || fabs(vsConstants_10[0]) < 0.000099999997f && fabs(vsConstants_10[1]) < 0.000099999997f && fabs(vsConstants_10[2]) < 0.000099999997f || fabs(vsConstants_9[0]) < 0.000099999997f && fabs(vsConstants_9[1]) < 0.000099999997f && fabs(vsConstants_9[2]) < 0.000099999997f)
                    {
                        pD3DDevice_A32894->LightEnable(lightIndex, FALSE);
                    }
                    else
                    {
                        pD3DDevice_A32894->SetLight(lightIndex, &light);
                        pD3DDevice_A32894->LightEnable(lightIndex++, TRUE);

                        if (lightIndex >= 8)
                            lightIndex = 7;
                    }
                }
                ++v3;
                v4 += 4;
            } while (v3 < 4);

            ++matrixIndex;
        } while (matrixIndex < dword_AAA418Plus3Div4);
    }

    if (bUsePixelShaders_A33374 && matrixIndex < 2)
    {
        v8 = 2 - matrixIndex;

        do
        {
            pD3DDevice_A32894->SetVertexShaderConstant(lightIndex + 47, vsConstants_1, 1);
            pD3DDevice_A32894->SetVertexShaderConstant(lightIndex++ + 55, vsConstants_1, 1);
            --v8;
        } while (v8);
    }

    copyof_dword_AAA418_A33580 = getDword_AAA418_50C470();
    v9 = 0;
    lightSourceCount = getLightSourceCount_50C590(); // Specular Hack Part 1 happens here

    v55 = 0;
    v48 = 0;
    dword_AAA418Plus3Div4 = 1;
    index = 0;

    if (lightSourceCount > 0)
    {
        vsRegister = 66;
        vsRegister_1 = 79;

        do
        {
            pLightStruct = getLightSourceStruct_50C5A0(index); // Specular Hack Part 2 happens here

            pLightStruct_1 = pLightStruct;
            lightType = pLightStruct->light.Type - 2;

            if (lightType)
            {
                if (lightType == 1)
                {
                    vsConstants_10[0] = pLightStruct_1->light.Ambient.a;
                    vsConstants_10[1] = pLightStruct_1->light.Position.x;
                    vsConstants_10[2] = pLightStruct_1->light.Position.y;
                    vsConstants_10[3] = pLightStruct_1->light.Position.z;
                    vsConstants_11[0] = pLightStruct_1->light.Falloff;
                    vsConstants_11[1] = pLightStruct_1->light.Attenuation0;
                    vsConstants_11[2] = pLightStruct_1->light.Attenuation1;
                    vsConstants_11[3] = pLightStruct_1->light.Attenuation2;

                    if (pLightStruct_1->extraFloats[1] == v47)
                    {
                        vsConstants_12[0] = vsConstants_1[0];
                        v13 = vsConstants_1[3];
                        vsConstants_12[1] = vsConstants_1[1];
                        vsConstants_12[2] = vsConstants_1[2];
                    }
                    else
                    {
                        vsConstants_12[0] = pLightStruct_1->light.Theta;
                        vsConstants_12[1] = pLightStruct_1->light.Phi;
                        vsConstants_12[2] = pLightStruct_1->extraFloats[0];
                        v13 = pLightStruct_1->extraFloats[1];
                    }

                    vsConstants_12[3] = v13;

                    if (bUsePixelShaders_A33374)
                    {
                        v14 = vsRegister_1;
                        pD3DDevice_A32894->SetVertexShaderConstant(vsRegister_1 - 2, vsConstants_10, 1);
                        pD3DDevice_A32894->SetVertexShaderConstant(v14, vsConstants_11, 1);
                        pD3DDevice_A32894->SetVertexShaderConstant(v14 - 1, vsConstants_12, 1);
                    }
                    else
                    {
                        ambientR = pLightStruct_1->light.Ambient.r;
                        ambientG = pLightStruct_1->light.Ambient.g;
                        light_1.Position.x = pLightStruct_1->light.Specular.a;
                        light_1.Position.y = ambientR;
                        light_1.Position.z = ambientG;
                        lightDirX = pLightStruct_1->light.Direction.x;
                        lightDirZ = pLightStruct_1->light.Direction.z;
                        light_1.Direction.y = pLightStruct_1->light.Direction.y;
                        light_1.Direction.x = lightDirX;
                        light_1.Direction.z = lightDirZ;
                        v62 = 0;
                        light_1.Ambient.r = 0.0f;
                        v63 = 0;
                        light_1.Ambient.g = 0.0f;
                        v64 = 0;
                        light_1.Ambient.b = 0.0f;
                        v65 = 1.0;
                        light_1.Ambient.a = 1.0f;
                        v68 = 0;
                        light_1.Specular.r = 0.0f;
                        v69 = 0;
                        light_1.Specular.g = 0.0f;
                        v70 = 0;
                        v71 = 1.0f;
                        light_1.Specular.a = 1.0f;
                        light_1.Specular.b = 0.0f;
                        v79 = vsConstants_12[3];
                        light_1.Diffuse.r = vsConstants_12[0];
                        v77 = vsConstants_12[1];
                        light_1.Diffuse.a = vsConstants_12[3];
                        v76 = vsConstants_12[0];
                        v78 = vsConstants_12[2];
                        light_1.Diffuse.g = vsConstants_12[1];
                        light_1.Type = D3DLIGHT_SPOT;
                        light_1.Range = 10000000.0f;
                        light_1.Attenuation0 = 1.0f;
                        light_1.Attenuation1 = 0.0f;
                        light_1.Attenuation2 = 0.0f;
                        light_1.Diffuse.b = vsConstants_12[2];
                        light_1.Phi = 2.575f;
                        light_1.Theta = 0.0f;
                        light_1.Falloff = 8.0f;
                        pD3DDevice_A32894->SetLight(lightIndex, &light_1);

                        if (pLightStruct_1->extraFloats[1] == v47 || fabs(pLightStruct_1->light.Direction.x) < 0.000099999997f && fabs(pLightStruct_1->light.Direction.y) < 0.000099999997f && fabs(pLightStruct_1->light.Direction.z) < 0.000099999997f || fabs(vsConstants_12[0]) < 0.000099999997f && fabs(vsConstants_12[1]) < 0.000099999997f && fabs(vsConstants_12[2]) < 0.000099999997f)
                        {
                            pD3DDevice_A32894->LightEnable(lightIndex, FALSE);
                        }
                        else
                        {
                            pD3DDevice_A32894->LightEnable(lightIndex++, TRUE);

                            if (lightIndex >= 8)
                                lightIndex = 7;
                        }
                    }

                    v19 = v48;
                    vsConstants_5[v48] = pLightStruct_1->extraFloats[10];
                    vsConstants_6[v19] = pLightStruct_1->extraFloats[11];
                    vsConstants_7[v19] = pLightStruct_1->extraFloats[8];
                    v20 = vsRegister_1;
                    vsConstants_8[v19] = pLightStruct_1->extraFloats[9];
                    v48 = v19 + 1;
                    vsRegister_1 = v20 + 3;

                    if (dword_A33370 && dword_AAA418Plus3Div4)
                    {
                        dword_1F7D718 = 1;

                        if (vsConstants_12[0] <= (double)vsConstants_12[1])
                            v21 = vsConstants_12[1];
                        else
                            v21 = vsConstants_12[0];

                        if (v21 <= vsConstants_12[2])
                            v21 = vsConstants_12[2];

                        if (vsConstants_12[0] != 7.0f || vsConstants_12[1] != 7.0f || vsConstants_12[0] != 7.0f || (v22 = cos(0.785398006439209), *(float*)&dword_AAA418Plus3Div4 = v22, v23 = v22 * 0.80000001f, v58 = v23, -v23 - 0.0099999998f >= pLightStruct_1->extraFloats[9]) || 0.0099999998f - v58 <= pLightStruct_1->extraFloats[9])
                        {
                            if (v21 <= 4.0)
                            {
                                if (v21 <= 2.0)
                                {
                                    if (v21 <= 1.0)
                                    {
                                        unkIndex_1F7D714 = 0;
                                        vsConstants_9[0] = vsConstants_12[0];
                                        vsConstants_9[1] = vsConstants_12[1];
                                        vsConstants_9[2] = vsConstants_12[2];
                                    }
                                    else
                                    {
                                        unkIndex_1F7D714 = 1;
                                        vsConstants_9[0] = vsConstants_12[0] * 0.5f;
                                        vsConstants_9[1] = vsConstants_12[1] * 0.5f;
                                        vsConstants_9[2] = vsConstants_12[2] * 0.5f;
                                    }
                                }
                                else
                                {
                                    unkIndex_1F7D714 = 2;
                                    vsConstants_9[0] = vsConstants_12[0] * 0.25f;
                                    vsConstants_9[1] = vsConstants_12[1] * 0.25f;
                                    vsConstants_9[2] = vsConstants_12[2] * 0.25f;
                                }
                            }
                            else
                            {
                                unkIndex_1F7D714 = 3;
                                vsConstants_9[0] = vsConstants_12[0] * 0.125f;
                                vsConstants_9[1] = vsConstants_12[1] * 0.125f;
                                vsConstants_9[2] = vsConstants_12[2] * 0.125f;
                            }
                        }
                        else
                        {
                            unkIndex_1F7D714 = 4;

                            if (dword_1F7D720)
                                v24 = 1.0f - *(float*)&dword_AAA418Plus3Div4 * 0.94f;
                            else
                                v24 = 1.0f - v58;

                            v25 = v24 * 1.75f;
                            vsConstants_9[1] = v25;
                            vsConstants_9[2] = v25;
                            vsConstants_9[0] = v25;
                            v66 = vsConstants_11[2];
                            v67 = vsConstants_11[0];
                            v26 = atan2(vsConstants_11[1], sqrt(vsConstants_11[0] * vsConstants_11[0] + vsConstants_11[2] * vsConstants_11[2]));
                            D3DXMatrixRotationX_41A2C4(&projMatrixTranspose, v26);
                            v27 = -atan2(v67, v66);
                            D3DXMatrixRotationY_41A360(&someMatrix, v27);
                            D3DXMatrixMultiply_419781(&someMatrix, &someMatrix, &projMatrixTranspose);

                            if (dword_1F7D720)
                            {
                                D3DXMatrixRotationX_41A2C4(&projMatrixTranspose, 0.61548001f);
                                D3DXMatrixMultiply_419781(&someMatrix, &someMatrix, &projMatrixTranspose);
                                D3DXMatrixRotationY_41A360(&projMatrixTranspose, 3.926991f);
                            }
                            else
                            {
                                D3DXMatrixRotationX_41A2C4(&projMatrixTranspose, -0.61548001f);
                                D3DXMatrixMultiply_419781(&someMatrix, &someMatrix, &projMatrixTranspose);
                                D3DXMatrixRotationY_41A360(&projMatrixTranspose, 0.78539819f);
                            }

                            D3DXMatrixMultiply_419781(&someMatrix, &someMatrix, &projMatrixTranspose);
                            D3DXMatrixTranspose_4199CA(&someMatrix, &someMatrix);
                            pD3DDevice_A32894->SetVertexShaderConstant(91, &someMatrix, 3);
                        }

                        pD3DDevice_A32894->SetPixelShader(pixelShaderHandleArr_1F7D6C4[unkIndex_1F7D714]);
                        psConstants[3] = pLightStruct_1->extraFloats[8];
                        psConstants[0] = (vsConstants_11[0] + 1.0f) * 0.5f;
                        psConstants[1] = (vsConstants_11[1] + 1.0f) * 0.5f;
                        psConstants[2] = (vsConstants_11[2] + 1.0f) * 0.5f;
                        v28 = pLightStruct_1->extraFloats[9];

                        if (dword_1F7D720)
                            v29 = v28 * -1.175f;
                        else
                            v29 = -v28;

                        vsConstants_9[3] = v29;

                        if (unkIndex_1F7D714 != 4)
                            pD3DDevice_A32894->SetPixelShaderConstant(1, psConstants, 1);

                        float_1F7D65C = vsConstants_9[0];
                        float_1F7D660 = vsConstants_9[1];
                        float_1F7D664 = vsConstants_9[2];
                        float_1F7D668 = vsConstants_9[3];
                        dword_AAA418Plus3Div4 = 0;
                    }
                    v9 = v55;
                }
            }
            else
            {
                if (bUsePixelShaders_A33374)
                {
                    vsConstants_10[0] = pLightStruct_1->light.Ambient.a;
                    vsConstants_10[1] = pLightStruct_1->light.Position.x;
                    vsConstants_10[2] = pLightStruct_1->light.Position.y;
                    vsConstants_10[3] = pLightStruct_1->light.Position.z;
                }
                else
                {
                    vsConstants_10[0] = pLightStruct_1->light.Specular.a;
                    vsConstants_10[1] = pLightStruct_1->light.Ambient.r;
                    vsConstants_10[2] = pLightStruct_1->light.Ambient.g;
                    vsConstants_10[3] = pLightStruct_1->light.Ambient.b;
                }

                if (pLightStruct_1->extraFloats[1] == v47)
                {
                    vsConstants_12[0] = vsConstants_1[0];
                    vsConstants_12[1] = vsConstants_1[1];
                    vsConstants_12[2] = vsConstants_1[2];
                    vsConstants_12[3] = vsConstants_1[3];
                }
                else
                {
                    vsConstants_12[0] = pLightStruct_1->light.Theta;
                    vsConstants_12[1] = pLightStruct_1->light.Phi;
                    vsConstants_12[2] = pLightStruct_1->extraFloats[0];
                    vsConstants_12[3] = pLightStruct_1->extraFloats[1];
                }

                if (bUsePixelShaders_A33374)
                {
                    pD3DDevice_A32894->SetVertexShaderConstant(vsRegister - 1, vsConstants_10, 1);
                    pD3DDevice_A32894->SetVertexShaderConstant(vsRegister, vsConstants_12, 1);
                }
                else
                {
                    v34 = 100.0 / pLightStruct_1->extraFloats[3];
                    v35 = pLightStruct_1->light.Ambient.r;
                    v36 = pLightStruct_1->light.Ambient.g;
                    light.Position.x = pLightStruct_1->light.Specular.a;
                    light.Position.z = v36;
                    v80[0] = 0.0f;
                    light.Ambient.r = 0.0f;
                    v80[2] = 0.0f;
                    light.Ambient.b = 0.0f;
                    v80[3] = 1.0f;
                    light.Ambient.a = 1.0f;
                    light.Position.y = v35;
                    v73 = 0;
                    light.Specular.g = 0.0f;
                    v74 = 0;
                    light.Specular.b = 0.0f;
                    v80[1] = 0.0f;
                    light.Ambient.g = 0.0f;
                    vsConstants[3] = vsConstants_12[3];
                    v72 = 0;
                    light.Specular.r = 0.0f;
                    v75 = 1.0f;
                    light.Specular.a = 1.0;
                    light.Type = D3DLIGHT_POINT;
                    light.Range = 10000000.0f;
                    light.Attenuation0 = 0.0f;
                    light.Attenuation2 = 0.0f;
                    light.Attenuation1 = v34;
                    v37 = light.Attenuation1 * pLightStruct_1->extraFloats[2];
                    vsConstants[0] = vsConstants_12[0] * v37;
                    light.Diffuse.r = vsConstants[0];
                    light.Diffuse.a = vsConstants_12[3];
                    vsConstants[1] = vsConstants_12[1] * v37;
                    light.Diffuse.g = vsConstants[1];
                    vsConstants[2] = vsConstants_12[2] * v37;
                    light.Diffuse.b = vsConstants[2];
                    pD3DDevice_A32894->SetLight(lightIndex, &light);

                    if (pLightStruct_1->extraFloats[1] == v47 || fabs(vsConstants_12[0]) < 0.000099999997f && fabs(vsConstants_12[1]) < 0.000099999997f && fabs(vsConstants_12[2]) < 0.000099999997f)
                    {
                        pD3DDevice_A32894->LightEnable(lightIndex, FALSE);
                    }
                    else
                    {
                        pD3DDevice_A32894->LightEnable(lightIndex++, TRUE);
                        if (lightIndex >= 8)
                            lightIndex = 7;
                    }
                }

                vsConstants_3[v9] = pLightStruct_1->extraFloats[10];
                vsConstants_4[v9++] = pLightStruct_1->extraFloats[11];
                v55 = v9;
                vsRegister += 2;
            }
            ++index;
        } while (index < lightSourceCount);
    }

    if (bUsePixelShaders_A33374)
    {
        if (v9 < 4)
        {
            v30 = 2 * v9 + 66;
            v31 = v9;

            do
            {
                pD3DDevice_A32894->SetVertexShaderConstant(v30, vsConstants_1, 1);
                vsConstants_3[v31] = 0.0;
                vsConstants_4[v31] = 0.0;
                ++v31;
                v30 += 2;
            } while (v31 < 4);

        }

        if (v48 < 4)
        {
            v32 = 3 * v48 + 78;
            v33 = v48;

            do
            {
                pD3DDevice_A32894->SetVertexShaderConstant(v32, vsConstants_1, 1);
                vsConstants_5[v33] = 0.0;
                vsConstants_6[v33] = 0.0;
                vsConstants_7[v33] = 0.0;
                vsConstants_8[v33] = 0.0;
                ++v33;
                v32 += 3;
            } while (v33 < 4);

        }

        if (v9)
        {
            pD3DDevice_A32894->SetVertexShaderConstant(63, vsConstants_3, 1);
            pD3DDevice_A32894->SetVertexShaderConstant(64, vsConstants_4, 1);
        }

        if (v48)
        {
            pD3DDevice_A32894->SetVertexShaderConstant(73, vsConstants_5, 1);
            pD3DDevice_A32894->SetVertexShaderConstant(74, vsConstants_6, 1);
            pD3DDevice_A32894->SetVertexShaderConstant(75, vsConstants_7, 1);
            pD3DDevice_A32894->SetVertexShaderConstant(76, vsConstants_8, 1);
        }
    }
    else
    {
        for (; lightIndex < 8; ++lightIndex)
            pD3DDevice_A32894->LightEnable(lightIndex, 0);
    }

    dword_A33584 = v48;
    dword_A33588 = v9;
    pD3DDevice_A32894->SetRenderState(D3DRS_FOGCOLOR, fogColor);
    v39 = float_942C30 - float_942C34;
    vsConstants_2[2] = 0.0;
    vsConstants_2[3] = 0.0;
    vsConstants_2[0] = (flt_942C38 * float_942C30 - flt_942C3C * float_942C34) / v39 * 0.00390625f;
    vsConstants_2[1] = (flt_942C3C - flt_942C38) * float_942C34 * float_942C30 / v39 * 0.00390625f;

    if (bUsePixelShaders_A33374)
    {
        pD3DDevice_A32894->SetVertexShaderConstant(46, vsConstants_2, 1);
    }
    else
    {
        pD3DDevice_A32894->SetRenderState(D3DRS_LIGHTING, TRUE);
        pD3DDevice_A32894->SetRenderState(D3DRS_COLORVERTEX, FALSE);
        projMatrixTranspose._21 = 1.0f;
        projMatrixTranspose._23 = 1.0f;
        projMatrixTranspose._22 = 1.0f;
        projMatrixTranspose._24 = 1.0f;
        projMatrixTranspose._12 = 1.0f;
        projMatrixTranspose._11 = 1.0f;
        projMatrixTranspose._13 = 1.0f;
        projMatrixTranspose._41 = 0.0f;
        projMatrixTranspose._14 = 1.0f;
        projMatrixTranspose._42 = 0.0f;
        projMatrixTranspose._44 = 1.0f;
        vsConstants[0] = 0.0f;
        projMatrixTranspose._31 = 0.0f;
        vsConstants[2] = 0.0f;
        projMatrixTranspose._33 = 0.0f;
        projMatrixTranspose._43 = 0.0f;
        vsConstants[3] = 1.0f;
        projMatrixTranspose._34 = 1.0f;
        vsConstants[1] = 0.0f;
        projMatrixTranspose._32 = 0.0f;
        v61 = 0;
        pD3DDevice_A32894->SetMaterial((D3DMATERIAL8*)&projMatrixTranspose);
        pD3DDevice_A32894->SetRenderState(D3DRS_FOGENABLE, TRUE);
        pD3DDevice_A32894->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
        fogColor = fogStart_1F5EE70;
        //lightSourceCount = maybeFogEnd_1F5EE74;
        pD3DDevice_A32894->SetRenderState(D3DRS_FOGSTART, fogStart_1F5EE70);
        //pD3DDevice_A32894->SetRenderState(D3DRS_FOGEND, lightSourceCount);
        pD3DDevice_A32894->SetRenderState(D3DRS_FOGEND, maybeFogEnd_1F5EE74);
    }

    if (dword_A33588)
    {
        if (dword_A33588 > 2)
        {

        LABEL_131:
            vsHandle = vsHandle_1F7D688;
            goto LABEL_132;
        }
    }
    else if (!dword_A33584)
    {
        vsHandle = dword_1F7D690;
    LABEL_132:
        goto LABEL_133;
    }

    if (dword_A33584 > 1)
        goto LABEL_131;

    if (!dword_1F7D718)
    {
        vsHandle = vsHandle_1F7D698;
        goto LABEL_132;
    }

    if (unkIndex_1F7D714 == 4)
    {
        vsHandle = vsHandle_1F7D6A8;
    LABEL_133:
        pD3DDevice_A32894->SetVertexShader(vsHandle);
        goto LABEL_134;
    }

    pD3DDevice_A32894->SetVertexShader(vsHandle_1F7D6A0);

    if (bUsePixelShaders_A33374)
    {
        psConstants[0] = flt_89FEEC[unkIndex_1F7D714];
        psConstants[1] = psConstants[0];
        psConstants[2] = flt_89FEEC[unkIndex_1F7D714];
        psConstants[3] = psConstants[2];
        pD3DDevice_A32894->SetVertexShaderConstant(1, psConstants, 1);
    }

LABEL_134:
    if (dword_1F7D718 && bUsePixelShaders_A33374)
        pD3DDevice_A32894->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
    else
        pD3DDevice_A32894->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
}
#pragma optimize("", on)

BOOL isCertainValues_50DE10(int value)
{
    if (value > 1065)
    {
        if (value > 1305)
        {
            switch (value)
            {
            case 1313:
            case 1321:
            case 1322:
            case 1336:
            case 1337:
            case 1339:
            case 1340:
            case 1341:
            case 1342:
            case 1343:
            case 1344:
            case 1345:
            case 1346:
            case 1347:
            case 1348:
            case 1349:
            case 1350:
            case 1351:
            case 1352:
            case 1353:
            case 1354:
            case 1355:
            case 1356:
            case 1357:
            case 1358:
            case 1359:
            case 1360:
            case 1361:
            case 1362:
            case 1363:
            case 1364:
            case 1365:
            case 1366:
                return TRUE;
            default:
                return FALSE;
            }
        }
        else
        {
            if (value == 1305)
                return TRUE;

            switch (value)
            {
            case 1068:
            case 1073:
            case 1082:
            case 1083:
            case 1084:
            case 1085:
            case 1280:
            case 1281:
            case 1282:
            case 1283:
            case 1284:
            case 1285:
            case 1286:
            case 1301:
                return FALSE;
            default:
                return FALSE;
            }
        }
    }
    else
    {
        if (value >= 1064)
            return TRUE;

        if (value <= 1042)
        {
            if (value != 1042)
            {
                if (value > 1034)
                {
                    if (value != 1036 && value != 1040)
                        return FALSE;
                }
                else if (value != 1034)
                {
                    switch (value)
                    {
                    case 768:
                    case 769:
                    case 770:
                    case 771:
                    case 772:
                    case 773:
                    case 774:
                    case 775:
                    case 776:
                    case 777:
                    case 778:
                    case 779:
                    case 780:
                    case 783:
                    case 784:
                    case 785:
                    case 786:
                    case 787:
                        return TRUE;
                    default:
                        return FALSE;
                    }
                    // return FALSE;
                }
            }
            return TRUE;
        }
        switch (value)
        {
        case 1044:
        case 1049:
        case 1056:
        case 1062:
            return TRUE;
        default:
            return FALSE;
        }
    }
    // return TRUE;
}

int getDword_AAA418Plus3Div4_50C480()
{
    return (dword_AAA418 + 3) / 4;
}

int getDword_AAA418_50C470()
{
    return dword_AAA418;
}

int getLightSourceCount_50C590()
{
    return lightSourceCount_AAA420;
}

LightSourceStruct* getLightSourceStruct_50C5A0(int index)
{
    if (index >= lightSourceCount_AAA420)
        return nullptr;
    else
        return lightSourceArray_AAA5A8[index];
}
