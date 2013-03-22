#include "ProjectGiraffeTab4.h"

#include "ControlUtilities.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;
using namespace ControlUtil;

ProjectGiraffeTab4::ProjectGiraffeTab4(void)
{

}

ProjectGiraffeTab4::~ProjectGiraffeTab4(void)
{

}

bool
ProjectGiraffeTab4::Initialize(void)
{
	result r = Construct(L"IDC_PANEL4");
	if (IsFailed(r))
		return false;

	return true;
}

result
ProjectGiraffeTab4::OnInitializing(void)
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
ProjectGiraffeTab4::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
ProjectGiraffeTab4::showLoginButton(void)
{
	RemoveAllControls();

	Label* loginLabel = new Label();
	loginLabel->Construct(Rectangle(0, 0, 600, 80), "To view your profile, please log in first.");
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
ProjectGiraffeTab4::showProfile(void)
{
	RemoveAllControls();

	//add scroll panel
	ScrollPanel *scrollPanel = new ScrollPanel();
	scrollPanel->Construct(this->GetBounds());

	User *cUser = User::currentUser();

	// Avatar button? image?
	// Full name

	Label* usernameLabel = new Label();
	usernameLabel->Construct(Rectangle(10, 260, 300, 40), "Username:");
	usernameLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	AppLogTag("user", "style %d", ALIGNMENT_MIDDLE == usernameLabel->GetTextVerticalAlignment());
	AppLogTag("user", "size %d", usernameLabel->GetTextSize());
	usernameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	usernameLabel->SetName("usernameLabel");
	scrollPanel->AddControl(*usernameLabel);

	EditField* usernameField = new EditField();
	usernameField->Construct(Rectangle(10, 310, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	usernameField->SetText(cUser->username());
	usernameField->SetName("usernameField");
	usernameField->SetKeypadAction(KEYPAD_ACTION_DONE);
	usernameField->AddKeypadEventListener(*this);
	scrollPanel->AddControl(*usernameField);

	Label* emailLabel = new Label();
	emailLabel->Construct(Rectangle(10, 400, 300, 40), "Email:");
	AppLogTag("user", "style %d", LABEL_TEXT_STYLE_BOLD == emailLabel->GetTextStyle());
	AppLogTag("user", "size %d", emailLabel->GetTextSize());
	emailLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	emailLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	emailLabel->SetName("emailLabel");
	scrollPanel->AddControl(*emailLabel);

	EditField* emailField = new EditField();
	emailField->Construct(Rectangle(10, 450, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_EMAIL, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	emailField->SetText(cUser->email());
	emailField->SetName("emailField");
	emailField->SetKeypadAction(KEYPAD_ACTION_DONE);
	emailField->AddKeypadEventListener(*this);
	scrollPanel->AddControl(*emailField);

	Button* updateButton1 = new Button();
	updateButton1->Construct(Rectangle(0, 540, 300, 80), "Update");
	centerHorizontally(updateButton1, this);
	updateButton1->SetName("updateButton1");
	updateButton1->SetActionId(ID_BUTTON_UPDATE1);
	updateButton1->AddActionEventListener(*this);
	scrollPanel->AddControl(*updateButton1);

	Label* oldPasswordLabel = new Label();
	oldPasswordLabel->Construct(Rectangle(10, 630, 300, 40), "Current password:");
	oldPasswordLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	oldPasswordLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	oldPasswordLabel->SetName("oldPassworldLabel");
	scrollPanel->AddControl(*oldPasswordLabel);

	EditField* oldPasswordField = new EditField();
	oldPasswordField->Construct(Rectangle(10, 680, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	oldPasswordField->SetName("oldPasswordField");
	oldPasswordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	oldPasswordField->AddKeypadEventListener(*this);
	scrollPanel->AddControl(*oldPasswordField);

	Label* passwordLabel = new Label();
	passwordLabel->Construct(Rectangle(10, 770, 300, 40), "New password:");
	passwordLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	passwordLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	passwordLabel->SetName("passwordLabel");
	scrollPanel->AddControl(*passwordLabel);

	EditField* passwordField = new EditField();
	passwordField->Construct(Rectangle(10, 820, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	passwordField->SetName("passwordField");
	passwordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	passwordField->AddKeypadEventListener(*this);
	scrollPanel->AddControl(*passwordField);

	Label* confirmPasswordLabel = new Label();
	confirmPasswordLabel->Construct(Rectangle(10, 910, 300, 40), "Confirm password:");
	confirmPasswordLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	confirmPasswordLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	confirmPasswordLabel->SetName("confirmPasswordLabel");
	scrollPanel->AddControl(*confirmPasswordLabel);

	EditField* confirmPasswordField = new EditField();
	confirmPasswordField->Construct(Rectangle(10, 960, this->GetBounds().width - 20, 80), EDIT_FIELD_STYLE_PASSWORD, INPUT_STYLE_OVERLAY, EDIT_FIELD_TITLE_STYLE_NONE, true);
	confirmPasswordField->SetName("confirmPasswordField");
	confirmPasswordField->SetKeypadAction(KEYPAD_ACTION_DONE);
	confirmPasswordField->AddKeypadEventListener(*this);
	scrollPanel->AddControl(*confirmPasswordField);

	Button* updateButton2 = new Button();
	updateButton2->Construct(Rectangle(0, 1050, 300, 80), "Change Password");
	centerHorizontally(updateButton2, this);
	updateButton2->SetName("updateButton2");
	updateButton2->SetActionId(ID_BUTTON_UPDATE2);
	updateButton2->AddActionEventListener(*this);
	scrollPanel->AddControl(*updateButton2);

	Label* spacer = new Label();
	spacer->Construct(Rectangle(0, 1140, this->GetBounds().width, 10), "");
	spacer->SetName("spacer");
	scrollPanel->AddControl(*spacer);

	AddControl(*scrollPanel);

	Draw();
}

void
ProjectGiraffeTab4::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO:
	// Add your scene activate code here
	AppLog("OnSceneActivatedN");

	// load user
	if (User::currentUser()->id() == 0) {
		AppLogTag("user", "no user");
		showLoginButton();
	} else {
		AppLogTag("user", "yes user");
		showProfile();
	}
}

void
ProjectGiraffeTab4::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
}

void
ProjectGiraffeTab4::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
		{
		case ID_BUTTON_LOGIN:
//			showPopup();
			break;
		case ID_BUTTON_AVATAR:
			break;
		case ID_BUTTON_UPDATE1:
//			updateUser();
			break;
		case ID_BUTTON_UPDATE2:
//			updateUser();
			break;
		default:
			break;
		}
}

void
ProjectGiraffeTab4::OnKeypadActionPerformed(Control &source, KeypadAction keypadAction)
{
	// Hide keypad when the action button is clicked
	if (keypadAction == KEYPAD_ACTION_DONE)
	{
		((EditField *)&source)->HideKeypad();
	}
}

void
ProjectGiraffeTab4::OnKeypadBoundsChanged(Control &source)
{

}

void
ProjectGiraffeTab4::OnKeypadClosed(Control &source)
{

}

void
ProjectGiraffeTab4::OnKeypadOpened(Control &source)
{
	/* may need to resize ui?
	Rectangle clientRect = GetClientAreaBounds();
	Rectangle editRect = __pEditField->GetBounds();
	editRect.y = clientRect.height - editRect.height - 50;
	__pEditField->SetBounds(editRect); // Move EditField to avoid overlapping
	*/
}

void
ProjectGiraffeTab4::OnKeypadWillOpen(Control &source)
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
ProjectGiraffeTab4::OnTransactionAborted(HttpSession &httpSession, HttpTransaction &httpTransaction, result r)
{
	AppLog("HTTP Transaction Aborted");
}

void
ProjectGiraffeTab4::OnTransactionCertVerificationRequiredN(HttpSession &httpSession, HttpTransaction &httpTransaction, Tizen::Base::String *pCert)
{

}

void
ProjectGiraffeTab4::OnTransactionCompleted(HttpSession &httpSession, HttpTransaction &httpTransaction)
{
	AppLog("HTTP Transaction Completed");
}

void
ProjectGiraffeTab4::OnTransactionHeaderCompleted(HttpSession &httpSession, HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired)
{

}

void
ProjectGiraffeTab4::OnTransactionReadyToRead(HttpSession &httpSession, HttpTransaction &httpTransaction, int availableBodyLen)
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

//		TraverseFunction(pValue);

		pJsonObject->RemoveAll(true);
		delete pJsonObject;
		delete pBody;
//		delete pValue;
	}else{
		AppLog("HTTP Status not OK");
	}
}

void
ProjectGiraffeTab4::OnTransactionReadyToWrite (HttpSession &httpSession, HttpTransaction &httpTransaction, int recommendedChunkSize)
{

}

void
ProjectGiraffeTab4::onUserUpdate(User *user)
{
	if (User::currentUser()->id() == 0) {
		AppLogTag("user", "update no user");
		showLoginButton();
	} else {
		AppLogTag("user", "update yes user");
		showProfile();
	}
}
