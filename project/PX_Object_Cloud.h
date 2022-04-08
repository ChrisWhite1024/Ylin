#ifndef PX_OBJECT_CLOUD_H
#define PX_OBJECT_CLOUD_H

//云运动的源码来自PainterEngineDemo狐狸跳跳跳 https://www.painterengine.com/example.html

#include "PainterEngine_Startup.h"

#define PX_OBJECT_CLOUD_BASE 200
#define PX_OBJECT_CLOUD_Z 5

typedef enum
{
	PX_Object_Cloud_State_Ready,
	PX_Object_Cloud_State_Run,
	PX_Object_Cloud_State_Stop,
}PX_Object_Cloud_State;

typedef struct
{
	PX_World* pWorld;
	PX_Runtime* pruntime;
	px_texture* ptextures;

	PX_Object_Cloud_State state;
}PX_Object_Cloud;

PX_Object* PX_Object_CloudCreate(PX_World* pWorld, PX_Runtime* pruntime);

#endif // !PX_OBJECT_CLOUD_H
