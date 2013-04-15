package com.androidnatic.maps.demo.activities;

import java.util.List;

import android.os.Bundle;

import com.androidnatic.maps.HeatMapOverlay;
import com.androidnatic.maps.SimpleMapView;
import com.androidnatic.maps.demo.R;
import com.androidnatic.maps.demo.db.MapExDBHelper;
import com.androidnatic.maps.events.PanChangeListener;
import com.androidnatic.maps.model.HeatPoint;
import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapActivity;

public class HeatMapActivity extends MapActivity {

	private MapExDBHelper helper;
	private HeatMapOverlay overlay;
	@Override
	protected boolean isRouteDisplayed() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	protected void onCreate(Bundle bundle) {
		super.onCreate(bundle);
		this.helper = new MapExDBHelper(this);
		setContentView(R.layout.heat);
		final SimpleMapView mapview = (SimpleMapView)findViewById(R.id.mapview);
		this.overlay = new HeatMapOverlay(20000, mapview);
		mapview.getOverlays().add(overlay);
		mapview.addPanChangeListener(new PanChangeListener() {
			
			@Override
			public void onPan(GeoPoint old, GeoPoint current) {
				List<HeatPoint> points = helper.loadPoints(mapview.getBounds());
				if(points.size() > 0){
					overlay.update(points);
				}
				
			}
		});
	}

}
