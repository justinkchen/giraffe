#ifndef _PROJECTGIRAFFE_TAB3_H_
#define _PROJECTGIRAFFE_TAB3_H_

#include <FBase.h>
#include <FUi.h>
#include <Fnet.h>
#include <FWeb.h>

class ProjectGiraffeTab3
: public Tizen::Ui::Controls::Panel
  , public Tizen::Ui::Scenes::ISceneEventListener
  , public Tizen::Net::Http::IHttpTransactionEventListener
  , public Tizen::Ui::IActionEventListener
  , public Tizen::Ui::ITextEventListener
  , public Tizen::Ui::IAdjustmentEventListener
  {
  public:
	ProjectGiraffeTab3(void)
	: __pButton(null)
	, __pEditArea(null)
	, __pEditAreaLabel(null)
	, __pSlider(null){}

	virtual ~ProjectGiraffeTab3(void);
	bool Initialize(void);

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	// ISceneEventListener
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
			const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
			const Tizen::Ui::Scenes::SceneId& nextSceneId);

	// IHttpTransactionEventListener
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, result r);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, Tizen::Base::String *pCert);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired);
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int availableBodyLen);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int recommendedChunkSize);

	// IActionEventListener
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	// ITextEventListener
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);

	// IAdjustmentEventListener
	virtual void OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment);
  private:
	static const int ID_BUTTON  = 301;
	Tizen::Ui::Controls::Button* __pButton;
	Tizen::Ui::Controls::EditArea* __pEditArea;
	Tizen::Ui::Controls::Label* __pEditAreaLabel;
	Tizen::Ui::Controls::Slider* __pSlider;
  };

#endif // _PROJECTGIRAFFE_TAB3_H_
