#pragma once

#define LIBAPI extern "C" __declspec(dllexport)

// Screen information
LIBAPI void  uwp_GetScreenSize(int* x, int* y);
LIBAPI float uwp_GetRefreshRate();
LIBAPI void* uwp_GetWindowReference();
LIBAPI int   uwp_SetFullscreen(); // Doesn't really do anything at the moment, debugging fullscreen issues in UWP
LIBAPI int	 uwp_SetWindowSize(int x, int y);

// Filepaths
LIBAPI void uwp_GetBundlePath(char* buffer);
LIBAPI void uwp_GetBundleFilePath(char* buffer, const char* filename);

// Events
LIBAPI void uwp_ProcessEvents();
LIBAPI void uwp_RegisterGamepadCallbacks(void (*callback)(void));

// Deprecated, use get window reference
LIBAPI void* uwp_GetWindowHandle();
LIBAPI void uwp_SetWindowHandle(void* handle);

