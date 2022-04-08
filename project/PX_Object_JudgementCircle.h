#ifndef PX_OBJECT_JUDGEMENTCIRCLE_H
#define PX_OBJECT_JUDGEMENTCIRCLE_H

#include "PainterEngine_Startup.h"

#define PX_OBJECT_JUDGEMENTCIRCLE_Z 5

typedef struct {
	PX_World* pWorld;
	px_dword time;
	px_point point;
}PX_Object_JudgementCircle;

PX_Object* PX_Object_JudgementCircleCreate(PX_World* pWorld, PX_Runtime* pruntime, px_point basepoint);

#endif // !PX_OBJECT_JUDGEMENTCIRCLE_H
