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
	_likeButton(null),
	_flagButton(null),
	kLikeButtonText(L"Like"),
	kUnlikeButtonText(L"Unlike"),
	kFlagButtonText(L"Flag"),
	kUnflagButtonText(L"Unflag")
{
	// TODO Auto-generated constructor stub
}

GraffitiCellSocialContextView::~GraffitiCellSocialContextView() {
	// TODO Auto-generated destructor stub
//	if (_graffiti) _graffiti->removeListener(this);
}

const int kSocialButtonSeparator = 70;

result GraffitiCellSocialContextView::OnDraw()
{
	// likeButton
	if (!_likeButton) {
		_likeButton = new Button();
		_likeButton->Construct(Rectangle(0, 0, 200, 100), L"Button");
		_likeButton->AddActionEventListener(*this);
		AddControl(*_likeButton);
	}
	_likeButton->SetText(likeButtonText());
	centerVertically(_likeButton, this);
	setRightEdge(_likeButton, (GetWidth() - kSocialButtonSeparator) / 2);

	// likeButton
	if (!_flagButton) {
		_flagButton = new Button();
		_flagButton->Construct(Rectangle(0, 0, 200, 100), L"Button");
		_flagButton->AddActionEventListener(*this);
		_flagButton->SetColor(BUTTON_STATUS_NORMAL, Color::GetColor(COLOR_ID_RED));
		AddControl(*_flagButton);
	}
	_flagButton->SetText(flagButtonText());
	centerInRect(_flagButton, GetBounds());
	setBoundsX(_flagButton, (GetWidth() + kSocialButtonSeparator) / 2);

	return E_SUCCESS;
}

void GraffitiCellSocialContextView::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	if (&source == _likeButton) {
		AppLog("like button tapped");
		if (_graffiti) {
			bool wasLiked = _graffiti->likeCount() > 0;
			_graffiti->setLikeCount(wasLiked ? 0 : 1);
			Draw(true);
		}
	} else if (&source == _flagButton) {
		AppLog("flag button tapped");
		if (_graffiti) {
			_graffiti->setFlagged(!_graffiti->flagged());
			Draw(true);
		}
	}
}

void GraffitiCellSocialContextView::setGraffiti(Graffiti *graffiti)
{
	if (_graffiti != graffiti) {
		AppLog("set graffiti");
//		if (_graffiti) _graffiti->removeListener(this);
		_graffiti = graffiti;
//		if (_graffiti) _graffiti->addListener(this);
	}
}

String GraffitiCellSocialContextView::likeButtonText()
{
	return _graffiti && _graffiti->likeCount() ? kUnlikeButtonText : kLikeButtonText;
}

String GraffitiCellSocialContextView::flagButtonText()
{
	return _graffiti && _graffiti->flagged() ? kUnflagButtonText : kFlagButtonText;
}

void GraffitiCellSocialContextView::onLikeCount()
{
	// Refresh UI
	Draw(true);
}

void GraffitiCellSocialContextView::onFlagged()
{
	// Refresh UI
	Draw(true);
}
