/*
 * GraffitiCell.cc
 *
 *  Created on: Mar 3, 2013
 *      Author: kkhorimoto
 */

#include "GraffitiCell.h"
#include <FGraphics.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Media;

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

GraffitiCell::GraffitiCell() {}
GraffitiCell::~GraffitiCell() {}

bool GraffitiCell::Initialize()
{
	return true;
    //return !IsFailed(Construct(L"GRAFFITI_CELL"));
}

int GraffitiCell::nameLabelFontSize() { return 16; }
int GraffitiCell::distanceLabelFontSize() { return 14; }
int GraffitiCell::textLabelFontSize() { return 16; }

result GraffitiCell::OnInitializing(void)
{
    // Flexible width layout
    const Form *form = dynamic_cast<Form *>(GetParent());
    RelativeLayout* layout = dynamic_cast<RelativeLayout *>(form->GetLandscapeLayoutN());
    layout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
    delete layout;
    layout = dynamic_cast<RelativeLayout *>(form->GetPortraitLayoutN());
    layout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
    delete layout;

    Rectangle bounds = form->GetClientAreaBounds();
    _nameLabel = new Label();
    _nameLabel->Construct(Rectangle(0, 0, bounds.width / 2, 20), L"");
    _nameLabel->SetTextConfig(nameLabelFontSize(), LABEL_TEXT_STYLE_BOLD);
    AddControl(*_nameLabel);

    _distanceLabel = new Label();
    _distanceLabel->Construct(Rectangle(bounds.width / 2, 0, bounds.width / 2, 20), L"");
    _distanceLabel->SetTextConfig(distanceLabelFontSize(), LABEL_TEXT_STYLE_NORMAL);
    AddControl(*_distanceLabel);

    _textLabel = new Label();
    _textLabel->Construct(Rectangle(0, 20, bounds.width, 40), L"");
    _textLabel->SetTextConfig(textLabelFontSize(), LABEL_TEXT_STYLE_NORMAL);
    AddControl(*_textLabel);

    return E_SUCCESS;
}

result GraffitiCell::OnTerminating(void)
{
    return E_SUCCESS;
}

void GraffitiCell::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
    			       const Tizen::Ui::Scenes::SceneId& currentSceneId, 
                       Tizen::Base::Collection::IList* pArgs)
{
}
	    
void GraffitiCell::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
					    const Tizen::Ui::Scenes::SceneId& nextSceneId)
{

}

void GraffitiCell::setUsername(String username)
{
    _username = username;
    _nameLabel->SetText(_username);
}

void GraffitiCell::setText(String text)
{
    _text = text;
    _textLabel->SetText(_text);
}

void GraffitiCell::setDistance(float distance)
{
    _distance = distance;

    String distanceString = L"";
    distanceString.Format(10, L"%d ft.", _distance);
    _distanceLabel->SetText(distanceString);
}
