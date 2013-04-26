package com.cs210.giraffe;


import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;
import android.widget.TextView;

public class ProfileFragment extends Fragment {
	
	private TextView _userText;
	private ListView _userPosts;
	
	
	public ProfileFragment () {
		
	}

	@Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);

    }
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_profile,
				container, false);
		
		_userText = (TextView) rootView.findViewById(R.id.userTextView);
		_userPosts = (ListView) rootView.findViewById(R.id.userPostListView);
		return rootView;
	}
	
	public void setUsername(String s) {
		_userText.setText(s);
	}
	
	
}
