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
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.SeekBar;

public class AddGraffitiFragment extends Fragment implements OnSeekBarChangeListener {
	
	private GoogleMap _circleOverlayMap = null;
	private SeekBar _radiusBar = null;
	private int _currentProgress = 50;
	
	private static final int MIN_RADIUS = 10; // meters
	
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
		_radiusBar = (SeekBar) rootView.findViewById(R.id.radiusSeekBar);
		_radiusBar.setOnSeekBarChangeListener(this);
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
			_circleOverlayMap.addCircle(new CircleOptions().center(myLatLng).radius(_radiusBar.getProgress()).fillColor(0x1fff0000).strokeWidth(5.0f)); // In meters
			_circleOverlayMap.addMarker(new MarkerOptions().position(myLatLng));
			Log.w("AddGraffitiFragment", "Map settings added in");
        }
    }

	@Override
	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		_circleOverlayMap.clear();
		Location myLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
		LatLng myLatLng = new LatLng(myLocation.getLatitude(), myLocation.getLongitude());
		_circleOverlayMap.addCircle(new CircleOptions().center(myLatLng).radius(progress).fillColor(0x1fff0000).strokeWidth(5.0f)); // In meters
		_circleOverlayMap.addMarker(new MarkerOptions().position(myLatLng));
		
		_currentProgress = progress + MIN_RADIUS;  //starts at 0 but we want it to start at 10
	}

	@Override
	public void onStartTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onStopTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub
		
	}
}
