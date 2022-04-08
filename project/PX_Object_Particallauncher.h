#ifndef PX_OBJECT_PARTICALLAUNCHER_H
#define PX_OBJECT_PARTICALLAUNCHER_H

#include "PainterEngine_Startup.h"

#define PX_OBJECT_PARTICALLAUNCHER_Z 10

typedef struct {
	PX_World* pWorld;
	PX_Runtime* pruntime;
	px_texture* ptexture;
	px_dword time;
	PX_ParticalLauncher launcher;
}PX_Object_Particallauncher;

PX_Object* PX_Object_ParticallauncherCreate(PX_World* pWorld, PX_Runtime* pruntime, px_point point);
#endif // !PX_OBJECT_PARTICALLAUNCHER_H