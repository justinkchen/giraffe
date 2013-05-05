package com.cs210.giraffe;


import java.io.File;
import java.util.ArrayList;


import android.app.Fragment;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

public class ProfileFragment extends Fragment {
	
	private TextView _userText;
	private ListView _userPostsView;
	ArrayAdapter<Graffiti> _adapter;
	private ArrayList<Graffiti> _userPosts; 
	private UserGraffitiListLoader _userPostLoader;
	private ImageView _userProfilePicture;
	
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
		_userPostsView = (ListView) rootView.findViewById(R.id.userPostListView);
		_userPostLoader = new UserGraffitiListLoader(getActivity());
		_userPosts = new ArrayList<Graffiti>();
		_adapter = new ArrayAdapter<Graffiti>(getActivity(), android.R.layout.simple_list_item_2, _userPosts);
		_userPostsView.setAdapter(_adapter);
		_userProfilePicture = (ImageView) rootView.findViewById(R.id.userImageView);
		
		return rootView;
	}
	
	public void setUsername(String s) {
		_userText.setText(s);
	}
	
	public void loadPosts() {
		//Make a nice function for loading data here
	}
	
	public void setProfilePicture(Bitmap photo) {
		Log.i("Johan", "Setting profile picture");
		_userProfilePicture.setImageBitmap(photo);
	}
	
}
