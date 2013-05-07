package com.cs210.giraffe;

import android.app.AlertDialog;
import android.support.v4.app.DialogFragment;
import android.app.Dialog;
import android.content.Intent;
import android.os.Bundle;
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
		    		getDialog().cancel();
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
        
        return builder.create();
    }
}
