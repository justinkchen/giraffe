#ifndef _PROJECTGIRAFFE_TAB4_H_
#define _PROJECTGIRAFFE_TAB4_H_

#include <FBase.h>
#include <FUi.h>
#include <Fnet.h>
#include <FWeb.h>
#include "User.h"
#include "UserPopup.h"
#include "StatusPopup.h"
#include "JsonParser.h"

class ProjectGiraffeTab4 :
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::IKeypadEventListener,
	public User::UserListener,
	public HTTPConnection::HTTPConnectionListener
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

	// IKeypadEventListener
	virtual void OnKeypadActionPerformed(Tizen::Ui::Control &source, Tizen::Ui::KeypadAction keypadAction);
	virtual void OnKeypadBoundsChanged(Tizen::Ui::Control &source);
	virtual void OnKeypadClosed(Tizen::Ui::Control &source);
	virtual void OnKeypadOpened(Tizen::Ui::Control &source);
	virtual void OnKeypadWillOpen(Tizen::Ui::Control &source);

	// UserListener
	virtual void onUserUpdate(User *user);

	// HTTPConnectionListener
	virtual void connectionDidFinish(HTTPConnection *connection, Tizen::Base::Collection::HashMap *response);
	virtual void connectionDidFail(HTTPConnection *connection);

private:
	static const int ID_BUTTON_LOGIN = 401;
	static const int ID_BUTTON_LOGOUT = 402;
	static const int ID_BUTTON_UPDATE1 = 403;
	static const int ID_BUTTON_UPDATE2 = 404;
	static const int ID_BUTTON_AVATAR = 405;

	void showLoginButton(void);
	void showProfile(void);

	void updateUser(void);
	void updatePassword(void);

	void logout(void);

	void showStatus(const Tizen::Base::String &statusTitle, const Tizen::Base::String &statusMessage, bool isError);
	void resetButtons(void);
};

#endif // _PROJECTGIRAFFE_TAB4_H_
