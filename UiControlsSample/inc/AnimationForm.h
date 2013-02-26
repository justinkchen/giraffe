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
#ifndef _ANIMATION_FORM_H_
#define _ANIMATION_FORM_H_

#include <FApp.h>
#include "BaseForm.h"

class AnimationForm
	: public BaseForm
	, public Tizen::Ui::IAnimationEventListener
{
public:
	AnimationForm(void);
	virtual ~AnimationForm(void);

	virtual result OnInitializing(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnAnimationStopped(const Tizen::Ui::Control& source);
	virtual bool Initialize(void);

private:
	static const int ID_BUTTON_ANIMATION_PLAY = 701;
	static const int ID_BUTTON_ANIMATION_STOP = 702;
	static const int ID_BUTTON_ANIMATION_PAUSE = 703;

	Tizen::Ui::Controls::Animation* __pAnimation;
	Tizen::Base::Collection::ArrayList* __pAnimationFrameList;
	Tizen::Ui::Controls::Button* __pAniPlayButton;
	Tizen::Ui::Controls::Button* __pAniPauseButton;
	Tizen::Ui::Controls::Button* __pAniStopButton;
}; // AnimationForm

#endif // _ANIMATION_FORM_H_

