package com.cs210.giraffe;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
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
import com.google.android.gms.maps.UiSettings;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Matrix;
import android.location.Location;
import android.media.ThumbnailUtils;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
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
	private Bitmap _photo = null;
	private ImageButton _removeImageButton;
	private TextView _addedImageText;
	
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
		rootView = inflater.inflate(R.layout.fragment_addgraffiti, container,
				false);
		_radiusBar = (SeekBar) rootView.findViewById(R.id.radiusSeekBar);
		_radiusBar.setOnSeekBarChangeListener(this);
		_messageBox = (EditText) rootView.findViewById(R.id.graffitiEditText);

		final ImageButton addImageButton = (ImageButton) rootView
				.findViewById(R.id.addImageButton);

		addImageButton.setOnClickListener(new AddImageButtonClickListener());

		_removeImageButton = (ImageButton) rootView
				.findViewById(R.id.removeImageButton);

		_removeImageButton
				.setOnClickListener(new RemoveImageButtonClickListener());
		
		_addedImageText = (TextView) rootView
				.findViewById(R.id.addedImageText);

		final Button submitButton = (Button) rootView
				.findViewById(R.id.submitButton);
		submitButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				if (MainActivity.isLoggedIn()) {
					// Perform action on click
					Location myLocation = MainActivity
							.getGiraffeLocationListener().getCurrentLocation();
					_newGraffiti = new Graffiti();
					_newGraffiti.setText(_messageBox.getText().toString());
					_newGraffiti.setLatitude(myLocation.getLatitude());
					_newGraffiti.setLongitude(myLocation.getLongitude());
					_newGraffiti.setRadius(_currentProgress);
					String uri = MainActivity.getBaseServerURI() + "/graffiti/new";
					new AddGraffitiTask().execute(uri);
				} else {
					_loginFragment = new LoginSupportFragment();
					_loginFragment.show(getFragmentManager(), "loginFragment");
				}
			}
		});
		
		setMapTransparent((ViewGroup) rootView);
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

		if(!getActivity().isFinishing()){
			Log.w("AddGraffitiFragment", "Destroying View");
			SupportMapFragment f = (SupportMapFragment) this.getActivity()
					.getSupportFragmentManager()
					.findFragmentById(R.id.addGraffitiMap);
			if (f != null) {
				FragmentTransaction ft = this.getActivity().getSupportFragmentManager().beginTransaction();
	//			ft.commitAllowingStateLoss();
				ft.remove(f).commit();
				_circleOverlayMap = null;
				
			}

		}
	}
	
	@Override
	public void onPause(){
		super.onPause();
//		Log.w("AddGraffitiFragment", "Pausing AddGraffitiFragment");
//		SupportMapFragment f = (SupportMapFragment) this.getActivity()
//				.getSupportFragmentManager()
//				.findFragmentById(R.id.addGraffitiMap);
//		if (f != null) {
//			FragmentTransaction ft = this.getActivity().getSupportFragmentManager().beginTransaction();
////			ft.commitAllowingStateLoss();
//			ft.remove(f).commit();
//			_circleOverlayMap = null;
//			
//		}
	}

	public void setUpMapIfNeeded() {
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

			_circleOverlayMap.getUiSettings().setZoomControlsEnabled(false);
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
			sb.append("message="
					+ URLEncoder.encode(newGraffiti.getText(), "UTF-8"));
			sb.append("&latitude="
					+ URLEncoder.encode(
							String.valueOf(newGraffiti.getLatitude()), "UTF-8"));
			sb.append("&longitude="
					+ URLEncoder.encode(
							String.valueOf(newGraffiti.getLongitude()), "UTF-8"));
			sb.append("&radius="
					+ URLEncoder.encode(
							String.valueOf(newGraffiti.getRadius()), "UTF-8"));
			sb.append("&userid="
					+ URLEncoder.encode(String.valueOf(MainActivity.getCurrentUser().getId()), "UTF-8"));
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		URL url = null;
		// HttpsTask task = new HttpsTask();
		// task.execute("https://ec2-54-243-69-6.compute-1.amazonaws.com/");
		// Log.d("Johan", "Posting URL");
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

	private class RemoveImageButtonClickListener implements
			View.OnClickListener {
		public void onClick(View v) {
			_photo = null;
			_addedImageText.setText("");
			_removeImageButton.setVisibility(8);
		}
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		Log.i("Johan", "Getting here");
		String picturePath = null;
		switch (requestCode) {

		case TAKE_CAMERA_PICTURE:
			if (resultCode == RESULT_OK)
				_photo = (Bitmap) data.getExtras().get("data");
			break;

		case CHOOSE_GALLERY_PHOTO:
			if (resultCode == RESULT_OK) {
				Uri targetUri = data.getData();
				try {
					Uri selectedImage = data.getData();
		            String[] filePathColumn = { MediaStore.Images.Media.DATA };
		            Cursor cursor = getActivity().getContentResolver().query(selectedImage,filePathColumn, null, null, null);
		            cursor.moveToFirst();
		            int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
		            picturePath = cursor.getString(columnIndex);		            
		            _photo = BitmapFactory.decodeFile(picturePath);
		            
		            Log.i("Johan", picturePath);
		            picturePath = picturePath.substring(picturePath.lastIndexOf('/')+1);
		            Log.i("Johan", picturePath);
		            cursor.close();

				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			break;

		default:
			break;

		}

		if (_photo != null) {
			_addedImageText.setText(picturePath);
			//Rescale if too big
			if(_photo.getWidth() > 150 || _photo.getHeight() > 150) {
				float widthRatio = (float) 150 / _photo.getWidth();
				float heightRatio = (float) 150 / _photo.getHeight();
				Log.i("Johan", Integer.toString(_photo.getWidth()));
				Log.i("Johan", Integer.toString(_photo.getHeight()));
				Log.i("Johan", Float.toString(widthRatio));
				Log.i("Johan", Float.toString(heightRatio));
				Matrix matrix = new Matrix();
			    matrix.postScale(widthRatio, heightRatio);
			    _photo = Bitmap.createBitmap(_photo, 0, 0, _photo.getWidth(), _photo.getHeight(), matrix, false);
			}
			_removeImageButton.setVisibility(0);
		}
		// Do something with photo
	}

	private class AddGraffitiTask extends
			AsyncTask<String, Integer, InputStream> {
		private boolean success = false;
		String error_message = null;
		private String attachmentName = "bitmap";
		private String attachmentFileName = "bitmap.bmp";
		private String crlf = "\r\n";
		private String twoHyphens = "--";
		private String boundary = "*****";
		private byte[] bytes;

		protected InputStream doInBackground(String... urls) {
			InputStream myInputStream = null;
			JSONObject returnJSONObject = null;
			StringBuilder sb = new StringBuilder();
			// adding some data to send along with the request to the server
			if (_photo == null) {
				try {
					sb.append("message="
							+ URLEncoder.encode(_newGraffiti.getText(), "UTF-8"));
					sb.append("&latitude="
							+ URLEncoder.encode(
									String.valueOf(_newGraffiti.getLatitude()),
									"UTF-8"));
					sb.append("&longitude="
							+ URLEncoder.encode(
									String.valueOf(_newGraffiti.getLongitude()),
									"UTF-8"));
					sb.append("&radius="
							+ URLEncoder.encode(
									String.valueOf(_newGraffiti.getRadius()),
									"UTF-8"));
					sb.append("&userid="
							+ URLEncoder.encode(String.valueOf(MainActivity.getCurrentUser().getId()), "UTF-8"));
				} catch (UnsupportedEncodingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				URL url = null;
				// HttpsTask task = new HttpsTask();
				// task.execute("https://ec2-54-243-69-6.compute-1.amazonaws.com/");
				// Log.d("Johan", "Posting URL");
				try {
					url = new URL(urls[0]);
					HttpURLConnection conn = (HttpURLConnection) url
							.openConnection();
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

				returnJSONObject = null;
				try {
					if (myInputStream != null) {
						returnJSONObject = new JSONObject(
								JSONHandler
										.convertStreamToString(myInputStream));
						System.out.println("JSONObject Response: "
								+ returnJSONObject.toString());
						if (returnJSONObject.has("error")) {
							error_message = (String) returnJSONObject
									.get("error");
							success = false;
						} else {
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
			} else {

				HttpURLConnection httpUrlConnection = null;
				try {
					Log.i("Johan", urls[0]);
					URL url = new URL(urls[0]);
					httpUrlConnection = (HttpURLConnection) url
							.openConnection();
					httpUrlConnection.setUseCaches(false);
					httpUrlConnection.setDoOutput(true);

					Log.i("Johan", "Set parameters.");
					httpUrlConnection.setRequestMethod("POST");

					httpUrlConnection.setRequestProperty("Connection",
							"Keep-Alive");
					httpUrlConnection.setRequestProperty("Cache-Control",
							"no-cache");
					httpUrlConnection.setRequestProperty("Content-Type",
							"multipart/form-data;boundary=" + this.boundary);
				} catch (Exception e) {
					Log.i("Johan", "Problem opening connection");
					e.printStackTrace();
				}

				Log.i("Johan", "Completed setup.");

				try {
					DataOutputStream request = new DataOutputStream(
							httpUrlConnection.getOutputStream());

					request.writeBytes(this.twoHyphens + this.boundary
							+ this.crlf);

					// Send userid
					request.writeBytes("Content-Disposition: form-data; name=\""
							+ "userid\"" + this.crlf);
					request.writeBytes(this.crlf);

					String userid = Integer.toString(MainActivity
							.getCurrentUser().getId());
					bytes = userid.getBytes();
					request.write(bytes);

					request.writeBytes(this.crlf);
					request.writeBytes(this.twoHyphens + this.boundary
							+ this.crlf);

					// Send latitude
					request.writeBytes("Content-Disposition: form-data; name=\""
							+ "latitude\"" + this.crlf);
					request.writeBytes(this.crlf);

					String latitude = Double.toString(_newGraffiti
							.getLatitude());
					bytes = latitude.getBytes();
					request.write(bytes);

					request.writeBytes(this.crlf);
					request.writeBytes(this.twoHyphens + this.boundary
							+ this.crlf);

					// Send longitude
					request.writeBytes("Content-Disposition: form-data; name=\""
							+ "longitude\"" + this.crlf);
					request.writeBytes(this.crlf);

					String longitude = Double.toString(_newGraffiti
							.getLongitude());
					bytes = longitude.getBytes();
					request.write(bytes);

					request.writeBytes(this.crlf);
					request.writeBytes(this.twoHyphens + this.boundary
							+ this.crlf);

					// Send radius
					request.writeBytes("Content-Disposition: form-data; name=\""
							+ "radius\"" + this.crlf);
					request.writeBytes(this.crlf);

					String radius = Integer.toString(_newGraffiti.getRadius());
					bytes = radius.getBytes();
					request.write(bytes);

					request.writeBytes(this.crlf);
					request.writeBytes(this.twoHyphens + this.boundary
							+ this.crlf);

					// Send message
					request.writeBytes("Content-Disposition: form-data; name=\""
							+ "message\"" + this.crlf);
					request.writeBytes(this.crlf);

					String message = _newGraffiti.getText();
					bytes = message.getBytes();
					request.write(bytes);

					request.writeBytes(this.crlf);
					request.writeBytes(this.twoHyphens + this.boundary
							+ this.crlf);

					// Send file
					request.writeBytes("Content-Disposition: form-data; name=\""
							+ this.attachmentName
							+ "\";filename=\""
							+ this.attachmentFileName + "\"" + this.crlf);
					request.writeBytes(this.crlf);

					Log.i("Johan", "Completed write prepare.");

					ByteArrayOutputStream stream = new ByteArrayOutputStream();
					_photo.compress(Bitmap.CompressFormat.PNG, 100, stream);
					byte[] byteArray = stream.toByteArray();

					request.write(byteArray);

					Log.i("Johan", "Completed write.");
					request.writeBytes(this.crlf);
					request.writeBytes(this.twoHyphens + this.boundary
							+ this.twoHyphens + this.crlf);

					Log.i("Johan", "Completed post-write.");
					request.flush();
					request.close();

					Log.i("Johan", "Response code incoming");
					Log.i("Johan", Integer.toString(httpUrlConnection
							.getResponseCode()));
					Log.i("Johan", "Ready to read.");
					myInputStream = httpUrlConnection.getInputStream();

					returnJSONObject = null;
					try {
						if (myInputStream != null) {
							returnJSONObject = new JSONObject(
									JSONHandler
											.convertStreamToString(myInputStream));
							System.out.println("JSONObject Response: "
									+ returnJSONObject.toString());
							if (returnJSONObject.has("error")) {
								error_message = (String) returnJSONObject
										.get("error");
								success = false;
							} else {
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

					// httpUrlConnection.disconnect();

				} catch (Exception e) {
					Log.i("Johan", "Problem sending data");
					e.printStackTrace();
				}
			}
			return myInputStream;
		}

		protected void onProgressUpdate(Integer... progress) {
			// Check progress
		}

		protected void onPostExecute(InputStream responseStream) {
			if (success) {
				new AlertDialog.Builder(getActivity())
						.setIcon(R.drawable.ic_navigation_accept)
						.setTitle("Success!")
						.setMessage("Adding Graffiti Successful!")
						.setCancelable(false)
						.setPositiveButton("Okay",
								new DialogInterface.OnClickListener() {
									@Override
									public void onClick(DialogInterface dialog,
											int which) {
										// Close dialog
										_messageBox.setText("");
									}
								}).show();

			} else {
				new AlertDialog.Builder(getActivity())
						.setIcon(R.drawable.ic_navigation_cancel)
						.setTitle("Failure!")
						.setMessage(
								"Adding Graffiti Unsuccessful:\n"
										+ error_message)
						.setCancelable(false)
						.setPositiveButton("Okay",
								new DialogInterface.OnClickListener() {
									@Override
									public void onClick(DialogInterface dialog,
											int which) {
										// Close dialog

									}
								}).show();
			}
		}
	}
	private void setMapTransparent(ViewGroup group) {
		int childCount = group.getChildCount();
		for (int i = 0; i < childCount; i++) {
			View child = group.getChildAt(i);

			if (child instanceof ViewGroup) {
				setMapTransparent((ViewGroup) child);
			} else if (child instanceof SurfaceView) {
				child.setBackgroundColor(0x00000000);
			}
		}
	}

}
