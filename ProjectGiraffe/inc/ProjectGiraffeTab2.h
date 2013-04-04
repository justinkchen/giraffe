#ifndef _PROJECTGIRAFFE_TAB2_H_
#define _PROJECTGIRAFFE_TAB2_H_

#include <FBase.h>
#include <FUi.h>
#include <FLocations.h>
#include <FWeb.h>

class LocationManagerThread;

class ProjectGiraffeTab2
	: public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::Scenes::ISceneEventListener,
 	public Tizen::Ui::ITouchEventListener,
 	public Tizen::Web::Controls::ILoadingListener
{
public:
	ProjectGiraffeTab2(void)
	: _longitudeLabel(null)
	, _latitudeLabel(null)
	, _graffitiMapWebView(null){}

	virtual ~ProjectGiraffeTab2(void);
	bool Initialize(void);

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	// ISceneEventListener
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);

	// ITouchEventListener
	virtual void OnTouchDoublePressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchFocusIn(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchFocusOut(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchLongPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchMoved(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchReleased(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);

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
private:
	Tizen::Ui::Controls::Label* _latitudeLabel;
	Tizen::Ui::Controls::Label* _longitudeLabel;
	Tizen::Web::Controls::Web *_graffitiMapWebView;
	bool locationFound;
	void SetUrl(const Tizen::Base::String& url);
	Tizen::Base::String GetValidUrl(Tizen::Base::String& url);


};

#endif // _PROJECTGIRAFFE_TAB2_H_
