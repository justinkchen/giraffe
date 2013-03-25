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
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::IAnimationEventListener
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

	// IAnimationEventListener
	virtual void OnAnimationStopped(const Tizen::Ui::Control& source);

private:
	static const int ID_BUTTON_CLOSE_POPUP = 601;
	static const int DURATION = 500;
	static const int PROGRESS_COUNT = 30;
	Tizen::Ui::RelativeLayout _popupLayout;

	bool _locationFound;

	Tizen::Base::Collection::ArrayList* _animationFrameList;
	Tizen::Ui::Controls::Animation* _launchAnimation;
};

#endif /* LAUNCHPOPUP_H_ */
