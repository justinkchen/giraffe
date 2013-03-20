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
	: __pLocProvider(null)
	, __pLocationManagerThread(null)
	, __regionId(-1)
	, __sParser(null)
	, __pUserPopup(null)
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
		AppResource* pAppResource = Application::GetInstance()->GetAppResource();

		Tizen::Graphics::Bitmap* pNearbyBitmap = pAppResource->GetBitmapN(L"74-location.png");
		Tizen::Graphics::Bitmap* pMapBitmap = pAppResource->GetBitmapN(L"73-radar.png");
		Tizen::Graphics::Bitmap* pSpraycanBitmap = pAppResource->GetBitmapN(L"bluespraycan.png");
		Tizen::Graphics::Bitmap* pProfileBitmap = pAppResource->GetBitmapN(L"111-user.png");
		Tizen::Graphics::Bitmap* pSettingsBitmap = pAppResource->GetBitmapN(L"19-gear.png");

		FooterItem footerItem1;
		FooterItem footerItem2;
		FooterItem footerItem3;
		FooterItem footerItem4;
		FooterItem footerItem5;

		footerItem1.Construct(ID_FOOTER_ITEM1);
		footerItem2.Construct(ID_FOOTER_ITEM2);
		footerItem3.Construct(ID_FOOTER_ITEM3);
		footerItem4.Construct(ID_FOOTER_ITEM4);
		footerItem5.Construct(ID_FOOTER_ITEM5);

		footerItem1.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pNearbyBitmap);
		footerItem2.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pMapBitmap);
		footerItem3.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pSpraycanBitmap);
		footerItem4.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pProfileBitmap);
		footerItem5.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pSettingsBitmap);

		pFooter->InsertItemAt(0, footerItem1);
		pFooter->InsertItemAt(1, footerItem2);
		pFooter->InsertItemAt(2, footerItem3);
		pFooter->InsertItemAt(3, footerItem4);
		pFooter->InsertItemAt(4, footerItem5);

		pFooter->AddActionEventListener(*this);

		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,false);
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
	__pLocProvider->StartLocationUpdatesByInterval(10);

	// Initialize UserPopup
	__pUserPopup = new UserPopup();

	__sParser = new SensorParser();

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
	delete __pUserPopup;

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
	Footer* pFooter = GetFooter();
	switch(actionId)
	{
	case ID_FOOTER_ITEM1:
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,false);
		pFooter->SetItemEnabled(1,true);
		pFooter->SetItemEnabled(2,true);
		pFooter->SetItemEnabled(3,true);
		pFooter->SetItemEnabled(4,true);
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_1"));
		pHeader->SetTitleText(L"Nearby Graffiti");
		AppLog("Tab1");
		break;
	case ID_FOOTER_ITEM2:
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,true);
		pFooter->SetItemEnabled(1,false);
		pFooter->SetItemEnabled(2,true);
		pFooter->SetItemEnabled(3,true);
		pFooter->SetItemEnabled(4,true);
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_2"));
		pHeader->SetTitleText(L"Graffiti Map");
		AppLog("Tab2");
		break;
	case ID_FOOTER_ITEM3:
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,true);
		pFooter->SetItemEnabled(1,true);
		pFooter->SetItemEnabled(2,false);
		pFooter->SetItemEnabled(3,true);
		pFooter->SetItemEnabled(4,true);
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_3"));
		pHeader->SetTitleText(L"Post Graffiti");
		AppLog("Tab3");
		break;
	case ID_FOOTER_ITEM4:
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,true);
		pFooter->SetItemEnabled(1,true);
		pFooter->SetItemEnabled(2,true);
		pFooter->SetItemEnabled(3,false);
		pFooter->SetItemEnabled(4,true);
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_4"));
		pHeader->SetTitleText(L"Profile");
		__pUserPopup->ShowPopup();

		AppLog("Tab4");
		break;
	case ID_FOOTER_ITEM5:
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,true);
		pFooter->SetItemEnabled(1,true);
		pFooter->SetItemEnabled(2,true);
		pFooter->SetItemEnabled(3,true);
		pFooter->SetItemEnabled(4,false);
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_5"));
		pHeader->SetTitleText(L"Settings");

		AppLog("THIS IS A GOOD SPOT FOR SENSOR TESTING");
		__sParser->CreateSensor();
		AppLog("Tab5");
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
//	__currentLocation = location;
//	AppLog("Location Assigned.");
//	double d = __currentLocation->GetCoordinates().GetLatitude();
//	AppLog("Current Latitude: %f.", d);
	if (location.IsValid())
	{
		currentLatitude = location.GetCoordinates().GetLatitude();
		currentLongitude = location.GetCoordinates().GetLongitude();
		SceneManager* pSceneManager = SceneManager::GetInstance();
		Scene* pScene = pSceneManager->GetCurrentScene();
		Panel* pPanel = pScene->GetPanel();
		pPanel->SendUserEvent(101, null);
		AppLog("The latitude is: %f", currentLatitude);
		AppLog("The longitude is: %f", currentLongitude);
	}else{
		AppLog("Location not valid");
	}

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
			SceneManager* pSceneManager = SceneManager::GetInstance();
			Scene* pScene = pSceneManager->GetCurrentScene();
			Panel* pPanel = pScene->GetPanel();
			pPanel->SendUserEvent(101, null);
			AppLog("The latitude is: %f", currentLatitude);
			AppLog("The longitude is: %f", currentLongitude);
		}else{
			AppLog("Location not valid");
		}
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


