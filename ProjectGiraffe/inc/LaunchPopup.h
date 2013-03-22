/*
 * LaunchPopup.h
 *
 *  Created on: Mar 21, 2013
 *      Author: Justin
 */

#ifndef LAUNCHPOPUP_H_
#define LAUNCHPOPUP_H_

#include <FBase.h>
#include <FUi.h>
#include <FWebJson.h>
#include <Fnet.h>
#include <FApp.h>

class LaunchPopup:
	public Tizen::Ui::Controls::Popup,
	public Tizen::Ui::IActionEventListener
{
public:
	LaunchPopup();
	virtual ~LaunchPopup();

	void ShowPopup(void);
	void HidePopup(void);

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);

	// IActionEventListener
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

private:
	static const int ID_BUTTON_CLOSE_POPUP = 601;

};

#endif /* LAUNCHPOPUP_H_ */
