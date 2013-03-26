//
// Tizen Native SDK
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

#ifndef _SAFE_MACROS_H_
#define _SAFE_MACROS_H_

#define SAFE_DELETE(x)  if (x) { delete x; x = null; }
#define SAFE_DELETE_ARRAY(x) if (x) { delete[] x; x = null; }
#define SAFE_RELEASE(x) if (x) { x->Release(); x = null; }

#define SIZE_OF_ARRAY(x)    (sizeof(x) / sizeof(x[0]))

#define SIZE_OF(x)          (SIZE_OF_ARRAY(x))
#define SIZEOF(x)           (SIZE_OF_ARRAY(x))

#define CONST_INT(x)        static const int x = __LINE__

#define _LINENAME_CONCAT(_name_, _line_) _name_ ## _line_
#define _LINENAME(_name_, _line_) _LINENAME_CONCAT(_name_, _line_)
#define _UNIQUE_VAR(_name_) _LINENAME(_name_, __LINE__)

#define SAFE_DELETE_ARRAYLIST(x) if (x) {x->RemoveAll(true); delete x; x = null; }
#define SAFE_DELETE_ARRAYLISTT(x) if (x) {x->RemoveAll(); delete x; x = null;}

#define SAFE_RETURN(type, var, list)  \
	{   type __type_var[] = list;	\
		for (int __i = 0; __i < sizeof(list) / sizeof(type); __i++)	\
			if (var == list[__i]) return var;	\
		return E_UNKNOWN;	\
	}

#define TRY_CATCH_RET(x)                    r = x; TryCatch(r == E_SUCCESS, , "%s %s", # x, GetErrorMessage(r))
#define TRY_CATCH_NUL(v, x)             v = x; TryCatch(v, r = GetLastResult(), "%s %s", # x, GetErrorMessage(GetLastResult()))
#define TRY_CATCH_NIL(x, err)               TryCatch(x, r = err, "%s is null", # x)
#define TRY_CATCH_RTV(x, msg, ...)      r = x; TryCatch(r == E_SUCCESS, , "%s %s" msg, # x, GetErrorMessage(r), __VA_ARGS__);

#define REGISTER_BUTTON(ctrlVar, rsrcId, actionId)	\
	ctrlVar = static_cast< Button* >(GetControl(rsrcId));	 \
	if (ctrlVar != null) { \
		ctrlVar->SetActionId(actionId);	\
		ctrlVar->AddActionEventListener(*this); }

#define REGISTER_BUTTON2(rsrcId, actionId)	\
	{ Tizen::Ui::Controls::Button* pButton = static_cast< Button* >(GetControl(rsrcId));	 \
	  if (pButton != null) { \
		  pButton->SetActionId(actionId); \
		  pButton->AddActionEventListener(*this); }	\
	}

#define REGISTER_CHECKBUTTON(ctrlVar, rsrcId, actionId1, actionId2)	\
	ctrlVar = static_cast< CheckButton* >(GetControl(rsrcId));	 \
	if (ctrlVar != null) { \
		ctrlVar->SetActionId(actionId1, actionId2);	 \
		ctrlVar->AddActionEventListener(*pThis); }

#define REGISTER_LIST(ctrlVar, rsrcId)	\
	ctrlVar = static_cast< List* >(GetControl(rsrcId));	 \
	if (ctrlVar != null) { \
		ctrlVar->AddItemEventListener(*this); }

#define BUTTON_UPDATE_TEXT(ctrl, value)	\
	if (ctrl) { ctrl->SetText(value); ctrl->RequestRedraw(); }

#define BUTTON_UPDATE_SHOW(ctrl, value, enabled)	\
	if (ctrl) { ctrl->SetShowState(value); ctrl->SetEnabled(enabled); ctrl->RequestRedraw(); }

#define CONTROL_UPDATE_SHOW(ctrl, value, enabled)	\
	if (ctrl) { ctrl->SetShowState(value); ctrl->SetEnabled(enabled); ctrl->RequestRedraw(); }


#define PERF_START()    long long __start, __end; \
	Tizen::System::SystemTime::GetTicks(__start);
#define PERF_STOP(tag)  Tizen::System::SystemTime::GetTicks(__end); AppLog("PERF:%s, %d", tag, __end - __start);

#define TRY_CATCH(eval, exp, ...)	TryCatch(eval, exp, __VA_ARGS__)

#endif // _SAFE_MACROS_H_
