#ifndef PX_OBJECT_KEYMANAGER_H
#define PX_OBJECT_KEYMANAGER_H

#include "PainterEngine_Startup.h"

typedef struct {
    px_dword time;
    PX_Json json;
    PX_World* pWorld;
	PX_Runtime* pruntime;
}PX_Object_KeyManager;

PX_Object *PX_Object_KeyManagerCreate(PX_World* pWorld, PX_Runtime* pruntime);
#endif