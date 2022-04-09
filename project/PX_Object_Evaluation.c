#include "PX_Object_Evaluation.h"

px_void PX_Object_EvaluationUpdate(PX_Object* pObject, px_dword elpased)
{
	PX_Object_Evaluation* pdesc = PX_ObjectGetDesc(PX_Object_Evaluation, pObject);
	pdesc->time += elpased;
	if (pdesc->time > 1000)
	{
		PX_WorldRemoveObject(pdesc->pWorld, pObject);
	}
}

px_void PX_Object_EvaluationRender(px_surface* psurface, PX_Object* pObject, px_dword elpased)
{
	PX_Object_Evaluation* pdesc = PX_ObjectGetDesc(PX_Object_Evaluation, pObject);
	if (pdesc->time < 1000)
	{
		PX_ParticalLauncherRender(psurface, &pdesc->launcher, elpased);
	}
}


PX_Object* PX_Object_EvaluationCreate(PX_World* pWorld, PX_Runtime* pruntime, px_point point, px_uint type)
{
	PX_Object_Evaluation desc;
	PX_ParticalLauncher_InitializeInfo info;
	PX_Object* pObject;
	PX_memset(&desc, 0, sizeof(desc));
	desc.pWorld = pWorld;
	desc.pruntime = pruntime;
	
	switch (type)
	{
	case 1:
		desc.ptexture = PX_ResourceLibraryGetTexture(&pruntime->ResourceLibrary, "perfect");
		break;
	case 2:
		desc.ptexture = PX_ResourceLibraryGetTexture(&pruntime->ResourceLibrary, "good");
		break;
	case 3:
		desc.ptexture = PX_ResourceLibraryGetTexture(&pruntime->ResourceLibrary, "miss");
		break;
	default:
		break;
	}
	
	
	PX_ParticalLauncherInitializeDefaultInfo(&info);
	info.direction = PX_POINT(0, -1, 0);
	//info.generateDuration = 4;
	//info.launchCount = -1;
	info.maxCount = 1;
	info.position = point;
	info.tex = desc.ptexture;
	info.velocity = 100;
	info.alive = 1000;
	info.a = PX_POINT(0, 100, 0);
	//info.rotation = 180;
	//info.deviation_rotation = 90;
	info.atomsize = 0.08f;
	///info.deviation_atomsize_max = 1.0f;
	//info.deviation_atomsize_min = 0.5f;
	//info.alpha = 0.8f;
	//info.deviation_alpha = 0.3f;
	info.alphaincrease = -0.8f;

	PX_ParticalLauncherInitialize(&desc.launcher, &pruntime->mp_resources, info);

	pObject = PX_ObjectCreateEx(&pruntime->mp_resources, PX_NULL, 0, 0, PX_OBJECT_EVALUATION_Z, 0, 0, 0, 0, PX_Object_EvaluationUpdate, PX_Object_EvaluationRender, PX_NULL, &desc, sizeof(desc));
	return pObject;
}