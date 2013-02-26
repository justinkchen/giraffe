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
#ifndef _CUSTOM_BUTTON_H_
#define _CUSTOM_BUTTON_H_

#include <FBase.h>
#include <FUi.h>

// forward declaration
class CustomButton;


class IClickListener
{
// Life-cycle
public:
	IClickListener(void) {}
	virtual ~IClickListener(void) {}
	virtual void OnClicked(CustomButton& source) {}
}; // IClickListener

class CustomButton
	: public Tizen::Ui::Container
{
// Life-cycle
public:
	CustomButton(void);
	virtual ~CustomButton(void);

	bool Construct(const Tizen::Graphics::Rectangle& rect);
	virtual void CleanUp(void);
	void SetClickListener(const IClickListener* pListener);
	void SetText(const Tizen::Base::String& text);
	Tizen::Base::String GetText(void) const;
	virtual void OnEvaluateSize(Tizen::Graphics::Dimension &evaluatedSize);
	virtual result OnBoundsChanging(const Tizen::Graphics::Rectangle& oldRect, const Tizen::Graphics::Rectangle& newRect);
	virtual void OnBoundsChanged(const Tizen::Graphics::Rectangle& oldRect, const Tizen::Graphics::Rectangle& newRect);
	virtual result OnDraw(void);

protected:
	void* _pImpl;
}; // CustomButton

#endif // _CUSTOM_BUTTON_H_
