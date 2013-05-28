package com.cs210.giraffe;

import java.util.List;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.GoogleMap.OnMyLocationChangeListener;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import android.location.Location;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.app.LoaderManager;
import android.support.v4.content.Loader;

public class GraffitiMapFragment extends Fragment implements
		LoaderManager.LoaderCallbacks<List<Graffiti>> {

	private GoogleMap _map = null;

	public GraffitiMapFragment() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);

		System.out.println("GraffitiMapFragment.onActivityCreated");

		// getLoaderManager().initLoader(0, null, this);
		this.getActivity().getSupportLoaderManager().initLoader(0, null, this);
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Toast toast;
		// int result =
		// GooglePlayServicesUtil.isGooglePlayServicesAvailable(this.getActivity().getApplicationContext());
		// Log.w("GraffitiMap", "Checking Google Play Services status");
		// switch(result) {
		// case ConnectionResult.SUCCESS:
		// // toast = Toast.makeText(this.getActivity().getApplicationContext(),
		// "Google Play Services Found",Toast.LENGTH_LONG);
		// // toast.show();
		// Log.w("GraffitiMapFragment", "Google Play Services Found");
		// break;
		// case ConnectionResult.SERVICE_MISSING:
		// // toast = Toast.makeText(this.getActivity().getApplicationContext(),
		// "Need Google Play Services: SERVICE_MISSING",Toast.LENGTH_LONG);
		// // toast.show();
		// Log.e("GraffitiMapFragment",
		// "Need Google Play Services: SERVICE_MISSING");
		// GooglePlayServicesUtil.getErrorDialog(result, getActivity(),
		// result).show();
		// // TODO: Set the Error Dialog:
		// GooglePlayServicesUtil.getErrorDialog(result, arg1, arg2)
		// break;
		// case ConnectionResult.SERVICE_VERSION_UPDATE_REQUIRED:
		// // toast = Toast.makeText(this.getActivity().getApplicationContext(),
		// "Need Google Play Services: SERVICE_VERSION_UPDATE_REQUIRED"
		// ,Toast.LENGTH_LONG);
		// // toast.show();
		// Log.e("GraffitiMapFragment",
		// "Need Google Play Services: SERVICE_VERSION_UPDATE_REQUIRED");
		// GooglePlayServicesUtil.getErrorDialog(result, getActivity(),
		// result).show();
		// // TODO: Set the Error Dialog:
		// GooglePlayServicesUtil.getErrorDialog(result, arg1, arg2)
		// break;
		// case ConnectionResult.SERVICE_DISABLED:
		// // toast = Toast.makeText(this.getActivity().getApplicationContext(),
		// "Need Google Play Services: SERVICE_DISABLED",Toast.LENGTH_LONG);
		// // toast.show();
		// Log.e("GraffitiMapFragment",
		// "Need Google Play Services: SERVICE_DISABLED");
		// GooglePlayServicesUtil.getErrorDialog(result, getActivity(),
		// result).show();
		// // TODO: Set the Error Dialog:
		// GooglePlayServicesUtil.getErrorDialog(result, arg1, arg2)
		// break;
		// }
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View v = inflater.inflate(R.layout.fragment_mapview, container, false);
		return v;
	}

	@Override
	public void onResume() {
		super.onResume();
		Log.w("GraffitiMap", "Resuming Map Fragment");
	}

	@Override
	public void onDestroyView() {
		super.onDestroyView();
		if (!getActivity().isFinishing()) {
			Log.w("GraffitiMap", "Destroying View");
			SupportMapFragment f = (SupportMapFragment) this.getActivity()
					.getSupportFragmentManager().findFragmentById(R.id.map);
			if (f != null) {
				FragmentTransaction ft = this.getActivity()
						.getSupportFragmentManager().beginTransaction();
				ft.remove(f).commit();
				_map = null;
			}
		}

	}

	@Override
	public void onPause() {
		super.onPause();
		// super.onDestroyView();
		// Log.w("GraffitiMap", "Pausing MapFragment");
		// SupportMapFragment f = (SupportMapFragment)
		// this.getActivity().getSupportFragmentManager().findFragmentById(R.id.map);
		// if (f != null){
		// FragmentTransaction ft =
		// this.getActivity().getSupportFragmentManager().beginTransaction();
		// ft.remove(f).commit();
		// _map = null;
		// }

	}

	public void setUpMapIfNeeded(List<Graffiti> data) {
		Log.w("GraffitiMap", "Setting up map");
		// Do a null check to confirm that we have not already instantiated the
		// map.
		if (_map == null) {
			SupportMapFragment mapFrag = (SupportMapFragment) this
					.getActivity().getSupportFragmentManager()
					.findFragmentById(R.id.map);
			if (mapFrag != null) {
				_map = mapFrag.getMap();
			} else {
				Log.e("GraffitiMap", "Fragment not found");
			}
		}
		// Check if we were successful in obtaining the map.
		if (_map != null) {
			_map.clear();
			// The Map is verified. It is now safe to manipulate the map.
			Location myLocation = MainActivity.getGiraffeLocationListener()
					.getCurrentLocation();
			LatLng myLatLng = new LatLng(myLocation.getLatitude(),
					myLocation.getLongitude());
			_map.moveCamera(CameraUpdateFactory.newLatLngZoom(myLatLng, 15));
			_map.setMyLocationEnabled(true);
			_map.animateCamera(CameraUpdateFactory.zoomIn());
			Log.w("GraffitiMap", "Map settings added in");

			// _map.setOnMyLocationChangeListener(new
			// OnMyLocationChangeListener(){
			//
			// @Override
			// public void onMyLocationChange(Location newLoc) {
			// // TODO Auto-generated method stub
			// LatLng newLatLng = new LatLng(newLoc.getLatitude(),
			// newLoc.getLongitude());
			// _map.moveCamera(CameraUpdateFactory.newLatLngZoom(newLatLng,
			// 15));
			// }
			// });
			// _map.addMarker(new MarkerOptions().position(myLatLng));
			if (data != null)
				for (Graffiti point : data) {
					System.out.println("Graffiti Map Message: "
							+ point.getText());
					LatLng pointLatLng = new LatLng(point.getLatitude(),
							point.getLongitude());
					_map.addMarker(new MarkerOptions().position(pointLatLng)
							.title(point.getText()));
					_map.addCircle(new CircleOptions().center(pointLatLng)
							.strokeWidth(1.0f).fillColor(0x0f0000ff)
							.radius(point.getRadius()));
				}

		}
	}

	@Override
	public Loader<List<Graffiti>> onCreateLoader(int arg0, Bundle arg1) {
		System.out.println("GraffitiMapFragment.onCreateLoader");
		Location currLocation = MainActivity.getGiraffeLocationListener()
				.getCurrentLocation();
		return new NearbyGraffitiListLoader(getActivity(),
				MainActivity.getBaseServerURI() + "/graffiti/nearby"
						+ "?latitude=" + currLocation.getLatitude()
						+ "&longitude=" + currLocation.getLongitude());
	}

	@Override
	public void onLoadFinished(Loader<List<Graffiti>> arg0, List<Graffiti> data) {
		System.out.println("GraffitiFragment.onLoadFinished");
		setUpMapIfNeeded(data);
	}

	@Override
	public void onLoaderReset(Loader<List<Graffiti>> arg0) {
		if (_map != null) {
			_map.clear();
		}
	}
}
