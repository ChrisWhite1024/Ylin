//山运动的源码来自PainterEngineDemo狐狸跳跳跳 https://www.painterengine.com/example.html
#include "PX_Object_Ground.h"

px_void PX_Object_GroundRender(px_surface* psurface, PX_Object* pObject, px_dword elpased)
{
	px_int requireTextureIndex = 0;
	px_int renderOffset;
	PX_Object_Ground* pDesc = PX_ObjectGetDesc(PX_Object_Ground, pObject);

	renderOffset = (px_int)pDesc->xoffset;
	

	while (renderOffset<pDesc->pruntime->surface_width)
	{
		px_texture* ptexture;
		ptexture = pDesc->ptexture;
		if (renderOffset+ptexture->width<0)
		{
			renderOffset += ptexture->width * (px_float)psurface->width / 1920;
			pDesc->xoffset += ptexture->width * (px_float)psurface->width / 1920;
			continue;
		}

		PX_TextureRenderEx(psurface, ptexture, renderOffset, (px_int)(pDesc->pruntime->surface_height), PX_ALIGN_LEFTBOTTOM, PX_NULL, (px_float)psurface->width / 1920, 0);

		requireTextureIndex++;
		renderOffset += ptexture->width * (px_float)psurface->width / 1920;
		
	}

	switch (pDesc->state)
	{
	case PX_Object_Ground_State_Ready:
	{
		pDesc->xoffset -= elpased / 16.0f;
	}
	break;
	case PX_Object_Ground_State_Run:
	{
		pDesc->xoffset -= elpased / 2.0f;
	}
	break;
	case PX_Object_Ground_State_Stop:
	{
		//nop
	}
	break;
	default:
		break;
	}
	
}

px_void PX_Object_GroundFree(PX_Object* pObject)
{
	px_int i;
	PX_Object_Ground* pDesc = PX_ObjectGetDesc(PX_Object_Ground, pObject);
}

px_void PX_Object_GroundOnReady(PX_Object* pObject, PX_Object_Event e, px_void* ptr)
{
	PX_Object_Ground* pDesc = PX_ObjectGetDesc(PX_Object_Ground, pObject);
	pDesc->state = PX_Object_Ground_State_Ready;
	return;
}

px_void PX_Object_GroundOnRun(PX_Object* pObject, PX_Object_Event e, px_void* ptr)
{
	PX_Object_Ground* pDesc = PX_ObjectGetDesc(PX_Object_Ground, pObject);
	pDesc->state = PX_Object_Ground_State_Run;
	return;
}

px_void PX_Object_GroundOnStop(PX_Object* pObject, PX_Object_Event e, px_void* ptr)
{
	PX_Object_Ground* pDesc = PX_ObjectGetDesc(PX_Object_Ground, pObject);
	pDesc->state = PX_Object_Ground_State_Stop;
	return;
}

PX_Object* PX_Object_GroundCreate(PX_World* pWorld, PX_Runtime* pruntime, px_int type)
{
	px_int z;
	PX_Object* pObject;
	PX_Object_Ground desc;
	PX_memset(&desc, 0, sizeof(desc));
	desc.pruntime = pruntime;
	desc.pWorld = pWorld;
	desc.state = PX_Object_Ground_State_Ready;
	switch (type)
	{
	case 1:
		desc.ptexture = PX_ResourceLibraryGetTexture(&pruntime->ResourceLibrary, "mountain01");
		z = 10;
		break;
	case 2:
		desc.ptexture = PX_ResourceLibraryGetTexture(&pruntime->ResourceLibrary, "mountain02");
		z = 12;
		break;
	default:
		break;
	}
	pObject=PX_ObjectCreateEx(&pruntime->mp_game, PX_NULL, 0, 0, z, 0, 0, 0, 0, 0, PX_Object_GroundRender, PX_Object_GroundFree, &desc, sizeof(desc));
	
	return pObject;
}

