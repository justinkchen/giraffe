/*
 * Copyright (C) 2011 by Vinicius Carvalho (vinnie@androidnatic.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package com.androidnatic.maps;


import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.MotionEvent;

import com.androidnatic.maps.events.PanChangeListener;
import com.androidnatic.maps.events.ZoomChangeListener;
import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapView;

public class SimpleMapView extends MapView {
	
	private int currentZoomLevel = -1;
	private GeoPoint currentCenter;
	private List<ZoomChangeListener> zoomEvents = new ArrayList<ZoomChangeListener>();
	private List<PanChangeListener> panEvents = new ArrayList<PanChangeListener>();
	
	public SimpleMapView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
	}

	public SimpleMapView(Context context, String apiKey) {
		super(context, apiKey);
	}

	public SimpleMapView(Context context, AttributeSet attrs) {
		super(context, attrs);
	}
	/**
	 * 
	 * @return
	 */
	public int[][] getBounds() {
		
		GeoPoint center = getMapCenter();
		int latitudeSpan = getLatitudeSpan();
		int longtitudeSpan = getLongitudeSpan();
		int[][] bounds = new int[2][2];

		bounds[0][0] = center.getLatitudeE6() - (latitudeSpan / 2);
		bounds[0][1] = center.getLongitudeE6() - (longtitudeSpan / 2);

		bounds[1][0] = center.getLatitudeE6() + (latitudeSpan / 2);
		bounds[1][1] = center.getLongitudeE6() + (longtitudeSpan / 2);
		return bounds;
	}
	
	public boolean onTouchEvent(MotionEvent ev) {
        if (ev.getAction() == MotionEvent.ACTION_UP) {
            GeoPoint centerGeoPoint = this.getMapCenter();
            if (currentCenter == null || 
                    (currentCenter.getLatitudeE6() != centerGeoPoint.getLatitudeE6()) ||
                    (currentCenter.getLongitudeE6() != centerGeoPoint.getLongitudeE6()) ) {
            	firePanEvent(currentCenter, this.getMapCenter());
            }
            currentCenter = this.getMapCenter();
        }
        return super.onTouchEvent(ev);
    }

	@Override
	protected void dispatchDraw(Canvas canvas) {
		super.dispatchDraw(canvas);
		if(getZoomLevel() != currentZoomLevel){
			fireZoomLevel(currentZoomLevel, getZoomLevel());
			currentZoomLevel = getZoomLevel();
		}
	}
	
	private void fireZoomLevel(int old, int current){
		for(ZoomChangeListener event : zoomEvents){
			event.onZoom(old, current);
		}
	}
	
	private void firePanEvent(GeoPoint old, GeoPoint current){
		for(PanChangeListener event : panEvents){
			event.onPan(old, current);
		}
	}
	
	public void addZoomChangeListener(ZoomChangeListener listener){
		this.zoomEvents.add(listener);
	}
	
	public void addPanChangeListener(PanChangeListener listener){
		this.panEvents.add(listener);
	}
	

}
