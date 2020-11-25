#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"
#include "Specular.h"

#pragma optimize("", off)
void __cdecl sub_501F40(/*ModelOffsetTable* pOffsetTable@<ebx>,*/ D3DMATRIX** ppMatrix)
{
	ModelOffsetTable* pOffsetTable;
	__asm mov pOffsetTable, ebx

	int materialCount;
	int modelId;
	ModelMaterial* pModelMaterial;

	materialCount = pOffsetTable->materialCount;
	ORIG_setupActorDrawOpaque_4FE850();
	modelId = getModelId_50B6C0();

	__asm mov edi, modelId
	sub_4FFDE0(/*modelId*/);

	pModelMaterial = (ModelMaterial*)((char*)pOffsetTable + pOffsetTable->materialsOffset);

	for (; materialCount > 0; --materialCount)
	{
		if (poseExists_50E080(ppMatrix, pModelMaterial->poseId))
			ORIG_actorDrawOpaque_501540(pModelMaterial);

		pModelMaterial = (ModelMaterial*)((char*)pModelMaterial + pModelMaterial->materialLength);
	}

	pD3DDevice_A32894->SetPixelShader(NULL);
	pD3DDevice_A32894->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	pD3DDevice_A32894->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	pD3DDevice_A32894->SetRenderState(D3DRS_LIGHTING, TRUE);
	pD3DDevice_A32894->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_ZERO);
	pD3DDevice_A32894->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pD3DDevice_A32894->SetRenderState(D3DRS_STENCILREF, 1);
	pD3DDevice_A32894->SetTextureStageState(0, D3DTSS_RESULTARG, D3DTA_CURRENT);
	pD3DDevice_A32894->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pD3DDevice_A32894->SetRenderState(D3DRS_STENCILWRITEMASK, 0);
	pD3DDevice_A32894->SetRenderState(D3DRS_FOGENABLE, FALSE);
	pD3DDevice_A32894->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	pD3DDevice_A32894->SetRenderState(D3DRS_ZBIAS, zbiasArray_6BCE48[zbiasIndex_A333C4 * 4]);
}
#pragma optimize("", on)

int getModelId_50B6C0()
{
	return dword_1F7FC60;
}

#pragma optimize("", off)
BOOL poseExists_50E080(D3DMATRIX** ppMatrix, int poseId)
{
	//return ((unsigned int)ppMatrix[poseId / 32 + 4] & (1 << poseId % 32)) != 0;

	int index = poseId / 32 + 4;

	unsigned int partA = (unsigned int)ppMatrix[index];
	unsigned int partB = 1 << poseId % 32;

	if (partA & partB)
		return TRUE;

	return FALSE;
}
#pragma optimize("", on)
