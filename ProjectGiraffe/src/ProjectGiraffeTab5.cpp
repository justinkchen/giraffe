#include "ProjectGiraffeTab5.h"

#include "ControlUtilities.h"

using namespace Tizen::App;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;
using namespace ControlUtil;

ProjectGiraffeTab5::ProjectGiraffeTab5(void)
{

}

ProjectGiraffeTab5::~ProjectGiraffeTab5(void)
{

}

bool
ProjectGiraffeTab5::Initialize(void)
{
	result r = Construct(L"IDC_PANEL5");
	if (IsFailed(r))
		return false;

	return true;
}

result
ProjectGiraffeTab5::OnInitializing(void)
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

	User::currentUser()->addListener(this);

	return r;
}

result
ProjectGiraffeTab5::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
ProjectGiraffeTab5::showLoginButton(void)
{
	RemoveAllControls();

	Label* loginLabel = new Label();
	loginLabel->Construct(Rectangle(0, 0, 600, 80), "To view this tab, please log in first.");
	centerHorizontally(loginLabel, this);
	loginLabel->SetName("loginLabel");
	AddControl(*loginLabel);

	Button* loginButton = new Button();
	loginButton->Construct(Rectangle(0, 100, 300, 80), "Log In");
	centerHorizontally(loginButton, this);
	loginButton->SetName("loginButton");
	loginButton->SetActionId(ID_BUTTON_LOGIN);
	loginButton->AddActionEventListener(*this);
	AddControl(*loginButton);

	Draw();
}

void
ProjectGiraffeTab5::showProfile(void)
{
	AppLogTag("user", "start draw profile");

	RemoveAllControls();
	AppLogTag("user", "g");
	//add scroll panel
	ScrollPanel *scrollPanel = new ScrollPanel();
	scrollPanel->Construct(GetBounds());

	User *cUser = User::currentUser();

	Label* usernameLabel = new Label();
	usernameLabel->Construct(Rectangle(10, 10, 300, 40), "Username:");
	usernameLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	usernameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	usernameLabel->SetName("usernameLabel");
	scrollPanel->AddControl(*usernameLabel);

	EditField* usernameField = new EditField();
	usernameField->Construct(Rectangle(10, 60, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	usernameField->SetText(cUser->username());
	usernameField->SetName("usernameField");
	usernameField->SetKeypadAction(KEYPAD_ACTION_DONE);
	usernameField->AddKeypadEventListener(*this);
	usernameField->SetLowerCaseModeEnabled(true);
	scrollPanel->AddControl(*usernameField);

	Label* emailLabel = new Label();
	emailLabel->Construct(Rectangle(10, 150, 300, 40), "Email:");
	emailLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	emailLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	emailLabel->SetName("emailLabel");
	scrollPanel->AddControl(*emailLabel);

	EditField* emailField = new EditField();
	emailField->Construct(Rectangle(10, 200, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_EMAIL, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	emailField->SetText(cUser->email());
	emailField->SetName("emailField");
	emailField->SetKeypadAction(KEYPAD_ACTION_DONE);
	emailField->AddKeypadEventListener(*this);
	emailField->SetLowerCaseModeEnabled(true);
	scrollPanel->AddControl(*emailField);

	Button* updateButton1 = new Button();
	updateButton1->Construct(Rectangle(0, 290, 300, 80), "Update");
	centerHorizontally(updateButton1, this);
	updateButton1->SetName("updateButton1");
	updateButton1->SetActionId(ID_BUTTON_UPDATE1);
	updateButton1->AddActionEventListener(*this);
	scrollPanel->AddControl(*updateButton1);

	Label* oldPasswordLabel = new Label();
	oldPasswordLabel->Construct(Rectangle(10, 380, 300, 40), "Current password:");
	oldPasswordLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	oldPasswordLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	oldPasswordLabel->SetName("oldPassworldLabel");
	scrollPanel->AddControl(*oldPasswordLabel);

	EditField* oldPasswordField = new EditField();
	oldPasswordField->Construct(Rectangle(10, 430, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	oldPasswordField->SetName("oldPasswordField");
	oldPasswordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	oldPasswordField->AddKeypadEventListener(*this);
	oldPasswordField->SetLowerCaseModeEnabled(true);
	scrollPanel->AddControl(*oldPasswordField);

	Label* passwordLabel = new Label();
	passwordLabel->Construct(Rectangle(10, 520, 300, 40), "New password:");
	passwordLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	passwordLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	passwordLabel->SetName("passwordLabel");
	scrollPanel->AddControl(*passwordLabel);

	EditField* passwordField = new EditField();
	passwordField->Construct(Rectangle(10, 570, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	passwordField->SetName("passwordField");
	passwordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	passwordField->AddKeypadEventListener(*this);
	passwordField->SetLowerCaseModeEnabled(true);
	scrollPanel->AddControl(*passwordField);

	Label* confirmPasswordLabel = new Label();
	confirmPasswordLabel->Construct(Rectangle(10, 660, 300, 40), "Confirm password:");
	confirmPasswordLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	confirmPasswordLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	confirmPasswordLabel->SetName("confirmPasswordLabel");
	scrollPanel->AddControl(*confirmPasswordLabel);

	EditField* confirmPasswordField = new EditField();
	confirmPasswordField->Construct(Rectangle(10, 710, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	confirmPasswordField->SetName("confirmPasswordField");
	confirmPasswordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	confirmPasswordField->AddKeypadEventListener(*this);
	confirmPasswordField->SetLowerCaseModeEnabled(true);
	scrollPanel->AddControl(*confirmPasswordField);

	Button* updateButton2 = new Button();
	updateButton2->Construct(Rectangle(0, 800, 300, 80), "Change Password");
	centerHorizontally(updateButton2, this);
	updateButton2->SetName("updateButton2");
	updateButton2->SetActionId(ID_BUTTON_UPDATE2);
	updateButton2->AddActionEventListener(*this);
	scrollPanel->AddControl(*updateButton2);

	// logout button
	Button* logoutButton = new Button();
	logoutButton->Construct(Rectangle(0, 890, 300, 80), "Logout");
	centerHorizontally(logoutButton, this);
	logoutButton->SetName("logoutButton");
	logoutButton->SetActionId(ID_BUTTON_LOGOUT);
	logoutButton->AddActionEventListener(*this);
	scrollPanel->AddControl(*logoutButton);

	Label* spacer = new Label();
	spacer->Construct(Rectangle(0, 980, this->GetBounds().width, 10), "");
	spacer->SetName("spacer");
	scrollPanel->AddControl(*spacer);
	scrollPanel->SetName("scrollPanel");

	AddControl(*scrollPanel);

	Draw();
}

void
ProjectGiraffeTab5::updateUser(void)
{
	// Validators
	String username = ((EditField *)GetControl("usernameField", true))->GetText();
	String email = ((EditField *)GetControl("emailField", true))->GetText();

	// Check not blank
	String blank("");
	if (username.Equals(blank)) {
		showStatus("User Update Status", "Please enter a username.", true);
		return;
	} else if (email.Equals(blank)) {
		showStatus("User Update Status", "Please enter an email.", true);
		return;
	} else if (username.Equals(User::currentUser()->username()) && email.Equals(User::currentUser()->email())) {
		showStatus("User Update Status", "Username and email unchanged.", true);
		return;
	}

	// Disable update button
	Button* updateButton1 = (Button *)GetControl("updateButton1", true);
	updateButton1->SetEnabled(false);
	updateButton1->SetText("Updating...");

	HttpMultipartEntity* userParameters = new HttpMultipartEntity();
	userParameters->Construct();
	userParameters->AddStringPart(L"username", username);
	userParameters->AddStringPart(L"email", email);

	HttpConnection *connection = HttpConnection::userUpdatePutConnection(this, userParameters);
	connection->begin();

	delete userParameters;
}

void
ProjectGiraffeTab5::updatePassword(void)
{
	// Validators
	String oldPassword = ((EditField *)GetControl("oldPasswordField", true))->GetText();
	String password = ((EditField *)GetControl("passwordField", true))->GetText();
	String confirmPassword = ((EditField *)GetControl("confirmPasswordField", true))->GetText();

	// Check not blank
	String blank("");
	if (oldPassword.Equals(blank)) {
		showStatus("User Update Status", "Please enter current password.", true);
		return;
	} else if (password.Equals(blank)) {
		showStatus("User Update Status", "Please enter new password.", true);
		return;
	} else if (confirmPassword.Equals(blank)) {
		showStatus("User Update Status", "Please enter new password confirmation.", true);
		return;
	} else if (!password.Equals(confirmPassword)) {
		showStatus("User Update Status", "New passwords do not match.", true);
		return;
	}

	// Disable update button
	Button* updateButton2 = (Button *)GetControl("updateButton2", true);
	updateButton2->SetEnabled(false);
	updateButton2->SetText("Changing...");

	HttpMultipartEntity* userParameters = new HttpMultipartEntity();
	userParameters->Construct();
	userParameters->AddStringPart(L"oldPassword", oldPassword);
	userParameters->AddStringPart(L"password", password);

	HttpConnection *connection = HttpConnection::userUpdatePutConnection(this, userParameters);
	connection->begin();

	delete userParameters;
}

void
ProjectGiraffeTab5::logout(void)
{
	// Disable logout button
	Button* logoutButton = (Button *)GetControl("logoutButton", true);
	logoutButton->SetEnabled(false);
	logoutButton->SetText("Logging out...");

	HttpConnection *connection = HttpConnection::userLogoutPostConnection(this);
	connection->begin();
}

void
ProjectGiraffeTab5::showStatus(const String &statusTitle, const String &statusMessage, bool isError)
{
	StatusPopup* statusPopup = StatusPopup::popup();
	statusPopup->setTitle(statusTitle);
	statusPopup->setMessage(statusMessage);

	if (isError) {
		statusPopup->setType(StatusPopup::STATUS_POPUP_ERROR);
	} else {
		statusPopup->setType(StatusPopup::STATUS_POPUP_DEFAULT);
	}

	statusPopup->showPopup();

	/*
	 * TODO: figure out if we can use messagebox or not because
	 * this looks like an event handler and they warn not to use inside
	 * event handlers because it's unsafe
	MessageBox msgBox;
//	msgBox.Construct(statusTitle, statusMessage, MSGBOX_STYLE_NONE, 3000);
//	msgBox.Construct(L"HTTP STATUS", L"HTTP Request Aborted, Check internet connection", MSGBOX_STYLE_NONE, 3000);
	int modalresult = 0;
	msgBox.ShowAndWait(modalresult);
	*/
}

void
ProjectGiraffeTab5::resetButtons(void)
{
	// Enable update button 1 and 2
	Button* updateButton1 = (Button *)GetControl("updateButton1", true);
	if (updateButton1 != NULL) {
		updateButton1->SetEnabled(true);
		updateButton1->SetText("Update");
	}

	Button* updateButton2 = (Button *)GetControl("updateButton2", true);
	if (updateButton2 != NULL) {
		updateButton2->SetEnabled(true);
		updateButton2->SetText("Change Password");
	}

	// Enable logout button
	Button* logoutButton = (Button *)GetControl("logoutButton", true);
	if (logoutButton != NULL) {
		logoutButton->SetEnabled(true);
		logoutButton->SetText("Logout");
	}

	Draw();
}

void
ProjectGiraffeTab5::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// Add your scene activate code here
	AppLog("OnSceneActivatedN");

	// load user
	if (User::currentUser()->id() == 0) {
		showLoginButton();
	} else {
		showProfile();
	}
}

void
ProjectGiraffeTab5::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
}

void
ProjectGiraffeTab5::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_BUTTON_LOGIN:
		UserPopup::popup()->showPopup();
		break;
	case ID_BUTTON_LOGOUT:
		logout();
		break;
	case ID_BUTTON_UPDATE1:
		updateUser();
		break;
	case ID_BUTTON_UPDATE2:
		updatePassword();
		break;
	default:
		break;
	}
}

void
ProjectGiraffeTab5::OnKeypadActionPerformed(Control &source, KeypadAction keypadAction)
{
	// Hide keypad when the action button is clicked
	if (keypadAction == KEYPAD_ACTION_DONE)
	{
		((EditField *)&source)->HideKeypad();
	}
}

void
ProjectGiraffeTab5::OnKeypadBoundsChanged(Control &source)
{

}

void
ProjectGiraffeTab5::OnKeypadClosed(Control &source)
{

}

void
ProjectGiraffeTab5::OnKeypadOpened(Control &source)
{
	/* may need to resize ui?
	Rectangle clientRect = GetClientAreaBounds();
	Rectangle editRect = __pEditField->GetBounds();
	editRect.y = clientRect.height - editRect.height - 50;
	__pEditField->SetBounds(editRect); // Move EditField to avoid overlapping
	*/
}

void
ProjectGiraffeTab5::OnKeypadWillOpen(Control &source)
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
ProjectGiraffeTab5::onUserUpdate(User *user)
{
	if (User::currentUser()->id() == 0) {
		AppLogTag("user", "update no user");
		showLoginButton();
	} else {
		AppLogTag("user", "update yes user");
		showProfile();
	}
}

void
ProjectGiraffeTab5::connectionDidFinish(HttpConnection *connection, HashMap *response)
{
	if (response) {
		String userKey("user");
		String messageKey("message");
		String logoutKey("logout");
		String errorKey("error");
		if (response->ContainsKey(userKey)) {
			HashMap *userDict = (HashMap *)response->GetValue(userKey);
			User::currentUser()->updateFromDictionary(userDict);

//			showProfile();

			String *message = (String *)response->GetValue(messageKey);
			showStatus("User Update Status", *message, false);
		} else if (response->ContainsKey(logoutKey)) {
			User::currentUser()->logout();

//			showLoginButton();

			String *message = (String *)response->GetValue(logoutKey);
			showStatus("Logout Status", *message, false);
		} else if (response->ContainsKey(errorKey)) {
			String *errorMessage = (String *)response->GetValue(errorKey);

			resetButtons();

			// Flash error message
			showStatus("User Update Status", *errorMessage, true);

			Draw();
		}

		delete connection;
//		delete response;
	} else {
		connectionDidFail(connection);
	}
}

void
ProjectGiraffeTab5::connectionDidFail(HttpConnection *connection)
{
	resetButtons();
	showStatus(L"HTTP Status", L"HTTP Request Aborted, check internet connection", true);

	delete connection;
}
