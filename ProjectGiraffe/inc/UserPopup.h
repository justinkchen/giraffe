/*
 * UserPopup.h
 *
 *  Created on: Mar 15, 2013
 *      Author: bryancheng
 */

#ifndef USERPOPUP_H_
#define USERPOPUP_H_

class UserPopup
	: public Tizen::Ui::Controls::Popup
    , public Tizen::Ui::IActionEventListener
	, public Tizen::Net::Http::IHttpTransactionEventListener
{
public:
	UserPopup();
	//: __pPopup(null){}
	virtual ~UserPopup();

	void ShowPopup(void);
	void HidePopup(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

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

	void ShowLogin(void);
	void ShowSignup(void);
};

#endif /* USERPOPUP_H_ */
