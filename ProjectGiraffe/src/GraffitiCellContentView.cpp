/*
 * GraffitiCell.cc
 *
 *  Created on: Mar 3, 2013
 *      Author: kkhorimoto
 */

#include "GraffitiCellContentView.h"
#include <FGraphics.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Media;

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

GraffitiCellContentView::GraffitiCellContentView() :
	_graffiti(null),
	_nameLabel(null),
	_distanceLabel(null),
	_textLabel(null){

}

GraffitiCellContentView::~GraffitiCellContentView() {
	// TODO Auto-generated destructor stub
}

int GraffitiCellContentView::nameLabelFontSize() { return 16; }
int GraffitiCellContentView::distanceLabelFontSize() { return 14; }
int GraffitiCellContentView::textLabelFontSize() { return 16; }

void GraffitiCellContentView::layoutSubviews()
{
    Rectangle bounds = GetBounds();

	// nameLabel
	if (_nameLabel) {
		RemoveControl(*_nameLabel);
		delete _nameLabel;
		_nameLabel = null;
	}
    _nameLabel = new Label();
    _nameLabel->Construct(Rectangle(0, 0, bounds.width, bounds.height), _graffiti->user()->username());
    _nameLabel->SetTextConfig(nameLabelFontSize(), LABEL_TEXT_STYLE_BOLD);
    AddControl(*_nameLabel);

    // distanceLabel
    if (_distanceLabel) {
    	RemoveControl(*_distanceLabel);
    	delete _distanceLabel;
    }
    _distanceLabel = new Label();
    _distanceLabel->Construct(Rectangle(bounds.width / 2, 0, bounds.width / 2, 20), _graffiti->text());
    _distanceLabel->SetTextConfig(distanceLabelFontSize(), LABEL_TEXT_STYLE_NORMAL);
    AddControl(*_distanceLabel);

    // textLabel
    if (_textLabel) {
    	RemoveControl(*_textLabel);
    	delete _textLabel;
    }
    _textLabel = new Label();
    _textLabel->Construct(Rectangle(0, 20, bounds.width, 40), distanceString());
    _textLabel->SetTextConfig(textLabelFontSize(), LABEL_TEXT_STYLE_NORMAL);
    AddControl(*_textLabel);
}

void GraffitiCellContentView::sizeToFit()
{

}

String GraffitiCellContentView::distanceString()
{
	// TODO: actually calculate the distance and use that value here.
	String distanceString = L"xx ft.";
	return distanceString;
}

void GraffitiCellContentView::setGraffiti(Graffiti *graffiti) {
	if (_graffiti != graffiti) {
		_graffiti = graffiti;
		layoutSubviews();
	}
}
