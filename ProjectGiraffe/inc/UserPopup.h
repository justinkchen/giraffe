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

class UserPopup
	: public Tizen::Ui::Controls::Popup
    , public Tizen::Ui::IActionEventListener
	, public Tizen::Net::Http::IHttpTransactionEventListener
{
public:
	UserPopup(void);
	virtual ~UserPopup();

	void ShowPopup(void);
	void HidePopup(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	// ITextEventListener
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);

	// IHttpTransactionEventListener
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, result r);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, Tizen::Base::String *pCert);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired);
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int availableBodyLen);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int recommendedChunkSize);




private:
	static const int ID_BUTTON_LOG_IN = 501;
	static const int ID_BUTTON_SIGN_UP = 502;
	static const int ID_BUTTON_CLOSE_POPUP = 503;
	//TODO: toggle button

	void ShowLogin(void);
	void ShowSignup(void);

	void SubmitLogin(void);
	void SubmitSignup(void);
};

#endif /* USERPOPUP_H_ */
