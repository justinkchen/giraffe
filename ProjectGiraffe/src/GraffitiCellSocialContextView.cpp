/*
 * GraffitiCellSocialContextItem.cpp
 *
 *  Created on: Mar 13, 2013
 *      Author: kkhorimoto
 */

#include "GraffitiCellSocialContextView.h"
#include "ControlUtilities.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace ControlUtil;

GraffitiCellSocialContextView::GraffitiCellSocialContextView() :
	_likeButton(null)
{
	// TODO Auto-generated constructor stub

}

GraffitiCellSocialContextView::~GraffitiCellSocialContextView() {
	// TODO Auto-generated destructor stub
}

String GraffitiCellSocialContextView::likeButtonText()
{
	String buttonText = L"Like Graffiti";
	if (_graffiti && _graffiti->likeCount()) {
		buttonText = L"Unlike Graffiti";
	}
	return buttonText;
}

result GraffitiCellSocialContextView::OnDraw()
{
	// likeButton
	if (!_likeButton) {
		_likeButton = new Button();
		_likeButton->Construct(Rectangle(0, 0, 400, 100), L"Button");
		_likeButton->AddActionEventListener(*this);
		AddControl(*_likeButton);
	}
	_likeButton->SetText(likeButtonText());
	centerInRect(_likeButton, GetBounds());

	return E_SUCCESS;
}

void GraffitiCellSocialContextView::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	if (&source == _likeButton) {
		AppLog("like button tapped");
		if (_graffiti) {
			_graffiti->setLikeCount(1);
			Draw(true);
		}
	}
}
