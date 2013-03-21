/*
 * LoadingPopup.h
 *
 *  Created on: Mar 21, 2013
 *      Author: Johan
 */

#ifndef LOADINGPOPUP_H_
#define LOADINGPOPUP_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FApp.h>
#include <FMedia.h>

class LoadingPopup
	: public Tizen::Ui::Controls::Popup
{
	public:

		LoadingPopup(void);
		virtual ~LoadingPopup();

		void ShowPopup(void);
		void HidePopup(void);

	private:
		Tizen::Ui::Controls::Animation* __pAnimation;
		Tizen::Base::Collection::ArrayList* __pAnimationFrameList;
};

#endif /* LOADINGPOPUP_H_ */
