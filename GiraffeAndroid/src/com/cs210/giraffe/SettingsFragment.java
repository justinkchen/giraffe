package com.cs210.giraffe;

import android.app.DialogFragment;
import android.os.Bundle;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceFragment;
import android.preference.Preference.OnPreferenceClickListener;
import android.util.Log;

public class SettingsFragment extends PreferenceFragment {
	
	public ChangePasswordFragment df;
	
	public SettingsFragment() {
		// TODO Auto-generated constructor stub
	}
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);

        // Load the preferences from an XML resource
        addPreferencesFromResource(R.xml.preferences);
        
        ListPreference pLocAuto = (ListPreference) findPreference("change_password");
        pLocAuto.setOnPreferenceClickListener(new myOnPreferenceClickListener());
    }

   
    private class myOnPreferenceClickListener implements OnPreferenceClickListener {
    	
    	public boolean onPreferenceClick(Preference preference) {
        	Log.i("Johan", "Click");
        	df = new ChangePasswordFragment();
    	    df.show(getFragmentManager(), "changePassword");
            return false;
        }
    }
}
