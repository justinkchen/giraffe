/*
 * LoadingPopupThread.h
 *
 *  Created on: Apr 2, 2013
 *      Author: Johan
 */

#ifndef LOADINGPOPUPTHREAD_H_
#define LOADINGPOPUPTHREAD_H_

#include <FUi.h>
#include "LoadingPopup.h"

class LoadingPopupThread
	:public Tizen::Base::Runtime::EventDrivenThread
{
public:
	LoadingPopupThread(void);
	virtual ~LoadingPopupThread(void);

	result Construct(void);
	bool OnStart(void);
	void OnStop(void);

private:
	const Tizen::Ui::Control* __pUiControl;
    LoadingPopup* __lPopup;
};
#endif /* LOADINGPOPUPTHREAD_H_ */
