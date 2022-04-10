#include "PX_Object_Dragon.h"
#include "PainterEngine_Application.h"


px_void PX_Object_DragonUpdate(PX_Object* pObject,px_dword elpased)
{
	
	PX_Object_Dragon *pDesc=PX_ObjectGetDesc(PX_Object_Dragon, pObject);
	
	pDesc->time += elpased;
	
	if (pDesc->AnimationElpased < 100 && pDesc->animationEffect == DRAGON_FLY_TO_SKY)
	{
		if (pObject->y <= pDesc->pWorld->world_height / 8)
		{
			pObject->y = pDesc->pWorld->world_height / 8;
		}
		else
		{
			pObject->y -= pDesc->pWorld->world_height / 8 * 5 / 100 * elpased;
		}
	}
	
	if (pDesc->AnimationElpased >= 180)
	{
		pDesc->animationEffect = DRAGON_LAND_TO_GROUND;
	}

	if (pDesc->animationEffect == DRAGON_LAND_TO_GROUND)
	{
		if (pObject->y >= pDesc->pWorld->world_height / 4 * 3 - pDesc->pWorld->world_height / 8 * 5 / 50 * elpased)
		{
			pObject->y = pDesc->pWorld->world_height / 4 * 3;
		}
		else
		{
			pObject->y += pDesc->pWorld->world_height / 8 * 5 / 50 * elpased;
		}
	}

	if (pDesc->AnimationElpased >= 230 && pDesc->status != DRAGON_BOTTOM_WALK)
	{
		pDesc->status = DRAGON_BOTTOM_WALK;
		pDesc->animationEffect = DRAGON_EFFECT_NULL;
		pObject->y = pDesc->pWorld->world_height / 4 * 3;
		PX_AnimationSetCurrentPlayAnimationByName(&animationDragon, "walk");
	}
	
	
}

px_void PX_Object_DragonRender(px_surface* psurface, PX_Object* pObject, px_dword elpased)
{



	PX_Object_Dragon* pDesc = PX_ObjectGetDesc(PX_Object_Dragon, pObject);
	pDesc->AnimationElpased += elpased;
	
	if (pDesc->status == DRAGON_BOTTOM_WALK)
	{
		PX_AnimationRender(psurface, &animationDragon, pDesc->pWorld->world_width / 8, pDesc->pWorld->world_height / 4 * 3 + 15 * PX_sin_radian(((px_float)pDesc->time / 100)), PX_ALIGN_CENTER, PX_NULL);
	}

	if (pDesc->status == DRAGON_BOTTOM_STRIKE)
	{
		PX_AnimationRender(psurface, &animationDragon, pDesc->pWorld->world_width / 6, pDesc->pWorld->world_height / 8 * 5, PX_ALIGN_CENTER, PX_NULL);
	}

	if (pDesc->status == DRAGON_TOP_FLYKICK)
	{
		PX_AnimationRender(psurface, &animationDragon, pDesc->pWorld->world_width / 6, pObject->y , PX_ALIGN_CENTER, PX_NULL);
	}
	
}

px_void PX_Object_DragonOnKeyDown(PX_Object* pObject, PX_Object_Event e, px_void* ptr)
{
	px_uint kd= PX_Object_Event_GetKeyDown(e);
	PX_Object_Dragon* pDesc = PX_ObjectGetDesc(PX_Object_Dragon,pObject);
}

px_void PX_Object_DragonOnCursorDown(PX_Object* pObject, PX_Object_Event e, px_void* ptr)
{
	PX_Object_Dragon* pDesc = PX_ObjectGetDesc(PX_Object_Dragon, pObject);

	pDesc->status = DRAGON_TOP_FLYKICK;
	pDesc->AnimationElpased = 0;
	pDesc->animationEffect = DRAGON_FLY_TO_SKY;
	PX_AnimationSetCurrentPlayAnimationByName(&animationDragon, "flyKick");
	/*
	px_dword hour, min, sec, msec;
	hour = pDesc->time / 3600000;
	min = (pDesc->time - hour * 3600000) / 60000;
	sec = (pDesc->time - hour * 3600000 - min * 60000) / 1000;
	msec = pDesc->time - hour * 3600000 - min * 60000 - sec * 1000;
	printf("{\"keytype\":0,\"keytime\":[%d,%d,%d,%d]},\n", hour, min, sec, msec);
	*/
	PX_WorldPostEvent(pDesc->pWorld, PX_OBJECT_BUILD_EVENT(PX_OBJECT_DRAGON_JUDGE));
}

px_void PX_Object_DragonOnCursorRDown(PX_Object* pObject, PX_Object_Event e, px_void* ptr)
{
	PX_Object_Dragon* pDesc = PX_ObjectGetDesc(PX_Object_Dragon, pObject);

	pDesc->status = DRAGON_BOTTOM_STRIKE;
	pDesc->AnimationElpased = 0;
	PX_AnimationSetCurrentPlayAnimationByName(&animationDragon, "strike");
	/*
	px_dword hour, min, sec, msec;
	hour = pDesc->time / 3600000;
	min = (pDesc->time - hour * 3600000) / 60000;
	sec = (pDesc->time - hour * 3600000 - min * 60000) / 1000;
	msec = pDesc->time - hour * 3600000 - min * 60000 - sec * 1000;
	printf("{\"keytype\":1,\"keytime\":[%d,%d,%d,%d]},\n", hour, min, sec, msec);
	*/
	PX_WorldPostEvent(pDesc->pWorld, PX_OBJECT_BUILD_EVENT(PX_OBJECT_DRAGON_JUDGE));
}

PX_Object* PX_Object_DragonCreate(PX_World *pworld, PX_Runtime* runtime)
{
	PX_Object_Dragon dragon;
	PX_Object* pObject;
	PX_memset(&dragon, 0, sizeof(dragon));
	dragon.status = DRAGON_BOTTOM_WALK;
	dragon.animationEffect = DRAGON_EFFECT_NULL;
	dragon.AnimationElpased = 0;
	dragon.pWorld = pworld;
	dragon.velocity = 0;
	dragon.time = 0;
	dragon.runtime = runtime;
	pObject=PX_ObjectCreateEx(pworld->mp, PX_NULL, pworld->world_width / 8, pworld->world_height / 4 * 3, 0, 0, 0, 0, 0, PX_Object_DragonUpdate, PX_Object_DragonRender, PX_NULL, &dragon, sizeof(dragon));
	pObject->diameter = 100;
	pObject->impact_object_type = 1;
	pObject->impact_target_type = 2;

	PX_ObjectRegisterEvent(pObject, PX_OBJECT_EVENT_KEYDOWN, PX_Object_DragonOnKeyDown,PX_NULL);
	PX_ObjectRegisterEvent(pObject, PX_OBJECT_EVENT_CURSORDOWN, PX_Object_DragonOnCursorDown, PX_NULL);
	PX_ObjectRegisterEvent(pObject, PX_OBJECT_EVENT_CURSORRDOWN, PX_Object_DragonOnCursorRDown, PX_NULL);

	return pObject;
}


