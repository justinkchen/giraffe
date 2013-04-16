package com.cs210.giraffe;

import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Color;
import android.location.Location;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.SeekBar;

public class AddGraffitiFragment extends Fragment implements OnSeekBarChangeListener {

	private GoogleMap _circleOverlayMap = null;
	private SeekBar _radiusBar = null;
	private EditText _messageBox = null;
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
		_messageBox = (EditText) rootView.findViewById(R.id.graffitiEditText);
		
		final Button submitButton = (Button) rootView.findViewById(R.id.submitButton);
		submitButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// Perform action on click
				Location myLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
				Graffiti newGraffiti = new Graffiti();
				newGraffiti.setText(_messageBox.getText().toString());
				newGraffiti.setLatitude(myLocation.getLatitude());
				newGraffiti.setLongitude(myLocation.getLongitude());
				newGraffiti.setRadius(_currentProgress);
				String uri = "http://ec2-54-243-69-6.compute-1.amazonaws.com/addgraffiti";
				InputStream responseStream = postGraffiti(newGraffiti, uri);
			}
		});

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
			_circleOverlayMap.clear();
			// The Map is verified. It is now safe to manipulate the map.
			Location myLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
			LatLng myLatLng = new LatLng(myLocation.getLatitude(), myLocation.getLongitude());

			_circleOverlayMap.moveCamera(CameraUpdateFactory.newLatLngZoom(myLatLng, 15));
			_circleOverlayMap.addCircle(new CircleOptions().center(myLatLng).radius(_radiusBar.getProgress()).fillColor(0x1fff0000).strokeWidth(5.0f)); // In meters
			_circleOverlayMap.addMarker(new MarkerOptions().position(myLatLng));
			Log.w("AddGraffitiFragment", "Map settings added in");
		}
	}

	@Override
	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		setUpMapIfNeeded();
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

	private InputStream postGraffiti(Graffiti newGraffiti, String urlString){
		InputStream myInputStream = null;
		StringBuilder sb = new StringBuilder();
		//adding some data to send along with the request to the server
		try {
			sb.append("message=" + URLEncoder.encode(newGraffiti.getText(), "UTF-8"));
			sb.append("&latitude=" + URLEncoder.encode(newGraffiti.getLatitude() + "", "UTF-8"));
			sb.append("&longitude=" + URLEncoder.encode(newGraffiti.getLongitude() + "", "UTF-8"));
			sb.append("&radius=" + URLEncoder.encode(newGraffiti.getRadius() + "", "UTF-8"));
			sb.append("&userid=" + URLEncoder.encode("1", "UTF-8"));
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		URL url;
		try {
			url = new URL(urlString);
			HttpURLConnection conn = (HttpURLConnection) url.openConnection();
			conn.setDoOutput(true);
			conn.setRequestMethod("POST");
			OutputStreamWriter wr = new OutputStreamWriter(conn
					.getOutputStream());
			// this is were we're adding post data to the request
			wr.write(sb.toString());
			wr.flush();
			myInputStream = conn.getInputStream();
			wr.close();
		} catch (Exception e) {
			//handle the exception !
			System.out.println("Error Message: " + e.getMessage());
		}
		// TODO: check response of server
		boolean success = true;
		if (success){
			new AlertDialog.Builder(getActivity())
			.setIcon(R.drawable.ic_navigation_accept)
			.setTitle("Success!")
			.setMessage("Graffiti Successfully Posted!")
			.setCancelable(false)
			.setPositiveButton("Okay", new DialogInterface.OnClickListener()
			{
				@Override
				public void onClick(DialogInterface dialog, int which) {
					// Close dialog  
				}
			})
			.show();
			_messageBox.setText("");
		}
		
		return myInputStream;
	}
}
