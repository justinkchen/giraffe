/*
 * GraffitiCell.h
 *
 *  Created on: Mar 3, 2013
 *      Author: kkhorimoto
 */

#ifndef GRAFFITICELL_H_
#define GRAFFITICELL_H_

#include <FBase.h>
#include <FUi.h>
#include "Graffiti.h"

class GraffitiCellContentView
    : public Tizen::Ui::Controls::Panel
{
    public:
	    // Accessors
	    Graffiti *graffiti() { return _graffiti; }
	    void setGraffiti(Graffiti *graffiti);

	    virtual result OnInitializing(void);

    private:
        Graffiti *_graffiti;

        void layoutSubviews();

        Tizen::Base::String distanceString();
        int nameLabelFontSize();
        int distanceLabelFontSize();
        int textLabelFontSize();
        Tizen::Ui::Controls::Label *_nameLabel;
        Tizen::Ui::Controls::Label *_distanceLabel;
        Tizen::Ui::Controls::Label *_textLabel;
};


#endif /* GRAFFITICELL_H_ */
