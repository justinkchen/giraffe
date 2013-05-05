package com.cs210.giraffe;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;

import android.app.AlertDialog;
import android.app.Fragment;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.preference.Preference;
import android.preference.Preference.OnPreferenceClickListener;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

public class ProfileFragment extends Fragment {

	public static final int TAKE_CAMERA_PICTURE = 100;
	public static final int CHOOSE_GALLERY_PHOTO = 101;
	public static final int RESULT_OK = -1;

	private TextView _userText;
	private ListView _userPostsView;
	ArrayAdapter<Graffiti> _adapter;
	private ArrayList<Graffiti> _userPosts;
	private UserGraffitiListLoader _userPostLoader;
	private ImageView _userProfilePicture;

	public ProfileFragment() {

	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_profile, container,
				false);

		_userText = (TextView) rootView.findViewById(R.id.userTextView);
		_userPostsView = (ListView) rootView
				.findViewById(R.id.userPostListView);
		_userPostLoader = new UserGraffitiListLoader(getActivity());
		_userPosts = new ArrayList<Graffiti>();
		_adapter = new ArrayAdapter<Graffiti>(getActivity(),
				android.R.layout.simple_list_item_2, _userPosts);
		_userPostsView.setAdapter(_adapter);
		_userProfilePicture = (ImageView) rootView
				.findViewById(R.id.userImageView);
		_userProfilePicture.setOnClickListener(new profileImageClickListener());

		return rootView;
	}

	public void setUsername(String s) {
		_userText.setText(s);
	}

	public void loadPosts() {
		// Make a nice function for loading data here
	}

	public void setProfilePicture(Bitmap photo) {
		Log.i("Johan", "Setting profile picture");
		_userProfilePicture.setImageBitmap(photo);
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
			setProfilePicture(photo);
	}
}
