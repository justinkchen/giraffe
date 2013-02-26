/**
 * Name        : HelloWorld
 * Version     :
 * Vendor      :
 * Description :
 */


#include "HelloWorld.h"
#include "HelloWorldFrame.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


HelloWorldApp::HelloWorldApp(void)
{
}

HelloWorldApp::~HelloWorldApp(void)
{
}

UiApp*
HelloWorldApp::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new HelloWorldApp();
}

bool
HelloWorldApp::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize Frame and App specific data.
	// The App's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the App will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// TODO:
	// Add your initialization code here
	return true;
}

bool
HelloWorldApp::OnAppInitialized(void)
{
	// TODO:
	// Comment.

	// Create a Frame
	HelloWorldFrame* pHelloWorldFrame = new HelloWorldFrame();
	pHelloWorldFrame->Construct();
	pHelloWorldFrame->SetName(L"HelloWorld");
	AddFrame(*pHelloWorldFrame);

	return true;
}

bool
HelloWorldApp::OnAppWillTerminate(void)
{
	// TODO:
	// Comment.
	return true;
}

bool
HelloWorldApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this App for termination.
	// The App's permanent data and context can be saved via appRegistry.
	return true;
}

void
HelloWorldApp::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void
HelloWorldApp::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void
HelloWorldApp::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
HelloWorldApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
HelloWorldApp::OnScreenOn(void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
HelloWorldApp::OnScreenOff(void)
{
	// TODO:
	// Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device
	// to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a
	// callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
