//
// Tizen native SDK
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "CustomButton.h"

using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

const Color BUTTON_NORMAL_BLACKGROUND_COLOR = Color(219, 219, 219, 255);
const Color BUTTON_NORMAL_FOREGROUND_COLOR = Color(0, 0, 0, 255);
const Color BUTTON_PRESSED_BLACKGROUND_COLOR = Color(57, 169, 251, 255);
const Color BUTTON_PRESSED_FOREGROUND_COLOR = Color(255, 255, 255, 255);
const Rectangle CUSTOM_CONTROL_SIZE = Rectangle(0, 0, 100, 100);

const int CUSTOM_BUTTON_MIN_SIZE = 100;
const int CUSTOM_BUTTON_MAX_SIZE = 400;
const int BUTTON_STATE_NORMAL = 0;
const int BUTTON_STATE_PRESSED = 1;
const int BUTTON_STATE_MAX = 2;

const int BUTTON_COLOR_BG_NORMAL = 0;
const int BUTTON_COLOR_FG_NORMAL = 1;
const int BUTTON_COLOR_BG_PRESSED = 2;
const int BUTTON_COLOR_FG_PRESSED = 3;
const int BUTTON_COLOR_MAX = 4;

#define GetImpl(x)	((CustomButtonImpl*) (x))

class CustomButtonImpl :
	public ITouchEventListener
{
public:
	CustomButtonImpl(void)
	{
		_pButton = null;
		_pListener = null;
		_state	= BUTTON_STATE_NORMAL;
	}

	bool Construct(CustomButton* pButton)
	{
		if (pButton != null)
		{
			_pButton = pButton;

			_pallete[BUTTON_COLOR_BG_NORMAL]  = BUTTON_NORMAL_BLACKGROUND_COLOR;
			_pallete[BUTTON_COLOR_FG_NORMAL]  = BUTTON_NORMAL_FOREGROUND_COLOR;
			_pallete[BUTTON_COLOR_BG_PRESSED] = BUTTON_PRESSED_BLACKGROUND_COLOR;
			_pallete[BUTTON_COLOR_FG_PRESSED] = BUTTON_PRESSED_FOREGROUND_COLOR;

			_bounds = _pButton->GetBounds();

			return true;
		}
		return false;
	}

	virtual ~CustomButtonImpl(void)
	{
	}

public:
	int GetState(void) const
	{
		return _state;
	}

	void SetState(int newState)
	{
		_state = newState;
	}


	IClickListener* GetClickListener(void) const
	{
		return _pListener;
	}


	void SetClickListener(const IClickListener* pListener)
	{
		_pListener = const_cast<IClickListener*>(pListener);
	}

	virtual void OnTouchCanceled(const Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo)
	{
		if (GetState() == BUTTON_STATE_PRESSED)
		{
			SetState(BUTTON_STATE_NORMAL);
			_pButton->Invalidate(false);
		}
	}

	virtual void OnTouchDoublePressed (const Control& source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
	}

	virtual void OnTouchFocusIn (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
	}

	virtual void OnTouchFocusOut (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
	}

	virtual void OnTouchLongPressed (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
	}

	virtual void OnTouchMoved (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
	}

	virtual void OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
		if (GetState() == BUTTON_STATE_NORMAL)
		{
			SetState(BUTTON_STATE_PRESSED);
			_pButton->Invalidate(false);
		}
	}

	virtual void OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
		if (GetState() == BUTTON_STATE_PRESSED)
		{
			SetState(BUTTON_STATE_NORMAL);
			_pButton->Invalidate(false);

			if (_pListener)
			{
				_pListener->OnClicked(*_pButton);
			}
		}
	}

	virtual result DrawButton(Canvas& canvas)
	{
		canvas.SetBackgroundColor(Color(0, 0, 0, 0));
		canvas.Clear();

		if (_state == BUTTON_STATE_NORMAL)
		{
			canvas.FillRoundRectangle(_pallete[BUTTON_COLOR_BG_NORMAL], Rectangle(0, 0 , _bounds.width, _bounds.height), Dimension(5, 5));
		}
		else
		{
			canvas.FillRoundRectangle(_pallete[BUTTON_COLOR_BG_PRESSED], Rectangle(0, 0 , _bounds.width, _bounds.height), Dimension(5, 5));
		}

        Font font;
        font.Construct(FONT_STYLE_PLAIN, 18);
        canvas.SetFont(font);

        if (_text != L"")
        {
        	EnrichedText enriched;
        	enriched.Construct(Dimension(_bounds.width, _bounds.height));
        	enriched.SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
        	enriched.SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);

        	TextElement element;
        	element.Construct(_text);
    		if (_state == BUTTON_STATE_NORMAL)
    		{
    			element.SetTextColor(_pallete[BUTTON_COLOR_FG_NORMAL]);
    		}
    		else
    		{
    			element.SetTextColor(_pallete[BUTTON_COLOR_FG_PRESSED]);
    		}
    		enriched.Add(element);
    		canvas.DrawText(Point(0, 0), enriched);
    		enriched.RemoveAll(false);
        }

		return E_SUCCESS;
	}


	String GetText(void) const
	{
		return _text;
	}

	void SetText(const String& text)
	{
		_text = text;
	}

protected:
	CustomButton*	_pButton;
	IClickListener*	_pListener;
	int _state;
	String _text;
	Rectangle _bounds;
	Color _pallete[BUTTON_COLOR_MAX];
}; // CustomButtonImpl

CustomButton::CustomButton(void)
{

}

CustomButton::~CustomButton(void)
{
	CleanUp();
}

bool
CustomButton::Construct(const Rectangle& rect)
{
	result r = E_SUCCESS;
	// construct base class

	if (rect.width < CUSTOM_BUTTON_MIN_SIZE || rect.width > CUSTOM_BUTTON_MAX_SIZE)
	{
		return false;
	}

	if (rect.height  < CUSTOM_BUTTON_MIN_SIZE || rect.height > CUSTOM_BUTTON_MAX_SIZE)
	{
			return false;
	}

	r = Container::Construct(CUSTOM_CONTROL_SIZE, true, true);

	if (r != E_SUCCESS)
	{
		return false;
	}

	SetMinimumSize(Dimension(CUSTOM_BUTTON_MIN_SIZE,CUSTOM_BUTTON_MIN_SIZE));
	SetMaximumSize(Dimension(CUSTOM_BUTTON_MAX_SIZE,CUSTOM_BUTTON_MAX_SIZE));

	SetBounds(rect);

	CustomButtonImpl* pImpl = new (std::nothrow) CustomButtonImpl;
	if (pImpl == null)
	{
		return false;
	}

	if (!pImpl->Construct(this))
	{
		delete pImpl;
		return false;
	}

	SetDefaultTouchEventListener(pImpl);
	_pImpl = (void*) pImpl;

	return true;
}

void
CustomButton::CleanUp(void)
{
	if (_pImpl)
	{
		SetDefaultTouchEventListener(null);
		delete GetImpl(_pImpl);
		_pImpl = null;
	}
}

void
CustomButton::SetClickListener(const IClickListener* pListener)
{
	if (_pImpl)
	{
		GetImpl(_pImpl)->SetClickListener(pListener);
	}
}

void
CustomButton::SetText(const String& text)
{
	if (_pImpl)
	{
		GetImpl(_pImpl)->SetText(text);
	}
}

String
CustomButton::GetText(void) const
{
	if (_pImpl)
	{
		return GetImpl(_pImpl)->GetText();
	}
	return String(L"");
}



void
CustomButton::OnEvaluateSize(Dimension &evaluatedSize)
{
	if (evaluatedSize.width < CUSTOM_BUTTON_MIN_SIZE)
	{
		evaluatedSize.width = CUSTOM_BUTTON_MIN_SIZE;
	}
	if (evaluatedSize.width > CUSTOM_BUTTON_MAX_SIZE)
	{
		evaluatedSize.width = CUSTOM_BUTTON_MAX_SIZE;
	}

	if (evaluatedSize.height < CUSTOM_BUTTON_MIN_SIZE)
	{
		evaluatedSize.height = CUSTOM_BUTTON_MIN_SIZE;
	}
	if (evaluatedSize.height > CUSTOM_BUTTON_MAX_SIZE)
	{
		evaluatedSize.height = CUSTOM_BUTTON_MAX_SIZE;
	}
}

result
CustomButton::OnBoundsChanging(const Rectangle& oldRect, const Rectangle& newRect)
{
	return E_SUCCESS;
}

void
CustomButton::OnBoundsChanged(const Rectangle& oldRect, const Rectangle& newRect)
{
}

result
CustomButton::OnDraw(void)
{
	result r;
	if (_pImpl)
	{
		Canvas* pCanvas = GetCanvasN();
		if (pCanvas)
		{
			r = GetImpl(_pImpl)->DrawButton(*pCanvas);
			delete pCanvas;
		}
	}
	return r;
}
