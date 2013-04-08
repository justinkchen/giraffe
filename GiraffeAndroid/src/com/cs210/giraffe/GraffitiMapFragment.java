package com.cs210.giraffe;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;

import android.location.Location;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;
import android.support.v4.app.Fragment;

public class GraffitiMapFragment extends Fragment {

	private GoogleMap mMap = null;
	
	public GraffitiMapFragment() {
		// TODO Auto-generated constructor stub
	}
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Toast toast;
		int result = GooglePlayServicesUtil.isGooglePlayServicesAvailable(this.getActivity().getApplicationContext());
		Log.w("GraffitiMap", "Checking Google Play Services status");
		switch(result) {
			case ConnectionResult.SUCCESS:
				toast = Toast.makeText(this.getActivity().getApplicationContext(), "Google Play Services Found",Toast.LENGTH_LONG);
				toast.show();
				break;
			case ConnectionResult.SERVICE_MISSING:
				toast = Toast.makeText(this.getActivity().getApplicationContext(), "Need Google Play Services: SERVICE_MISSING",Toast.LENGTH_LONG);
				toast.show();
//				TODO: GooglePlayServicesUtil.getErrorDialog(result, arg1, arg2)
				break;
			case ConnectionResult.SERVICE_VERSION_UPDATE_REQUIRED:
				toast = Toast.makeText(this.getActivity().getApplicationContext(), "Need Google Play Services: SERVICE_VERSION_UPDATE_REQUIRED" ,Toast.LENGTH_LONG);
				toast.show();
				break;
			case ConnectionResult.SERVICE_DISABLED:
				toast = Toast.makeText(this.getActivity().getApplicationContext(), "Need Google Play Services: SERVICE_DISABLED",Toast.LENGTH_LONG);
				toast.show();
				break;
		}
	}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
		View v = inflater.inflate(R.layout.fragment_mapview, container, false);
		return v;
	}
	
	@Override
	public void onResume(){
		super.onResume();
		Log.w("GraffitiMap", "Resuming Map Fragment");
		setUpMapIfNeeded();
	}
	
    @Override
    public void onDestroyView() {
        super.onDestroyView();
        Log.w("GraffitiMap", "Destroying View");
        SupportMapFragment f = (SupportMapFragment) this.getActivity().getSupportFragmentManager().findFragmentById(R.id.map);
        if (f != null){
        	this.getActivity().getSupportFragmentManager().beginTransaction().remove(f).commit();
        	mMap = null;
        }
        
        
    }
    
    private void setUpMapIfNeeded() {
    	Log.w("GraffitiMap", "Setting up map");
        // Do a null check to confirm that we have not already instantiated the map.
        if (mMap == null) {
        	SupportMapFragment mapFrag = (SupportMapFragment) this.getActivity().getSupportFragmentManager().findFragmentById(R.id.map);
        	if(mapFrag != null){
        		mMap = mapFrag.getMap();
        	}else{
        		Log.e("GraffitiMap", "Fragment not found");
        	}
        }
        // Check if we were successful in obtaining the map.
        if (mMap != null){
        	// The Map is verified. It is now safe to manipulate the map.
			Location myLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
			LatLng myLatLng = new LatLng(myLocation.getLatitude(), myLocation.getLongitude());
			mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(myLatLng, 15));
			mMap.animateCamera(CameraUpdateFactory.zoomIn());
			Log.w("GraffitiMap", "Map settings added in");
        }
    }
}
