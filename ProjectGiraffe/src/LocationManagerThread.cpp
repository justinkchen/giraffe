//
// Tizen Native SDK
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
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

#include <FUi.h>
#include <FLocations.h>
#include "LocationManagerThread.h"
#include "ProjectGiraffeTab2.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Locations;

LocationManagerThread::LocationManagerThread(void)
	: Tizen::Base::Runtime::Thread()
	, __pUiControl(null)
{
}

LocationManagerThread::~LocationManagerThread(void)
{
}

result
LocationManagerThread::Construct(const Tizen::Ui::Control& uiControl)
{
	__pUiControl = &uiControl;
	return Thread::Construct();
}

Object*
LocationManagerThread::Run(void)
{
	AppLog("Starting to parse for location.");
	result lastResult = E_SUCCESS;
	LocationCriteria locCriteria;

	locCriteria.SetAccuracy(LOC_ACCURACY_HUNDRED_METERS);

	Location location = LocationProvider::GetLocation(locCriteria);


	double longitude = location.GetCoordinates().GetLongitude();

	AppLog("The longitude is: %f", longitude);
	AppLog("Requested for current location in new thread.");

	lastResult = GetLastResult();

	if (lastResult == E_LOCATION_UNAVAILABLE)
	{
		AppLog("Location was unavailable.");
	}

	if (lastResult == E_USER_NOT_CONSENTED)
	{
		AppLog("User did not consent.");
		__pUiControl->SendUserEvent(102, null);
	}

	ArrayList* pList = new (std::nothrow) ArrayList();
	Location* pLocation = new (std::nothrow) Location(location);
	pList->Construct();
	pList->Add(*pLocation);


	__pUiControl->SendUserEvent(101, pList);

	return null;
}
