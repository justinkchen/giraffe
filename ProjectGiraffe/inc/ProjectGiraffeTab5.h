#ifndef _PROJECTGIRAFFE_TAB5_H_
#define _PROJECTGIRAFFE_TAB5_H_

#include <FBase.h>
#include <FUi.h>
#include <Fnet.h>
#include <FWeb.h>
#include "User.h"
#include "UserPopup.h"
#include "StatusPopup.h"
#include "JsonParser.h"

class ProjectGiraffeTab5 :
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::IKeypadEventListener,
	public User::UserListener,
	public HttpConnection::HttpConnectionListener
{
public:
	ProjectGiraffeTab5(void);
	virtual ~ProjectGiraffeTab5(void);
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

	// IKeypadEventListener
	virtual void OnKeypadActionPerformed(Tizen::Ui::Control &source, Tizen::Ui::KeypadAction keypadAction);
	virtual void OnKeypadBoundsChanged(Tizen::Ui::Control &source);
	virtual void OnKeypadClosed(Tizen::Ui::Control &source);
	virtual void OnKeypadOpened(Tizen::Ui::Control &source);
	virtual void OnKeypadWillOpen(Tizen::Ui::Control &source);

	// UserListener
	virtual void onUserUpdate(User *user);

	// HttpConnectionListener
	virtual void connectionDidFinish(HttpConnection *connection, Tizen::Base::Collection::HashMap *response);
	virtual void connectionDidFail(HttpConnection *connection);

private:
	static const int ID_BUTTON_LOGIN = 501;
	static const int ID_BUTTON_LOGOUT = 502;
	static const int ID_BUTTON_UPDATE1 = 503;
	static const int ID_BUTTON_UPDATE2 = 504;

	void showLoginButton(void);
	void showProfile(void);

	void updateUser(void);
	void updatePassword(void);

	void logout(void);

	void showStatus(const Tizen::Base::String &statusTitle, const Tizen::Base::String &statusMessage, bool isError);
	void resetButtons(void);
};

#endif // _PROJECTGIRAFFE_TAB5_H_
