package com.cs210.giraffe;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpCookie;
import java.net.HttpURLConnection;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLEncoder;

import org.json.JSONException;
import org.json.JSONObject;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.GoogleMap.OnMyLocationChangeListener;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.location.Location;
import android.net.Uri;
import android.os.AsyncTask;
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

public class AddGraffitiFragment extends Fragment implements
OnSeekBarChangeListener {

	private GoogleMap _circleOverlayMap = null;
	private SeekBar _radiusBar = null;
	private EditText _messageBox = null;
	private Graffiti _newGraffiti = null;
	private int _currentProgress = 50;
	private LoginSupportFragment _loginFragment;

	private static final int MIN_RADIUS = 10; // meters
	public static final int TAKE_CAMERA_PICTURE = 100;
	public static final int CHOOSE_GALLERY_PHOTO = 101;
	public static final int RESULT_OK = -1;

	/**
	 * The fragment argument representing the section number for this fragment.
	 */
	public AddGraffitiFragment() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {

		View rootView;
		rootView = inflater.inflate(R.layout.fragment_addgraffiti,
				container, false);
		_radiusBar = (SeekBar) rootView.findViewById(R.id.radiusSeekBar);
		_radiusBar.setOnSeekBarChangeListener(this);
		_messageBox = (EditText) rootView.findViewById(R.id.graffitiEditText);


		final Button addImageButton = (Button) rootView
				.findViewById(R.id.addImageButton);

		addImageButton.setOnClickListener(new AddImageButtonClickListener());

		final Button submitButton = (Button) rootView.findViewById(R.id.submitButton);
		submitButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				if(MainActivity.isLoggedIn()){
					// Perform action on click
					Location myLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
					_newGraffiti = new Graffiti();
					_newGraffiti.setText(_messageBox.getText().toString());
					_newGraffiti.setLatitude(myLocation.getLatitude());
					_newGraffiti.setLongitude(myLocation.getLongitude());
					_newGraffiti.setRadius(_currentProgress);
					String uri = "http://ec2-54-243-69-6.compute-1.amazonaws.com/graffiti/new";
					new AddGraffitiTask().execute(uri);
				}else{
					_loginFragment = new LoginSupportFragment();
					_loginFragment.show(getFragmentManager(), "loginFragment");
				}
			}
		});
		return rootView;
	}

	@Override
	public void onResume() {
		super.onResume();
		Log.w("AddGraffitiFragment", "Resuming Add Graffiti Fragment");
		setUpMapIfNeeded();
	}

	@Override
	public void onDestroyView() {
		super.onDestroyView();
		Log.w("AddGraffitiFragment", "Destroying View");
		SupportMapFragment f = (SupportMapFragment) this.getActivity()
				.getSupportFragmentManager()
				.findFragmentById(R.id.addGraffitiMap);
		if (f != null) {
			this.getActivity().getSupportFragmentManager().beginTransaction()
			.remove(f).commit();
			_circleOverlayMap = null;
		}

	}

	private void setUpMapIfNeeded() {
		Log.w("AddGraffitiFragment", "Setting up map");
		// Do a null check to confirm that we have not already instantiated the
		// map.
		if (_circleOverlayMap == null) {
			SupportMapFragment mapFrag = (SupportMapFragment) this
					.getActivity().getSupportFragmentManager()
					.findFragmentById(R.id.addGraffitiMap);
			if (mapFrag != null) {
				_circleOverlayMap = mapFrag.getMap();
			} else {
				Log.e("AddGraffitiFragment", "Fragment not found");
			}
		}
		// Check if we were successful in obtaining the map.
		if (_circleOverlayMap != null) {
			_circleOverlayMap.clear();
			// The Map is verified. It is now safe to manipulate the map.
			Location myLocation = MainActivity.getGiraffeLocationListener()
					.getCurrentLocation();
			LatLng myLatLng = new LatLng(myLocation.getLatitude(),
					myLocation.getLongitude());

			_circleOverlayMap.moveCamera(CameraUpdateFactory.newLatLngZoom(
					myLatLng, 15));
			_circleOverlayMap.addCircle(new CircleOptions().center(myLatLng)
					.radius(_radiusBar.getProgress()).fillColor(0x1fff0000)
					.strokeWidth(5.0f)); // In meters
			_circleOverlayMap.addMarker(new MarkerOptions().position(myLatLng));
			
			_circleOverlayMap.setOnMyLocationChangeListener(new OnMyLocationChangeListener(){

				@Override
				public void onMyLocationChange(Location newLoc) {
					// TODO Auto-generated method stub
					LatLng newLatLng = new LatLng(newLoc.getLatitude(), newLoc.getLongitude());
					_circleOverlayMap.moveCamera(CameraUpdateFactory.newLatLngZoom(newLatLng, 15));
				}
			});
			Log.w("AddGraffitiFragment", "Map settings added in");
		}
	}

	@Override
	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		setUpMapIfNeeded();
		_currentProgress = progress + MIN_RADIUS; // starts at 0 but we want it
		// to start at 10
	}

	@Override
	public void onStartTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onStopTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub

	}

	private InputStream postGraffiti(Graffiti newGraffiti, String urlString) {
		InputStream myInputStream = null;
		StringBuilder sb = new StringBuilder();
		// adding some data to send along with the request to the server

		try {
			sb.append("message=" + URLEncoder.encode(newGraffiti.getText(), "UTF-8"));
			sb.append("&latitude=" + URLEncoder.encode(String.valueOf(newGraffiti.getLatitude()), "UTF-8"));
			sb.append("&longitude=" + URLEncoder.encode(String.valueOf(newGraffiti.getLongitude()), "UTF-8"));
			sb.append("&radius=" + URLEncoder.encode(String.valueOf(newGraffiti.getRadius()), "UTF-8"));
			sb.append("&userid=" + URLEncoder.encode(String.valueOf(1), "UTF-8"));
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		URL url = null;
		//		HttpsTask task = new HttpsTask();
		//		task.execute("https://ec2-54-243-69-6.compute-1.amazonaws.com/");
		//		Log.d("Johan", "Posting URL");
		try {
			url = new URL(urlString);
			HttpURLConnection conn = (HttpURLConnection) url.openConnection();
			conn.setDoOutput(true);
			conn.setRequestMethod("POST");
			OutputStreamWriter wr = new OutputStreamWriter(
					conn.getOutputStream());
			// this is were we're adding post data to the request
			wr.write(sb.toString());
			wr.flush();
			myInputStream = conn.getInputStream();
			wr.close();
		} catch (Exception e) {
			// handle the exception !
			System.out.println("Error Message: " + e.getMessage());
		}

		return myInputStream;
	}

	private class AddImageButtonClickListener implements View.OnClickListener {
		public void onClick(View v) {
			final CharSequence[] items = { "Camera", "Gallery" };

			AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
			builder.setTitle("Get image from");
			builder.setItems(items, new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int item) {
					switch (item) {

					case 0:
						// Use the camer
						Intent cameraIntent = new Intent(
								android.provider.MediaStore.ACTION_IMAGE_CAPTURE);
						startActivityForResult(cameraIntent,
								TAKE_CAMERA_PICTURE);
						break;

					case 1:
						// Choose from the gallery
						Intent pickPhoto = new Intent(
								Intent.ACTION_PICK,
								android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
						startActivityForResult(pickPhoto, CHOOSE_GALLERY_PHOTO);
						break;

					default:
						break;

					}
				}
			}).setNegativeButton("Cancel", null);
			AlertDialog alert = builder.create();
			alert.show();
		}
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		Log.i("Johan", "Getting here");
		Bitmap photo = null;
		switch (requestCode) {

		case TAKE_CAMERA_PICTURE:
			if (resultCode == RESULT_OK)
				photo = (Bitmap) data.getExtras().get("data");
			break;

		case CHOOSE_GALLERY_PHOTO:
			if (resultCode == RESULT_OK) {
				Uri targetUri = data.getData();
				try {
					photo = BitmapFactory.decodeStream(getActivity()
							.getContentResolver().openInputStream(targetUri));
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			break;

		default:
			break;

		}

		if (photo != null)
			;
		// Do something with photo
	}
	
	private class AddGraffitiTask extends AsyncTask<String, Integer, InputStream> {
		private boolean success = false;
		String error_message = null;

		protected InputStream doInBackground(String... urls) {
			InputStream myInputStream = null;
			StringBuilder sb = new StringBuilder();
			// adding some data to send along with the request to the server

			try {
				sb.append("message=" + URLEncoder.encode(_newGraffiti.getText(), "UTF-8"));
				sb.append("&latitude=" + URLEncoder.encode(String.valueOf(_newGraffiti.getLatitude()), "UTF-8"));
				sb.append("&longitude=" + URLEncoder.encode(String.valueOf(_newGraffiti.getLongitude()), "UTF-8"));
				sb.append("&radius=" + URLEncoder.encode(String.valueOf(_newGraffiti.getRadius()), "UTF-8"));
				sb.append("&userid=" + URLEncoder.encode(String.valueOf(1), "UTF-8"));
			} catch (UnsupportedEncodingException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			URL url = null;
			//		HttpsTask task = new HttpsTask();
			//		task.execute("https://ec2-54-243-69-6.compute-1.amazonaws.com/");
			//		Log.d("Johan", "Posting URL");
			try {
				url = new URL(urls[0]);
				HttpURLConnection conn = (HttpURLConnection) url.openConnection();
				conn.setDoOutput(true);
				conn.setRequestMethod("POST");
				OutputStreamWriter wr = new OutputStreamWriter(
						conn.getOutputStream());
				// this is were we're adding post data to the request
				wr.write(sb.toString());
				wr.flush();
				myInputStream = conn.getInputStream();
				wr.close();
			} catch (Exception e) {
				// handle the exception !
				System.out.println("Error Message: " + e.getMessage());
			}
			
			JSONObject returnJSONObject = null;
			try {
				if(myInputStream != null){
					returnJSONObject = new JSONObject(JSONHandler.convertStreamToString(myInputStream));
					System.out.println("JSONObject Response: " + returnJSONObject.toString());
					if(returnJSONObject.has("error")){
						error_message = (String)returnJSONObject.get("error");
						success = false;
					}else{
						success = true;
					}
				}
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			return myInputStream;
		}

		protected void onProgressUpdate(Integer... progress) {
			// Check progress
		}

		protected void onPostExecute(InputStream responseStream) {
			if (success){
				new AlertDialog.Builder(getActivity())
				.setIcon(R.drawable.ic_navigation_accept)
				.setTitle("Success!")
				.setMessage("Adding Graffiti Successful!")
				.setCancelable(false)
				.setPositiveButton("Okay", new DialogInterface.OnClickListener()
				{
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// Close dialog  
						_messageBox.setText("");
					}
				})
				.show();

			} else {
				new AlertDialog.Builder(getActivity())
				.setIcon(R.drawable.ic_navigation_cancel)
				.setTitle("Failure!")
				.setMessage("Adding Graffiti Unsuccessful:\n" + error_message)
				.setCancelable(false)
				.setPositiveButton("Okay", new DialogInterface.OnClickListener()
				{
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// Close dialog  

					}
				})
				.show();			
			}
		}
	}
	
}
