#ifndef PX_OBJECT_DRAGON_H
#define PX_OBJECT_DRAGON_H
#include "PainterEngine_Startup.h"
#include "Game_Text.h"
#include "PX_Object_Bean.h"

typedef enum
{
	DRAGON_TOP_FLYKICK,
	DRAGON_BOTTOM_STRIKE,
	DRAGON_BOTTOM_ATTACK,
	DRAGON_BOTTOM_WALK,
}DRAGON_STATUS;

typedef enum
{
	DRAGON_EFFECT_NULL,
	DRAGON_FLY_TO_SKY,
	DRAGON_LAND_TO_GROUND,
}ANIMATION_EFFECT;

typedef struct  
{
	PX_World* pWorld;
	px_float velocity;
	DRAGON_STATUS status;
	ANIMATION_EFFECT animationEffect;
	px_dword AnimationElpased;
	px_dword time;
	PX_Runtime* runtime;

}PX_Object_Dragon;



PX_Object* PX_Object_DragonCreate(PX_World* pworld, PX_Runtime* runtime);
#endif
