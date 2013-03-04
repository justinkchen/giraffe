#ifndef _PROJECTGIRAFFE_TAB2_H_
#define _PROJECTGIRAFFE_TAB2_H_

#include <FBase.h>
#include <FUi.h>
#include <FLocations.h>

class LocationManagerThread;

class ProjectGiraffeTab2
	: public Tizen::Ui::Controls::Panel
	, public Tizen::Ui::Scenes::ISceneEventListener,
 	public Tizen::Ui::ITouchEventListener,
 	public Tizen::Locations::ILocationProviderListener
{
public:
	ProjectGiraffeTab2(void);
	virtual ~ProjectGiraffeTab2(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);


	virtual void OnTouchDoublePressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchFocusIn(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchFocusOut(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchLongPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchMoved(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnTouchReleased(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
	virtual void OnAccuracyChanged (Tizen::Locations::LocationAccuracy accuracy);
	virtual void OnLocationUpdated (const Tizen::Locations::Location &location);
	virtual void OnLocationUpdateStatusChanged (Tizen::Locations::LocationServiceStatus status);
	virtual void OnRegionEntered (Tizen::Locations::RegionId regionId);
	virtual void OnRegionLeft (Tizen::Locations::RegionId regionId);
	virtual void OnRegionMonitoringStatusChanged (Tizen::Locations::LocationServiceStatus status);
	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);

private:
		Tizen::Locations::LocationProvider* __pLocProvider;
		LocationManagerThread* __pLocationManagerThread;
		Tizen::Locations::RegionId __regionId;
		Tizen::Locations::Coordinates __regionCenter;
		Tizen::Ui::Controls::Label* pLabel1;

};

#endif // _PROJECTGIRAFFE_TAB2_H_
