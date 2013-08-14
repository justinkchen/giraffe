package com.cs210.giraffe;

import java.util.ArrayList;

import android.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

public class NotLoggedInFragment extends Fragment {
	
	private LoginFragment _loginFragment;
	
	public NotLoggedInFragment () {
		
	}

	@Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);

    }
	
	@Override
	public void onResume(){
		super.onResume();
		System.out.println("Resuming NotLoggedInFragment");
	}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_notloggedin,
				container, false);
		
		final Button loginButton = (Button) rootView.findViewById(R.id.loginbutton);
		final Button registerButton = (Button) rootView.findViewById(R.id.registerbutton);

		loginButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// Perform action on click
				_loginFragment = new LoginFragment();
				_loginFragment.show(getFragmentManager(), "loginFragment");
				
				
			}
		});

		registerButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// Perform action on click
				Intent intent = new Intent(getActivity(), RegisterActivity.class);
				getActivity().startActivity(intent);
			}
		});
		
		return rootView;
	}
}
