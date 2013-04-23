#include "ProjectGiraffeTab4.h"

#include "ControlUtilities.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Net::Http;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace ControlUtil;

ProjectGiraffeTab4::ProjectGiraffeTab4(void)
{
	_avatarContextMenu = null;
}

ProjectGiraffeTab4::~ProjectGiraffeTab4(void)
{
	delete _avatarContextMenu;
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

	// Avatar button? image?
	Button* avatarButton = new Button();
	avatarButton->Construct(Rectangle(10, 10, 250, 250), "");
	avatarButton->SetName("avatarButton");
	avatarButton->SetActionId(ID_BUTTON_AVATAR);
	avatarButton->AddActionEventListener(*this);
	AddControl(*avatarButton);

	if (_avatarContextMenu == null) {
		_avatarContextMenu = new ContextMenu();
		_avatarContextMenu->Construct(Point(135, 420), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_DOWNWARD);
		_avatarContextMenu->AddItem("Choose from library", ID_CONTEXT_CHOOSE);
		_avatarContextMenu->AddItem("Take photo", ID_CONTEXT_TAKE);
		_avatarContextMenu->AddActionEventListener(*this);
		_avatarContextMenu->SetShowState(false);
		_avatarContextMenu->Invalidate(true);

	}

	Label* usernameLabel = new Label();
	usernameLabel->Construct(Rectangle(270, 10, GetBounds().width - 20, 60), cUser->username());
	usernameLabel->SetTextConfig(48, LABEL_TEXT_STYLE_BOLD);
	usernameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	usernameLabel->SetName("usernameLabel");
	AddControl(*usernameLabel);

	Label* postsLabel = new Label();
	postsLabel->Construct(Rectangle(270, 80, GetBounds().width/3, 40), "posts");
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
ProjectGiraffeTab4::showAvatarMenu(void)
{
	_avatarContextMenu->SetShowState(true);
	_avatarContextMenu->Show();
}

void
ProjectGiraffeTab4::choosePhoto(void)
{
	AppLog("choose photo from library");

	AppControl* appControl = AppManager::FindAppControlN(L"tizen.filemanager", L"http://tizen.org/appcontrol/operation/pick");

	HashMap extraData;
	extraData.Construct();
	String selectKey = L"selectionType";
	String selectVal = L"single";
	extraData.Add(&selectKey, &selectVal);
	String typeKey = L"type";
	String typeVal = L"image";
	extraData.Add(&typeKey, &typeVal);

	if (appControl) {
		appControl->Start(null, null, &extraData, this);
		delete appControl;
	}
}

void
ProjectGiraffeTab4::takePhoto(void)
{
	AppLog("take photo with camera");

	AppControl* appControl = AppManager::FindAppControlN(L"tizen.camera", L"http://tizen.org/appcontrol/operation/createcontent");

	HashMap extraData;
	extraData.Construct();
	String typeKey = L"type";
	String typeVal = L"camera";
	extraData.Add(&typeKey, &typeVal);

	if (appControl) {
		appControl->Start(null, null, &extraData, this);
		delete appControl;
	}
}

void
ProjectGiraffeTab4::showStatus(const String &statusTitle, const String &statusMessage, bool isError)
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
	switch (actionId)
	{
	case ID_BUTTON_LOGIN:
		UserPopup::popup()->showPopup();
		break;
	case ID_BUTTON_AVATAR:
		showAvatarMenu();
		break;
	case ID_CONTEXT_CHOOSE:
		choosePhoto();
		break;
	case ID_CONTEXT_TAKE:
		takePhoto();
		break;
	}
}

void
ProjectGiraffeTab4::OnAppControlCompleteResponseReceived(const AppId &appId, const String &operationId, AppCtrlResult appControlResult, const IMap *extraData)
{
	AppLogTag("camera1", "appid %ls opid %ls", appId.GetPointer(), operationId.GetPointer());
	if (appId.Equals(L"tizen.filemanager", true) &&
			operationId.Equals(L"http://tizen.org/appcontrol/operation/pick", true))
	{
		if (appControlResult == APP_CTRL_RESULT_SUCCEEDED) {
			AppLogTag("camera1", "Media list success.");
			String pathKey = L"path";
			String *filePath = (String *)extraData->GetValue(pathKey);

			AppLogTag("camera1", "filepath: %ls", filePath->GetPointer());

			HttpMultipartEntity* userParameters = new HttpMultipartEntity();
			userParameters->Construct();
			userParameters->AddFilePart(L"avatar", *filePath);

			HttpConnection *connection = HttpConnection::userUpdatePutConnection(this, userParameters);
			connection->begin();

			// TODO: figure out when to free
//			delete userParameters;
		} else if (appControlResult == APP_CTRL_RESULT_CANCELED) {
			AppLogTag("camera1", "Media list canceled.");
		} else if (appControlResult == APP_CTRL_RESULT_FAILED) {
			AppLogTag("camera1", "Media list failed.");
		}
	} else if (appId.Equals(L"tizen.camera", true) &&
			operationId.Equals(L"http://tizen.org/appcontrol/operation/createcontent", true))
	{
		AppLogTag("camera1", "camcam");
		if (appControlResult == APP_CTRL_RESULT_SUCCEEDED) {
			AppLogTag("camera1", "Camera capture success.");

			String pathKey = L"path";
			String *filePath = (String *)extraData->GetValue(pathKey);

			AppLogTag("camera1", "filepath: %ls", filePath->GetPointer());

			HttpMultipartEntity* userParameters = new HttpMultipartEntity();
			userParameters->Construct();
			userParameters->AddFilePart(L"avatar", *filePath);

			HttpConnection *connection = HttpConnection::userUpdatePutConnection(this, userParameters);
			connection->begin();

			// TODO: figure out when to free
			// delete userParameters;
		} else if (appControlResult == APP_CTRL_RESULT_CANCELED) {
			AppLogTag("camera1", "Camera capture canceled.");
		} else if (appControlResult == APP_CTRL_RESULT_FAILED) {
			AppLogTag("camera1", "Camera capture failed.");
		} else if (appControlResult == APP_CTRL_RESULT_TERMINATED) {
			AppLogTag("camera1", "Camera capture terminated.");
		} else if (appControlResult == APP_CTRL_RESULT_ABORTED) {
			AppLogTag("camera1", "Camera capture aborted.");
		}
	}
}

void
ProjectGiraffeTab4::OnAppControlStartResponseReceived(const AppId &appId, const String &operationId, result r)
{
	AppLogTag("camera1", "start response");
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
	if (response) {
		String userKey("user");
		String messageKey("message");
		String errorKey("error");
		if (response->ContainsKey(userKey)) {
			HashMap *userDict = (HashMap *)response->GetValue(userKey);
			User::currentUser()->updateFromDictionary(userDict);

//			showProfile();

			String *message = (String *)response->GetValue(messageKey);
			showStatus("User Update Status", *message, false);
		} else if (response->ContainsKey(errorKey)) {
			String *errorMessage = (String *)response->GetValue(errorKey);

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
ProjectGiraffeTab4::connectionDidFail(HttpConnection *connection)
{
	showStatus(L"HTTP Status", L"HTTP Request Aborted, check internet connection", true);

	delete connection;
}
