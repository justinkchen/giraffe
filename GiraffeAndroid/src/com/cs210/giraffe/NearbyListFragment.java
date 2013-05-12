package com.cs210.giraffe;

import java.util.List;

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
        Log.i("NearbyListFragment", "Item clicked: " + id);
        if (v.findViewById(R.id.button_layout).getVisibility() == 0)
        	v.findViewById(R.id.button_layout).setVisibility(8);
        else
        	v.findViewById(R.id.button_layout).setVisibility(0);
    }
	
	@Override
	public Loader<List<Graffiti>> onCreateLoader(int arg0, Bundle arg1) {
		System.out.println("NearbyListFragment.onCreateLoader");
		return new NearbyGraffitiListLoader(getActivity());
	}

	@Override
	public void onLoadFinished(Loader<List<Graffiti>> arg0, List<Graffiti> data) {
		_adapter.setData(data);
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
