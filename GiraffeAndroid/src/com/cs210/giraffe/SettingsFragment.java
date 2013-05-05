package com.cs210.giraffe;

import java.io.File;
import java.io.FileNotFoundException;

import android.app.AlertDialog;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.preference.Preference;
import android.preference.PreferenceFragment;
import android.preference.Preference.OnPreferenceClickListener;
import android.provider.MediaStore;
import android.util.Log;
import android.view.MenuInflater;
import android.widget.PopupMenu;

public class SettingsFragment extends PreferenceFragment {

	public static final int TAKE_CAMERA_PICTURE = 100;
	public static final int CHOOSE_GALLERY_PHOTO = 101;
	protected Context context;
	public ChangePasswordFragment df;

	public SettingsFragment() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Load the preferences from an XML resource
		addPreferencesFromResource(R.xml.preferences);

		Preference changePasswordPreference = findPreference("change_password");
		changePasswordPreference
				.setOnPreferenceClickListener(new passwordOnPreferenceClickListener());

		Preference changeProfileImagePreference = findPreference("change_profile_image");
		changeProfileImagePreference
				.setOnPreferenceClickListener(new profileImageOnPreferenceClickListener());

		context = getActivity();
	}

	// Listener to start change password dialog
	private class passwordOnPreferenceClickListener implements
			OnPreferenceClickListener {

		public boolean onPreferenceClick(Preference preference) {
			df = new ChangePasswordFragment();
			df.show(getFragmentManager(), "changePassword");
			return true;
		}
	}

	// Listener to change profile image
	private class profileImageOnPreferenceClickListener implements
			OnPreferenceClickListener {

		public boolean onPreferenceClick(Preference preference) {

			final CharSequence[] items = { "Camera", "Gallery" };

			AlertDialog.Builder builder = new AlertDialog.Builder(context);
			builder.setTitle("Get image from");
			builder.setItems(items, new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int item) {
					switch (item) {
					
					case 0:
						//Use the camer
						Intent cameraIntent = new Intent(
								android.provider.MediaStore.ACTION_IMAGE_CAPTURE);
						startActivityForResult(cameraIntent,
								TAKE_CAMERA_PICTURE);
						break;

					case 1:
						//Choose from the gallery
						Intent pickPhoto = new Intent(
								Intent.ACTION_PICK,
								android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
						startActivityForResult(pickPhoto, CHOOSE_GALLERY_PHOTO);
						break;

					default:
						break;

					}
					// Do something with the selection
				}
			}).setNegativeButton("Cancel", null);
			AlertDialog alert = builder.create();
			alert.show();

			return true;
		}
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		Bitmap photo;
		switch (requestCode) {

		case TAKE_CAMERA_PICTURE:
			photo = (Bitmap) data.getExtras().get("data");
			break;

		case CHOOSE_GALLERY_PHOTO:
			Uri targetUri = data.getData();
			try {
				photo = BitmapFactory.decodeStream(context.getContentResolver()
						.openInputStream(targetUri));
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			break;

		default:
			break;

		}

	}
}
