package com.cs210.giraffe;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.Preference;
import android.preference.PreferenceFragment;
import android.preference.Preference.OnPreferenceClickListener;
import android.util.Log;

public class SettingsFragment extends PreferenceFragment {

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
		
		Preference logoutPreference = findPreference("logout");
		logoutPreference
				.setOnPreferenceClickListener(new logoutOnPreferenceClickListener());
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

	private class logoutOnPreferenceClickListener implements
			OnPreferenceClickListener {

		public boolean onPreferenceClick(Preference preference) {
			LogoutTask logoutTask = new LogoutTask();
			Log.i("Johan", "About to log out");
			logoutTask.execute(MainActivity.getBaseServerURI() + "/users/logout");
			return true;
		}
	}

	private class LogoutTask extends AsyncTask<String, Void, InputStream> {
		private String error_message = null;
		private boolean success = false;
		@Override
		protected InputStream doInBackground(String... urls) {
			URL url = null;
			JSONObject returnJSONObject = null;
			InputStream myInputStream = null;
			try {
				Log.i("Johan", "About to post");
				url = new URL(urls[0]);
				HttpURLConnection conn = (HttpURLConnection) url
						.openConnection();
				MainActivity.addSessionCookie(conn);
				conn.setDoOutput(true);
				conn.setRequestMethod("POST");
				conn.connect();
				Log.i("Johan", "Posted");
				myInputStream = conn.getInputStream();
				
			} catch (Exception e) {
				// handle the exception !
				System.out.println("Error Message: " + e.getMessage());
			}

			returnJSONObject = null;
			try {
				if (myInputStream != null) {
					returnJSONObject = new JSONObject(
							JSONHandler.convertStreamToString(myInputStream));
					System.out.println("JSONObject Response: "
							+ returnJSONObject.toString());
					if (returnJSONObject.has("error")) {
						error_message = (String) returnJSONObject.get("error");
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
			return myInputStream;
		}
		
		protected void onPostExecute(InputStream responseStream) {
			if (success) {
				MainActivity.getCookieManager().getCookieStore().removeAll();
				MainActivity.setCurrentUser(null);
				NotLoggedInFragment _notLoggedInFragment = new NotLoggedInFragment();
		        getFragmentManager().beginTransaction()
		    		.replace(android.R.id.content, _notLoggedInFragment)
		    		.commit();
			} else {
				
			}
		}

	}
	
}
