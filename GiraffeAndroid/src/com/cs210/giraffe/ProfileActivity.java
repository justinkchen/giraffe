package com.cs210.giraffe;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class ProfileActivity extends Activity {

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
		_pf.setUsername("Clicked");
	}
}
