package com.cs210.giraffe;

import java.util.List;

import android.location.Location;
import android.os.Bundle;
import android.support.v4.app.ListFragment;
import android.support.v4.app.LoaderManager;
import android.support.v4.content.Loader;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;

public class NearbyListFragment extends ListFragment implements LoaderManager.LoaderCallbacks<List<Graffiti>>{

	NearbyGraffitiListAdapter _adapter;

	@Override
	public void onActivityCreated(Bundle savedInstanceState){
		super.onActivityCreated(savedInstanceState);

		System.out.println("NearbyListFragment.onActivityCreated");

		setEmptyText("No nearby graffiti");

		_adapter = new NearbyGraffitiListAdapter(getActivity());
		setListAdapter(_adapter);

		setListShown(false);

		//		getLoaderManager().initLoader(0, null, this);
		this.getActivity().getSupportLoaderManager().initLoader(0, null, this);
	}

	@Override
	public void onListItemClick(ListView l, View v, int position, long id) {
		// Insert desired behavior here.
		Log.i("Johan", "Item clicked: " + id);
		Log.i("NearbyListFragment", "Item clicked: " + id);
		if (MainActivity.isLoggedIn()) {
			if (v.findViewById(R.id.button_layout).getVisibility() == View.VISIBLE)
				v.findViewById(R.id.button_layout).setVisibility(View.GONE);
			else {
				v.findViewById(R.id.button_layout).setVisibility(View.VISIBLE);
				//Apparently you need to set unfocusable in code and not xml because Android
				v.findViewById(R.id.like_button).setFocusable(false);
				v.findViewById(R.id.flag_button).setFocusable(false);
			}
		}
	}

	@Override
	public Loader<List<Graffiti>> onCreateLoader(int arg0, Bundle arg1) {
		System.out.println("NearbyListFragment.onCreateLoader");
		Location currLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
		return new NearbyGraffitiListLoader(getActivity(), MainActivity.getBaseServerURI() + "/graffiti/nearby" + "?latitude=" + currLocation.getLatitude() + "&longitude=" + currLocation.getLongitude());
	}

	@Override
	public void onLoadFinished(Loader<List<Graffiti>> arg0, List<Graffiti> data) {
		_adapter.setData(data);
		_adapter.notifyDataSetChanged();
		System.out.println("NearbyGraffitiListFragment.onLoadFinished");
		// The list should now be shown.
		if (isResumed()) {
			setListShown(true);
		} else {
			setListShownNoAnimation(true);
		}
	}

	@Override
	public void onLoaderReset(Loader<List<Graffiti>> arg0) {
		_adapter.setData(null);
	}
}
