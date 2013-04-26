package com.cs210.giraffe;

import android.app.Activity;
import android.os.Bundle;

public class ProfileActivity extends Activity {

	public ProfileActivity() {
		// TODO Auto-generated constructor stub
	}

	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getFragmentManager().beginTransaction()
    		.replace(android.R.id.content, new ProfileFragment())
    		.commit();
        getActionBar().setDisplayHomeAsUpEnabled(true);
    }
}
