package com.cs210.giraffe;

import com.google.android.gms.maps.SupportMapFragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ImageButton;

public class NearbyGraffitiFragment extends Fragment {
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_nearby, container,
				false);

		ImageButton refreshButton = (ImageButton) rootView.findViewById(R.id.refreshbutton);
		
		refreshButton.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				NearbyListFragment nearbyListFrag = (NearbyListFragment) getActivity().getSupportFragmentManager()
						.findFragmentById(R.id.nearbyListFragment);
			
				getActivity().getSupportLoaderManager().restartLoader(0, null, nearbyListFrag);
			}
			
		});
		
		return rootView;
	}
	
	@Override
	public void onDestroyView() {
		super.onDestroyView();
		if(!getActivity().isFinishing()){
			Log.w("NearbyListFragment", "Destroying View");
			NearbyListFragment f = (NearbyListFragment) this.getActivity()
					.getSupportFragmentManager()
					.findFragmentById(R.id.nearbyListFragment);
			if (f != null) {
				FragmentTransaction ft = this.getActivity().getSupportFragmentManager().beginTransaction();
				ft.remove(f).commit();
			}
		}
	}
}
