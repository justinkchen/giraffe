#ifndef _PROJECTGIRAFFE_TAB4_H_
#define _PROJECTGIRAFFE_TAB4_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include "User.h"
#include "HttpConnection.h"
#include "User.h"
#include "UserPopup.h"
#include "StatusPopup.h"

class ProjectGiraffeTab4 :
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::IActionEventListener,
	public Tizen::App::IAppControlResponseListener,
	public User::UserListener,
	public HttpConnection::HttpConnectionListener
{
public:
	ProjectGiraffeTab4(void);
	virtual ~ProjectGiraffeTab4(void);
	bool Initialize(void);

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	// ISceneEventListener
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

	// IActionEventListener
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	//IAppControlResponseListener
	virtual void OnAppControlCompleteResponseReceived(const Tizen::App::AppId &appId, const Tizen::Base::String &operationId, Tizen::App::AppCtrlResult appControlResult, const Tizen::Base::Collection::IMap *extraData);
	virtual void OnAppControlStartResponseReceived(const Tizen::App::AppId &appId, const Tizen::Base::String &operationId, result r);

	// UserListener
	virtual void onUserUpdate(User *user);

	// HttpConnectionListener
	virtual void connectionDidFinish(HttpConnection *connection, Tizen::Base::Collection::HashMap *response);
	virtual void connectionDidFail(HttpConnection *connection);

private:
	static const int ID_BUTTON_LOGIN = 401;

	static const int ID_BUTTON_AVATAR = 405;
	static const int ID_CONTEXT_CHOOSE = 406;
	static const int ID_CONTEXT_TAKE = 407;

	Tizen::Ui::Controls::ContextMenu* _avatarContextMenu;

	void showLoginButton(void);
	void showProfile(void);

	void showAvatarMenu(void);
	void choosePhoto(void);
	void takePhoto(void);

	void showStatus(const Tizen::Base::String &statusTitle, const Tizen::Base::String &statusMessage, bool isError);
};

#endif // _PROJECTGIRAFFE_TAB4_H_
