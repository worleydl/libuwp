/*
    Various helpers for UWP apps, add a new function if you need to interop between a dll and UWP calls
*/
#define _UNICODE
#define UNICODE

#include "pch.h"
#include "libuwp.h"

#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Gaming.Input.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Display.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>

static int width = 0;
static int height = 0;

static void* winHandle = NULL;

using namespace winrt::Windows;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Graphics::Display::Core;
using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::UI::ViewManagement;


void uwp_GetBundlePath(char* buffer)
{
    sprintf_s(buffer, 256, "%s", winrt::to_string(ApplicationModel::Package::Current().InstalledPath()).c_str());
}

void uwp_GetBundleFilePath(char* buffer, const char *filename)
{
    sprintf_s(buffer, 256, "%s\\%s", winrt::to_string(ApplicationModel::Package::Current().InstalledPath()).c_str(), filename);
}


void uwp_GetScreenSize(int* x, int* y)
{
	if (width == 0) {
        HdmiDisplayInformation hdi = HdmiDisplayInformation::GetForCurrentView();
        width = hdi.GetCurrentDisplayMode().ResolutionWidthInRawPixels();
        height = hdi.GetCurrentDisplayMode().ResolutionHeightInRawPixels();
	}

    *x = width;
    *y = height;
}

float uwp_GetRefreshRate()
{
    return HdmiDisplayInformation::GetForCurrentView().GetCurrentDisplayMode().RefreshRate();
}

void* uwp_GetWindowReference()
{
    void* ptr = reinterpret_cast<void*>(winrt::get_abi(CoreWindow::GetForCurrentThread()));
    return ptr;
}

// Deprecated, was using static var when debugging glfw but should be okay as long as you call from main thread
void* uwp_GetWindowHandle()
{
    return winHandle;
}

void uwp_SetWindowHandle(void* handle)
{
    winHandle = handle;
}

void uwp_ProcessEvents()
{
    CoreWindow::GetForCurrentThread().Dispatcher().ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
}

int uwp_SetFullscreen()
{
    int width, height;
    uwp_GetScreenSize(&width, &height);
    Foundation::Size size(width, height); // TODO: May need DIPS conversion similar to what SDL does

    ApplicationView::GetForCurrentView().TryResizeView(size);
    return ApplicationView::GetForCurrentView().TryEnterFullScreenMode();
}

int uwp_SetWindowSize(int x, int y)
{
    const Size size(x, y);
    ApplicationView::GetForCurrentView().TryResizeView(size);
}

// Register gamepad event hooks to method inside of calling program
void uwp_RegisterGamepadCallbacks(void (*callback)(void))
{
    namespace WGI = winrt::Windows::Gaming::Input;

    try
    {
        WGI::Gamepad::GamepadAdded([callback](auto&&, const WGI::Gamepad) {
            callback();
        });

        WGI::Gamepad::GamepadRemoved([callback](auto&&, const WGI::Gamepad) {
            callback();
        });
    }
    catch (winrt::hresult_error)
    {
    }

}
