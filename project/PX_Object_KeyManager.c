#include "PX_Object_KeyManager.h"
#include "PainterEngine_Application.h"
#include "Game_Text.h"


px_void PX_Object_KeyManagerUpdate(PX_Object* pObject, px_dword elpased)
{
	PX_Object_KeyManager* pdesc = PX_ObjectGetDesc(PX_Object_KeyManager, pObject);
    pdesc->time += elpased;
    PX_Json_Value *bean;
    px_int keytime = 0;
    px_int keytype = 0;

    if (pdesc->nodecount < keynum) {

        bean = PX_JsonGetArrayValue(keymap, pdesc->nodecount);
        keytype = (px_int)PX_JsonValueGetNumber(bean, "keytype");

        for (px_int i = 0; i < 4; i++) {
            px_char *time = (px_char *)MP_Malloc(&pdesc->pruntime->mp_resources, 11 * sizeof(px_char));
            px_stringformat format;
            format = PX_STRINGFORMAT_INT(i);
            PX_sprintf1(time, sizeof("keytime[0]"), "keytime[%1]", format);
        
            switch (i)
            {
            case 0:
                keytime += (px_dword)PX_JsonValueGetNumber(bean, time) * 3600000;
                break;
            case 1:
                keytime += (px_dword)PX_JsonValueGetNumber(bean, time) * 60000;
                break;
            case 2:
                keytime += (px_dword)PX_JsonValueGetNumber(bean, time) * 1000;
                break;
            case 3:
                keytime += (px_dword)PX_JsonValueGetNumber(bean, time);
                break;
            default:
                break;
            }
        
        }
    
        if (keytime - GAME_KEY_PRETIME <= (px_int)pdesc->time) {
            
            switch (keytype)
            {
            case 0:
                PX_WorldAddObject(pdesc->pWorld, PX_Object_BeanCreate(pdesc->pWorld, pdesc->pruntime->surface_width, pdesc->pruntime->surface_height / 8 + 65, 1, pdesc->pruntime));
                //printf("%d", (px_int)pdesc->time);
                break;
            case 1:
                PX_WorldAddObject(pdesc->pWorld, PX_Object_BeanCreate(pdesc->pWorld, pdesc->pruntime->surface_width, pdesc->pruntime->surface_height / 8 * 5 + 65, 2, pdesc->pruntime));
                //printf("%d", (px_int)pdesc->time);
                break;
            default:
                break;
            }
            
            pdesc->nodecount++;
        }
    }
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
    desc.nodecount = 0;

    PX_ListInitialize(&pruntime->mp_game, &desc.keylist);
    PX_JsonInitialize(&pruntime->mp_resources, &desc.json);
    if (!PX_LoadJsonFromFile(&desc.json, GAME_MAP_PATH_LOAD))
	return PX_FALSE;

    keynum = (px_int)PX_JsonGetNumber(&desc.json, "keynum");
    keymap = PX_JsonGetValue(&desc.json, "keymap");
    /*
    PX_Json_Value *test;
    test = PX_JsonGetArrayValue(keymap, desc.nodecount);
    printf(PX_JsonValueGetString(test, "keytype"));
    */

    pObject = PX_ObjectCreateEx(&pruntime->mp_resources, PX_NULL, \
		0, 0, 0, 0, 0, 0, 0, \
        PX_Object_KeyManagerUpdate, \
		PX_Object_KeyManagerRender, \
		PX_NULL, \
		&desc, \
		sizeof(desc)\
	);
    return pObject;
}