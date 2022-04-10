#include "PX_Object_Bean.h"
#include "PainterEngine_Application.h"
#include "PX_Object_Dragon.h"
#include "PX_Object_Particallauncher.h"
#include "PX_Object_Evaluation.h"
#include "Game_Text.h"

px_void PX_Object_BeanUpdate(PX_Object* pObject, px_dword elpased)
{
	PX_Object_Bean *pBean=PX_ObjectGetDesc(PX_Object_Bean,pObject);
	PX_Object_Dragon* pDragon = PX_ObjectGetDesc(PX_Object_Dragon, dragon);

	//pObject->x -= elpased / 2.0f;
	pObject->x -= ((px_float)pBean->pruntime->surface_width / 6 * 5 - 85) * elpased / GAME_KEY_PRETIME;
	
	if (pBean->state==PX_OBJECT_BEAN_STATE_DEAD || pObject->x < 0 - pObject->diameter / 2)
	{
		pObject->diameter-=elpased * 2.f;
		if (pObject->diameter<=0)
		{
			PX_WorldRemoveObject(pBean->pWorld,pObject);
		}
	}

	if (pObject->x <= pBean->pWorld->world_width / 6 && pBean->hasmissed == PX_OBJECT_BEAN_MISSING)
	{
		PX_WorldAddObject(pBean->pWorld, PX_Object_EvaluationCreate(pBean->pWorld, pBean->pruntime, PX_POINT((px_float)pBean->pruntime->surface_height / 6 + 125, pObject->y - 40, pObject->z), 3));
		pBean->hasmissed = PX_OBJECT_BEAN_MISSED;
	}	
	
}

px_void PX_Object_BeanRender(px_surface *psurface,PX_Object* pObject, px_dword elpased)
{
	PX_Object_Bean *pBean=PX_ObjectGetDesc(PX_Object_Bean,pObject);
	switch (pBean->position)
	{
	case PX_OBJECT_FIREBALL_POSITION_TOP:
		pObject->y = (px_float)psurface->height / 8 + 65;
		break;
	case PX_OBJECT_FIREBALL_POSITION_BOTTOM:
		pObject->y = (px_float)psurface->height / 8 * 5 + 65;
		break;
	default:
		break;
	}
	PX_GeoDrawSolidCircle(psurface,(px_int)pObject->x,(px_int)pObject->y,(px_int)pObject->diameter/2,PX_COLOR(255,255,255,255));
}

px_void PX_Object_Judge(PX_Object *pObject,PX_Object_Event e,px_void *ptr)
{
	PX_Object_Bean *pBean=PX_ObjectGetDesc(PX_Object_Bean,pObject);
	PX_Object_Dragon* pDragon = PX_ObjectGetDesc(PX_Object_Dragon, dragon);

	if (pObject->x < pBean->pWorld->world_width / 6 + 120 && pObject->x > pBean->pWorld->world_width / 6 + 60)
	{
		switch (pDragon->status)
		{
		case DRAGON_FLY_TO_SKY:
			if (pBean->position == PX_OBJECT_FIREBALL_POSITION_BOTTOM)
			{
				//PX_SoundPlayAdd(&pBean->pruntime->soundplay, PX_SoundCreate(&soundeffect, PX_FALSE));
				pBean->state = PX_OBJECT_BEAN_STATE_DEAD;
				pObject->impact_object_type = 0;
				PX_WorldAddObject(pBean->pWorld, PX_Object_ParticallauncherCreate(pBean->pWorld, pBean->pruntime, PX_POINT(pObject->x, pObject->y, pObject->z)));
				PX_WorldAddObject(pBean->pWorld, PX_Object_EvaluationCreate(pBean->pWorld, pBean->pruntime, PX_POINT((px_float)pBean->pruntime->surface_height / 6 + 125, (px_float)pBean->pruntime->surface_height / 8 * 5 + 25, pObject->z), 1));
			}
			break;
		case DRAGON_LAND_TO_GROUND:
		case DRAGON_EFFECT_NULL:
			if (pBean->position == PX_OBJECT_FIREBALL_POSITION_TOP)
			{
				//PX_SoundPlayAdd(&pBean->pruntime->soundplay, PX_SoundCreate(&soundeffect, PX_FALSE));
				pBean->state = PX_OBJECT_BEAN_STATE_DEAD;
				pObject->impact_object_type = 0;
				PX_WorldAddObject(pBean->pWorld, PX_Object_ParticallauncherCreate(pBean->pWorld, pBean->pruntime, PX_POINT(pObject->x, pObject->y, pObject->z)));
				PX_WorldAddObject(pBean->pWorld, PX_Object_EvaluationCreate(pBean->pWorld, pBean->pruntime, PX_POINT((px_float)pBean->pruntime->surface_height / 6 + 125, (px_float)pBean->pruntime->surface_height / 8 + 25, pObject->z), 1));
			}
			break;
		default:
			break;
		}
	}

	if ((pObject->x >= pBean->pWorld->world_width / 6 + 120 && pObject->x < pBean->pWorld->world_width / 6 + 160) \
		|| (pObject->x <= pBean->pWorld->world_width / 6 + 60 && pObject->x > pBean->pWorld->world_width / 6 + 30))
	{
		switch (pDragon->status)
		{
		case DRAGON_FLY_TO_SKY:
			if (pBean->position == PX_OBJECT_FIREBALL_POSITION_BOTTOM)
			{
				//PX_SoundPlayAdd(&pBean->pruntime->soundplay, PX_SoundCreate(&soundeffect, PX_FALSE));
				pBean->state = PX_OBJECT_BEAN_STATE_DEAD;
				pObject->impact_object_type = 0;
				PX_WorldAddObject(pBean->pWorld, PX_Object_ParticallauncherCreate(pBean->pWorld, pBean->pruntime, PX_POINT(pObject->x, pObject->y, pObject->z)));
				PX_WorldAddObject(pBean->pWorld, PX_Object_EvaluationCreate(pBean->pWorld, pBean->pruntime, PX_POINT((px_float)pBean->pruntime->surface_height / 6 + 125, (px_float)pBean->pruntime->surface_height / 8 * 5 + 25, pObject->z), 2));
			}
			break;
		case DRAGON_LAND_TO_GROUND:
		case DRAGON_EFFECT_NULL:
			if (pBean->position == PX_OBJECT_FIREBALL_POSITION_TOP)
			{
				//PX_SoundPlayAdd(&pBean->pruntime->soundplay, PX_SoundCreate(&soundeffect, PX_FALSE));
				pBean->state = PX_OBJECT_BEAN_STATE_DEAD;
				pObject->impact_object_type = 0;
				PX_WorldAddObject(pBean->pWorld, PX_Object_ParticallauncherCreate(pBean->pWorld, pBean->pruntime, PX_POINT(pObject->x, pObject->y, pObject->z)));
				PX_WorldAddObject(pBean->pWorld, PX_Object_EvaluationCreate(pBean->pWorld, pBean->pruntime, PX_POINT((px_float)pBean->pruntime->surface_height / 6 + 125, (px_float)pBean->pruntime->surface_height / 8 + 25, pObject->z), 2));
			}
			break;
		default:
			break;
		}
	}
}

PX_Object* PX_Object_BeanCreate(PX_World* pworld,px_float x,px_float y, px_int type, PX_Runtime *pruntime)
{
	PX_Object_Bean bean;
	PX_Object* pObject;
	PX_memset(&bean, 0, sizeof(bean));
	bean.pWorld=pworld;
	bean.state=PX_OBJECT_BEAN_STATE_NORMAL;
	bean.hasmissed = PX_OBJECT_BEAN_MISSING;
	bean.pruntime = pruntime;
	switch (type)
	{
	case 1:
		bean.position = PX_OBJECT_FIREBALL_POSITION_TOP;
		break;
	case 2:
		bean.position = PX_OBJECT_FIREBALL_POSITION_BOTTOM;
		break;
	default:
		break;
	}
	
	pObject=PX_ObjectCreateEx(pworld->mp, PX_NULL, x, y, -1, 0, 0, 0, 0, PX_Object_BeanUpdate, PX_Object_BeanRender, PX_NULL, &bean, sizeof(bean));
	pObject->diameter = 60;
	pObject->impact_object_type = 2;
	PX_ObjectRegisterEvent(pObject,PX_OBJECT_DRAGON_JUDGE,PX_Object_Judge,PX_NULL);
	return pObject;
}

