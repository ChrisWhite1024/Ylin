#ifndef PX_OBJECT_EVALUATION_H
#define PX_OBJECT_EVALUATION_H

#include "PainterEngine_Startup.h"

#define PX_OBJECT_EVALUATION_Z -5

typedef struct {
	PX_World* pWorld;
	PX_Runtime* pruntime;
	px_texture* ptexture;
	px_dword time;
	PX_ParticalLauncher launcher;
}PX_Object_Evaluation;

PX_Object* PX_Object_EvaluationCreate(PX_World* pWorld, PX_Runtime* pruntime, px_point point, px_uint type);
#endif // !PX_OBJECT_EVALUATION_H