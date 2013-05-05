package com.cs210.giraffe;

import android.os.Bundle;
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

		Preference changePasswordPreference = findPreference("change_password");
		changePasswordPreference
				.setOnPreferenceClickListener(new passwordOnPreferenceClickListener());

		Preference changeProfileImagePreference = findPreference("change_profile_image");
		changeProfileImagePreference
				.setOnPreferenceClickListener(new profileImageOnPreferenceClickListener());
	}

	private class passwordOnPreferenceClickListener implements
			OnPreferenceClickListener {

		public boolean onPreferenceClick(Preference preference) {
			df = new ChangePasswordFragment();
			df.show(getFragmentManager(), "changePassword");
			return true;
		}
	}

	private class profileImageOnPreferenceClickListener implements
			OnPreferenceClickListener {

		public boolean onPreferenceClick(Preference preference) {
			
			return true;
		}
	}
}
