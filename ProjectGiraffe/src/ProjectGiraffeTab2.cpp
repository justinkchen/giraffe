#include "ProjectGiraffeTab2.h"
#include "ProjectGiraffeMainForm.h"
#include "LocationManagerThread.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Locations;
using namespace Tizen::Web::Controls;
using namespace Tizen::Base;
using namespace Tizen::Base::Utility;

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

	locationFound = false;

	// Adds the label to the form
	//AddControl(*__pLabel);
	AddControl(*pLabellat);
	AddControl(*pLabellong);

	__pWeb = new Web();
	__pWeb->Construct(Rectangle(0, 100, pForm->GetClientAreaBounds().width, pForm->GetClientAreaBounds().height-100));
//	String url = "http://ec2-54-243-69-6.compute-1.amazonaws.com/maps.html";
//	__pWeb->LoadUrl(GetValidUrl(url));
	__pWeb->SetLoadingListener(this);
	AddControl(*__pWeb);
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

//	String url = "http://ec2-54-243-69-6.compute-1.amazonaws.com/maps.html";
//	__pWeb->LoadUrl(GetValidUrl(url));
//	SceneManager* pSceneManager = SceneManager::GetInstance();
//	Scene* pScene = pSceneManager->GetCurrentScene();
//	Panel* pPanel = pScene->GetPanel();
//	pPanel->RequestRedraw(true);
//	AppLog("OnSceneActivatedN");
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
	if(!locationFound){
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
			locationFound = true;

			String url = "http://ec2-54-243-69-6.compute-1.amazonaws.com/graffitimap.html?latitude=" + dublat->ToString() + "&longitude=" + dublong->ToString();

			__pWeb->LoadUrl(GetValidUrl(url));
			SceneManager* pSceneManager = SceneManager::GetInstance();
			Form* pForm = pSceneManager->GetCurrentScene()->GetForm();
			pForm->RequestRedraw(true);
		}
		else if(requestId == 102)
		{

		}
	}
	if(pArgs)
	{
		pArgs->RemoveAll(true);
		delete pArgs;
	}
}

String
ProjectGiraffeTab2::GetValidUrl(Tizen::Base::String& url)
{
	String absoluteUrl = url;
	Uri uri;

	uri.SetUri(url);
	if (uri.GetScheme() == L"")
	{
		absoluteUrl.Insert(L"http://", 0);
	}
	return absoluteUrl;
}

bool
ProjectGiraffeTab2::OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication)
{
	return false;
}

void
ProjectGiraffeTab2::OnHttpAuthenticationCanceled(void)
{
}

void
ProjectGiraffeTab2::OnLoadingStarted(void)
{
}

void
ProjectGiraffeTab2::OnLoadingCanceled(void)
{
}

void
ProjectGiraffeTab2::OnLoadingErrorOccurred(LoadingErrorType error, const String& reason)
{
	Tizen::Ui::Controls::MessageBox msgBox;
	int modalresult = 0;
	Tizen::Base::String errReason;

	switch (error)
	{
	case WEB_REQUEST_TIMEOUT:
	{
		errReason = Tizen::Base::String(L"Request timeout");
	}
	break;

	case WEB_NO_CONNECTION:
	{
		errReason = Tizen::Base::String(L"Network is not in service");
	}
	break;

	case WEB_MIME_NOT_SUPPORTED:
	{
		errReason = Tizen::Base::String(L"The content type is not supported");
	}
	break;

	case WEB_BAD_URL:
	{
		errReason = Tizen::Base::String(L"The url is invalid");
	}
	break;

	case WEB_HTTP_RESPONSE:
	{
		errReason = Tizen::Base::String(L"HTTP response");
	}
	break;

	case WEB_OUT_OF_MEMORY:
	{
		errReason = Tizen::Base::String(L"Page Too Large");
	}
	break;

	case WEB_REQUEST_MAX_EXCEEDED:
	{
		errReason = Tizen::Base::String(L"Request Max Exceeded");
	}
	break;

	case WEB_ERROR_UNKNOWN:
	default:
	{
		errReason = Tizen::Base::String(L"An Unknown error");
	}
	break;
	}

	msgBox.Construct(L"LOADING ERROR TYPE", errReason, MSGBOX_STYLE_NONE, 3000);
	msgBox.ShowAndWait(modalresult);
}

void
ProjectGiraffeTab2::OnLoadingCompleted(void)
{
}

void
ProjectGiraffeTab2::OnEstimatedProgress(int progress)
{
}

void
ProjectGiraffeTab2::OnPageTitleReceived(const Tizen::Base::String& title)
{
}

bool
ProjectGiraffeTab2::OnLoadingRequested(const Tizen::Base::String& url, WebNavigationType type)
{
	AppLog("%S",url.GetPointer());
	return false;
}



DecisionPolicy
ProjectGiraffeTab2::OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header)
{
	return WEB_DECISION_CONTINUE;
}




