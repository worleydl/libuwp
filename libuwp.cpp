/*
    Various helpers for UWP apps, add a new function if you need to interop between a dll and UWP calls
*/
#include "libuwp.h"

#include <mutex>

#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Gaming.Input.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Display.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>

using namespace winrt::Windows;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Graphics::Display::Core;
using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::UI::ViewManagement;

static int width = 0;
static int height = 0;
static std::mutex dim_mutex;

void uwp_GetBundlePath(char* buffer)
{
    sprintf_s(buffer, 256, "%s", winrt::to_string(ApplicationModel::Package::Current().InstalledPath()).c_str());
}

void uwp_GetBundleFilePath(char* buffer, const char *filename)
{
    sprintf_s(buffer, 256, "%s\\%s", winrt::to_string(ApplicationModel::Package::Current().InstalledPath()).c_str(), filename);
}

void uwp_GetActualSize(int* x, int* y)
{
    HdmiDisplayInformation hdi = HdmiDisplayInformation::GetForCurrentView();
    *x = hdi.GetCurrentDisplayMode().ResolutionWidthInRawPixels();
    *y = hdi.GetCurrentDisplayMode().ResolutionHeightInRawPixels();
}

void uwp_GetScreenSize(int* x, int* y)
{
    std::lock_guard<std::mutex> lock(dim_mutex);

    if (width == 0) {
        uwp_GetActualSize(&width, &height);
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
    return reinterpret_cast<void*>(winrt::get_abi(CoreWindow::GetForCurrentThread()));
}

void uwp_ProcessEvents()
{
    CoreWindow::GetForCurrentThread().Dispatcher().ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
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

void uwp_SetScreenSize(int x, int y)
{
    // Without the mutex you can trigger some funny resizes in multithreaded apps
    std::lock_guard<std::mutex> lock(dim_mutex);

    width = x;
    height = y;
}
