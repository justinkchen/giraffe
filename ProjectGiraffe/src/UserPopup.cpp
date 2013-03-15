/*
 * UserPopup.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: bryancheng
 */

#include "UserPopup.h"
#include <FGraphics.h>

using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;

UserPopup::UserPopup() {
	// TODO Auto-generated constructor stub

}

UserPopup::~UserPopup() {
	// TODO Auto-generated destructor stub
}

result
UserPopup::OnInitializing(void)
{
	result r = E_SUCCESS;

	// Creates an instance of Popup
	__pPopup = new Popup();
	__pPopup->Construct(true, Dimension(600,800));
	__pPopup->SetTitleText(L"Log In");

	// Creates an instance of Button to close the popup.
	Button* pCloseButton = new Button();
	pCloseButton->Construct(Rectangle(10, 10, 250, 80), L"Close Popup");
	pCloseButton->SetActionId(ID_BUTTON_CLOSE_POPUP);
	pCloseButton->AddActionEventListener(*this);

	// Adds the button to the popup
	__pPopup->AddControl(*pCloseButton);

	// Creates an instance of Button to open the popup.
	Button* pOpenButton = new Button();
	pOpenButton->Construct(Rectangle(10, 10, 250, 60), L"Open Popup");
	pOpenButton->SetActionId(ID_BUTTON_OPEN_POPUP);
	pOpenButton->AddActionEventListener(*this);

	// Adds the button to the form
	AddControl(*pOpenButton);

	return r;
}

void
UserPopup::ShowPopup(void)
{
	SetShowState(true);
	Show();
}

void
UserPopup::HidePopup(void)
{
	SetShowState(false);
	Invalidate(true);
}

void
UserPopup::ShowLogin(void)
{
	RemoveAllControls();

	// add username / email field
	// add password field
	// add submit button

	// add close/skip button
	// add signup button
}

void
UserPopup::ShowSignup(void)
{
	RemoveAllControls();

	// add name field?
	// add username field
	// add email field
	// add password field
	// add confirm password field
	// add submit field

	// add close/skip button
	// add login button
}

void
UserPopup::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_BUTTON_OPEN_POPUP:
		{
			ShowPopup();
		}
		break;
	case ID_BUTTON_CLOSE_POPUP:
		{
			HidePopup();
		}
		break;
	default:
		break;
	}
}

void
UserPopup::OnTransactionAborted (HttpSession &httpSession, HttpTransaction &httpTransaction, result r)
{

}

void
UserPopup::OnTransactionCertVerificationRequiredN (HttpSession &httpSession, HttpTransaction &httpTransaction, Tizen::Base::String *pCert)
{

}

void
UserPopup::OnTransactionCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction)
{

}

void
UserPopup::OnTransactionHeaderCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired)
{

}

void
UserPopup::OnTransactionReadyToRead (HttpSession &httpSession, HttpTransaction &httpTransaction, int availableBodyLen)
{
	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	HttpHeader* pHttpHeader = null;
	AppLog("Checking HTTP Status Code");
	if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
	{
		ByteBuffer* pBody = null;
		String statusText = pHttpResponse->GetStatusText();
		String version = pHttpResponse->GetVersion();

		pHttpHeader = pHttpResponse->GetHeader();
		pBody = pHttpResponse->ReadBodyN();
		//delete pBody;

		//Parses from ByteBuffer
		IJsonValue* pValue = JsonParser::ParseN(*pBody);

		// Converts the pValue to JsonObject
		JsonObject* pJsonObject = static_cast<JsonObject*>(pValue);

		AppLog("Received HTTP response.");

		TraverseFunction(pValue);

		pJsonObject->RemoveAll(true);
		delete pJsonObject;
		delete pBody;
//		delete pValue;
	}else{
		AppLog("HTTP Status not OK");
	}
}

void
UserPopup::OnTransactionReadyToWrite (HttpSession &httpSession, HttpTransaction &httpTransaction, int recommendedChunkSize)
{

}
