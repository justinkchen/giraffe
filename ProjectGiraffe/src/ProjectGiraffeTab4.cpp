#include "ProjectGiraffeTab4.h"
#include "ProjectGiraffeMainForm.h"
#include "ControlUtilities.h"
#include "GraffitiCellContentView.h"
#include "GraffitiCellSocialContextView.h"

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
	if (_items)
	{
		_items->RemoveAll(true);
		delete _items;
		_items = null;
	}
	// TODO: Add your termination code here

	return r;
}

void
ProjectGiraffeTab4::showLoginButton(void)
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


	// Create tableView
	_tableView = new TableView();
	_tableView->Construct(Rectangle(0,270,GetBounds().width, GetBounds().height-270), \
			true, TABLE_VIEW_SCROLL_BAR_STYLE_FADE_OUT);
	_tableView->SetItemProvider(this);
	_tableView->AddTableViewItemEventListener(*this);
	AddControl(*_tableView);


	_items = new (std::nothrow) ArrayList();

	updateItems();
	Draw();
}

void
ProjectGiraffeTab4::updateItems()
{
	AppLog("updating items");
	HttpConnection *connection = HttpConnection::userPostsGetConnection(this,User::currentUser()->id());
	connection->begin();
}

void ProjectGiraffeTab4::updateViews()
{
	AppLog("updating views");
	// Remove all views if they exist
	if (_contentViews) _contentViews->RemoveAll(true);
	delete _contentViews;
	if (_contextViews) _contextViews->RemoveAll(true);
	delete _contextViews;

	if (_items && _items->GetCount()) {
		_contentViews = new ArrayList(SingleObjectDeleter);
		_contentViews->Construct();
		_contextViews = new ArrayList(SingleObjectDeleter);
		_contextViews->Construct();

		IEnumerator *iter = _items->GetEnumeratorN();
		int width = GetSize().width;
		while (iter->MoveNext() == E_SUCCESS) {
			Graffiti *graffiti = static_cast<Graffiti *>(iter->GetCurrent());
			if (graffiti) {
				// Create content view
				GraffitiCellContentView *contentView = new GraffitiCellContentView();
				contentView->Construct(Rectangle(0, 0, width, GetDefaultItemHeight()));
				contentView->setGraffiti(graffiti);
				contentView->sizeToFit();
				_contentViews->Add((Panel *)contentView);

				// Create social context view
				GraffitiCellSocialContextView *socialContextView = new GraffitiCellSocialContextView();
				socialContextView->Construct(contentView->GetBounds());
				socialContextView->setGraffiti(graffiti);
				_contextViews->Add((Panel *)socialContextView);
			}
		}
	} else {
		_contentViews = NULL;
		_contextViews = NULL;
	}
}

void ProjectGiraffeTab4::setItems(ArrayList *items)
{
	AppLog("setItems");
	if (_items != items) {
		// Deallocate old items
		if (_items) _items->RemoveAll(true);
		delete _items;
		_items = items;
		AppLog("previous items deleted");

		// Update views
		updateViews();

		AppLog("updating tableview");
		// Use new items/views in table
		_tableView->UpdateTableView();
		AppLog("tableview updated");
	}
}

void ProjectGiraffeTab4::displayNoGraffiti(){
	Label* noGraffitiLabel = new Label();
	noGraffitiLabel->Construct(Rectangle(0, 270, GetBounds().width, 40), "posts");
	noGraffitiLabel->SetTextConfig(32, LABEL_TEXT_STYLE_BOLD);
	noGraffitiLabel->SetTextHorizontalAlignment(ALIGNMENT_CENTER);
	noGraffitiLabel->SetName("noGraffitiLabel");
	noGraffitiLabel->SetText(L"No graffiti posted yet");
	AddControl(*noGraffitiLabel);
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
	/*
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
	}
	*/
	AppLog("HttpConnection finished");
	if (response) {
		// TODO: check for the return value
		ArrayList *graffitiList = static_cast<ArrayList *>(response->GetValue(kHTTPParamNameGraffiti));
		if (graffitiList) {
			AppLog("Retrieved list");
			ArrayList *newItems = new ArrayList(SingleObjectDeleter);
			newItems->Construct();

			for (int i = 0; i < graffitiList->GetCount(); i++) {
				HashMap *graffitiDictionary = static_cast<HashMap *>(graffitiList->GetAt(i));
				AppLog("updating dictionary");
				if (graffitiDictionary) {
					Graffiti *newGraffiti = new Graffiti();
					newGraffiti->updateFromDictionary(graffitiDictionary);
					newGraffiti->setUser(User::currentUser());
					AppLog("Updated from dictionary");
					newItems->Add(newGraffiti);
				}
			}
			if(graffitiList->GetCount() == 0){
				AppLog("No graffiti to display");
				displayNoGraffiti();
			}
			AppLog("Setting new items");
			setItems(newItems);
		}else{
			AppLog("Failed to retrieve graffiti list");
			displayNoGraffiti();
		}
	} else {

		connectionDidFail(connection);
	}
}

void
ProjectGiraffeTab4::connectionDidFail(HttpConnection *connection)
{
	AppLog("connection failed");
	showStatus(L"HTTP Status", L"HTTP Request Aborted, check internet connection", true);

	displayNoGraffiti();
	delete connection;
}

// ITableViewItemEventListener
void ProjectGiraffeTab4::OnTableViewItemStateChanged(Tizen::Ui::Controls::TableView& tableView,
		int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status)
{

}

void ProjectGiraffeTab4::OnTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::TableView& tableView, int itemIndex,
		Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated)
{
}

void ProjectGiraffeTab4::OnTableViewItemReordered(Tizen::Ui::Controls::TableView& tableView, int itemIndexFrom, int itemIndexTo)
{
}

// ITableViewItemProvider
int ProjectGiraffeTab4::GetItemCount(void)
{
	AppLog("Counting Items");
	return _items ? _items->GetCount() : 0;
}

TableViewItem* ProjectGiraffeTab4::CreateItem(int itemIndex, int itemWidth)
{
	AppLog("Creating Items");

	// Fetch Graffiti object
	Graffiti *graffiti = dynamic_cast<Graffiti *>(_items->GetAt(itemIndex));

	// Create item
	TableViewItem *item = new TableViewItem();
	item->Construct(Dimension(itemWidth, GetDefaultItemHeight()),
			TABLE_VIEW_ANNEX_STYLE_NORMAL);

	// Create contextItem
	TableViewContextItem *contextItem = new TableViewContextItem();
	contextItem->Construct(item->GetSize());
	item->SetContextItem(contextItem);

	Control *contentView = static_cast<Control *>(_contentViews->GetAt(itemIndex));
	if (contentView) {
		item->AddControl(*contentView);
		item->SetSize(contentView->GetSize());
		contextItem->SetSize(contentView->GetSize());
	}
	Control *contextView = static_cast<Control *>(_contextViews->GetAt(itemIndex));
	if (contextView) {
		contextItem->AddControl(*contextView);
	}


	return item;
}

bool ProjectGiraffeTab4::DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem)
{
	AppLog("Deleting item %d", itemIndex);
// TODO: Figure out what is causing this to crash...seems to work fine without this, but would be good to fix I think.
//	delete pItem;
	return true;
}

void ProjectGiraffeTab4::UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem)
{
	AppLog("Updating Items");
}

int ProjectGiraffeTab4::GetDefaultItemHeight(void)
{
	return 150;
}
