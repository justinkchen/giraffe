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
	_enrichedText->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);
	_enrichedText->SetTextAbbreviationEnabled(false);
	_enrichedText->Add(*_textElement);
}

EnrichedLabel::~EnrichedLabel() {
	// TODO Auto-generated destructor stub
}

result EnrichedLabel::OnDraw()
{
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
	int lineBeginIndex = 0;
	int lastSpaceIndex = 0;
	int lineCount = 1;
	int maxNeededWidth = 0;
	for (int i = 0; i < text.GetLength(); i++) {

		// Update prevSpaceIndex
		wchar_t ch;
		text.GetCharAt(i,ch);
		if (ch == ' ') {
			lastSpaceIndex = i;
		}

		// Calculate line substring
		String substring;
		text.SubString(lineBeginIndex, i - lineBeginIndex + 1, substring);

		// Calculate size of line using font
		Dimension dim;
		font->GetTextExtent(substring, substring.GetLength(), dim);
		maxNeededWidth = fmax(maxNeededWidth, dim.width);

		// Update lineCount if necessary
		if (dim.width > maxWidth) {
			if (lastSpaceIndex == 0) {
				// The string begins with a word that requires more width than
				// maxWidth, so it will be character line wrapped.  We just set
				// it to the current index regardless of if it's the beginning of a word.
				lineBeginIndex = i;
			} else if (lineBeginIndex == lastSpaceIndex + 1) {
				// If we haven't encountered any spaces since the last time we passed
				// maxWidth, we also need to use use the current character despite the
				// fact that it isn't the beginning of a word.
				lineBeginIndex = i;
			} else {
				// The line's width is greater than maxWidth and we've encountered a
				// space in the current line, so we begin the next line with the word
				// following the last encountered space.
				lineBeginIndex = lastSpaceIndex + 1;
			}
			lineCount++;
		}
	}

	// Calculate size that fits
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
