#include "PainterEngine_Application.h"
#include "PX_Object_Dragon.h"
#include "PX_Object_Background.h"
#include "PX_Object_Cloud.h"
#include "PX_Object_JudgementCircle.h"
#include "PX_Object_Ground.h"
#include "PX_Object_Bean.h"
#include "PX_Object_KeyManager.h"
#include "PX_Object_Particallauncher.h"
#include "Game_Text.h"

PX_Application App;

PX_Animation animationDragon;
PX_Object* dragon;
PX_Object* background;
PX_Object* mountain;
PX_Object* cloud;
PX_Object* judgementcircleT;
PX_Object* judgementcircleB;
px_dword cloud_gen;
px_point basepoint;
PX_SoundData soundeffect;
PX_Json_Value* keymap;
px_int keynum;

px_bool PX_ApplicationInitialize(PX_Application *pApp,px_int screen_width,px_int screen_height)
{
	PX_ApplicationInitializeDefault(&pApp->runtime, screen_width, screen_height);

	PX_LoadAnimationLibraryFromFile(&pApp->runtime.mp_resources, &pApp->animationlibrary, GAME_ANIMATIONLIBRARY_PATH_DRAGON);
	PX_AnimationCreate(&animationDragon, &pApp->animationlibrary);
	PX_AnimationSetCurrentPlayAnimationByName(&animationDragon, "walk");

	PX_SoundPlayInitialize(&pApp->runtime.mp_game, &pApp->runtime.soundplay);
	PX_AudioInitialize(&pApp->runtime.soundplay);
	PX_SoundPlayClear(&pApp->runtime.soundplay);
	PX_SoundStaticDataFree(&pApp->sounddata);
	PX_LoadSoundFromFile(&pApp->runtime.mp_resources, &pApp->sounddata, GAME_SOUND_PATH_LOAD);
	PX_SoundStaticDataFree(&soundeffect);
	PX_LoadSoundFromFile(&pApp->runtime.mp_resources, &soundeffect, GAME_SOUNDEFFECT_PATH_MOTION_ATTACK);
	PX_SoundPlayAdd(&pApp->runtime.soundplay, PX_SoundCreate(&pApp->sounddata, PX_FALSE));
	
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_SKY, "sky"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_CLOUD01, "cloud01"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_CLOUD02, "cloud02"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_CLOUD03, "cloud03"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_MOUNTAIN01, "mountain01"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_MOUNTAIN02, "mountain02"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_PARTICAL01, "partical01"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_EVALUATION_PERFECT, "perfect"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_EVALUATION_GOOD, "good"))
		return PX_FALSE;
	if (!PX_LoadTextureToResource(&pApp->runtime.ResourceLibrary, GAME_TEXTURE_PATH_EVALUATION_MISS, "miss"))
		return PX_FALSE;
	
	PX_WorldInitialize(&pApp->runtime.mp_game, &pApp->world, pApp->runtime.surface_width, pApp->runtime.surface_height, pApp->runtime.surface_width, pApp->runtime.surface_height, 1024 * 1024 * 4);
	
	dragon = PX_Object_DragonCreate(&pApp->world, &pApp->runtime);
	background = PX_Object_BackgroundCreate(&pApp->world, &pApp->runtime);

	basepoint.x = (px_float)pApp->runtime.surface_width / 6 + 85;
	basepoint.y = (px_float)pApp->runtime.surface_height / 8 + 65;
	judgementcircleT = PX_Object_JudgementCircleCreate(&pApp->world, &pApp->runtime, basepoint);

	basepoint.x = (px_float)pApp->runtime.surface_width / 6 + 85;
	basepoint.y = (px_float)pApp->runtime.surface_height / 8 * 5 + 65;
	judgementcircleB = PX_Object_JudgementCircleCreate(&pApp->world, &pApp->runtime, basepoint);

	PX_WorldAddObject(&pApp->world, background);
	PX_WorldAddObject(&pApp->world, judgementcircleT);
	PX_WorldAddObject(&pApp->world, judgementcircleB);
	PX_WorldAddObject(&pApp->world, dragon);
	PX_WorldAddObject(&pApp->world, PX_Object_GroundCreate(&pApp->world, &pApp->runtime, 1));
	PX_WorldAddObject(&pApp->world, PX_Object_GroundCreate(&pApp->world, &pApp->runtime, 2));
	PX_WorldAddObject(&pApp->world, PX_Object_KeyManagerCreate(&pApp->world, &pApp->runtime));
	
	return PX_TRUE;
}

px_void PX_ApplicationUpdate(PX_Application *pApp,px_dword elapsed)
{
	PX_WorldUpdate(&pApp->world, elapsed);
	PX_AnimationUpdate(&animationDragon, elapsed);

	static px_dword reservedTime = 0;
	px_dword updateTime = elapsed + reservedTime;

	while (updateTime >= 20)
	{
		if (cloud_gen > 20)
		{
			cloud_gen -= 20;
		}
		else
		{
			cloud_gen = 100 + PX_rand() % 5000;
			PX_WorldAddObject(&pApp->world, PX_Object_CloudCreate(&pApp->world, &pApp->runtime));
			//PX_WorldAddObject(&pApp->world, PX_Object_BeanCreate(&pApp->world, pApp->runtime.surface_width, pApp->runtime.surface_height / 8 + 65, 1, &pApp->runtime));
			//PX_WorldAddObject(&pApp->world, PX_Object_BeanCreate(&pApp->world, pApp->runtime.surface_width + 200, pApp->runtime.surface_height / 8 * 5 + 65, 2, &pApp->runtime));
		}
		updateTime -= 20;
	}
	reservedTime = updateTime;

}

px_void PX_ApplicationRender(PX_Application *pApp,px_dword elapsed)
{
	px_surface *pRenderSurface=&pApp->runtime.RenderSurface;
	PX_RuntimeRenderClear(&pApp->runtime,PX_OBJECT_UI_DEFAULT_BACKGROUNDCOLOR);
	PX_WorldRender(pRenderSurface, &pApp->world, elapsed);
}

px_void PX_ApplicationPostEvent(PX_Application *pApp,PX_Object_Event e)
{
	PX_ApplicationEventDefault(&pApp->runtime, e);
	PX_ObjectPostEvent(dragon, e);

}

