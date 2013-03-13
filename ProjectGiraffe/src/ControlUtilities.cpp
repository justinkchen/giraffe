/*
 * ControlUtilities.cpp
 *
 *  Created on: Mar 12, 2013
 *      Author: kkhorimoto
 */

#include "ControlUtilities.h"

using namespace Tizen::Ui;
using namespace Tizen::Graphics;

void ControlUtil::setBoundsX(Tizen::Ui::Control *control, int x)
{
	Rectangle bounds = control->GetBounds();
	bounds.x = x;
	control->SetBounds(bounds);
}

void ControlUtil::setBoundsY(Tizen::Ui::Control *control, int y)
{
	Rectangle bounds = control->GetBounds();
	bounds.y = y;
	control->SetBounds(bounds);
}

void ControlUtil::setBoundsWidth(Tizen::Ui::Control *control, int width)
{
	Rectangle bounds = control->GetBounds();
	bounds.width = width;
	control->SetBounds(bounds);
}

void ControlUtil::setBoundsHeight(Tizen::Ui::Control *control, int height)
{
	Rectangle bounds = control->GetBounds();
	bounds.height = height;
	control->SetBounds(bounds);
}

int ControlUtil::rightEdge(Tizen::Ui::Control *control)
{
	Rectangle bounds = control->GetBounds();
	return bounds.x + bounds.width;
}

int ControlUtil::bottomEdge(Tizen::Ui::Control *control)
{
	Rectangle bounds = control->GetBounds();
	return bounds.y + bounds.height;
}

void ControlUtil::setRightEdge(Tizen::Ui::Control *control, int rightEdge)
{
	setBoundsX(control, rightEdge - control->GetWidth());
}

void ControlUtil::setBottomEdge(Tizen::Ui::Control *control, int bottomEdge)
{
	setBoundsY(control, bottomEdge - control->GetHeight());
}

void ControlUtil::centerInRect(Tizen::Ui::Control *controlToCenter, Tizen::Graphics::Rectangle rect)
{
	Rectangle centerBounds = controlToCenter->GetBounds();
	setBoundsY(controlToCenter, rect.y + (rect.height - centerBounds.height) / 2);
	setBoundsX(controlToCenter, rect.x + (rect.width - centerBounds.width) / 2);
}

void ControlUtil::centerVertically(Tizen::Ui::Control *controlToCenter, Tizen::Ui::Control *referenceControl)
{
	Rectangle referenceBounds = referenceControl->GetBounds();
	Rectangle centerBounds = controlToCenter->GetBounds();
	setBoundsY(controlToCenter, referenceBounds.y + (referenceBounds.height - centerBounds.height) / 2);
}

void ControlUtil::centerHorizontally(Tizen::Ui::Control *controlToCenter, Tizen::Ui::Control *referenceControl)
{
	Rectangle referenceBounds = referenceControl->GetBounds();
	Rectangle centerBounds = controlToCenter->GetBounds();
	setBoundsX(controlToCenter, referenceBounds.x + (referenceBounds.width - centerBounds.width) / 2);
}
