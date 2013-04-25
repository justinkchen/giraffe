#include "ProjectGiraffeTab3.h"
#include "ProjectGiraffeMainForm.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Web::Controls;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;
using namespace Tizen::Base::Utility;

ProjectGiraffeTab3::~ProjectGiraffeTab3(void)
{

}

bool
ProjectGiraffeTab3::Initialize(void)
{
	result r = Construct(L"IDC_PANEL3");
	if (IsFailed(r))
		return false;

	return true;
}

result
ProjectGiraffeTab3::OnInitializing(void)
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

	pRelativeLayout = dynamic_cast<RelativeLayout*>(pForm->GetPortraitLayoutN());

	double latitude = ProjectGiraffeMainForm::currentLatitude;
	double longitude = ProjectGiraffeMainForm::currentLongitude;
	AppLog("Latitude is now: %f", latitude);
	AppLog("Longitude is now: %f", longitude);
	Tizen::Base::Double* dublat = new Tizen::Base::Double(latitude);
	Tizen::Base::Double* dublong = new Tizen::Base::Double(longitude);

    // Creates an instance of EditArea
    _messageArea = new EditArea();
    _messageArea->Construct(Rectangle(50, 100, pForm->GetClientAreaBounds().width-100, 200), INPUT_STYLE_OVERLAY, 300);
    _messageArea->SetKeypadAction(KEYPAD_ACTION_DONE);
    _messageArea->AddKeypadEventListener(*this);
    _messageArea->AddTextEventListener(*this);
    AddControl(*_messageArea);

    // Creates an instance of Label
    _messageLabel = new Label();
    _messageLabel->Construct(Rectangle(50, 50, pForm->GetClientAreaBounds().width-100, 50),L"Graffiti Message:");
    AddControl(*_messageLabel);

    _addGraffitiWebView = new Web();
    _addGraffitiWebView->Construct(Rectangle(50, 350, pForm->GetClientAreaBounds().width-100, 250));
    String url = "http://ec2-54-243-69-6.compute-1.amazonaws.com/addgraffiti_map.html?latitude=" + dublat->ToString() + "&longitude=" + dublong->ToString();
    _addGraffitiWebView->SetLoadingListener(this);
    AddControl(*_addGraffitiWebView);

    _addGraffitiWebView->LoadUrl(GetValidUrl(url));

    // Creates an instance of Slider
    _radiusSlider = new Slider();
    _radiusSlider->Construct(Rectangle(0, 600, pForm->GetClientAreaBounds().width, 200), BACKGROUND_STYLE_NONE, true, 10, 300);
    _radiusSlider->SetTitleText(L"Radius of post (in meters):");
    _radiusSlider->SetValue(50);
    _radiusSlider->AddAdjustmentEventListener(*this);
    AddControl(*_radiusSlider);

	// Creates an instance of Button
	_submitButton = new Button();
	int submitButtonW = 400;
	int submitButtonH = 100;
	_submitButton->Construct(Rectangle((pForm->GetClientAreaBounds().width-submitButtonW)/2, 850, submitButtonW, submitButtonH), L"Post Graffiti");
	_submitButton->SetActionId(ID_BUTTON);
	_submitButton->AddActionEventListener(*this);
	AddControl(*_submitButton);

//    pRelativeLayout->SetCenterAligned(*_messageArea, CENTER_ALIGN_HORIZONTAL);
//    pRelativeLayout->SetCenterAligned(*_messageLabel, CENTER_ALIGN_HORIZONTAL);
//    pRelativeLayout->SetCenterAligned(*_addGraffitiWebView, CENTER_ALIGN_HORIZONTAL);
//    pRelativeLayout->SetCenterAligned(*_radiusSlider, CENTER_ALIGN_HORIZONTAL);
//    pRelativeLayout->SetCenterAligned(*_submitButton, CENTER_ALIGN_HORIZONTAL);

    delete pRelativeLayout;

	return r;
}

result
ProjectGiraffeTab3::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
ProjectGiraffeTab3::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
		const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO:
	// Add your scene activate code here
	AppLog("OnSceneActivatedN");
}

void
ProjectGiraffeTab3::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
}

void
ProjectGiraffeTab3::OnTransactionAborted (HttpSession &httpSession, HttpTransaction &httpTransaction, result r)
{
	AppLog("HTTP Transaction Aborted");

	MessageBox msgBox;
	msgBox.Construct(L"HTTP STATUS", L"HTTP Request Aborted", MSGBOX_STYLE_NONE, 3000);
	int modalresult = 0;
	msgBox.ShowAndWait(modalresult);
}

void
ProjectGiraffeTab3::OnTransactionCertVerificationRequiredN (HttpSession &httpSession, HttpTransaction &httpTransaction, Tizen::Base::String *pCert)
{

}

void
ProjectGiraffeTab3::OnTransactionCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction)
{
	AppLog("HTTP Transaction Completed");
}

void
ProjectGiraffeTab3::OnTransactionHeaderCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired)
{

}

void
ProjectGiraffeTab3::OnTransactionReadyToRead (HttpSession &httpSession, HttpTransaction &httpTransaction, int availableBodyLen)
{
	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	HttpHeader* pHttpHeader = null;
	AppLog("Checking HTTP Status Code");
	if (true || pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
	{
		ByteBuffer* pBody = null;
		String statusText = pHttpResponse->GetStatusText();
		String version = pHttpResponse->GetVersion();

		pHttpHeader = pHttpResponse->GetHeader();
		pBody = pHttpResponse->ReadBodyN();
		//delete pBody;

		WcharBuffer* charBuffer = pBody->AsWcharBufferN();
		String pString;
		wchar_t value;
		for (int i = 0; i < availableBodyLen; i++)
		{
			charBuffer->Get(value);
			pString.Append(value);
		}
		String out;
		pString.SubString(0, availableBodyLen, out);
		AppLog("Response body: %s",out.GetPointer());
		//		//Parses from ByteBuffer
		//		IJsonValue* pValue = JsonParser::ParseN(*pBody);
		//
		//		// Converts the pValue to JsonObject
		//		JsonObject* pJsonObject = static_cast<JsonObject*>(pValue);
		//
		//		AppLog("Received HTTP response.");
		//		// Populate the panel
		//
		//		pJsonObject->RemoveAll(true);
		//		delete pJsonObject;
		delete pBody;
		MessageBox msgBox;
		msgBox.Construct(L"Success", L"Graffiti successfully posted!", MSGBOX_STYLE_OK , 0);
		int modalresult = 0;
		msgBox.ShowAndWait(modalresult);
		_messageArea->SetText(L"");
		_messageArea->Draw();
	}else{
		AppLog("HTTP Status not OK");
	}
}

void
ProjectGiraffeTab3::OnTransactionReadyToWrite (HttpSession &httpSession, HttpTransaction &httpTransaction, int recommendedChunkSize)
{

}

// IActionEventListener implementation
void
ProjectGiraffeTab3::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_BUTTON:
	{
		/*
		HttpSession* pHttpSession = null;
		HttpTransaction* pHttpTransaction = null;
		String* pProxyAddr = null;
		String hostAddr = L"http://ec2-54-243-69-6.compute-1.amazonaws.com";
		String uri = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/graffiti/new";

		AppLog("Starting the HTTP Session");
		pHttpSession = new HttpSession();

		// HttpSession construction.
		pHttpSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, pProxyAddr, hostAddr, null);

		// Open a new HttpTransaction.
		pHttpTransaction = pHttpSession->OpenTransactionN();

		// Add a listener.
		pHttpTransaction->AddHttpTransactionListener(*this);

		// Get an HTTP request.
		HttpRequest* pHttpRequest = pHttpTransaction->GetRequest();

		// Set the HTTP method and URI:
		pHttpRequest->SetMethod(NET_HTTP_METHOD_POST);
		pHttpRequest->SetUri(uri);
		*/

		// Set POST body

		HttpMultipartEntity* graffitiParameters = new HttpMultipartEntity();
		graffitiParameters->Construct();
		String message = _messageArea->GetText();
		String latitude;
		latitude.Append(ProjectGiraffeMainForm::currentLatitude);
		String longitude;
		longitude.Append(ProjectGiraffeMainForm::currentLongitude);
		String radius;
		radius.Append(_radiusSlider->GetValue());

		graffitiParameters->AddStringPart(L"message", message);
		graffitiParameters->AddStringPart(L"latitude", latitude);
		graffitiParameters->AddStringPart(L"longitude", longitude);
		graffitiParameters->AddStringPart(L"radius", radius);

		Graffiti *g = new Graffiti();
		g->setText(_messageArea->GetText());
		g->setLatitude(ProjectGiraffeMainForm::currentLatitude);
		g->setLongitude(ProjectGiraffeMainForm::currentLongitude);
		g->setRadius(_radiusSlider->GetValue());

		HttpConnection *connection = HttpConnection::graffitiNewPostConnection(this, graffitiParameters);
		AppLogTag("user", "asdf");
		connection->begin();
		/*
		String userId = L"";
		userId.Append((int)User::currentUser()->id());
		pHttpUrlEncodedEntity->AddParameter(L"userId", userId);
		pHttpRequest->SetEntity(*pHttpUrlEncodedEntity);

		// Submit the request:
		if(message.GetLength() == 0){
			MessageBox msgBox;
			msgBox.Construct(L"Error", L"Graffiti can't be empty!", MSGBOX_STYLE_OK , 0);
			int modalresult = 0;
			msgBox.ShowAndWait(modalresult);
		}else{
			pHttpTransaction->Submit();
		}
		*/
	}
	break;
	default:
		break;
	}
}

// ITextEventListener implementation
void
ProjectGiraffeTab3::OnTextValueChanged(const Tizen::Ui::Control& source)
{
    // ....
}

void
ProjectGiraffeTab3::OnTextValueChangeCanceled(const Tizen::Ui::Control& source)
{
    // ....
}

// IAdjustmentEventListener implementation
void
ProjectGiraffeTab3::OnAdjustmentValueChanged(const Control& source, int adjustment)
{
	Tizen::Base::Integer* newRadius = new Tizen::Base::Integer(adjustment);
    _addGraffitiWebView->EvaluateJavascriptN(L"updateRadius(" + newRadius->ToString() + ");");
}

String
ProjectGiraffeTab3::GetValidUrl(Tizen::Base::String& url)
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
ProjectGiraffeTab3::OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication)
{
	AppLog("OnHttpAuthenticationRequested");
	return false;
}

void
ProjectGiraffeTab3::OnHttpAuthenticationCanceled(void)
{
	AppLog("OnHttpAuthenticationCanceled");
}

void
ProjectGiraffeTab3::OnLoadingStarted(void)
{
	AppLog("OnLoadingStarted");
}

void
ProjectGiraffeTab3::OnLoadingCanceled(void)
{
	AppLog("OnLoadingCanceled");
}

void
ProjectGiraffeTab3::OnLoadingErrorOccurred(LoadingErrorType error, const String& reason)
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
ProjectGiraffeTab3::OnLoadingCompleted(void)
{
	AppLog("OnLoadingCompleted");
}

void
ProjectGiraffeTab3::OnEstimatedProgress(int progress)
{
}

void
ProjectGiraffeTab3::OnPageTitleReceived(const Tizen::Base::String& title)
{
}

bool
ProjectGiraffeTab3::OnLoadingRequested(const Tizen::Base::String& url, WebNavigationType type)
{
	AppLog("%S",url.GetPointer());
	return false;
}



DecisionPolicy
ProjectGiraffeTab3::OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header)
{
	return WEB_DECISION_CONTINUE;
}

void
ProjectGiraffeTab3::OnKeypadActionPerformed(Control &source, KeypadAction keypadAction)
{
	// Hide keypad when the action button is clicked
	if (keypadAction == KEYPAD_ACTION_DONE)
	{
		((EditArea *)&source)->HideKeypad();
	}
}

void
ProjectGiraffeTab3::OnKeypadBoundsChanged(Control &source)
{

}

void
ProjectGiraffeTab3::OnKeypadClosed(Control &source)
{

}

void
ProjectGiraffeTab3::OnKeypadOpened(Control &source)
{

}

void
ProjectGiraffeTab3::OnKeypadWillOpen(Control &source)
{

}

void
ProjectGiraffeTab3::connectionDidFinish(HttpConnection *connection, HashMap *response)
{
	AppLogTag("user", "HttpConnection finished");
	if (response) {

	} else {
		connectionDidFail(connection);
	}
}

void
ProjectGiraffeTab3::connectionDidFail(HttpConnection *connection)
{
	AppLogTag("user", "failed");
	delete connection;
}
