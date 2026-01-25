#pragma once

#include <filesystem>
#include <functional>
#include <list>

#define LIBAPI extern "C" __declspec(dllexport)

using FilePickedCallback = void(*)(const char* path);

// :: Screen information
LIBAPI void  uwp_GetScreenSize(int* x, int* y);
LIBAPI float uwp_GetRefreshRate();
LIBAPI void* uwp_GetWindowReference();
LIBAPI void  uwp_SetupHDR(bool enabled);

// :: Filepaths
LIBAPI void uwp_GetBundlePath(char* buffer);
LIBAPI void uwp_GetBundleFilePath(char* buffer, const char* filename);
LIBAPI void uwp_PickAFile(std::function<void(const char* path)>);
LIBAPI void uwp_PickMultipleFiles(std::function<void(const std::list<std::filesystem::path>)> callback);

// :: Events

// If not using SDL or other helper you must occasionally call this to get anything to show on screen
LIBAPI void uwp_ProcessEvents();

// If not using SDL or other helper you must register event callbacks to read controller input
LIBAPI void uwp_RegisterGamepadCallbacks(void (*callback)(void));
