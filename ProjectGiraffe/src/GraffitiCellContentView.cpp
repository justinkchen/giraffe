/*
 * GraffitiCell.cc
 *
 *  Created on: Mar 3, 2013
 *      Author: kkhorimoto
 */

#include "GraffitiCellContentView.h"
#include "ProjectGiraffeMainForm.h"
#include "User.h"
#include "EnrichedLabel.h"
#include "Macros.h"
#include "ControlUtilities.h"
#include <FGraphics.h>
#include <math.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Media;

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace ControlUtil;

GraffitiCellContentView::GraffitiCellContentView() :
	_graffiti(null),
	_nameLabelFont(new Font()),
	_distanceLabelFont(new Font()),
	_textLabelFont(new Font()),
	_nameLabel(null),
	_distanceLabel(null),
	_textLabel(null)
{
	_nameLabelFont->Construct(FONT_STYLE_BOLD, 38);
	_distanceLabelFont->Construct(FONT_STYLE_PLAIN, 30);
	_textLabelFont->Construct(FONT_STYLE_PLAIN, 36);
}

GraffitiCellContentView::~GraffitiCellContentView() {
//	delete _graffiti;
	delete _nameLabel;
	delete _distanceLabel;
	delete _textLabel;
	delete _nameLabelFont;
	delete _distanceLabelFont;
	delete _textLabelFont;
}

const int kCellInset = 20;
const int kCellSeparatorPadding = 10;

void GraffitiCellContentView::layoutSubviews()
{
    Rectangle bounds = GetBounds();

    AppLog("graffiti cell layoutsubviews");

	// nameLabel
    if (!_nameLabel) {
        _nameLabel = new EnrichedLabel();
        _nameLabel->Construct(kRectConstruct);
        _nameLabel->setFont(_nameLabelFont);
        _nameLabel->setTextColor(kTextColor);
        AddControl(*_nameLabel);
    }
    AppLog("setting username");
    _nameLabel->setText(_graffiti->user()->username());
    _nameLabel->sizeToFitInWidth(bounds.width - 2 * kCellInset);
    _nameLabel->SetPosition(kCellInset, kCellInset);

    // distanceLabel
    if (!_distanceLabel) {
        _distanceLabel = new EnrichedLabel();
        _distanceLabel->Construct(kRectConstruct);
        _distanceLabel->setFont(_distanceLabelFont);
        _distanceLabel->setTextColor(Color::GetColor(COLOR_ID_GREY));
        AddControl(*_distanceLabel);
    }
    AppLog("setting distance");
    _distanceLabel->setText(distanceString());
    _distanceLabel->sizeToFitInWidth(bounds.width - 2 * kCellInset - rightEdge(_nameLabel));
    centerVertically(_distanceLabel, _nameLabel);
    setBoundsX(_distanceLabel, rightEdge(_nameLabel) + kCellInset);

    // textLabel
    if (!_textLabel) {
        _textLabel = new EnrichedLabel();
        _textLabel->Construct(kRectConstruct);
        _textLabel->setFont(_textLabelFont);
        _textLabel->setTextColor(kTextColor);
        AddControl(*_textLabel);
    }
    AppLog("setting text");
    _textLabel->setText(_graffiti->text());
    _textLabel->sizeToFitInWidth(bounds.width - 2 * kCellInset);
    _textLabel->SetPosition(kCellInset, bottomEdge(_nameLabel) + kCellSeparatorPadding);
}

void GraffitiCellContentView::sizeToFit()
{
	Dimension size = GetSize();
	size.height = kCellInset; // top inset
	size.height += EnrichedLabel::sizeThatFitsInWidth(_graffiti->user()->username(), _distanceLabelFont, size.width - 2 * kCellInset).height; // nameLabel height
	size.height += kCellSeparatorPadding; // separator padding
	size.height += EnrichedLabel::sizeThatFitsInWidth(_graffiti->text(), _textLabelFont, size.width - 2 * kCellInset).height; // textLabel height
	size.height += kCellInset; // bottom inset
	SetSize(size);
}

String GraffitiCellContentView::distanceString()
{
	// TODO: actually calculate the distance and use that value here.
	double lat = ProjectGiraffeMainForm::currentLatitude;
	double lon = ProjectGiraffeMainForm::currentLongitude;
	double earthRadius = 6371.0;
	double dLatRad = (_graffiti->latitude() - lat) * M_PI / 180.0;
	double dLonRad = (_graffiti->longitude() - lon) * M_PI / 180.0;
	double currLatRad = lat * M_PI / 180.0;
	double graffitiLatRad = _graffiti->latitude() * M_PI / 180.0;

	AppLog("current lat : %f", lat);
	AppLog("current lon : %f", lon);
	AppLog("graffiti lat : %f", _graffiti->latitude());
	AppLog("graffiti lon : %f", _graffiti->longitude());

	double a = sin(dLatRad / 2.0) * sin(dLatRad / 2.0) +
			   sin(dLonRad / 2.0) * sin(dLonRad / 2.0) * cos(currLatRad) * cos(graffitiLatRad);
	double c = 2 * atan2(sqrt(a), sqrt(1.0 - a));
	double distance = earthRadius * c;

	String distanceString;
	distanceString.Format(17, L"%f km.", distance);
	return distanceString;
}

void GraffitiCellContentView::setGraffiti(Graffiti *graffiti) {
	if (_graffiti != graffiti) {
		_graffiti = graffiti;
		layoutSubviews();
	}
}
