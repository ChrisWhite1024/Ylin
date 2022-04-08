#include "PX_Object_JudgementCircle.h"

px_void PX_Object_JudgementCircleUpdate(PX_Object* pObject, px_dword elpased)
{
	PX_Object_JudgementCircle* pdesc = PX_ObjectGetDesc(PX_Object_JudgementCircle, pObject);

	pdesc->time += elpased;
}

px_void PX_Object_JudgementCircleRender(px_surface* psurface, PX_Object* pObject, px_dword elpased)
{
	PX_Object_JudgementCircle* pdesc = PX_ObjectGetDesc(PX_Object_JudgementCircle, pObject);

	PX_GeoDrawRing(psurface, pdesc->point.x, pdesc->point.y, 30.f + 2 * PX_sin_radian(((px_float)pdesc->time / 200)), 5.f, PX_COLOR(255, 255, 255, 255), 360 * PX_sin_radian(((px_float)pdesc->time / 200)), (360 * PX_sin_radian(((px_float)pdesc->time / 200)) + 100) - 360);
}

PX_Object* PX_Object_JudgementCircleCreate(PX_World* pWorld, PX_Runtime* pruntime, px_point basepoint)
{
	PX_Object_JudgementCircle desc;
	PX_Object* pObject;
	PX_memset(&desc, 0, sizeof(desc));
	
	desc.time = 0;
	desc.pWorld = pWorld;
	desc.point.x = basepoint.x;
	desc.point.y = basepoint.y;
	desc.point.z = PX_OBJECT_JUDGEMENTCIRCLE_Z;
	
	pObject = PX_ObjectCreateEx(&pruntime->mp_game, PX_NULL, 0, 0, PX_OBJECT_JUDGEMENTCIRCLE_Z, 0, 0, 0, 0, PX_Object_JudgementCircleUpdate, PX_Object_JudgementCircleRender, PX_NULL, &desc, sizeof(desc));

	return pObject;
}