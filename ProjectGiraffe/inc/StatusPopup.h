/*
 * StatusPopup.h
 *
 *  Created on: Apr 2, 2013
 *      Author: bryancheng
 */

#ifndef STATUSPOPUP_H_
#define STATUSPOPUP_H_

#include <FBase.h>
#include <FUi.h>


class StatusPopup:
	public Tizen::Ui::Controls::Popup,
	public Tizen::Ui::ITouchEventListener
{
public:
	enum StatusType
	{
		STATUS_POPUP_DEFAULT,
		STATUS_POPUP_ERROR
	};

	static StatusPopup *popup(void);

	StatusPopup();
	virtual ~StatusPopup();

	void showPopup(void);
	void setTitle(const Tizen::Base::String &title);
	void setMessage(const Tizen::Base::String &message);
	void setType(StatusType type);

	// ITouchEventListener
	virtual void OnTouchCanceled (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusIn (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusOut (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchMoved (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchReleased (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);

private:
	Tizen::Ui::Controls::TextBox *messageBox;

	void hidePopup(void);
};

#endif /* STATUSPOPUP_H_ */
