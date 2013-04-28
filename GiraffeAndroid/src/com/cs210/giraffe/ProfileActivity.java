package com.cs210.giraffe;


import android.app.Dialog;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class ProfileActivity extends FragmentActivity {

	private ProfileFragment _pf;
	private ChangePasswordFragment _df;
	TextView _passwordErrorMessage;
	
	public ProfileActivity() {
		// TODO Auto-generated constructor stub
	}

	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        _pf = new ProfileFragment();
        
        getFragmentManager().beginTransaction()
    		.replace(android.R.id.content, _pf)
    		.commit();
        getActionBar().setDisplayHomeAsUpEnabled(true);
    }
	
	public void changePassword(View v) {
		_df = new ChangePasswordFragment();
	    _df.show(getSupportFragmentManager(), "changePassword");
	}
	
	public void cancelPasswordDialog(View v) {
    	_df.dismiss();
    }
	
	public void submitPasswordDialog(View v) {
		_df.submitChangePassword();
	}
	
	
}
