#ifndef PX_OBJECT_BACKGROUND_H
#define PX_OBJECT_BACKGROUND_H

#include "PainterEngine_Startup.h"

#define PX_OBJECT_BACKGROUND_Z 20

typedef struct {
	PX_World* pWorld;
	PX_Runtime* pruntime;
	px_texture* ptexture;
}PX_Object_Background;

PX_Object* PX_Object_BackgroundCreate(PX_World* pWorld, PX_Runtime* pruntime);
#endif // !PX_OBJECT_BACKGROUND_H
