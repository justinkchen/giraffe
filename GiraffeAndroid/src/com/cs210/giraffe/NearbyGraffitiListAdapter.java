package com.cs210.giraffe;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Typeface;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListAdapter;
import android.widget.TextView;

public class NearbyGraffitiListAdapter extends ArrayAdapter<Graffiti> implements ListAdapter{

	private final LayoutInflater _inflater;
	
	public NearbyGraffitiListAdapter(Context context) {
		super(context, android.R.layout.simple_list_item_2);
		_inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	}
	
	
	public void setData(List<Graffiti> data){
		clear();
		if(data != null){
			addAll(data);
		}
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		View view;
		
		if(convertView == null){
			view = _inflater.inflate(R.layout.nearby_graffiti_item, parent, false);
		}else{
			view = convertView;
		}
		
		Graffiti item = getItem(position);
		((TextView)view.findViewById(R.id.username)).setTypeface(null, Typeface.BOLD);
		((TextView)view.findViewById(R.id.username)).setText(item.getUsername());
		((TextView)view.findViewById(R.id.message)).setText(item.getText());
		
		System.out.println("item image url: " + item.getImageURL());
		if(!item.getImageURL().equals("null")){
			new DownloadImageTask((ImageView) view.findViewById(R.id.graffiti_image))
			.execute(item.getImageURL());
		}
		return view;
	}

}
