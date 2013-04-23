#ifndef _PROJECTGIRAFFE_TAB5_H_
#define _PROJECTGIRAFFE_TAB5_H_

#include <FBase.h>
#include <FUi.h>
#include "User.h"
#include "HttpConnection.h"

class ProjectGiraffeTab5 :
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::IActionEventListener,
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

	// UserListener
	virtual void onUserUpdate(User *user);

	// HttpConnectionListener
	virtual void connectionDidFinish(HttpConnection *connection, Tizen::Base::Collection::HashMap *response);
	virtual void connectionDidFail(HttpConnection *connection);

private:
	static const int ID_BUTTON_LOGIN = 401;

	void showLoginButton(void);
	void showProfile(void);
};

#endif // _PROJECTGIRAFFE_TAB5_H_
