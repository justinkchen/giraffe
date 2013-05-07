package com.cs210.giraffe;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.location.Location;
import android.support.v4.content.AsyncTaskLoader;
import android.util.Log;
import android.content.Context;

public class UserGraffitiListLoader extends AsyncTaskLoader<List<Graffiti>> {
	
	List<Graffiti> _graffitiData;
	
	public UserGraffitiListLoader(Context context) {
		super(context);
		System.out.println("UserGraffitiListLoader constructed");
	}

	@Override
	public List<Graffiti> loadInBackground() {
		System.out.println("UserGraffitiListLoader.loadInBackground");
		URL url = null;
		Location currLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
		try {
			//url = new URL("http://ec2-54-243-69-6.compute-1.amazonaws.com/graffiti/User" + "?latitude=" + currLocation.getLatitude() + "&longitude=" + currLocation.getLongitude());
			url = new URL("http://ec2-54-243-69-6.compute-1.amazonaws.com/graffiti/nearby?latitude=37.4280040&longitude=-122.1706350");
			Log.i("Johan", "Trying url");
		} 
		catch (MalformedURLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		Log.w("UserGraffitiListLoader", "Loading in background");
		JSONArray graffitiJSONArray = JSONHandler.getJsonArrayFromURL(url, "graffiti");
		List<Graffiti> graffitiList = new ArrayList<Graffiti>(graffitiJSONArray.length());

		Log.i("Johan", Integer.toString(graffitiJSONArray.length()));
		for (int i = 0; i < graffitiJSONArray.length(); i++){
			Graffiti newGraffiti = new Graffiti();
			try {
				System.out.println("JSONObject: " + ((JSONObject)graffitiJSONArray.get(i)).toString());
				String graffitiMessage = ((JSONObject)graffitiJSONArray.get(i)).getString("message");
				int graffitiRadius = ((JSONObject)graffitiJSONArray.get(i)).getInt("radius");
				double graffitiLatitude = ((JSONObject)graffitiJSONArray.get(i)).getDouble("latitude");
				double graffitiLongitude = ((JSONObject)graffitiJSONArray.get(i)).getDouble("longitude");
				String graffitiImageUrl = ((JSONObject)graffitiJSONArray.get(i)).getString("imageUrl");
				newGraffiti.setText(graffitiMessage);
				newGraffiti.setImageURL(graffitiImageUrl);
				newGraffiti.setRadius(graffitiRadius);
				newGraffiti.setLatitude(graffitiLatitude);
				newGraffiti.setLongitude(graffitiLongitude);
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			graffitiList.add(newGraffiti);
		}
//		Graffiti testGraffiti = new Graffiti();
//		testGraffiti.setText("Test Graffiti");
//		graffitiList.add(testGraffiti);
		return graffitiList;
	}
	
	 /**
     * Called when there is new data to deliver to the client.  The
     * super class will take care of delivering it; the implementation
     * here just adds a little more logic.
     */
    @Override public void deliverResult(List<Graffiti> listOfData) {
        if (isReset()) {
            // An async query came in while the loader is stopped.  We
            // don't need the result.
            if (listOfData != null) {
                onReleaseResources(listOfData);
            }
        }
        List<Graffiti> oldApps = listOfData;
        _graffitiData = listOfData;

        if (isStarted()) {
            // If the Loader is currently started, we can immediately
            // deliver its results.
            super.deliverResult(listOfData);
        }

        // At this point we can release the resources associated with
        // 'oldApps' if needed; now that the new result is delivered we
        // know that it is no longer in use.
        if (oldApps != null) {
            onReleaseResources(oldApps);
        }
    }

    /**
     * Handles a request to start the Loader.
     */
    @Override protected void onStartLoading() {
        if (_graffitiData != null) {
            // If we currently have a result available, deliver it
            // immediately.
            deliverResult(_graffitiData);
        }


        if (takeContentChanged() || _graffitiData == null) {
            // If the data has changed since the last time it was loaded
            // or is not currently available, start a load.
            forceLoad();
        }
    }
    
    /**
     * Handles a request to stop the Loader.
     */
    @Override protected void onStopLoading() {
        // Attempt to cancel the current load task if possible.
        cancelLoad();
    }

    /**
     * Handles a request to cancel a load.
     */
    @Override public void onCanceled(List<Graffiti> apps) {
        super.onCanceled(apps);

        // At this point we can release the resources associated with 'apps'
        // if needed.
        onReleaseResources(apps);
    }

    /**
     * Handles a request to completely reset the Loader.
     */
    @Override protected void onReset() {
        super.onReset();

        // Ensure the loader is stopped
        onStopLoading();

        // At this point we can release the resources associated with 'apps'
        // if needed.
        if (_graffitiData != null) {
            onReleaseResources(_graffitiData);
            _graffitiData = null;
        }
    }
    
    /**
     * Helper function to take care of releasing resources associated
     * with an actively loaded data set.
     */
    protected void onReleaseResources(List<Graffiti> apps) {}
}
