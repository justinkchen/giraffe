#ifndef _PROJECTGIRAFFE_TAB3_H_
#define _PROJECTGIRAFFE_TAB3_H_

#include <FBase.h>
#include <FUi.h>
#include <Fnet.h>
#include <FWeb.h>

class ProjectGiraffeTab3
: public Tizen::Ui::Controls::Panel,
  public Tizen::Ui::Scenes::ISceneEventListener,
  public Tizen::Net::Http::IHttpTransactionEventListener,
  public Tizen::Ui::IActionEventListener,
  public Tizen::Ui::ITextEventListener,
  public Tizen::Ui::IKeypadEventListener,
  public Tizen::Ui::IAdjustmentEventListener,
  public Tizen::Web::Controls::ILoadingListener
  {
  public:
	ProjectGiraffeTab3(void)
	: _submitButton(null),
	  _messageArea(null),
	  _messageLabel(null),
	  _radiusSlider(null),
	  _addGraffitiWebView(null){}

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

	// ILoadingListener
	virtual bool OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication);
	virtual void OnHttpAuthenticationCanceled(void);
	virtual void OnLoadingStarted(void);
	virtual void OnLoadingCanceled(void);
	virtual void OnLoadingErrorOccurred(Tizen::Web::Controls::LoadingErrorType error, const Tizen::Base::String& reason);
	virtual void OnLoadingCompleted(void);
	virtual void OnEstimatedProgress(int progress);
	virtual void OnPageTitleReceived(const Tizen::Base::String& title);
	virtual bool OnLoadingRequested(const Tizen::Base::String& url, Tizen::Web::Controls::WebNavigationType type);
	virtual Tizen::Web::Controls::DecisionPolicy OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header);

	// IKeypadEventListener
	virtual void OnKeypadActionPerformed(Tizen::Ui::Control &source, Tizen::Ui::KeypadAction keypadAction);
	virtual void OnKeypadBoundsChanged(Tizen::Ui::Control &source);
	virtual void OnKeypadClosed(Tizen::Ui::Control &source);
	virtual void OnKeypadOpened(Tizen::Ui::Control &source);
	virtual void OnKeypadWillOpen(Tizen::Ui::Control &source);

  private:
	static const int ID_BUTTON  = 301;
	Tizen::Ui::Controls::Button* _submitButton;
	Tizen::Ui::Controls::EditArea* _messageArea;
	Tizen::Ui::Controls::Label* _messageLabel;
	Tizen::Ui::Controls::Slider* _radiusSlider;

	Tizen::Web::Controls::Web* _addGraffitiWebView;

	Tizen::Base::String GetValidUrl(Tizen::Base::String& url);
  };

#endif // _PROJECTGIRAFFE_TAB3_H_
