#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#include <string>
#include <nlohmann/json.hpp>

#ifndef WIN32 // Android
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#endif

#include "rect.h"
#include "constants.h"

namespace util
{
	inline void log(const std::string msg)
	{
		SDL_Log("%s", msg.c_str());
		
//#ifdef _DEBUG
//		// Add to log file potentially
//#endif
	}

	inline void logInfo(const std::string msg, const bool verbose = false)
	{
		if ((verbose && Consts::LOG_VERBOSE) || !verbose)
			log("[INFO]: " + msg);
	}
	
	inline void logError(const std::string msg)
	{
		log("[ERROR]: " + msg + " (" + SDL_GetError() + ")");
	}

	inline Vect<uint32_t> getSize(SDL_Texture* texture)
	{
		Vect<int> result(0, 0);
		SDL_QueryTexture(texture, NULL, NULL, &result.x, &result.y);
		return result.cast<uint32_t>();
	}

#ifndef WIN32
	inline void loadAssetManager(AAssetManager*& manager)
	{
		// Code I copied off of Stackoverflow (https://stackoverflow.com/questions/22436259/android-ndk-why-is-aassetmanager-open-returning-null/22436260#22436260)
		// Just gets the Android Asset Manager pointer without having to interface with the JNI

		JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();

		jobject activity = (jobject)SDL_AndroidGetActivity();

		jclass activity_class = env->GetObjectClass(activity);

		jmethodID activity_class_getAssets = env->GetMethodID(activity_class, "getAssets", "()Landroid/content/res/AssetManager;");
		jobject asset_manager = env->CallObjectMethod(activity, activity_class_getAssets); // activity.getAssets();

		manager = AAssetManager_fromJava(env, env->NewGlobalRef(asset_manager));
	}
#endif

	inline const nlohmann::json loadJSON(const std::string path)
	{
#ifdef WIN32
		return nlohmann::json::parse(std::ifstream(path));
#else
		static AAssetManager* androidAssetManager;
		if (androidAssetManager == NULL) loadAssetManager(androidAssetManager);

		AAsset* file = AAssetManager_open(androidAssetManager, path.c_str(), AASSET_MODE_STREAMING);
		off64_t length = AAsset_getLength64(file);
		char contents[length];
		AAsset_read(file, contents, length);

		std::string result(contents);
		util::logInfo(result);
		return nlohmann::json::parse(result);
#endif
	}
}