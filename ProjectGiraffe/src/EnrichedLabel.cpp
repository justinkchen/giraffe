/*
 * EnrichedLabel.cpp
 *
 *  Created on: Mar 11, 2013
 *      Author: kkhorimoto
 */

#include "EnrichedLabel.h"
#include "Macros.h"
#include <algorithm>

using namespace Tizen::Base;
using namespace Tizen::Graphics;

EnrichedLabel::EnrichedLabel() :
	_lastCanvas(NULL)
{
	// Create textElement
    _textElement = new TextElement();
    _textElement->Construct();

    // Create enrichedText
	_enrichedText = new EnrichedText();
	_enrichedText->Construct(kDimConstruct);
	_enrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
	_enrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
	_enrichedText->SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
	_enrichedText->SetTextAbbreviationEnabled(false);
	_enrichedText->Add(*_textElement);
}

EnrichedLabel::~EnrichedLabel() {
	// TODO Auto-generated destructor stub
}

result EnrichedLabel::OnDraw()
{
	AppLog("Enriched label onDraw");
	_lastCanvas = GetCanvasN();
	_lastCanvas->Clear();
	_lastCanvas->DrawText(Point(0, 0), *_enrichedText);
	_lastCanvas->Show();

	return E_SUCCESS;
}

void EnrichedLabel::OnBoundsChanged(const Tizen::Graphics::Rectangle& oldRect, const Tizen::Graphics::Rectangle& newRect)
{
	if (oldRect != newRect) {
		if (_lastCanvas) {
			_lastCanvas->Clear();
			delete _lastCanvas;
			_lastCanvas = null;
		}
	}
}

Dimension EnrichedLabel::sizeThatFitsInWidth(Tizen::Base::String text, Tizen::Graphics::Font *font, int maxWidth)
{
	int textLength = text.GetLength();
	int prevLineCharIndex = 0;
	int lineCount = 0;
	int maxNeededWidth = 0;
	AppLog("maxWidth = %d", maxWidth);
	for (int i = 0; i < textLength; i++) {
		AppLog("lineCount = %d", lineCount);

		// Calculate line substring
		String substring;
		text.SubString(prevLineCharIndex, i - prevLineCharIndex + 1, substring);
		AppLog("substring line: %ls", substring.GetPointer());

		// Calculate size of line using font
		Dimension dim;
		font->GetTextExtent(substring, substring.GetLength(), dim);
		maxNeededWidth = fmax(maxNeededWidth, dim.width);
		AppLog("line width: %d", dim.width);

		// Update lineCount if necessary
		if (dim.width > maxWidth) {
			prevLineCharIndex = i;
			lineCount++;
		}
	}
	lineCount++;

	// Resize the label
	int newWidth = fmin(maxWidth, maxNeededWidth);
	int newHeight = lineCount * font->GetMaxHeight();
	return Dimension(newWidth, newHeight);
}

void EnrichedLabel::sizeToFitInWidth(int width)
{
	Dimension newSize = sizeThatFitsInWidth(this->text(), _font, width);
	_enrichedText->SetSize(newSize.width, newSize.height);
	SetSize(newSize.width, newSize.height);
	AppLog("enriched label newSize: (%d, %d)", newSize.width, newSize.height);
}

String EnrichedLabel::text()
{
    return _textElement->GetText();
}

void EnrichedLabel::setText(String text)
{
   _textElement->SetText(text); 
   RequestRedraw(true);
}

Font *EnrichedLabel::font()
{
    return _font;
}

void EnrichedLabel::setFont(Font *font)
{
	_font = font;
    _textElement->SetFont(*_font);
    RequestRedraw(true);
}

Color EnrichedLabel::textColor()
{
    return _textElement->GetTextColor();
}

void EnrichedLabel::setTextColor(Color color)
{
    _textElement->SetTextColor(color);
    RequestRedraw(true);
}
