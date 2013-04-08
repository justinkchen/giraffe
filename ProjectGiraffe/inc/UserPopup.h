/*
 * UserPopup.h
 *
 *  Created on: Mar 15, 2013
 *      Author: bryancheng
 */

#ifndef USERPOPUP_H_
#define USERPOPUP_H_

#include <FBase.h>
#include <FUi.h>
#include <FWebJson.h>
#include <Fnet.h>
#include <FWeb.h>

#include "User.h"
#include "JsonParser.h"
#include "HttpConnection.h"

class UserPopup:
	public Tizen::Ui::Controls::Popup,
    public Tizen::Ui::IActionEventListener,
    public Tizen::Ui::IKeypadEventListener,
    public HttpConnection::HttpConnectionListener
{
public:
	static UserPopup *popup(void);

	UserPopup(void);
	virtual ~UserPopup();

	void showPopup(void);
	void hidePopup(void);

	// IActionEventListener
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	// IKeypadEventListener
	virtual void OnKeypadActionPerformed(Tizen::Ui::Control &source, Tizen::Ui::KeypadAction keypadAction);
	virtual void OnKeypadBoundsChanged(Tizen::Ui::Control &source);
	virtual void OnKeypadClosed(Tizen::Ui::Control &source);
	virtual void OnKeypadOpened(Tizen::Ui::Control &source);
	virtual void OnKeypadWillOpen(Tizen::Ui::Control &source);

	// HttpConnectionListener
	virtual void connectionDidFinish(HttpConnection *connection, Tizen::Base::Collection::HashMap *response);
	virtual void connectionDidFail(HttpConnection *connection);

private:
	static const int ID_BUTTON_CLOSE_POPUP = 501;
	static const int ID_BUTTON_LOGIN = 502;
	static const int ID_BUTTON_SIGNUP = 503;
	static const int ID_BUTTON_VIEW_LOGIN = 504;
	static const int ID_BUTTON_VIEW_SIGNUP = 505;

	void showLogin(void);
	void showSignup(void);

	void submitLogin(void);
	void submitSignup(void);

	void showError(const Tizen::Base::String &errorMessage);
	void resetButtons(void);
};

#endif /* USERPOPUP_H_ */
