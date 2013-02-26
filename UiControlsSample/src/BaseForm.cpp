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

#include "BaseForm.h"

using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

BaseForm::BaseForm(void)
{
}

BaseForm::~BaseForm(void)
{
}

bool
BaseForm::SetFooter(void)
{
	Footer* pFooter = GetFooter();
	pFooter->SetStyle(FOOTER_STYLE_SEGMENTED_TEXT);
	pFooter->SetBackButton();
	return true;
}

void
BaseForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_EXIT:
		SceneManager* pSceneManager = SceneManager::GetInstance();
		AppAssert(pSceneManager);
		pSceneManager->GoBackward(BackwardSceneTransition());
		break;
	}
}

result
BaseForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	SetFormBackEventListener(this);

	return r;
}

void
BaseForm::OnFormBackRequested(Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	pSceneManager->GoBackward(BackwardSceneTransition());
}
