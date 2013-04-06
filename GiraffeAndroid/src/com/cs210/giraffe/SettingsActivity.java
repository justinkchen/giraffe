package com.cs210.giraffe;

import android.app.Activity;
import android.os.Bundle;

public class SettingsActivity extends Activity {

	public SettingsActivity() {
		// TODO Auto-generated constructor stub
	}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Display the fragment as the main content.
        getFragmentManager().beginTransaction()
                .replace(android.R.id.content, new SettingsFragment())
                .commit();
    }
}
