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
#ifndef _UICONTROLS_H_
#define _UICONTROLS_H_

#include <FBase.h>
#include <FApp.h>
#include <FUi.h>
#include <FSystem.h>

 // application must inherit from Application class
 // which provides basic features necessary to define an application.
class UiControls :
	public Tizen::App::Application,
	public Tizen::System::IScreenEventListener
{
public:
	 // [HelloWorld] application must have a factory method that creates an instance of itself.
	static Tizen::App::Application* CreateInstance(void);

public:
	UiControls(void);
	virtual ~UiControls(void);

public:

	 // Called when the application is initializing.
	bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);

	 // Called when the application is terminating.
	bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);

	 // Called when the application's frame moves to the top of the screen.
	void OnForeground(void);

	 // Called when this application's frame is moved from top of the screen to the background.
	void OnBackground(void);

	 // Called when the system memory is not sufficient to run the application any further.
	void OnLowMemory(void);

	 // Called when the battery level changes.
	void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);

	 //	Called when the screen turns on.
	void OnScreenOn (void);

	 //	Called when the screen turns off.
	void OnScreenOff (void);
	
};

#endif
