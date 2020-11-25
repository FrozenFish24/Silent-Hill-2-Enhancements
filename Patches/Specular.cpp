#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Patches.h"
#include "Common\Utils.h"
#include "Wrappers\d3d8\DirectX81SDK\include\d3d8.h"
#include "Specular.h"

void PatchSpecular()
{
    WriteCalltoMemory((BYTE*)0x501F46, setupActorDrawOpaque_4FE850, 5); // Issues with certain transparencies e.g. Maria's hair in 3F Hospital turns black
    //WriteCalltoMemory((BYTE*)0x501F77, actorDrawOpaque_501540, 5);        // No known issues

    //WriteCalltoMemory((BYTE*)0x504E8E, setupActorDrawTransparent_502220, 5);
    //WriteCalltoMemory((BYTE*)0x501FAF, sub_501F40, 5);
    //WriteCalltoMemory((BYTE*)0x50B471, sub_50EA80, 5);

    //WriteCalltoMemory((BYTE*)0x50EB2B, sub_501F90, 5);
}
