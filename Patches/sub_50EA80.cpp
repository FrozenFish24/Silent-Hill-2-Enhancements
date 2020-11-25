#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"
#include "Specular.h"

void __cdecl sub_50EA80(int* a1, ModelOffsetTable* pOffsetTable, D3DMATRIX** ppMatrix, D3DMATRIX* pMatrix)
{
	sub_50E060();

	if (dword_1F7FC64->word10 == 0x517)
		fogColor_1F7D634 = 0;
	else
		fogColor_1F7D634 = sub_50E530();

	sub_50DAF0(pOffsetTable, ppMatrix, pMatrix, a1[6]); // Does some kind of setup
	sub_50DA30(pOffsetTable);
	sub_50DC50(pOffsetTable);
	sub_50DCB0();
	sub_50DD00();

	if (pOffsetTable[1].materialsOffset)
		sub_507200(a1[168], ppMatrix[3]);

	sub_50FDD0(pOffsetTable, ppMatrix);

	if (pFuncPtrArrayArray_1F7A950)
	{
		auto funcPtrArray = pFuncPtrArrayArray_1F7A950[13];

		if (funcPtrArray)
		{
			auto funcPtr = funcPtrArray[3];

			if (funcPtr)
				funcPtr(a1, &float_1F7D510); // 0x59ECD0 at Forest gate
		}
	}

	sub_501F90(pOffsetTable, ppMatrix); // Draws opaque portions of actors
	sub_509F70();
	sub_504F90(pOffsetTable, ppMatrix); // Draw transparent portions of actors (e.g. hair)
}

void __cdecl sub_501F90(ModelOffsetTable* pOffsetTable, D3DMATRIX** ppMatrix)
{
	dword_A3358C ^= 1;
	dword_A3357C = &pOffsetTable->field_0;

	__asm mov ebx, pOffsetTable
	ORIG_sub_501F40(/*pOffsetTable,*/ ppMatrix);
}
