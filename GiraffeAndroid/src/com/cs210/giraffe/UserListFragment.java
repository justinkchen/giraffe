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

public class UserListFragment extends ListFragment implements LoaderManager.LoaderCallbacks<List<Graffiti>>{

	UserGraffitiListAdapter _adapter;
	
	@Override
	public void onActivityCreated(Bundle savedInstanceState){
		super.onActivityCreated(savedInstanceState);
		
		System.out.println("UserListFragment.onActivityCreated");
		
		setEmptyText("No User graffiti");
		
		_adapter = new UserGraffitiListAdapter(getActivity());
		setListAdapter(_adapter);
		
		setListShown(false);
		
		getLoaderManager().initLoader(0, null, this);
	}

	@Override
    public void onListItemClick(ListView l, View v, int position, long id) {
        // Insert desired behavior here.
        Log.i("UserListFragment", "Item clicked: " + id);
    }
	
	@Override
	public Loader<List<Graffiti>> onCreateLoader(int arg0, Bundle arg1) {
		System.out.println("UserListFragment.onCreateLoader");
		Log.i("Johan", "onCreateLoader");
		return new UserGraffitiListLoader(getActivity());
	}

	@Override
	public void onLoadFinished(Loader<List<Graffiti>> arg0, List<Graffiti> data) {
		_adapter.setData(data);
        System.out.println("UserGraffitiListFragment.onLoadFinished");
        Log.i("Johan", "onLoadFinished");
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
