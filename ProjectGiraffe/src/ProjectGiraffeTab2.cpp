#include "ProjectGiraffeTab2.h"
#include "LocationManagerThread.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Locations;

ProjectGiraffeTab2::ProjectGiraffeTab2(void)
: __pLocationManagerThread(null)
, __pLocProvider(null)
, __regionId(-1)
{

}

ProjectGiraffeTab2::~ProjectGiraffeTab2(void)
{

}

bool
ProjectGiraffeTab2::Initialize(void)
{
	result r = Construct(L"IDC_PANEL2");
	if (IsFailed(r))
		return false;

	return true;
}

result
ProjectGiraffeTab2::OnInitializing(void)
{
	result r = E_SUCCESS;

	// Layout setting
	const Form* pForm = dynamic_cast<Form*>(GetParent());
	RelativeLayout* pRelativeLayout = dynamic_cast<RelativeLayout*>(pForm->GetLandscapeLayoutN());
	pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
	pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
	delete pRelativeLayout;
	pRelativeLayout = dynamic_cast<RelativeLayout*>(pForm->GetPortraitLayoutN());
	pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
	pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
	delete pRelativeLayout;

	Label *pLabel1 = static_cast<Label *>(GetControl(L"IDC_LABEL1"));  
	if(pLabel1)
	{
		pLabel1->AddTouchEventListener(*this);
	}

	__pLocationManagerThread =  new (std::nothrow) LocationManagerThread();
	res = __pLocationManagerThread->Construct(*this);
	if (IsFailed(res))
	{
		AppLog("Thread Construct failed.");
		return res;
	}


	return r;
}

result
ProjectGiraffeTab2::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
ProjectGiraffeTab2::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO:
	// Add your scene activate code here
	AppLog("OnSceneActivatedN");
}

void
ProjectGiraffeTab2::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
}

void
ProjectGiraffeTab2::OnTouchDoublePressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeTab2::OnTouchFocusIn(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeTab2::OnTouchFocusOut(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeTab2::OnTouchLongPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeTab2::OnTouchMoved(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeTab2::OnTouchPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
{
	// TODO: Add your implementation codes here
	AppLog("It got pressed");
	Label *pLabel1 = static_cast<Label *>(GetControl(L"IDC_LABEL1"));
	Tizen::Base::String output = pLabel1->GetText();
	Tizen::Base::String str = L"test";
	AppLog("String: %ls", output.GetPointer());


	pLabel1->SetText(L"DID I CLICK?");
	pLabel1->Draw();

}

void
ProjectGiraffeTab2::OnTouchReleased(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
{
	// TODO: Add your implementation codes here

}


void
ProjectGiraffeTab2::OnLocationUpdated(const Tizen::Locations::Location& location)
{

}

void
ProjectGiraffeTab2::OnLocationUpdateStatusChanged(LocationServiceStatus status)
{

}

void
ProjectGiraffeTab2::OnRegionEntered(RegionId regionId)
{

}

void
ProjectGiraffeTab2::OnRegionLeft(RegionId regionId)
{

}

void
ProjectGiraffeTab2::OnRegionMonitoringStatusChanged(LocationServiceStatus status)
{

}

void
ProjectGiraffeTab2::OnAccuracyChanged(LocationAccuracy accuracy)
{

}
