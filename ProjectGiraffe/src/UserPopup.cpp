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

UserPopup *userPopupSingleton = NULL;

UserPopup *
UserPopup::popup(void)
{
	if (!userPopupSingleton) {
		userPopupSingleton = new UserPopup();
	}
	return userPopupSingleton;
}

UserPopup::UserPopup() {
	Construct(true, Dimension(600,800));

	showLogin();
}

UserPopup::~UserPopup() {

}

void
UserPopup::showPopup(void)
{
	SetShowState(true);
	Show();
}

void
UserPopup::hidePopup(void)
{
	SetShowState(false);
	Invalidate(true);
}

void
UserPopup::showLogin(void)
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
	usernameEmailField->SetLowerCaseModeEnabled(true);
	AddControl(*usernameEmailField);

	// Password edit field
	EditField* passwordField = new EditField();
	passwordField->Construct(Rectangle(0, 140, 580, 120), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	passwordField->SetTitleText("Password");
	passwordField->SetName("passwordField");
	passwordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	passwordField->AddKeypadEventListener(*this);
	passwordField->SetLowerCaseModeEnabled(true);
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
UserPopup::showSignup(void)
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
	usernameField->SetLowerCaseModeEnabled(true);
	AddControl(*usernameField);

	// Email edit field
	EditField* emailField = new EditField();
	emailField->Construct(Rectangle(0, 140, 580, 120), EDIT_FIELD_STYLE_EMAIL, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	emailField->SetTitleText("Email");
	emailField->SetName("emailField");
	emailField->SetKeypadAction(KEYPAD_ACTION_DONE);
	emailField->AddKeypadEventListener(*this);
	emailField->SetLowerCaseModeEnabled(true);
	AddControl(*emailField);

	// Password edit field
	EditField* passwordField = new EditField();
	passwordField->Construct(Rectangle(0, 270, 580, 120), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	passwordField->SetTitleText("Password");
	passwordField->SetName("passwordField");
	passwordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	passwordField->AddKeypadEventListener(*this);
	passwordField->SetLowerCaseModeEnabled(true);
	AddControl(*passwordField);

	// Password confirmation edit field
	EditField* passwordConfirmField = new EditField();
	passwordConfirmField->Construct(Rectangle(0, 400, 580, 120), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_TOP, true);
	passwordConfirmField->SetTitleText("Confirm Password");
	passwordConfirmField->SetName("passwordConfirmField");
	passwordConfirmField->SetKeypadAction(KEYPAD_ACTION_DONE);
	passwordConfirmField->AddKeypadEventListener(*this);
	passwordConfirmField->SetLowerCaseModeEnabled(true);
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
UserPopup::submitLogin(void)
{
	// Validators
	String usernameEmail = ((EditField *)GetControl("usernameEmailField"))->GetText();
	String password = ((EditField *)GetControl("passwordField"))->GetText();
	// Check not blank
	String blank("");
	if (usernameEmail.Equals(blank)) {
		showError("Please enter a username or email.");
		return;
	} else if (password.Equals(blank)) {
		showError("Please enter a password.");
		return;
	}

	// Disable login button
	Button* loginButton = (Button *)GetControl("loginButton");
	loginButton->SetEnabled(false);
	loginButton->SetText("Logging in...");

	// Create HTTP multipart entity
	HttpMultipartEntity* userParameters = new HttpMultipartEntity();
	userParameters->Construct();
	userParameters->AddStringPart(L"usernameEmail", usernameEmail);
	userParameters->AddStringPart(L"password", password);

	HttpConnection *connection = HttpConnection::userLoginPostConnection(this, userParameters);
	connection->begin();

	delete userParameters;
}

void
UserPopup::submitSignup(void)
{
	// Validators
	String username = ((EditField *)GetControl("usernameField"))->GetText();
	String email = ((EditField *)GetControl("emailField"))->GetText();
	String password = ((EditField *)GetControl("passwordField"))->GetText();
	String passwordConfirm = ((EditField *)GetControl("passwordConfirmField"))->GetText();
	// Check not blank
	String blank("");
	if (username.Equals(blank)) {
		showError("Please enter a username.");
		return;
	} else if (email.Equals(blank)) {
		showError("Please enter an email.");
		return;
	} else if (password.Equals(blank)) {
		showError("Please enter a password.");
		return;
	} else if (passwordConfirm.Equals(blank)) {
		showError("Please enter password confirmation.");
		return;
	}
	// Check valid email - done in the backend
	// Check passwords =
	else if (!password.Equals(passwordConfirm)) {
		showError("Passwords do not match.");
		return;
	}

	// Disable signup button
	Button* signupButton = (Button *)GetControl("signupButton");
	signupButton->SetEnabled(false);
	signupButton->SetText("Signing up...");

	HttpMultipartEntity* userParameters = new HttpMultipartEntity();
	userParameters->Construct();
	userParameters->AddStringPart(L"username", username);
	userParameters->AddStringPart(L"email", email);
	userParameters->AddStringPart(L"password", password);

	HttpConnection *connection = HttpConnection::userSignupPostConnection(this, userParameters);
	connection->begin();

	delete userParameters;
}

void
UserPopup::showError(const String &errorMessage)
{
	Label* errorLabel = (Label* )GetControl("errorLabel");
	errorLabel->SetText(errorMessage);

	Draw();
}

void
UserPopup::resetButtons(void)
{
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

	Draw();
}

void
UserPopup::OnActionPerformed(const Control& source, int actionId)
{
	//TODO: populate correctly
	switch (actionId)
	{
	case ID_BUTTON_CLOSE_POPUP:
		hidePopup();
		break;
	case ID_BUTTON_LOGIN:
		submitLogin();
		break;
	case ID_BUTTON_SIGNUP:
		submitSignup();
		break;
	case ID_BUTTON_VIEW_LOGIN:
		showLogin();
		break;
	case ID_BUTTON_VIEW_SIGNUP:
		showSignup();
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
//		SetFocus();
		//((EditField)source).HideKeypad();
		((EditField *)&source)->HideKeypad();
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
UserPopup::connectionDidFinish(HttpConnection *connection, HashMap *response)
{
	AppLog("HttpConnection finished");

	if (response) {
		String userKey("user");
		String errorKey("error");
		if (response->ContainsKey(userKey)) {
			HashMap *userDict = (HashMap *)response->GetValue(userKey);

			User::currentUser()->updateFromDictionary(userDict);

			resetButtons();
//			Draw();

			hidePopup();
		} else if (response->ContainsKey(errorKey)) {
			String *errorMessage = (String *)response->GetValue(errorKey);

			resetButtons();

			// Flash error message
			showError(*errorMessage);

			Draw();
		}
		delete connection;
	} else {
		connectionDidFail(connection);
	}
}

void
UserPopup::connectionDidFail(HttpConnection *connection)
{
	AppLog("HttpConnection failed");

	resetButtons();

	MessageBox msgBox;
	msgBox.Construct(L"HTTP STATUS", L"HTTP Request Aborted, Check internet connection", MSGBOX_STYLE_NONE, 3000);
	int modalresult = 0;
	msgBox.ShowAndWait(modalresult);
	delete connection;
}
