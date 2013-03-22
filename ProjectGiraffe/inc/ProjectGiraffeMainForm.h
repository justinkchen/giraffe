#ifndef _PROJECTGIRAFFE_MAIN_FORM_H_
#define _PROJECTGIRAFFE_MAIN_FORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FLocations.h>

#include "UserPopup.h"

class LocationManagerThread;

class ProjectGiraffeMainForm :
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::Controls::IFormBackEventListener,
 	public Tizen::Ui::Scenes::ISceneEventListener,
 	public Tizen::Locations::ILocationProviderListener
{
public:
	ProjectGiraffeMainForm(void);
	virtual ~ProjectGiraffeMainForm(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnAccuracyChanged (Tizen::Locations::LocationAccuracy accuracy);
	virtual void OnLocationUpdated (const Tizen::Locations::Location &location);
	virtual void OnLocationUpdateStatusChanged (Tizen::Locations::LocationServiceStatus status);
	virtual void OnRegionEntered (Tizen::Locations::RegionId regionId);
	virtual void OnRegionLeft (Tizen::Locations::RegionId regionId);
	virtual void OnRegionMonitoringStatusChanged (Tizen::Locations::LocationServiceStatus status);
	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
	virtual void MainFormParseLocation();
	static double MainFormGetLatitude();
	bool TestFunction();
	static Tizen::Locations::Location* __currentLocation;
	static double currentLongitude;
	static double currentLatitude;


protected:
	static const int ID_FOOTER_ITEM1 = 101;
	static const int ID_FOOTER_ITEM2 = 102;
	static const int ID_FOOTER_ITEM3 = 103;
	static const int ID_FOOTER_ITEM4 = 104;
	static const int ID_FOOTER_ITEM5 = 105;

	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

private:
		Tizen::Locations::LocationProvider* __pLocProvider;
		LocationManagerThread* __pLocationManagerThread;
		Tizen::Locations::RegionId __regionId;
		Tizen::Locations::Coordinates __regionCenter;

		User* _user;
		UserPopup* _userPopup;
};

#endif	//_PROJECTGIRAFFE_MAIN_FORM_H_
