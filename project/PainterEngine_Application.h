#ifndef PAINTERENGINE_APPLICATION_H
#define PAINTERENGINE_APPLICATION_H

#ifdef __cplusplus
extern "C"{
#endif

#include "PainterEngine_Startup.h"
#include "platform/modules/px_audio.h"

#ifdef __cplusplus
}
#endif
typedef struct
{
	PX_Runtime runtime;
	PX_AnimationLibrary animationlibrary;
	PX_SoundData sounddata;
	PX_World world;
}PX_Application;



extern PX_Application App;

extern PX_Animation animationDragon;
extern PX_Object* dragon;
extern PX_Object* background;
extern PX_SoundData soundeffect;
extern PX_Json_Value* keymap;
extern px_int keynum;

px_bool PX_ApplicationInitialize(PX_Application *App,px_int screen_Width,px_int screen_Height);
px_void PX_ApplicationUpdate(PX_Application *App,px_dword elapsed);
px_void PX_ApplicationRender(PX_Application *App,px_dword elapsed);
px_void PX_ApplicationPostEvent(PX_Application *App,PX_Object_Event e);

#endif
