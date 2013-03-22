#ifndef _PROJECTGIRAFFE_TAB4_H_
#define _PROJECTGIRAFFE_TAB4_H_

#include <FBase.h>
#include <FUi.h>
#include <Fnet.h>
#include <FWeb.h>
#include "User.h"

class ProjectGiraffeTab4 :
	public Tizen::Ui::Controls::ScrollPanel,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::IKeypadEventListener,
	public Tizen::Net::Http::IHttpTransactionEventListener
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

	// IHttpTransactionEventListener
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, result r);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, Tizen::Base::String *pCert);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired);
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int availableBodyLen);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int recommendedChunkSize);

private:
	static const int ID_BUTTON_LOGIN = 401;
	static const int ID_BUTTON_AVATAR = 402;
	static const int ID_BUTTON_UPDATE1 = 403;
	static const int ID_BUTTON_UPDATE2 = 404;

	void showLoginButton(void);
	void showProfile(void);
};

#endif // _PROJECTGIRAFFE_TAB4_H_
