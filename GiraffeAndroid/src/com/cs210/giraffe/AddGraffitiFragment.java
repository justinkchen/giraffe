package com.cs210.giraffe;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import android.graphics.Color;
import android.location.Location;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class AddGraffitiFragment extends Fragment {
	
	private GoogleMap _circleOverlayMap = null;
	
	/**
	 * The fragment argument representing the section number for this
	 * fragment.
	 */
	public AddGraffitiFragment() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_addgraffiti,
				container, false);
		return rootView;
	}
	
	@Override
	public void onResume(){
		super.onResume();
		Log.w("AddGraffitiFragment", "Resuming Map Fragment");
		setUpMapIfNeeded();
	}
	
    @Override
    public void onDestroyView() {
        super.onDestroyView();
        Log.w("AddGraffitiFragment", "Destroying View");
        SupportMapFragment f = (SupportMapFragment) this.getActivity().getSupportFragmentManager().findFragmentById(R.id.addGraffitiMap);
        if (f != null){
        	this.getActivity().getSupportFragmentManager().beginTransaction().remove(f).commit();
        	_circleOverlayMap = null;
        }
        
        
    }
    
    private void setUpMapIfNeeded() {
    	Log.w("AddGraffitiFragment", "Setting up map");
        // Do a null check to confirm that we have not already instantiated the map.
        if (_circleOverlayMap == null) {
        	SupportMapFragment mapFrag = (SupportMapFragment) this.getActivity().getSupportFragmentManager().findFragmentById(R.id.addGraffitiMap);
        	if(mapFrag != null){
        		_circleOverlayMap = mapFrag.getMap();
        	}else{
        		Log.e("AddGraffitiFragment", "Fragment not found");
        	}
        }
        // Check if we were successful in obtaining the map.
        if (_circleOverlayMap != null){
        	// The Map is verified. It is now safe to manipulate the map.
			Location myLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
			LatLng myLatLng = new LatLng(myLocation.getLatitude(), myLocation.getLongitude());
			
			_circleOverlayMap.moveCamera(CameraUpdateFactory.newLatLngZoom(myLatLng, 15));
			_circleOverlayMap.animateCamera(CameraUpdateFactory.zoomIn());
			_circleOverlayMap.addCircle(new CircleOptions().center(myLatLng).radius(300).fillColor(0x0fff0000).strokeWidth(5.0f)); // In meters
			_circleOverlayMap.addMarker(new MarkerOptions().position(myLatLng));
			Log.w("AddGraffitiFragment", "Map settings added in");
        }
    }
}
