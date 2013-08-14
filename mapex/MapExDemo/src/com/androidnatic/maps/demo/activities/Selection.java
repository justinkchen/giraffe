package com.androidnatic.maps.demo.activities;

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.androidnatic.maps.MapSelectionOverlay;
import com.androidnatic.maps.SimpleMapView;
import com.androidnatic.maps.demo.R;
import com.google.android.maps.MapActivity;

public class Selection extends MapActivity {
	
	private MapSelectionOverlay overlay;
	
	@Override
	protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);
		setContentView(R.layout.selection);
		SimpleMapView mapView = (SimpleMapView)findViewById(R.id.mapview);
		
		overlay = new MapSelectionOverlay(mapView);
		mapView.getOverlays().add(overlay);
	}
	
	@Override
	protected boolean isRouteDisplayed() {
		return false;
	}
	
	public void showBounds(View v){
		int[][] bounds = overlay.getBounds();
		if(bounds != null){
			String msg = "top left: (" + bounds[0][0] + "," + bounds[0][1]+") \n bottom right: (" + bounds[1][0] + "," + bounds[1][1] + ")";
			Toast toast = Toast.makeText(this, msg, Toast.LENGTH_SHORT);
			toast.show();
		}
	}

	

}
