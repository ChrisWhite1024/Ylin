#include "PX_Object_Particallauncher.h"

px_void PX_Object_ParticallauncherUpdate(PX_Object* pObject, px_dword elpased)
{
	PX_Object_Particallauncher* pdesc = PX_ObjectGetDesc(PX_Object_Particallauncher, pObject);
	pdesc->time += elpased;
	if (pdesc->time > 2000)
	{
		PX_WorldRemoveObject(pdesc->pWorld, pObject);
	}
}

px_void PX_Object_ParticallauncherRender(px_surface* psurface, PX_Object* pObject, px_dword elpased)
{
	PX_Object_Particallauncher* pdesc = PX_ObjectGetDesc(PX_Object_Particallauncher, pObject);
	PX_ParticalLauncherRender(psurface, &pdesc->launcher, elpased);
}


PX_Object* PX_Object_ParticallauncherCreate(PX_World* pWorld, PX_Runtime* pruntime, px_point point)
{
	PX_Object_Particallauncher desc;
	PX_ParticalLauncher_InitializeInfo info;
	PX_Object* pObject;
	PX_memset(&desc, 0, sizeof(desc));
	desc.pWorld = pWorld;
	desc.pruntime = pruntime;
	desc.ptexture = PX_ResourceLibraryGetTexture(&pruntime->ResourceLibrary, "partical01");
	
	PX_ParticalLauncherInitializeDefaultInfo(&info);
	info.deviation_rangAngle = 360;
	//info.deviation_velocity = 10;
	info.direction = PX_POINT(-1, 0, 0);
	info.generateDuration = 4;
	info.launchCount = -1;
	info.maxCount = 30;
	info.position = point;
	info.tex = desc.ptexture;
	info.velocity = 400;
	info.alive = 2000;
	info.a = PX_POINT(0, 100, 0);
	info.rotation = 180;
	//info.deviation_rotation = 90;
	info.atomsize = 0.04f;
	//info.deviation_atomsize_max = 0.04f;
	//info.deviation_atomsize_min = 0.02f;
	info.alpha = 0.8f;
	info.deviation_alpha = 0.3f;
	info.alphaincrease = -0.5f;

	PX_ParticalLauncherInitialize(&desc.launcher, &pruntime->mp_resources, info);

	pObject = PX_ObjectCreateEx(&pruntime->mp_resources, PX_NULL, 0, 0, PX_OBJECT_PARTICALLAUNCHER_Z, 0, 0, 0, 0, PX_Object_ParticallauncherUpdate, PX_Object_ParticallauncherRender, PX_NULL, &desc, sizeof(desc));
	return pObject;
}