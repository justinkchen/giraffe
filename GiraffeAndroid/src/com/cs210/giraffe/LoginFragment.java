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

import org.json.JSONException;
import org.json.JSONObject;

import android.app.AlertDialog;
import android.app.DialogFragment;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class LoginFragment extends DialogFragment {
	private String _usernameEmail;
	private String _password;
	private TextView _errorMessage;

	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		// Use the Builder class for convenient dialog construction
		AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
		LayoutInflater inflater = getActivity().getLayoutInflater();
		View loginView = inflater.inflate(R.layout.login_dialog, null);

		builder.setView(loginView).setTitle("Login");

		final Button loginButton = (Button) loginView.findViewById(R.id.loginbutton);
		final Button cancelButton = (Button) loginView.findViewById(R.id.cancelbutton);

		loginButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// Perform action on click
				_errorMessage = (TextView) getDialog().findViewById(R.id.errormessage);
				_usernameEmail = ((EditText) getDialog().findViewById(R.id.username)).getText().toString();
				_password = ((EditText) getDialog().findViewById(R.id.password)).getText().toString();

				if (_password.isEmpty() || _usernameEmail.isEmpty()){
					_errorMessage.setText("Please fill out all fields");		
				} else {
					// Check login credentials
					new LoginTask().execute(MainActivity.getBaseServerURI() + "/users/login");
				}
			}
		});

		cancelButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// Perform action on click
				getDialog().cancel();	
			}
		});

		final Button registerButton = (Button) loginView.findViewById(R.id.registerbutton);
		registerButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				// Perform action on click
				Intent intent = new Intent(getActivity(), RegisterActivity.class);
				getActivity().startActivity(intent);
				getDialog().cancel();
			}
		});

		return builder.create();
	}

	private class LoginTask extends AsyncTask<String, Integer, InputStream> {
		private boolean success = false;
		String error_message = null;

		protected InputStream doInBackground(String... urls) {
			InputStream myInputStream = null;
			StringBuilder sb = new StringBuilder();
			String username = ((EditText) getDialog().findViewById(R.id.username)).getText().toString();
			String password = ((EditText) getDialog().findViewById(R.id.password)).getText().toString();
			String urlString = urls[0];
			//adding some data to send along with the request to the server
			System.out.println("Username: " + username);
			System.out.println("Password: " + password);
			System.out.println("url: " + urls[0]);
			try {
				sb.append("usernameEmail=" + URLEncoder.encode(username, "UTF-8"));
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
				MainActivity.addSessionCookie(conn);
				conn.setDoOutput(true);
				conn.setRequestMethod("POST");
				OutputStreamWriter wr = new OutputStreamWriter(conn
						.getOutputStream());
				// this is were we're adding post data to the request
				wr.write(sb.toString());
				wr.flush();
				myInputStream = conn.getInputStream();
				System.out.println("Response message: " + conn.getResponseMessage());

				String headerfields = conn.getHeaderField(0);
				int i = 1;
				while ((headerfields = conn.getHeaderField(i)) != null) {
					String key = conn.getHeaderFieldKey(i);
					System.out.println(((key==null) ? "" : key + ": ") + headerfields);
					i++;
				}
				wr.close();
				
				String cookieStr = conn.getHeaderField("Set-Cookie");
				if (cookieStr != null){
					cookieStr = cookieStr.substring(0, cookieStr.indexOf(';'));
					Log.w("LoginFragment", "Login"); 
					Log.w("LoginFragment", "Key: " + cookieStr.substring(0, cookieStr.indexOf('=')));
					Log.w("LoginFragment", "Value: " + cookieStr.substring(cookieStr.indexOf('=') +1, cookieStr.length()));
					HttpCookie cookie = new HttpCookie(cookieStr.substring(0, cookieStr.indexOf('=')), cookieStr.substring(cookieStr.indexOf('=')+1, cookieStr.length()));
					cookie.setDomain(MainActivity.getBaseServerURI());
					cookie.setPath("/");
					cookie.setVersion(0);
					Log.w("LoginFragment", "Cookie Value: " + cookie.getValue());
					try {
						MainActivity.getCookieManager().getCookieStore().removeAll();
						MainActivity.getCookieManager().getCookieStore().add(new URI(MainActivity.getBaseServerURI()), cookie);
					} catch (URISyntaxException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				Log.w("LoginFragment", "cookie store: " + MainActivity.getCookieManager().getCookieStore().getCookies().get(0).getValue());

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
						if(!userObject.getString("avatarUrl").equals("null")){
							currentUser.setAvatar(userObject.getString("avatarUrl"));
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
				.setMessage("Login Successful!")
				.setCancelable(false)
				.setPositiveButton("Okay", new DialogInterface.OnClickListener()
				{
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// Close dialog  
						getDialog().cancel();
						getActivity().finish();
						Intent intent = new Intent(getActivity(), getActivity().getClass());
						getActivity().startActivity(intent);
						;
					}
				})
				.show();


			} else {
				new AlertDialog.Builder(getActivity())
				.setIcon(R.drawable.ic_navigation_cancel)
				.setTitle("Failure!")
				.setMessage("Login Unsuccessful:\n" + error_message)
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
