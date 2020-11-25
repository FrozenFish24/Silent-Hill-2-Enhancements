#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"

/*
* Unique Id signifying the model we're configuring/drawing
*/
enum MODELID
{
	MODELID_JAMES_HOSPITAL = 257,
	MODELID_MARIA_HOSPITAL = 262,
	MODELID_MARIA_BOFW = 270,
	MODELID_MARIA_REVOLVER = 2057,
};

struct struct_dword_1F7FC64
{
	BYTE gap0[16];
	WORD word10;
};
static_assert(sizeof(struct_dword_1F7FC64) == 18, "struct_dword_1F7FC64 is not 18 bytes large");

/*
* Found 0x40 bytes in to every mdl file
* Points to parts of the model, e.g. bones, materials
*/
struct ModelOffsetTable
{
	int field_0;
	int field_4;
	int skeleton_points_offset;
	int skeleton_point_count;
	int skeleton_index_buffer_part_1_offset;
	int field_14;
	int skeleton_index_buffer_part_2_offset;
	int field_1C;
	int materialCount;
	unsigned int materialsOffset;
	int field_2C;
	unsigned int offset_30;
	int field_34;
	unsigned int offset_38;
	int field_3C;
	unsigned int offset_40;
	int field_44;
	int field_48;
	int field_4C;
	int field_50;
};
static_assert(sizeof(ModelOffsetTable) == 80, "ModelOffsetTable is not 80 bytes large");

struct struct_dword38_dword0
{
	int field_0;
};

struct struct_dword38
{
	struct_dword38_dword0* pIndexData;
};

struct ModelSamplerStates
{
	BYTE addressu;
	BYTE addressv;
	BYTE magfilter;
	BYTE minfilter;
};
static_assert(sizeof(ModelSamplerStates) == 4, "ModelSamplerStates is not 4 bytes large");

struct ModelMaterial
{
	DWORD materialLength;
	DWORD reserved0;
	DWORD unkU16Count0;
	DWORD unkU16Array0Offset;
	DWORD unkU16Count1;
	DWORD unkU16Array1Offset;
	DWORD unkU16Count2;
	DWORD unkU16Array2Offset;
	DWORD samplerStatesOffset;
	BYTE materialType;
	BYTE unkMaterialSubtype;
	BYTE poseId;
	BYTE unkByte0x27;
	DWORD cullMode;
	float unkDiffuseFloat;
	float unkAmbientFloat;
	float specularHighlightScale;
	struct_dword38* reserved1;
	DWORD reserved2;
	float diffuseX;
	float diffuseR;
	float diffuseG;
	float diffuseB;
	float ambientX;
	float ambientR;
	float ambientG;
	float ambientB;
	float specularX;
	float specularR;
	float specularG;
	float specularB;
	DWORD reserved3;
	DWORD unkIndex;
	DWORD unkCount;
	DWORD reserved4;
};
static_assert(sizeof(ModelMaterial) == 128, "ModelMaterial is not 128 bytes large");

struct struct_pUnkStruct_1
{
	DWORD pIndexData;
	BYTE gap0[28];
	float d3dvalue20;
	float float24;
	float float28;
	float float2C;
	float float30;
	float float34;
	float float38;
	float float3C;
	float float40;
	float d3dvalue44;
	float float48;
	BYTE gap4C[4];
	float float50;
	float float54;
	float float58;
	float float5C;
	float float60;
	float float64;
	float float68;
	float float6C;
	float float70;
	float float74;
	BYTE gap78[16];
	float float88;
	float float8C;
	float float90;
	float float94;
};
static_assert(sizeof(struct_pUnkStruct_1) == 152, "struct_pUnkStruct_1 is not 152 bytes large");

struct struct_1F7D4AC
{
	D3DMATRIX matrices[897];
	BYTE gap0[96];
	void* textureBase;
	BYTE gap1[251];
	IDirect3DBaseTexture8* specularTexture;
};
static_assert(sizeof(struct_1F7D4AC) == 57764, "struct_1F7D4AC is not 57764 bytes large");

struct LightSourceStruct
{
	D3DLIGHT8 light;
	float extraFloats[12];
};
static_assert(sizeof(LightSourceStruct) == 152, "LightSourceStruct is not 152 bytes large");

extern IDirect3DDevice8*& pD3DDevice_A32894;
extern int& dword_A33370;
extern BOOL& bUsePixelShaders_A33374;
extern int& dword_A333C0;
extern IDirect3DVertexBuffer8** vertexBufferArray_A33540;
extern char* byte_A33590;

extern struct_1F7D4AC*& pMoreUnkModelData_1F7D4AC;

extern float& float_1F7D510;
extern float& float_1F7D514;
extern float& float_1F7D518;
extern float& float_1F7D51C;
extern float& float_1F7D65C;
extern float& float_1F7D660;
extern float& float_1F7D664;
extern float& float_1F7D668;
extern IDirect3DBaseTexture8*& cubeMapTexture_1F7D710;
extern int& dword_1F7D718;

extern DWORD& fogColor_1F7D634;
extern int& dword_A3FD90;
extern int& bUseVertexShaders_A33370;
extern float& vsConstant_1F7D500;
extern D3DMATRIX& projMatrix_1F7D570;
extern D3DMATRIX& worldMatrix0_1F7D5F0;
extern D3DMATRIX& viewMatrix_1F7D530;
extern int& dword_1F7D720;
extern int& unkIndex_1F7D714;
extern int& dword_A33584;
extern int& dword_A33588;
extern float& float_942C30;
extern float& float_942C34;
extern float& flt_942C38;
extern float& flt_942C3C;
extern DWORD& fogStart_1F5EE70;
extern float& maybeFogEnd_1F5EE74;
extern DWORD& vsHandle_1F7D688;
extern int& dword_1F7D690;
extern int& vsHandle_1F7D698;
extern int& vsHandle_1F7D6A8;
extern DWORD& vsHandle_1F7D6A0;
extern int& copyof_dword_AAA418_A33580;

extern float* flt_89FEEC;
extern int* pixelShaderHandleArr_1F7D6C4;

extern int& dword_A54218;
extern int* dword_A53DC8;
extern int& copyof_dword_AAA418_A53DC0;

extern float& float_1F7D63C;
extern float& float_1F7D640;
extern float& float_1F7D644;
extern float& float_1F7D648;
extern float& float_1F7D64C;
extern float& float_1F7D650;
extern float& float_1F7D654;
extern float& float_1F7D658;

extern int& dword_A541D0;
extern int& dword_A541DC;

extern int& dword_1F7D68C;
extern int& dword_1F7D694;
extern int& dword_1F7D69C;
extern int& dword_1F7D6AC;
extern int& dword_1F7D6A4;

extern int* zbiasArray_6BCE48;
extern int& zbiasIndex_A333C4;

extern struct_dword_1F7FC64* dword_1F7FC64;

extern int& dword_A3358C;
extern int* dword_A3357C;

extern int& dword_1F7FC60;

extern int& dword_AAA418;
extern int& lightSourceCount_AAA420;
extern LightSourceStruct** lightSourceArray_AAA5A8;

extern void (__cdecl***&pFuncPtrArrayArray_1F7A950)(int*, float*);

// FUNCTIONS
BOOL isCertainValues_50DE10(int value);
int getDword_AAA418Plus3Div4_50C480();
int getDword_AAA418_50C470();
int getLightSourceCount_50C590();
LightSourceStruct* getLightSourceStruct_50C5A0(int index);
int getModelId_50B6C0();
BOOL poseExists_50E080(D3DMATRIX** ppMatrix, int poseId);
void sub_501F90(ModelOffsetTable* pOffsetTable, D3DMATRIX** ppMatrix);

void setupActorDrawTransparent_502220();
void setupActorDrawOpaque_4FE850();
void actorDrawOpaque_501540(ModelMaterial* pModelMaterial);
void sub_501F40(/*ModelOffsetTable* pOffsetTable@<ebx>,*/ D3DMATRIX** ppMatrix);
void sub_50EA80(int* a1, ModelOffsetTable* pOffsetTable, D3DMATRIX** ppMatrix, D3DMATRIX* pMatrix);
void sub_501F90(ModelOffsetTable* pOffsetTable, D3DMATRIX** ppMatrix);

extern void (__cdecl* sub_5014C0)(/*unkU16Array1Offset, pModelMaterial*/);
extern float (__cdecl* sub_50C500)();

// D3DMATRIX should really be D3DXMATRIX, but would require linking against d3dx8.lib
extern D3DMATRIX* (__stdcall* D3DXMatrixRotationX_41A2C4)(D3DMATRIX* pOut, FLOAT Angle);
extern D3DMATRIX* (__stdcall* D3DXMatrixRotationY_41A360)(D3DMATRIX* pOut, FLOAT Angle);
extern D3DMATRIX* (__stdcall* D3DXMatrixMultiply_419781)(D3DMATRIX* pOut, CONST D3DMATRIX* pM1, CONST D3DMATRIX* pM2);
extern D3DMATRIX* (__stdcall* D3DXMatrixTranspose_4199CA)(D3DMATRIX* pOut, CONST D3DMATRIX* pM);

extern void (__cdecl* copyMatrixFromAAA634_50C570)(D3DMATRIX* pM);
extern void (__cdecl* copyMatrixFromAAA4A8AtIndex_50C4C0)(D3DMATRIX*, int);
extern void (__cdecl* copyMatrixFromAAA428AtIndex_50C4A0)(D3DMATRIX*, int);
extern void (__cdecl* copyMatrixFromAAA528AtIndex_50C4E0)(D3DMATRIX*, int);

extern void (__cdecl* sub_4FFDE0)(/*int*/);

extern void (__cdecl* sub_50E060)();
extern int (__cdecl* sub_50E530)();
extern void (__cdecl* sub_50DAF0)(ModelOffsetTable*, D3DMATRIX**, D3DMATRIX*, int);
extern void (__cdecl* sub_50DA30)(ModelOffsetTable*);
extern void (__cdecl* sub_50DC50)(ModelOffsetTable*);
extern void (__cdecl* sub_50DCB0)();
extern void (__cdecl* sub_50DD00)();
extern void (__cdecl* sub_507200)(int, D3DMATRIX*);
extern void (__cdecl* sub_50FDD0)(ModelOffsetTable*, D3DMATRIX**);
extern void (__cdecl* sub_509F70)();
extern void (__cdecl* sub_504F90)(ModelOffsetTable*, D3DMATRIX**);

extern void (__cdecl* sub_4FE750)(/*float*, D3DMATRIX**/);

// ORIGINAL FUNCTIONS
extern BOOL (__cdecl* ORIG_isCertainValues_50DE10)(int);
extern int (__cdecl* ORIG_getDword_AAA418Plus3Div4_50C480)();
extern int (__cdecl* ORIG_getDword_AAA418_50C470)();
extern int (__cdecl* ORIG_getFogEnd_50C590)();
extern LightSourceStruct* (__cdecl* ORIG_getLightSourceStruct_50C5A0)(int);
extern int (__cdecl* ORIG_getModelId_50B6C0)();
extern BOOL (__cdecl* ORIG_poseExists_50E080)(D3DMATRIX**, int);
extern void (__cdecl* ORIG_sub_501F90)(ModelOffsetTable*, D3DMATRIX**);
extern void (__cdecl* ORIG_setupActorDrawTransparent_502220)();
extern void (__cdecl* ORIG_setupActorDrawOpaque_4FE850)();
extern void (__cdecl* ORIG_actorDrawOpaque_501540)(ModelMaterial*);
extern void (__cdecl* ORIG_sub_501F40)(/*ModelOffsetTable*,*/ D3DMATRIX**);
