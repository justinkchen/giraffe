#include "ProjectGiraffeTab2.h"
#include "ProjectGiraffeMainForm.h"
#include "LocationManagerThread.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Locations;


ProjectGiraffeTab2::ProjectGiraffeTab2(void)
: pLabel1(null)
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


//	pLabel1 = static_cast<Label *>(GetControl(L"IDC_LABEL1"));
//	if(pLabel1)
//	{
//		pLabel1->AddTouchEventListener(*this);
//	}
	// Creates an instance of Label
	pLabellat = new Label();
	pLabellat->Construct(Rectangle(0, 0, 500, 50), L"Obtaining Location...");
	pLabellat->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pLabellat->SetTextConfig(30, LABEL_TEXT_STYLE_BOLD);
	pLabellong = new Label();
	pLabellong->Construct(Rectangle(0, 50, 500, 50), L"");
	pLabellong->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pLabellong->SetTextConfig(30, LABEL_TEXT_STYLE_BOLD);

	// Adds the label to the form
	//AddControl(*__pLabel);
	AddControl(*pLabellat);
	AddControl(*pLabellong);
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
//	double latitude = ProjectGiraffeMainForm::currentLatitude;
//	double longitude = ProjectGiraffeMainForm::currentLongitude;
//	AppLog("Latitude is now: %f", latitude);
//	AppLog("Longitude is now: %f", longitude);
//	Tizen::Base::Double* dublat = new Tizen::Base::Double(latitude);
//	Tizen::Base::Double* dublong = new Tizen::Base::Double(longitude);
//	pLabellat->SetText(dublat->ToString());
//	pLabellong->SetText(dublong->ToString());

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

}

void
ProjectGiraffeTab2::OnTouchReleased(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeTab2::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{
	AppLogDebug("We received an event.");
	if (requestId == 101)
	{
		double latitude = ProjectGiraffeMainForm::currentLatitude;
		double longitude = ProjectGiraffeMainForm::currentLongitude;
		AppLog("Latitude is now: %f", latitude);
		AppLog("Longitude is now: %f", longitude);
		Tizen::Base::Double* dublat = new Tizen::Base::Double(latitude);
		Tizen::Base::Double* dublong = new Tizen::Base::Double(longitude);
		pLabellat->SetText(L"Location Found");
		pLabellat->Draw();
		pLabellong->SetText(dublat->ToString() + L", " + dublong->ToString());
		pLabellong->Draw();
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




