package com.cs210.giraffe;

import android.app.Activity;
import android.app.DialogFragment;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.Preference.OnPreferenceClickListener;
import android.preference.PreferenceActivity;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;

public class SettingsActivity extends PreferenceActivity {

	private SettingsFragment _sf;
	
	public SettingsActivity() {
		// TODO Auto-generated constructor stub
	}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
    	_sf = new SettingsFragment();
        super.onCreate(savedInstanceState);
        getFragmentManager().beginTransaction()
    		.replace(android.R.id.content, _sf)
    		.commit();
        getActionBar().setDisplayHomeAsUpEnabled(true);
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                // This is called when the Home (Up) button is pressed
                // in the Action Bar.
//                Intent parentActivityIntent = new Intent(this, MainActivity.class);
//                parentActivityIntent.addFlags(
//                        Intent.FLAG_ACTIVITY_CLEAR_TOP |
//                        Intent.FLAG_ACTIVITY_NEW_TASK);
//                startActivity(parentActivityIntent);
                finish();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }
    
    public void cancelPasswordDialog(View v) {
    	_sf.df.dismiss();
    }
	
	public void submitPasswordDialog(View v) {
		_sf.df.submitChangePassword();
	}
}
