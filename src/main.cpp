#include <iostream>
#include <SDL2/SDL.h>

#include "game.h"

int main(int argc, char* args[])
{
    if (!Game::init()) return -1;
	
	Game game;
	game.start();
	
    return 0;
}


/*#ifndef WIN32
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

AAssetManager* androidAssetManager;

extern "C" JNIEXPORT void JNICALL
Java_com_stavitic_speedup_Speedup_getAssetManager(JNIEnv *env, jclass clazz, jobject mgr) {
    androidAssetManager = AAssetManager_fromJava(env, mgr);

    if (androidAssetManager == NULL) util::logError("Android Asset Manager failed to load");
    else util::logInfo("Android Asset Manager loaded!");
}

#endif*/