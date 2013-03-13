/*
 * EnrichedLabel.h
 *
 *  Created on: Mar 11, 2013
 *      Author: kkhorimoto
 */

#ifndef ENRICHEDLABEL_H_
#define ENRICHEDLABEL_H_

#include <FBase.h>
#include <FUi.h>
#include <climits>

class EnrichedLabel :
    public Tizen::Ui::Controls::Panel
{
public:
	EnrichedLabel();
	virtual ~EnrichedLabel();

	virtual void OnBoundsChanged(const Tizen::Graphics::Rectangle& oldRect, const Tizen::Graphics::Rectangle& newRect);
	virtual result OnDraw();

	static Tizen::Graphics::Dimension sizeThatFitsInWidth(Tizen::Base::String text, Tizen::Graphics::Font *font, int maxWidth = INT_MAX);
	void sizeToFitInWidth(int width);

	// Accessors
	Tizen::Base::String text();
	void setText(Tizen::Base::String text);
	Tizen::Graphics::Font *font();
	void setFont(Tizen::Graphics::Font *font);
    Tizen::Graphics::Color textColor(); 
    void setTextColor(Tizen::Graphics::Color color);

private:
    Tizen::Graphics::TextElement *_textElement;
    Tizen::Graphics::Font *_font;
	Tizen::Graphics::EnrichedText *_enrichedText;
	Tizen::Graphics::Canvas *_lastCanvas;
};

#endif /* ENRICHEDLABEL_H_ */
