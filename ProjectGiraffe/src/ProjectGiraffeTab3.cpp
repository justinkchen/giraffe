#include "ProjectGiraffeTab3.h"
#include "ProjectGiraffeMainForm.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

using namespace Tizen::Base;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;

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

	// Creates an instance of Button
	__pButton = new Button();
	int submitButtonW = 500;
	int submitButtonH = 150;
	__pButton->Construct(Rectangle((pForm->GetClientAreaBounds().width-submitButtonW)/2, 700, submitButtonW, submitButtonH), L"Post Graffiti");
	__pButton->SetActionId(ID_BUTTON);
	__pButton->AddActionEventListener(*this);
	AddControl(*__pButton);

    // Creates an instance of EditArea
    __pEditArea = new EditArea();
    __pEditArea->Construct(Rectangle(50, 100, pForm->GetClientAreaBounds().width-100, 300));
    __pEditArea->AddTextEventListener(*this);
    AddControl(*__pEditArea);

    // Creates an instance of Label
    __pEditAreaLabel = new Label();
    __pEditAreaLabel->Construct(Rectangle(50, 50, pForm->GetClientAreaBounds().width-100, 50),L"Graffiti Message:");
    AddControl(*__pEditAreaLabel);

    // Creates an instance of Slider
    __pSlider = new Slider();
    __pSlider->Construct(Rectangle(0, 450, pForm->GetClientAreaBounds().width, 200), BACKGROUND_STYLE_DEFAULT, true, 5, 500);
    __pSlider->SetTitleText(L"Radius of post (in meters):");
    __pSlider->SetValue(25);
    __pSlider->AddAdjustmentEventListener(*this);
    AddControl(*__pSlider);

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
		__pEditArea->SetText(L"");
		__pEditArea->Draw();
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
		HttpSession* pHttpSession = null;
		HttpTransaction* pHttpTransaction = null;
		String* pProxyAddr = null;
		String hostAddr = L"http://ec2-54-243-69-6.compute-1.amazonaws.com";
		String uri = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/addgraffiti";

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

		// Set POST body
		HttpUrlEncodedEntity* pHttpUrlEncodedEntity = new HttpUrlEncodedEntity();
		pHttpUrlEncodedEntity->Construct();
		String message = __pEditArea->GetText();
		String latitude;
		latitude.Append(ProjectGiraffeMainForm::currentLatitude);
		String longitude;
		longitude.Append(ProjectGiraffeMainForm::currentLongitude);
		String radius;
		radius.Append(__pSlider->GetValue());


		pHttpUrlEncodedEntity->AddParameter(L"message", message);
		pHttpUrlEncodedEntity->AddParameter(L"latitude", latitude);
		pHttpUrlEncodedEntity->AddParameter(L"longitude", longitude);
		pHttpUrlEncodedEntity->AddParameter(L"radius", radius);
		pHttpUrlEncodedEntity->AddParameter(L"userid", L"1");
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
    // ....
}
