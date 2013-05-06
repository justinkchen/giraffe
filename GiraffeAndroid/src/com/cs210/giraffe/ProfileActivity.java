package com.cs210.giraffe;


import android.app.Activity;
import android.os.Bundle;
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
        setContentView(R.layout.activity_profile);
//        _pf = new ProfileFragment();
//        
//        getFragmentManager().beginTransaction()
//    		.replace(android.R.id.content, _pf)
//    		.commit();
        getActionBar().setDisplayHomeAsUpEnabled(true);
    }
	
	
	
	
}
