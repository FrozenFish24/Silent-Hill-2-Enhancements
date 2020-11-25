#include "Specular.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"

// TODO: This decltype(name) name stuff is extremely ugly

decltype(pD3DDevice_A32894) pD3DDevice_A32894 = *reinterpret_cast<IDirect3DDevice8**>(0xA32894);
decltype(dword_A33370) dword_A33370 = *reinterpret_cast<int*>(0xA33370);
decltype(bUsePixelShaders_A33374) bUsePixelShaders_A33374 = *reinterpret_cast<BOOL*>(0xA33374);
decltype(dword_A333C0) dword_A333C0 = *reinterpret_cast<int*>(0xA333C0);
decltype(vertexBufferArray_A33540) vertexBufferArray_A33540 = reinterpret_cast<IDirect3DVertexBuffer8**>(0xA33540);
decltype(byte_A33590) byte_A33590 = reinterpret_cast<char*>(0xA33590);

decltype(pMoreUnkModelData_1F7D4AC) pMoreUnkModelData_1F7D4AC = *reinterpret_cast<struct_1F7D4AC**>(0x1F7D4AC);

decltype(float_1F7D510) float_1F7D510 = *reinterpret_cast<float*>(0x1F7D510);
decltype(float_1F7D514) float_1F7D514 = *reinterpret_cast<float*>(0x1F7D514);
decltype(float_1F7D518) float_1F7D518 = *reinterpret_cast<float*>(0x1F7D518);
decltype(float_1F7D51C) float_1F7D51C = *reinterpret_cast<float*>(0x1F7D51C);
decltype(float_1F7D65C) float_1F7D65C = *reinterpret_cast<float*>(0x1F7D65C);
decltype(float_1F7D660) float_1F7D660 = *reinterpret_cast<float*>(0x1F7D660);
decltype(float_1F7D664) float_1F7D664 = *reinterpret_cast<float*>(0x1F7D664);
decltype(float_1F7D668) float_1F7D668 = *reinterpret_cast<float*>(0x1F7D668);
decltype(cubeMapTexture_1F7D710) cubeMapTexture_1F7D710 = *reinterpret_cast<IDirect3DBaseTexture8**>(0x1F7D710);
decltype(dword_1F7D718) dword_1F7D718 = *reinterpret_cast<int*>(0x1F7D718);

decltype(fogColor_1F7D634) fogColor_1F7D634 = *reinterpret_cast<DWORD*>(0x1F7D634);
decltype(dword_A3FD90) dword_A3FD90 = *reinterpret_cast<int*>(0xA3FD90);
decltype(bUseVertexShaders_A33370) bUseVertexShaders_A33370 = *reinterpret_cast<int*>(0xA33370);
decltype(vsConstant_1F7D500) vsConstant_1F7D500 = *reinterpret_cast<float*>(0x1F7D500);
decltype(projMatrix_1F7D570) projMatrix_1F7D570 = *reinterpret_cast<D3DMATRIX*>(0x1F7D570);
decltype(worldMatrix0_1F7D5F0) worldMatrix0_1F7D5F0 = *reinterpret_cast<D3DMATRIX*>(0x1F7D5F0);
decltype(viewMatrix_1F7D530) viewMatrix_1F7D530 = *reinterpret_cast<D3DMATRIX*>(0x1F7D530);
decltype(dword_1F7D720) dword_1F7D720 = *reinterpret_cast<int*>(0x1F7D720);
decltype(unkIndex_1F7D714) unkIndex_1F7D714 = *reinterpret_cast<int*>(0x1F7D714);
decltype(dword_A33584) dword_A33584 = *reinterpret_cast<int*>(0xA33584);
decltype(dword_A33588) dword_A33588 = *reinterpret_cast<int*>(0xA33588);
decltype(float_942C30) float_942C30 = *reinterpret_cast<float*>(0x942C30);
decltype(float_942C34) float_942C34 = *reinterpret_cast<float*>(0x942C34);
decltype(flt_942C38) flt_942C38 = *reinterpret_cast<float*>(0x942C38);
decltype(flt_942C3C) flt_942C3C = *reinterpret_cast<float*>(0x942C3C);
decltype(fogStart_1F5EE70) fogStart_1F5EE70 = *reinterpret_cast<DWORD*>(0x1F5EE70);
decltype(maybeFogEnd_1F5EE74) maybeFogEnd_1F5EE74 = *reinterpret_cast<float*>(0x1F5EE74);
decltype(vsHandle_1F7D688) vsHandle_1F7D688 = *reinterpret_cast<DWORD*>(0x1F7D688);
decltype(dword_1F7D690) dword_1F7D690 = *reinterpret_cast<int*>(0x1F7D690);
decltype(vsHandle_1F7D698) vsHandle_1F7D698 = *reinterpret_cast<int*>(0x1F7D698);
decltype(vsHandle_1F7D6A8) vsHandle_1F7D6A8 = *reinterpret_cast<int*>(0x1F7D6A8);
decltype(vsHandle_1F7D6A0) vsHandle_1F7D6A0 = *reinterpret_cast<DWORD*>(0x1F7D6A0);
decltype(copyof_dword_AAA418_A33580) copyof_dword_AAA418_A33580 = *reinterpret_cast<int*>(0xA33580);

decltype(flt_89FEEC) flt_89FEEC = reinterpret_cast<float*>(0x89FEEC);
decltype(pixelShaderHandleArr_1F7D6C4) pixelShaderHandleArr_1F7D6C4 = reinterpret_cast<int*>(0x1F7D6C4);

decltype(dword_A54218) dword_A54218 = *reinterpret_cast<int*>(0xA54218);
decltype(dword_A53DC8) dword_A53DC8 = reinterpret_cast<int*>(0xA53DC8);
decltype(copyof_dword_AAA418_A53DC0) copyof_dword_AAA418_A53DC0 = *reinterpret_cast<int*>(0xA53DC0);

decltype(float_1F7D63C) float_1F7D63C = *reinterpret_cast<float*>(0x1F7D63C);
decltype(float_1F7D640) float_1F7D640 = *reinterpret_cast<float*>(0x1F7D640);
decltype(float_1F7D644) float_1F7D644 = *reinterpret_cast<float*>(0x1F7D644);
decltype(float_1F7D648) float_1F7D648 = *reinterpret_cast<float*>(0x1F7D648);
decltype(float_1F7D64C) float_1F7D64C = *reinterpret_cast<float*>(0x1F7D64C);
decltype(float_1F7D650) float_1F7D650 = *reinterpret_cast<float*>(0x1F7D650);
decltype(float_1F7D654) float_1F7D654 = *reinterpret_cast<float*>(0x1F7D654);
decltype(float_1F7D658) float_1F7D658 = *reinterpret_cast<float*>(0x1F7D658);

decltype(dword_A541D0) dword_A541D0 = *reinterpret_cast<int*>(0xA541D0);
decltype(dword_A541DC) dword_A541DC = *reinterpret_cast<int*>(0xA541DC);

decltype(dword_1F7D68C) dword_1F7D68C = *reinterpret_cast<int*>(0x1F7D68C);
decltype(dword_1F7D694) dword_1F7D694 = *reinterpret_cast<int*>(0x1F7D694);
decltype(dword_1F7D69C) dword_1F7D69C = *reinterpret_cast<int*>(0x1F7D69C);
decltype(dword_1F7D6AC) dword_1F7D6AC = *reinterpret_cast<int*>(0x1F7D6AC);
decltype(dword_1F7D6A4) dword_1F7D6A4 = *reinterpret_cast<int*>(0x1F7D6A4);

decltype(zbiasArray_6BCE48) zbiasArray_6BCE48 = reinterpret_cast<int*>(0x6BCE48);
decltype(zbiasIndex_A333C4) zbiasIndex_A333C4 = *reinterpret_cast<int*>(0xA333C4);

decltype(dword_1F7FC64) dword_1F7FC64 = reinterpret_cast<struct_dword_1F7FC64*>(0x1F7FC64);

decltype(dword_A3358C) dword_A3358C = *reinterpret_cast<int*>(0xA3358C);
decltype(dword_A3357C) dword_A3357C = reinterpret_cast<int*>(0xA3357C);

decltype(dword_1F7FC60) dword_1F7FC60 = *reinterpret_cast<int*>(0x1F7FC60);

decltype(dword_AAA418) dword_AAA418 = *reinterpret_cast<int*>(0xAAA418);
decltype(lightSourceCount_AAA420) lightSourceCount_AAA420 = *reinterpret_cast<int*>(0xAAA420);
decltype(lightSourceArray_AAA5A8) lightSourceArray_AAA5A8 = reinterpret_cast<LightSourceStruct**>(0xAAA5A8);

decltype(pFuncPtrArrayArray_1F7A950) pFuncPtrArrayArray_1F7A950 = *reinterpret_cast<void(__cdecl****)(int*, float*)>(0x1F7A950);

decltype(sub_5014C0) sub_5014C0 = reinterpret_cast<void(__cdecl*)(/*unkU16Array1Offset, pModelMaterial*/)>(0x5014C0);
decltype(sub_50C500) sub_50C500 = reinterpret_cast<float(__cdecl*)()>(0x50C500);

// D3DMATRIX should really be D3DXMATRIX, but would require linking against d3dx8.libRIX should really be D3DXMATRIX, but would require linking against d3dx8.lib
decltype(D3DXMatrixRotationX_41A2C4) D3DXMatrixRotationX_41A2C4 = reinterpret_cast<D3DMATRIX * (__stdcall*)(D3DMATRIX * pOut, FLOAT Angle)>(0x41A2C4);
decltype(D3DXMatrixRotationY_41A360) D3DXMatrixRotationY_41A360 = reinterpret_cast<D3DMATRIX * (__stdcall*)(D3DMATRIX * pOut, FLOAT Angle)>(0x41A360);
decltype(D3DXMatrixMultiply_419781) D3DXMatrixMultiply_419781 = reinterpret_cast<D3DMATRIX * (__stdcall*)(D3DMATRIX * pOut, CONST D3DMATRIX * pM1, CONST D3DMATRIX * pM2)>(0x419781);
decltype(D3DXMatrixTranspose_4199CA) D3DXMatrixTranspose_4199CA = reinterpret_cast<D3DMATRIX * (__stdcall*)(D3DMATRIX * pOut, CONST D3DMATRIX * pM)>(0x4199CA);

decltype(copyMatrixFromAAA634_50C570) copyMatrixFromAAA634_50C570 = reinterpret_cast<void(__cdecl*)(D3DMATRIX * pM)>(0x50C570);
decltype(copyMatrixFromAAA4A8AtIndex_50C4C0) copyMatrixFromAAA4A8AtIndex_50C4C0 = reinterpret_cast<void(__cdecl*)(D3DMATRIX*, int)>(0x50C4C0);
decltype(copyMatrixFromAAA428AtIndex_50C4A0) copyMatrixFromAAA428AtIndex_50C4A0 = reinterpret_cast<void(__cdecl*)(D3DMATRIX*, int)>(0x50C4A0);
decltype(copyMatrixFromAAA528AtIndex_50C4E0) copyMatrixFromAAA528AtIndex_50C4E0 = reinterpret_cast<void(__cdecl*)(D3DMATRIX*, int)>(0x50C4E0);

decltype(sub_4FFDE0) sub_4FFDE0 = reinterpret_cast<void(__cdecl*)(/*int*/)>(0x4FFDE0);

decltype(sub_50E060) sub_50E060 = reinterpret_cast<void(__cdecl*)()>(0x50E060);
decltype(sub_50E530) sub_50E530 = reinterpret_cast<int(__cdecl*)()>(0x50E530);
decltype(sub_50DAF0) sub_50DAF0 = reinterpret_cast<void(__cdecl*)(ModelOffsetTable*, D3DMATRIX**, D3DMATRIX*, int)>(0x50DAF0);
decltype(sub_50DA30) sub_50DA30 = reinterpret_cast<void(__cdecl*)(ModelOffsetTable*)>(0x50DA30);
decltype(sub_50DC50) sub_50DC50 = reinterpret_cast<void(__cdecl*)(ModelOffsetTable*)>(0x50DC50);
decltype(sub_50DCB0) sub_50DCB0 = reinterpret_cast<void(__cdecl*)()>(0x50DCB0);
decltype(sub_50DD00) sub_50DD00 = reinterpret_cast<void(__cdecl*)()>(0x50DD00);
decltype(sub_507200) sub_507200 = reinterpret_cast<void(__cdecl*)(int, D3DMATRIX*)>(0x507200);
decltype(sub_50FDD0) sub_50FDD0 = reinterpret_cast<void(__cdecl*)(ModelOffsetTable*, D3DMATRIX**)>(0x50FDD0);
decltype(sub_509F70) sub_509F70 = reinterpret_cast<void(__cdecl*)()>(0x509F70);
decltype(sub_504F90) sub_504F90 = reinterpret_cast<void(__cdecl*)(ModelOffsetTable*, D3DMATRIX**)>(0x504F90);

decltype(sub_4FE750) sub_4FE750 = reinterpret_cast<void(__cdecl*)(/*float*, D3DMATRIX**/)>(0x4FE750);

// ORIGINALSALS
decltype(ORIG_isCertainValues_50DE10) ORIG_isCertainValues_50DE10 = reinterpret_cast<BOOL(__cdecl*)(int)>(0x50DE10);
decltype(ORIG_getDword_AAA418Plus3Div4_50C480) ORIG_getDword_AAA418Plus3Div4_50C480 = reinterpret_cast<int(__cdecl*)()>(0x50C480);
decltype(ORIG_getDword_AAA418_50C470) ORIG_getDword_AAA418_50C470 = reinterpret_cast<int(__cdecl*)()>(0x50C470);
decltype(ORIG_getFogEnd_50C590) ORIG_getFogEnd_50C590 = reinterpret_cast<int(__cdecl*)()>(0x50C590);
decltype(ORIG_getLightSourceStruct_50C5A0) ORIG_getLightSourceStruct_50C5A0 = reinterpret_cast<LightSourceStruct* (__cdecl*)(int)>(0x50C5A0);
decltype(ORIG_getModelId_50B6C0) ORIG_getModelId_50B6C0 = reinterpret_cast<int(__cdecl*)()>(0x50B6C0);
decltype(ORIG_poseExists_50E080) ORIG_poseExists_50E080 = reinterpret_cast<BOOL(__cdecl*)(D3DMATRIX**, int)>(0x50E080);
decltype(ORIG_sub_501F90) ORIG_sub_501F90 = reinterpret_cast<void(__cdecl*)(ModelOffsetTable*, D3DMATRIX**)>(0x501F90);

decltype(ORIG_setupActorDrawTransparent_502220) ORIG_setupActorDrawTransparent_502220 = reinterpret_cast<void(__cdecl*)()>(0x502220);
decltype(ORIG_setupActorDrawOpaque_4FE850) ORIG_setupActorDrawOpaque_4FE850 = reinterpret_cast<void(__cdecl*)()>(0x4FE850);
decltype(ORIG_actorDrawOpaque_501540) ORIG_actorDrawOpaque_501540 = reinterpret_cast<void(__cdecl*)(ModelMaterial*)>(0x501540);
decltype(ORIG_sub_501F40) ORIG_sub_501F40 = reinterpret_cast<void(__cdecl*)(/*ModelOffsetTable*,*/ D3DMATRIX**)>(0x501F40);
