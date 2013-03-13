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
#include "EnrichedLabel.h"
#include "Graffiti.h"

class GraffitiCellContentView
    : public Tizen::Ui::Controls::Panel
{
    public:

    	GraffitiCellContentView();
    	~GraffitiCellContentView();

    	void sizeToFit();

	    // Accessors
	    Graffiti *graffiti() { return _graffiti; }
	    void setGraffiti(Graffiti *graffiti);

    private:
        Graffiti *_graffiti;
        Tizen::Graphics::Font *_nameLabelFont;
        Tizen::Graphics::Font *_distanceLabelFont;
        Tizen::Graphics::Font *_textLabelFont;
        EnrichedLabel *_nameLabel;
        EnrichedLabel *_distanceLabel;
        EnrichedLabel *_textLabel;

        Tizen::Base::String distanceString();
        void layoutSubviews();
};


#endif /* GRAFFITICELL_H_ */
