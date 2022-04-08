#include "PX_Object_Background.h"


px_void PX_Object_BackgroundRender(px_surface* psurface, PX_Object* pObject, px_dword elpased)
{
	PX_Object_Background* pdesc = PX_ObjectGetDesc(PX_Object_Background, pObject);
	PX_TextureRenderEx(psurface, pdesc->ptexture, 0, 0, PX_ALIGN_LEFTTOP, PX_NULL, (px_float)psurface->width / 1920, 0);
}

PX_Object* PX_Object_BackgroundCreate(PX_World* pWorld, PX_Runtime* pruntime)
{
	PX_Object_Background desc;
	PX_Object* pObject;
	PX_memset(&desc, 0, sizeof(desc));
	desc.pWorld = pWorld;
	desc.pruntime = pruntime;
	desc.ptexture = PX_ResourceLibraryGetTexture(&pruntime->ResourceLibrary, "sky");
	if (!desc.ptexture)
	{
		return PX_FALSE;
	}
	pObject = PX_ObjectCreateEx(&pruntime->mp_game, PX_NULL, 0, 0, PX_OBJECT_BACKGROUND_Z, 0, 0, 0, 0, PX_NULL, PX_Object_BackgroundRender, PX_NULL, &desc, sizeof(desc));

	return pObject;
}