package com.cs210.giraffe;

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
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class ChangePasswordFragment extends DialogFragment{
	
	private String _oldPassword;
	private String _newPassword1;
	private String _newPassword2;
	private TextView _errorMessage;
	
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        // Use the Builder class for convenient dialog construction
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        LayoutInflater inflater = getActivity().getLayoutInflater();
       
        
        
        builder.setView(inflater.inflate(R.layout.password_dialog, null)).setTitle("Change Password");
        return builder.create();
    }
    
    public void submitChangePassword() {
    	_errorMessage = (TextView) getDialog().findViewById(R.id.errormessage);
    	_oldPassword = ((EditText) getDialog().findViewById(R.id.oldpassword)).getText().toString();
    	_newPassword1 = ((EditText) getDialog().findViewById(R.id.newpassword1)).getText().toString();
    	_newPassword2 = ((EditText) getDialog().findViewById(R.id.newpassword2)).getText().toString();
    	
    	if (_oldPassword.isEmpty() || _newPassword1.isEmpty() || _newPassword2.isEmpty())
    		_errorMessage.setText("	You have to fill out all of the fields");	
    	else if (!_newPassword1.equals(_newPassword2))
    		_errorMessage.setText("	New password doesn't match");	
    	else {
    		changePassword(_oldPassword, _newPassword1);
    		
    	}
    		
    }
    
    private void changePassword(String oldPassword, String newPassword) {
    	ChangePasswordTask changePasswordTask = new ChangePasswordTask();
    	changePasswordTask.execute(MainActivity.getBaseServerURI() + "/users/update", oldPassword, newPassword);
    }

    private class ChangePasswordTask extends AsyncTask<String, Void, InputStream> {

    	private boolean success = false;
    	String error_message = null;
    	
    	@Override
    	protected InputStream doInBackground(String... params) {
    		InputStream myInputStream = null;
    		StringBuilder sb = new StringBuilder();
    		try {
    			sb.append("oldPassword="
    					+ URLEncoder.encode(params[1], "UTF-8"));
    			sb.append("&password="
    					+ URLEncoder.encode(params[2],"UTF-8"));
    			
    		} catch (UnsupportedEncodingException e1) {
    			// TODO Auto-generated catch block
    			e1.printStackTrace();
    		}
    		URL url = null;
    		
    		try {
    			Log.i("Johan", params[0]);
    			url = new URL(params[0]);
    			HttpURLConnection conn = (HttpURLConnection) url
    					.openConnection();
    			conn.setDoOutput(true);
    			conn.setRequestMethod("PUT");
    			OutputStreamWriter wr = new OutputStreamWriter(
    					conn.getOutputStream());
    			// this is were we're adding post data to the request
    			Log.i("Johan", "Before writing");
    			wr.write(sb.toString());
    			Log.i("Johan", "Finished writing");
    			wr.flush();
    			myInputStream = conn.getInputStream();
    			wr.close();
    		} catch (Exception e) {
    			// handle the exception !
    			Log.i("Johan", "Write exception");
    			e.printStackTrace();
    			System.out.println("Error Message: " + e.getMessage());
    		}

    		
    		JSONObject returnJSONObject = null;
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
    		return myInputStream;
    	}
    	
    	protected void onPostExecute(InputStream responseStream) {
    		if (success) {
    			Log.i("Johan", "Successful change");
    			getDialog().cancel();
    		} else {
    			Log.i("Johan", "Unsuccessful change");
    			_errorMessage.setText('\t' + error_message);	
    		}
    	}	
    }
}
