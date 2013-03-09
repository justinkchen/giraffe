#include <FApp.h>
#include "ProjectGiraffeMainForm.h"
#include "LocationManagerThread.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Locations;

Location* ProjectGiraffeMainForm::__currentLocation;
double ProjectGiraffeMainForm::currentLatitude = 0;
double ProjectGiraffeMainForm::currentLongitude = 0;

ProjectGiraffeMainForm::ProjectGiraffeMainForm(void)
: __pLocProvider(null),
__pLocationManagerThread(null),
__regionId(-1)
{
}

ProjectGiraffeMainForm::~ProjectGiraffeMainForm(void)
{
}

bool
ProjectGiraffeMainForm::Initialize(void)
{
	Construct(L"IDF_FORM");

	return true;
}

result
ProjectGiraffeMainForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO:
	// Add your initialization code here
	Header* pHeader = GetHeader();
	if (pHeader)
	{
		pHeader->AddActionEventListener(*this);
	}
	Footer* pFooter = GetFooter();
	if (pFooter)
	{
		pFooter->AddActionEventListener(*this);
	}

	// Setup back event listener
	SetFormBackEventListener(this);


	__pLocationManagerThread =  new (std::nothrow) LocationManagerThread();
	r = __pLocationManagerThread->Construct(*this);
	if (IsFailed(r))
	{
		AppLog("Thread Construct failed.");
		return r;
	}

	LocationCriteria criteria;
	criteria.SetAccuracy(LOC_ACCURACY_HUNDRED_METERS);
	__pLocProvider = new (std::nothrow) LocationProvider();
	r = __pLocProvider->Construct(criteria, *this);
	if (r != E_SUCCESS)
	{
		AppLog("Location Provider construct failed.");
	}
	//__pLocProvider->StartLocationUpdatesByInterval(3);

	AppLog("Everything is initialized, Location updates started.");
	MainFormParseLocation();
	return r;
}

result
ProjectGiraffeMainForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	__pLocProvider->StopLocationUpdates();
	delete __pLocProvider;
	__pLocationManagerThread->Join();
	delete __pLocationManagerThread;
	//delete __currentLocation;
	// TODO:
	// Add your termination code here
	return r;
}

void
ProjectGiraffeMainForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Header* pHeader = GetHeader();

	switch(actionId)
	{
	case ID_FOOTER_ITEM1:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_1"));
		pHeader->SetTitleText(L"Nearby Graffiti");
		break;
	case ID_FOOTER_ITEM2:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_2"));
		pHeader->SetTitleText(L"Graffiti Map");
		break;
	case ID_FOOTER_ITEM3:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_3"));
		pHeader->SetTitleText(L"Post Graffiti");
		break;
	case ID_FOOTER_ITEM4:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_4"));
		pHeader->SetTitleText(L"Profile");
		break;
	case ID_FOOTER_ITEM5:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_5"));
		pHeader->SetTitleText(L"Settings");
		break;
	default:
		break;
	}
}

void
ProjectGiraffeMainForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}

void
ProjectGiraffeMainForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeMainForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeMainForm::OnLocationUpdated(const Tizen::Locations::Location& location)
{
	AppLog("Location Updated.");
	//__currentLocation = &location;
	AppLog("Location Assigned.");
	double d = __currentLocation->GetCoordinates().GetLatitude();
	AppLog("Current Latitude: %f.", d);
}


void
ProjectGiraffeMainForm::OnLocationUpdateStatusChanged(LocationServiceStatus status)
{
	AppLog("Location Status Updated.");
	switch(status)
	{
	case LOC_SVC_STATUS_IDLE:
		AppLog("Service is idle.");
		break;
	case LOC_SVC_STATUS_RUNNING:
		AppLog("Service is running.");
		break;
	case LOC_SVC_STATUS_PAUSED :
		AppLog("Service is paused.");
		break;
	case LOC_SVC_STATUS_DENIED :
		AppLog("Service is denied.");
		break;
	case LOC_SVC_STATUS_NOT_FIXED:
		AppLog("Service is not fixed");
		break;
	default:
		AppLog("Service is undetermined.");
		break;
	}
}

void
ProjectGiraffeMainForm::OnRegionEntered(RegionId regionId)
{

}

void
ProjectGiraffeMainForm::OnRegionLeft(RegionId regionId)
{

}

void
ProjectGiraffeMainForm::OnRegionMonitoringStatusChanged(LocationServiceStatus status)
{

}

void
ProjectGiraffeMainForm::OnAccuracyChanged(LocationAccuracy accuracy)
{

}

void
ProjectGiraffeMainForm::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{
	AppLog("We received an event.");
	if (requestId == 101)
	{
		__currentLocation = static_cast<Location*> (pArgs->GetAt(0));

		if (__currentLocation->IsValid())
		{
			currentLatitude = __currentLocation->GetCoordinates().GetLatitude();
			currentLongitude = __currentLocation->GetCoordinates().GetLongitude();
		}

		AppLog("The latitude is: %f", currentLatitude);

	}
	else if(requestId == 102)
	{

	}

	if(pArgs)
	{
		pArgs->RemoveAll(true);
		delete pArgs;
	}
}

void
ProjectGiraffeMainForm::MainFormParseLocation()
{
	AppLog("Starting location parse");
	__pLocationManagerThread->Start();
	AppLog("Ended location parse");
}

double
ProjectGiraffeMainForm::MainFormGetLatitude()
{
	//Location* loc =__currentLocation;
	//AppLog("Returning latitude: %f", result);
	return 0; //result;
}

bool
ProjectGiraffeMainForm::TestFunction()
{
	return true;
}

	//result res = __pLocProvider->StartLocationUpdatesByInterval(3);
	//Location loc = __pLocProvider->GetLastKnownLocation();


