#ifndef PX_OBJECT_BEAN
#define PX_OBJECT_BEAN
#include "PainterEngine_Startup.h"
#include "Game_Text.h"

typedef enum 
{
	PX_OBJECT_BEAN_STATE_NORMAL,
	PX_OBJECT_BEAN_STATE_DEAD,
}PX_OBJECT_BEAN_STATE;

typedef enum {
	PX_OBJECT_FIREBALL_POSITION_TOP,
	PX_OBJECT_FIREBALL_POSITION_BOTTOM,
}PX_OBJECT_FIREBALL_POSITION;

typedef enum {
	PX_OBJECT_BEAN_MISSED,
	PX_OBJECT_BEAN_MISSING,
}PX_OBJECT_BEAN_HASMISSED;

typedef struct
{
	PX_World* pWorld;
	PX_Runtime* pruntime;
	PX_OBJECT_BEAN_STATE state;
	PX_OBJECT_FIREBALL_POSITION position;
	PX_OBJECT_BEAN_HASMISSED hasmissed;
}PX_Object_Bean;

PX_Object* PX_Object_BeanCreate(PX_World* pworld,px_float x,px_float y, px_int type, PX_Runtime* pruntime);
#endif