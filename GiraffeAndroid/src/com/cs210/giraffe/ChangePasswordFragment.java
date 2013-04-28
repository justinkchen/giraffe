package com.cs210.giraffe;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
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
    		getDialog().cancel();
    	}
    		
    }
    
    private void changePassword(String oldPassword, String newPassword) {
    	//TODO: Change password
    }

    
}
