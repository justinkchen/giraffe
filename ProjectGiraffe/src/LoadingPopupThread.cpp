#include "LoadingPopupThread.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Runtime;

LoadingPopupThread::LoadingPopupThread(void)
	: Tizen::Base::Runtime::EventDrivenThread()
	, __pUiControl(null),
	__lPopup(null)
{
}

LoadingPopupThread::~LoadingPopupThread(void)
{
}

result
LoadingPopupThread::Construct(void)
{
	return EventDrivenThread::Construct();
}

bool
LoadingPopupThread::OnStart(void)
{
	//__pUiControl = &uiControl;
	__lPopup = new LoadingPopup();
	__lPopup->ShowPopup();

}

void
LoadingPopupThread::OnStop(void)
{
	__lPopup->HidePopup();
	//return Thread::Exit();
}
