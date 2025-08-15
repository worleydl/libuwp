﻿#pragma once

#define LIBAPI extern "C" __declspec(dllexport)

// :: Screen information
LIBAPI void  uwp_GetActualSize(int* x, int* y); // Gets the display resolution
LIBAPI void  uwp_GetScreenSize(int* x, int* y); // Gets the display resolution OR override from user
LIBAPI float uwp_GetRefreshRate();
LIBAPI void* uwp_GetWindowReference();

// By default GetScreenSize will return display resolution, but this will allow apps to override those values
LIBAPI void  uwp_SetScreenSize(int x, int y);

// :: Filepaths
LIBAPI void uwp_GetBundlePath(char* buffer);
LIBAPI void uwp_GetBundleFilePath(char* buffer, const char* filename);

// :: Events

// If not using SDL or other helper you must occasionally call this to get anything to show on screen
LIBAPI void uwp_ProcessEvents();

// If not using SDL or other helper you must register event callbacks to read controller input
LIBAPI void uwp_RegisterGamepadCallbacks(void (*callback)(void));
