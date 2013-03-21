/*
 * UserPopup.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: bryancheng
 */

#include "UserPopup.h"
#include <FGraphics.h>

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;

UserPopup::UserPopup() {
	// TODO Auto-generated constructor stub

	Construct(true, Dimension(600,800));

	ShowLogin();
}

UserPopup::~UserPopup() {
	// TODO Auto-generated destructor stub
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

	SetTitleText(L"Log In");

	// Username / email edit field
	EditField* usernameEmailField = new EditField();
	usernameEmailField->Construct(Rectangle(0, 10, 580, 120), EDIT_FIELD_STYLE_EMAIL, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	usernameEmailField->SetTitleText("Username or Email");
	usernameEmailField->SetName("usernameEmailField");
	usernameEmailField->SetKeypadAction(KEYPAD_ACTION_DONE);
	usernameEmailField->AddKeypadEventListener(*this);
	AddControl(*usernameEmailField);

	// Password edit field
	EditField* passwordField = new EditField();
	passwordField->Construct(Rectangle(0, 140, 580, 120), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	passwordField->SetTitleText("Password");
	passwordField->SetName("passwordField");
	passwordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	passwordField->AddKeypadEventListener(*this);
	AddControl(*passwordField);

	// Submit button to log in
	Button* loginButton = new Button();
	loginButton->Construct(Rectangle(130, 530, 300, 80), L"Log In");
	loginButton->SetName("loginButton");
	loginButton->SetActionId(ID_BUTTON_LOGIN);
	loginButton->AddActionEventListener(*this);
	AddControl(*loginButton);

	// Close button to close popup
	Button* closeButton = new Button();
	closeButton->Construct(Rectangle(130, 620, 300, 80), L"Close");
	closeButton->SetName("closeButton");
	closeButton->SetActionId(ID_BUTTON_CLOSE_POPUP);
	closeButton->AddActionEventListener(*this);
	AddControl(*closeButton);

	// Signup button to show signup page
	// Don't have an account?
	Button* signupLink = new Button();
	signupLink->Construct(Rectangle(310, -60, 250, 50), L"Sign Up");
	Color *c = new Color(5555);
	Bitmap *b = new Bitmap();
	b->Construct(signupLink->GetBounds());
	b->SetAlphaConstant(255);
	b->SetMaskingColor(c);
//	signupLink->SetNormalBitmap(*b);
	signupLink->SetNormalBackgroundBitmap(*b);
//	signupLink->SetPressedBitmap();
//	signedLink->SetPressedBackgorundBitmap();

	signupLink->SetHighlightedTextColor(*c);
//	signupLink->SetPressedTextColor(*c);
	signupLink->SetActionId(ID_BUTTON_VIEW_SIGNUP);
	signupLink->AddActionEventListener(*this);
	AddControl(*signupLink);

	// Error Label
	Label* errorLabel = new Label();
	errorLabel->Construct(Rectangle(-10, -130, 600, 40), L"");
	errorLabel->SetTextColor(Color(0xFF, 0x00, 0x00));
	errorLabel->SetName("errorLabel");
	AddControl(*errorLabel);

	Draw();
}

void
UserPopup::ShowSignup(void)
{
	RemoveAllControls();

	SetTitleText(L"Sign Up");

	// Username edit field
	EditField* usernameField = new EditField();
	usernameField->Construct(Rectangle(0, 10, 580, 120), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	usernameField->SetTitleText("Username");
	usernameField->SetName("usernameField");
	usernameField->SetKeypadAction(KEYPAD_ACTION_DONE);
	usernameField->AddKeypadEventListener(*this);
	AddControl(*usernameField);

	// Email edit field
	EditField* emailField = new EditField();
	emailField->Construct(Rectangle(0, 140, 580, 120), EDIT_FIELD_STYLE_EMAIL, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	emailField->SetTitleText("Email");
	emailField->SetName("emailField");
	emailField->SetKeypadAction(KEYPAD_ACTION_DONE);
	emailField->AddKeypadEventListener(*this);
	AddControl(*emailField);

	// Password edit field
	EditField* passwordField = new EditField();
	passwordField->Construct(Rectangle(0, 270, 580, 120), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	passwordField->SetTitleText("Password");
	passwordField->SetName("passwordField");
	passwordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	passwordField->AddKeypadEventListener(*this);
	AddControl(*passwordField);

	// Password confirmation edit field
	EditField* passwordConfirmField = new EditField();
	passwordConfirmField->Construct(Rectangle(0, 400, 580, 120), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	passwordConfirmField->SetTitleText("Confirm Password");
	passwordConfirmField->SetName("passwordConfirmField");
	passwordConfirmField->SetKeypadAction(KEYPAD_ACTION_DONE);
	passwordConfirmField->AddKeypadEventListener(*this);
	AddControl(*passwordConfirmField);

	// Submit button to sign up
	Button* signupButton = new Button();
	signupButton->Construct(Rectangle(130, 530, 300, 80), L"Sign Up");
	signupButton->SetName("signupButton");
	signupButton->SetActionId(ID_BUTTON_SIGNUP);
	signupButton->AddActionEventListener(*this);
	AddControl(*signupButton);

	/// Close button to close popup
	Button* closeButton = new Button();
	closeButton->Construct(Rectangle(130, 620, 300, 80), L"Close");
	closeButton->SetName("closeButton");
	closeButton->SetActionId(ID_BUTTON_CLOSE_POPUP);
	closeButton->AddActionEventListener(*this);
	AddControl(*closeButton);

	// Login button to show login page
	// Already have an account?
	Button* loginLink = new Button();
	loginLink->Construct(Rectangle(310, -60, 250, 50), L"Log In");
	Color *c = new Color(5555);
	Bitmap *b = new Bitmap();
	b->Construct(loginLink->GetBounds());
	b->SetAlphaConstant(255);
	b->SetMaskingColor(c);
	//	loginLink->SetNormalBitmap(*b);
	loginLink->SetNormalBackgroundBitmap(*b);
	//	loginLink->SetPressedBitmap();
	//	loginLink->SetPressedBackgorundBitmap();

	loginLink->SetHighlightedTextColor(*c);
	//	loginLink->SetPressedTextColor(*c);
	loginLink->SetActionId(ID_BUTTON_VIEW_LOGIN);
	loginLink->AddActionEventListener(*this);
	AddControl(*loginLink);

	// Error Label
	Label* errorLabel = new Label();
	errorLabel->Construct(Rectangle(-10, -130, 600, 40), L"");
	errorLabel->SetTextColor(Color(0xFF, 0x00, 0x00));
	errorLabel->SetName("errorLabel");
	AddControl(*errorLabel);

	Draw();
}

void
UserPopup::SubmitLogin(void)
{
	// Disable login button
	Button* loginButton = (Button *)GetControl("loginButton");
	loginButton->SetEnabled(false);
	loginButton->SetText("Logging in...");

	HttpSession* pHttpSession = null;
	HttpTransaction* pHttpTransaction = null;
	String* pProxyAddr = null;
	String hostAddr = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/"; // TODO: convert to HTTPS
	String uri = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/login";

	AppLog("Starting the HTTP Session");
	pHttpSession = new HttpSession();

	// HttpSession construction.
	pHttpSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, pProxyAddr, hostAddr, null);

	// Open a new HttpTransaction.
	pHttpTransaction = pHttpSession->OpenTransactionN(); //TODO: figure out NET_HTTP_AUTH_WWW_BASIC

	// Add a listener.
	pHttpTransaction->AddHttpTransactionListener(*this);

	// Get an HTTP request.
	HttpRequest* pHttpRequest = pHttpTransaction->GetRequest();

	// Set the HTTP method and URI:
	pHttpRequest->SetMethod(NET_HTTP_METHOD_POST);
	pHttpRequest->SetUri(uri);

	// Create HTTP multipart entity
	HttpMultipartEntity* pMultipartEntity = new HttpMultipartEntity();
	pMultipartEntity->Construct();
	String usernameEmail = ((EditField *)GetControl("usernameEmailField"))->GetText();
	pMultipartEntity->AddStringPart(L"usernameEmail", usernameEmail);
	String password = ((EditField *)GetControl("passwordField"))->GetText();
	pMultipartEntity->AddStringPart(L"password", password);

	pHttpRequest->SetEntity(*pMultipartEntity);

	// Submit the request:
	pHttpTransaction->Submit();
}

void
UserPopup::SubmitSignup(void)
{
	// Disable signup button
	Button* signupButton = (Button *)GetControl("signupButton");
	signupButton->SetEnabled(false);
	signupButton->SetText("Signing up...");

	HttpSession* pHttpSession = null;
	HttpTransaction* pHttpTransaction = null;
	String* pProxyAddr = null;
	String hostAddr = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/";
	String uri = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/signup";

	AppLog("Starting the HTTP Session");
	pHttpSession = new HttpSession();

	// HttpSession construction.
	pHttpSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, pProxyAddr, hostAddr, null);

	// Open a new HttpTransaction.
	pHttpTransaction = pHttpSession->OpenTransactionN(); //TODO: figure out NET_HTTP_AUTH_WWW_BASIC

	// Add a listener.
	pHttpTransaction->AddHttpTransactionListener(*this);

	// Get an HTTP request.
	HttpRequest* pHttpRequest = pHttpTransaction->GetRequest();

	// Set the HTTP method and URI:
	pHttpRequest->SetMethod(NET_HTTP_METHOD_POST);
	pHttpRequest->SetUri(uri);

	// Create HTTP multipart entity
	HttpMultipartEntity* pMultipartEntity = new HttpMultipartEntity();
	pMultipartEntity->Construct();
	String username = ((EditField *)GetControl("usernameField"))->GetText();
	pMultipartEntity->AddStringPart(L"username", username);
	String email = ((EditField *)GetControl("emailField"))->GetText();
	pMultipartEntity->AddStringPart(L"email", email);
	String password = ((EditField *)GetControl("passwordField"))->GetText();
	pMultipartEntity->AddStringPart(L"password", password);

	pHttpRequest->SetEntity(*pMultipartEntity);

	// Submit the request:
	pHttpTransaction->Submit();
}

void
UserPopup::OnActionPerformed(const Control& source, int actionId)
{
	//TODO: populate correctly
	switch (actionId)
	{
	case ID_BUTTON_CLOSE_POPUP:
		HidePopup();
		break;
	case ID_BUTTON_LOGIN:
		//ValidateForm(); // TODO: make sure fields are correct
		SubmitLogin();
		break;
	case ID_BUTTON_SIGNUP:
		//ValidateForm(); // TODO: make sure fields are correct
		SubmitSignup();
		break;
	case ID_BUTTON_VIEW_LOGIN:
		ShowLogin();
		break;
	case ID_BUTTON_VIEW_SIGNUP:
		ShowSignup();
		break;
	default:
		break;
	}
}

void
UserPopup::OnKeypadActionPerformed(Control &source, KeypadAction keypadAction)
{
	// Hide keypad when the action button is clicked
	if (keypadAction == KEYPAD_ACTION_DONE)
	{
		//Temp fix for this, hides keyboard by setting focus on popup
		SetFocus();
		//((EditField)source).HideKeypad();
	}
}

void
UserPopup::OnKeypadBoundsChanged(Control &source)
{

}

void
UserPopup::OnKeypadClosed(Control &source)
{

}

void
UserPopup::OnKeypadOpened(Control &source)
{
	/* may need to resize ui?
	Rectangle clientRect = GetClientAreaBounds();
	Rectangle editRect = __pEditField->GetBounds();
	editRect.y = clientRect.height - editRect.height - 50;
	__pEditField->SetBounds(editRect); // Move EditField to avoid overlapping
	*/
}

void
UserPopup::OnKeypadWillOpen(Control &source)
{
	/*
	Rectangle clientRect = GetClientAreaBounds();
	Rectangle editRect = __pEditField->GetBounds();
	editRect.y = clientRect.height - 500;
	__pEditField->SetBounds(editRect); // Move back to original position

	Invalidate(true);
	*/
}

void
UserPopup::OnTransactionAborted(HttpSession &httpSession, HttpTransaction &httpTransaction, result r)
{

}

void
UserPopup::OnTransactionCertVerificationRequiredN(HttpSession &httpSession, HttpTransaction &httpTransaction, Tizen::Base::String *pCert)
{

}

void
UserPopup::OnTransactionCompleted(HttpSession &httpSession, HttpTransaction &httpTransaction)
{
	HttpMultipartEntity* pMultipartEntity = static_cast< HttpMultipartEntity* >(httpTransaction.GetUserObject());

	if (pMultipartEntity)
		delete pMultipartEntity;

		delete &httpTransaction;
}

void
UserPopup::OnTransactionHeaderCompleted(HttpSession &httpSession, HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired)
{
	HttpResponse* httpResponse = httpTransaction.GetResponse();
//	HttpHeader* httpHeader = httpResponse->GetHeader();
	IList* cookieList = httpResponse->GetCookies();

	for (int i = 0; i < cookieList->GetCount(); i++) {
		HttpCookie *cookie = static_cast<HttpCookie*>(cookieList->GetAt(0));

		// TODO: save cookie somewhere
	}

	if (bAuthRequired)
	{
		AppLog("auth required");
		HttpAuthentication* pAuth = httpTransaction.OpenAuthenticationInfoN();
		String basicName("Name");
		String basicpass("Pass");
		HttpCredentials* pCredential = new HttpCredentials(basicName, basicpass);
		String* pRealm = pAuth->GetRealmN();
		NetHttpAuthScheme scheme = pAuth->GetAuthScheme();
		if (scheme == NET_HTTP_AUTH_WWW_BASIC || scheme == NET_HTTP_AUTH_PROXY_BASIC)
		{
			HttpTransaction* pNewTransaction =  pAuth->SetCredentials(*pCredential);
		}
	}
}

void
UserPopup::OnTransactionReadyToRead(HttpSession &httpSession, HttpTransaction &httpTransaction, int availableBodyLen)
{
	HttpResponse* httpResponse = httpTransaction.GetResponse();
	HttpHeader* httpHeader = null;
	AppLog("Checking HTTP Status Code");
	if (httpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
	{
		ByteBuffer* body = null;
		String statusText = httpResponse->GetStatusText();
		String version = httpResponse->GetVersion();

		httpHeader = httpResponse->GetHeader();
		body = httpResponse->ReadBodyN();

		//Parses from ByteBuffer
		IJsonValue* jsonValue = JsonParser::ParseN(*body);

		// Convert jsonValue to hashmap
		HashMap* dict = JSONParser::dictionaryForJSONValue(jsonValue);

		String userKey("user");
		String errorKey("error");
		if (dict->ContainsKey(userKey)) {
			HashMap *userDict = (HashMap *)dict->GetValue(userKey);
			AppLogTag("cookie", "user");

			//HidePopup();
		} else if (dict->ContainsKey(errorKey)) {
			String *errorMessage = (String *)dict->GetValue(errorKey);

			// Enable login button
			Button* loginButton = (Button *)GetControl("loginButton");
			if (loginButton != NULL) {
				loginButton->SetEnabled(true);
				loginButton->SetText("Log In");
			}

			// Enable signup button
			Button* signupButton = (Button *)GetControl("signupButton");
			if (signupButton != NULL) {
				signupButton->SetEnabled(true);
				signupButton->SetText("Sign Up");
			}

			// Flash error message
			Label* errorLabel = (Label* )GetControl("errorLabel");
			errorLabel->SetText(*errorMessage);

			Draw();
		}

		delete body;
		delete jsonValue;
		delete dict;
	}else{
		AppLog("HTTP Status not OK");
	}
}

void
UserPopup::OnTransactionReadyToWrite(HttpSession &httpSession, HttpTransaction &httpTransaction, int recommendedChunkSize)
{

}
