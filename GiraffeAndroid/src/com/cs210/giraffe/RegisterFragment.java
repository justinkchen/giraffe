package com.cs210.giraffe;

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
import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.AlertDialog;
import android.support.v4.app.Fragment;
import android.content.DialogInterface;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class RegisterFragment extends Fragment {

	private String _username;
	private String _email;
	private String _password1;
	private String _password2;
	private TextView _errorMessage;

	public RegisterFragment(){

	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_register,
				container, false);

		final Button registerButton = (Button) rootView.findViewById(R.id.registerbutton);

		registerButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// Perform action on click
				new RegisterTask().execute(MainActivity.getBaseServerURI() + "/users/signup");
			}
		});

		return rootView;
	}

	private InputStream postRegister(String username, String email, String password, String urlString){
		InputStream myInputStream = null;
		StringBuilder sb = new StringBuilder();
		//adding some data to send along with the request to the server
		System.out.println("Username: " + username);
		System.out.println("Email: " + email);
		System.out.println("Password: " + password);
		System.out.println("url: " + urlString);
		try {
			sb.append("username=" + URLEncoder.encode(username, "UTF-8"));
			sb.append("&email=" + URLEncoder.encode(email, "UTF-8"));
			sb.append("&password=" + URLEncoder.encode(password, "UTF-8"));
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
			OutputStreamWriter wr = new OutputStreamWriter(conn
					.getOutputStream());
			// this is were we're adding post data to the request
			wr.write(sb.toString());
			wr.flush();
			myInputStream = conn.getInputStream();
			wr.close();
		} catch (Exception e) {
			//handle the exception !
			e.printStackTrace();
		}
		return myInputStream;
	}

	private class RegisterTask extends AsyncTask<String, Integer, InputStream> {
		private boolean success = false;
		String error_message = null;

		protected InputStream doInBackground(String... urls) {
			InputStream myInputStream = null;
			StringBuilder sb = new StringBuilder();
			String username = ((EditText) getActivity().findViewById(R.id.username)).getText().toString();
			String email = ((EditText) getActivity().findViewById(R.id.email)).getText().toString();
			String password = ((EditText) getActivity().findViewById(R.id.password)).getText().toString();
			String urlString = urls[0];
			//adding some data to send along with the request to the server
			System.out.println("Username: " + username);
			System.out.println("Email: " + email);
			System.out.println("Password: " + password);
			System.out.println("url: " + urls[0]);
			try {
				sb.append("username=" + URLEncoder.encode(username, "UTF-8"));
				sb.append("&email=" + URLEncoder.encode(email, "UTF-8"));
				sb.append("&password=" + URLEncoder.encode(password, "UTF-8"));
			} catch (UnsupportedEncodingException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			URL url = null;
			//			HttpsTask task = new HttpsTask();
			//			task.execute("https://ec2-54-243-69-6.compute-1.amazonaws.com/");
			//			Log.d("Johan", "Posting URL");
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
				
				String cookieStr = conn.getHeaderField("Set-Cookie");
				if (cookieStr != null){
					cookieStr = cookieStr.substring(0, cookieStr.indexOf(';'));
					HttpCookie cookie = new HttpCookie(cookieStr.substring(0, cookieStr.indexOf('=')), cookieStr.substring(cookieStr.indexOf('='), cookieStr.length()));
					cookie.setDomain(MainActivity.getBaseServerURI());
					cookie.setPath("/");
					cookie.setVersion(0);
					try {
						if(MainActivity.getCookieManager().getCookieStore().get(new URI(MainActivity.getBaseServerURI())).size() == 0){
							MainActivity.getCookieManager().getCookieStore().add(new URI(MainActivity.getBaseServerURI()), cookie);
						}
					} catch (URISyntaxException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				System.out.println("cookie store: " + MainActivity.getCookieManager().getCookieStore().getCookies().get(0).getValue());

			} catch (Exception e) {
				//handle the exception !
				e.printStackTrace();
			}
			JSONObject returnJSONObject = null;
			try {
				if(myInputStream != null){
					returnJSONObject = new JSONObject(JSONHandler.convertStreamToString(myInputStream));
					System.out.println("JSONObject: " + returnJSONObject.toString());
					if(returnJSONObject.has("error")){
						error_message = (String)returnJSONObject.get("error");
						success = false;
					}else{
						JSONObject userObject = (JSONObject) returnJSONObject.get("user");
						User currentUser = new User();
						currentUser.setEmail(userObject.getString("email"));
						currentUser.setId(userObject.getInt("id"));
						currentUser.setUsername(userObject.getString("username"));
						if(!userObject.getString("avatar").equals("null")){
							currentUser.setAvatar(userObject.getString("avatar"));
						}
						MainActivity.setCurrentUser(currentUser);
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
				.setMessage("Registration Successful!")
				.setCancelable(false)
				.setPositiveButton("Okay", new DialogInterface.OnClickListener()
				{
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// Close dialog  
						getActivity().finish();
					}
				})
				.show();
				
				HttpCookie cookie = new HttpCookie("user", "fr");
				cookie.setDomain(MainActivity.getBaseServerURI());
				cookie.setPath("/");
				cookie.setVersion(0);
				try {
					MainActivity.getCookieManager().getCookieStore().add(new URI(MainActivity.getBaseServerURI()), cookie);
				} catch (URISyntaxException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			} else {
				new AlertDialog.Builder(getActivity())
				.setIcon(R.drawable.ic_navigation_cancel)
				.setTitle("Failure!")
				.setMessage("Registration Unsuccessful:\n" + error_message)
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


