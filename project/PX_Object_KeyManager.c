#include "PX_Object_KeyManager.h"
#include "Game_Text.h"


px_void PX_Object_KeyManagerUpdate(PX_Object* pObject, px_dword elpased)
{
	PX_Object_KeyManager* pdesc = PX_ObjectGetDesc(PX_Object_KeyManager, pObject);
    pdesc->time += elpased;
}

px_void PX_Object_KeyManagerRender(px_surface* psurface, PX_Object* pObject, px_dword elpased)
{
	PX_Object_KeyManager* pdesc = PX_ObjectGetDesc(PX_Object_KeyManager, pObject);
}


PX_Object *PX_Object_KeyManagerCreate(PX_World* pWorld, PX_Runtime* pruntime)
{
    PX_Object_KeyManager desc;
    PX_Object *pObject;
    PX_memset(&desc, 0, sizeof(desc));

    desc.pWorld = pWorld;
	desc.pruntime = pruntime;
    desc.time = 0;

    if (!PX_LoadJsonFromFile(&desc.json, GAME_MAP_PATH_LOAD))
	return PX_FALSE;

    pObject = PX_ObjectCreateEx(&pruntime->mp_resources, PX_NULL, \
		0, 0, 0, 0, 0, 0, 0, \
        PX_Object_KeyManagerUpdate, \
		PX_Object_KeyManagerRender, \
		PX_NULL, \
		& desc, \
		sizeof(desc)\
	);




}