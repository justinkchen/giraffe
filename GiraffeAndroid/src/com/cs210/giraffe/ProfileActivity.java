package com.cs210.giraffe;


import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.View;

public class ProfileActivity extends FragmentActivity {

	private ProfileFragment _pf;
	
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
		DialogFragment newFragment = new ChangePasswordFragment();
	    newFragment.show(getSupportFragmentManager(), "changePassword");
	}
}
