/*
 * StatusPopup.cpp
 *
 *  Created on: Apr 2, 2013
 *      Author: bryancheng
 */

#include "StatusPopup.h"

using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

StatusPopup *statusPopupSingleton = NULL;

StatusPopup *
StatusPopup::popup(void)
{
	if (!statusPopupSingleton) {
		statusPopupSingleton = new StatusPopup();
	}
	return statusPopupSingleton;
}

StatusPopup::StatusPopup()
{
	// TODO Auto-generated constructor stub
	Construct(true, Dimension(680,200));

	// initialize messageLabel
	// TODO: convert messageLabel to enrichedtext to allow text wrap
	messageLabel = new Label();
	messageLabel->Construct(Rectangle(0, 0, 660, 80), L"");
	messageLabel->SetName("messageLabel");
	messageLabel->SetTextConfig(40, LABEL_TEXT_STYLE_NORMAL);
	messageLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	messageLabel->SetTextVerticalAlignment(ALIGNMENT_TOP);
	AddControl(*messageLabel);

	AddTouchEventListener(*this);
}

StatusPopup::~StatusPopup()
{
	// TODO Auto-generated destructor stub

	// destroy messageLabel
}

void
StatusPopup::showPopup()
{
	Draw();
	SetShowState(true);
	Show();
}

void
StatusPopup::hidePopup()
{
	SetShowState(false);
	Invalidate(true);
}

void
StatusPopup::setTitle(const String &title)
{
	this->SetTitleText(title);
}

void
StatusPopup::setMessage(const String &message)
{
	messageLabel->SetText(message);
}

void
StatusPopup::setType(StatusType type)
{
	switch(type)
	{
	case STATUS_POPUP_DEFAULT:
		messageLabel->SetTextColor(Color(0x00, 0x00, 0x00));
		break;
	case STATUS_POPUP_ERROR:
		messageLabel->SetTextColor(Color(0xFF, 0x00, 0x00));
		break;
	default:
		messageLabel->SetTextColor(Color(0x00, 0x00, 0x00));
		break;
	}
}

void
StatusPopup::OnTouchCanceled (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{

}

void
StatusPopup::OnTouchFocusIn (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{

}

void
StatusPopup::OnTouchFocusOut (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{

}

void
StatusPopup::OnTouchMoved (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{

}

void
StatusPopup::OnTouchPressed (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	hidePopup();
}

void
StatusPopup::OnTouchReleased (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{

}
