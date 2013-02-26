//
// Tizen native SDK
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "UiControls.h"
#include "SceneRegister.h"

using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::App;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

UiControls::UiControls(void)
{
}

UiControls::~UiControls(void)
{
}

Application*
UiControls::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new UiControls();
}

bool
UiControls::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize UI resources (forms, buttons, etc.) and application specific data.
	// The application's permanent data and context can be obtained from the appRegistry.
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the application will be terminated.
	/////////////////////////////////////////////////////////////////////////////////////
	//this codes is automatically inserted by Tizen application wizard.
	Frame* pAppFrame = new Frame();
	pAppFrame->Construct();
	AddFrame(*pAppFrame);
	////////////////////////////////////////////////////////////////////////////////////

	// Prepare Scene management.

	SceneRegister::RegisterAllScenes();
	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_FORM));

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);
	
	return true;
}


bool
UiControls::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application.
	// The application's permanent data and context can be saved via appRegistry.

	return true;
}


void
UiControls::OnForeground(void)
{
	//TODO:
	// Add code to execute when the application is moved to the foreground.
}

void
UiControls::OnBackground(void)
{
	//TODO:
	// Add code to execute when the application is moved to the backgorund.
}

void
UiControls::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}


void
UiControls::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// It is recommended that the application is closed if the battery level is low.
}

void
UiControls::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
UiControls::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}

