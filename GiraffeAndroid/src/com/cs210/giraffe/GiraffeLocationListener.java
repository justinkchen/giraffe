package com.cs210.giraffe;

import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.widget.Toast;

public class GiraffeLocationListener implements LocationListener {

	private static final int TWO_MINUTES = 1000 * 60 * 2;
	
	private LocationManager locationManager;
	private Location currentLocation;
	private boolean locationFound = false;
	
	public GiraffeLocationListener(LocationManager lm, String provider) {
		locationManager = lm;
		currentLocation = locationManager.getLastKnownLocation(provider);
		if(currentLocation != null){
			System.out.println("Location already found, Latitude: " + currentLocation.getLatitude() + ", Longitude: " + currentLocation.getLongitude());
			locationFound = true;
		}else{
			System.out.println("Can't get a location from provider");
		}
	}

	@Override
	public void onLocationChanged(Location location) {
		// Called when a new location is found by the network location provider.
		System.out.println("Location has changed, Latitude: " + location.getLatitude() + ", Longitude: " + location.getLongitude());
		if(isBetterLocation(location, currentLocation)){
			System.out.println("New Location-> Latitude: " + location.getLatitude() + ", Longitude: " + location.getLongitude());
			currentLocation = location;
		}
	}

	@Override
	public void onProviderDisabled(String provider) {
		System.out.println("Provider is disabled");
	}

	@Override
	public void onProviderEnabled(String provider) {
		// TODO Auto-generated method stub
		System.out.println("Provider is enabled");
	}

	@Override
	public void onStatusChanged(String provider, int status, Bundle extras) {
		// TODO Auto-generated method stub
		System.out.println("Provider status changed");
	}

	public Location getCurrentLocation(){
		return currentLocation;
	}
	
	public void setCurrentLocation(Location newLoc){
		currentLocation = newLoc;
	}
	
	public boolean isLocationFound(){
		return locationFound;
	}
	
	/** Determines whether one Location reading is better than the current Location fix
	  * @param location  The new Location that you want to evaluate
	  * @param currentBestLocation  The current Location fix, to which you want to compare the new one
	  */
	protected boolean isBetterLocation(Location location, Location currentBestLocation) {
	    if (currentBestLocation == null) {
	        // A new location is always better than no location
	        return true;
	    }

	    // Check whether the new location fix is newer or older
	    long timeDelta = location.getTime() - currentBestLocation.getTime();
	    boolean isSignificantlyNewer = timeDelta > TWO_MINUTES;
	    boolean isSignificantlyOlder = timeDelta < -TWO_MINUTES;
	    boolean isNewer = timeDelta > 0;

	    // If it's been more than two minutes since the current location, use the new location
	    // because the user has likely moved
	    if (isSignificantlyNewer) {
	        return true;
	    // If the new location is more than two minutes older, it must be worse
	    } else if (isSignificantlyOlder) {
	        return false;
	    }

	    // Check whether the new location fix is more or less accurate
	    int accuracyDelta = (int) (location.getAccuracy() - currentBestLocation.getAccuracy());
	    boolean isLessAccurate = accuracyDelta > 0;
	    boolean isMoreAccurate = accuracyDelta < 0;
	    boolean isSignificantlyLessAccurate = accuracyDelta > 200;

	    // Check if the old and new location are from the same provider
	    boolean isFromSameProvider = isSameProvider(location.getProvider(),
	            currentBestLocation.getProvider());

	    // Determine location quality using a combination of timeliness and accuracy
	    if (isMoreAccurate) {
	        return true;
	    } else if (isNewer && !isLessAccurate) {
	        return true;
	    } else if (isNewer && !isSignificantlyLessAccurate && isFromSameProvider) {
	        return true;
	    }
	    return false;
	}

	/** Checks whether two providers are the same */
	private boolean isSameProvider(String provider1, String provider2) {
	    if (provider1 == null) {
	      return provider2 == null;
	    }
	    return provider1.equals(provider2);
	}
	
}
