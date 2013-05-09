package com.cs210.giraffe;

import java.io.FileNotFoundException;
import java.io.InputStream;
import java.net.URL;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.media.ThumbnailUtils;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

public class ProfileFragment extends Fragment implements AsyncResponse {

	public static final int TAKE_CAMERA_PICTURE = 100;
	public static final int CHOOSE_GALLERY_IMAGE = 101;
	public static final int RESULT_OK = -1;
	public static final int THUMBNAIL_HEIGHT = 66;
	public static final int THUMBNAIL_WIDTH = 66;

	private TextView _userText;
	private ImageView _userProfilePicture;
	
	SetProfilePictureTask setProfilePictureTask = new SetProfilePictureTask();
	
	public ProfileFragment() {

	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//Set call back for profile image loader
		setProfilePictureTask.delegate = this;
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_profile, container,
				false);

		_userText = (TextView) rootView.findViewById(R.id.userTextView);
		_userProfilePicture = (ImageView) rootView
				.findViewById(R.id.userImageView);
		_userProfilePicture.setOnClickListener(new profileImageClickListener());

		User currentUser = MainActivity.getCurrentUser();
		String username = currentUser.getUsername();
		String imagePath = currentUser.getAvatar();

		_userText.setText(username);
		if (imagePath != null) {
			Log.i("Johan", imagePath);
			setProfilePictureTask.execute(imagePath);
		}
		Log.i("Johan", "Done setting image");
		return rootView;
	}

	public void setUsername(String s) {
		_userText.setText(s);
	}


	public void setProfilePicture(Bitmap image) {
		Log.i("Johan", "Setting profile picture");
		_userProfilePicture.setImageBitmap(image);
	}

	private class profileImageClickListener implements OnClickListener {

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
						Intent pickimage = new Intent(
								Intent.ACTION_PICK,
								android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
						startActivityForResult(pickimage, CHOOSE_GALLERY_IMAGE);
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
		Bitmap image = null;
		switch (requestCode) {

		case TAKE_CAMERA_PICTURE:
			if (resultCode == RESULT_OK)
				image = (Bitmap) data.getExtras().get("data");
			break;

		case CHOOSE_GALLERY_IMAGE:
			if (resultCode == RESULT_OK) {
				Uri targetUri = data.getData();
				try {
					image = BitmapFactory.decodeStream(getActivity()
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

		if (image != null) {
			image = ThumbnailUtils.extractThumbnail(image, THUMBNAIL_WIDTH,
					THUMBNAIL_HEIGHT);
			setProfilePicture(image);
			UpdateProfilePictureTask updateProfilePictureTask = new UpdateProfilePictureTask();
			updateProfilePictureTask.execute(image);
		}
	}

	public void processFinish(Drawable output) {
		// this you will received result fired from async class of
		// onPostExecute(result) method.
		_userProfilePicture.setImageDrawable(output);
	}
	
	
	private class SetProfilePictureTask extends AsyncTask<String, Void, Drawable> {

		public AsyncResponse delegate=null;
		
		@Override
		protected Drawable doInBackground(String... urls) {
			Drawable image = null;
			try {
				Log.i("Johan", "We open the URL");
				InputStream is = (InputStream) new URL(urls[0]).getContent();
				Log.i("Johan", "We got the URL");
				image = Drawable.createFromStream(is, "src");
			} catch (Exception ex) {
				Log.i("Johan", "Exception in setting image");
				ex.printStackTrace();
			}
			return image;
		}
		
		protected void onPostExecute(Drawable result) {
			delegate.processFinish(result);
		}

	}
}
