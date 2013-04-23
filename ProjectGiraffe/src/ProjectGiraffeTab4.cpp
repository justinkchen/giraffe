#include "ProjectGiraffeTab4.h"

#include "ControlUtilities.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base::Collection;
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
	scrollPanel->Construct(Rectangle(0, 160, GetBounds().width, GetBounds().height - 160));

	User *cUser = User::currentUser();

	Label* usernameLabel = new Label();
	usernameLabel->Construct(Rectangle(10, 10, GetBounds().width - 20, 60), cUser->username());
	usernameLabel->SetTextConfig(48, LABEL_TEXT_STYLE_BOLD);
	usernameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	usernameLabel->SetName("usernameLabel");
	AddControl(*usernameLabel);

	Label* postsLabel = new Label();
	postsLabel->Construct(Rectangle(10, 80, GetBounds().width/3, 40), "posts");
	postsLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	postsLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	postsLabel->SetName("postsLabel");
	AddControl(*postsLabel);

	/*
	// logout button
	Button* logoutButton = new Button();
	logoutButton->Construct(Rectangle(GetBounds().width/2 + 30, 10, 300, 80), "Logout");
//	centerHorizontally(updateButton1, this);
	logoutButton->SetName("logoutButton");
	logoutButton->SetActionId(ID_BUTTON_LOGOUT);
	logoutButton->AddActionEventListener(*this);
	scrollPanel->AddControl(*logoutButton);

	// Avatar button? image?
	Button* avatarButton = new Button();
	avatarButton->Construct(Rectangle(10, 10, 250, 250), "");
	avatarButton->SetName("avatarButton");
	avatarButton->SetActionId(ID_BUTTON_AVATAR);
	avatarButton->AddActionEventListener(*this);
	scrollPanel->AddControl(*avatarButton);

	if (_avatarContextMenu == null) {
		_avatarContextMenu = new ContextMenu();
		_avatarContextMenu->Construct(Point(135, 420), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_DOWNWARD);
		_avatarContextMenu->AddItem("Choose from library", ID_CONTEXT_CHOOSE);
		_avatarContextMenu->AddItem("Take photo", ID_CONTEXT_TAKE);
		_avatarContextMenu->AddActionEventListener(*this);
		_avatarContextMenu->SetShowState(false);
		_avatarContextMenu->Invalidate(true);

	}
	*/


	scrollPanel->SetName("scrollPanel");

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
		showLoginButton();
	} else {
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

void
ProjectGiraffeTab4::connectionDidFinish(HttpConnection *connection, HashMap *response)
{
	/*
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
	*/
		connectionDidFail(connection);
//	}
}

void
ProjectGiraffeTab4::connectionDidFail(HttpConnection *connection)
{
//	showStatus(L"HTTP Status", L"HTTP Request Aborted, check internet connection", true);

	delete connection;
}
