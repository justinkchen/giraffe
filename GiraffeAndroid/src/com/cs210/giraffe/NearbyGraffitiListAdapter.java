package com.cs210.giraffe;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.graphics.Typeface;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListAdapter;
import android.widget.TextView;

public class NearbyGraffitiListAdapter extends ArrayAdapter<Graffiti> implements
		ListAdapter {

	private final LayoutInflater _inflater;
	private TextView username;
	private TextView message;
	private ImageView graffitiImage;
	private Graffiti item;
	private LinearLayout buttonLayout;
	private Button likeButton;
	private Button flagButton;

	public NearbyGraffitiListAdapter(Context context) {
		super(context, android.R.layout.simple_list_item_2);
		_inflater = (LayoutInflater) context
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	}

	public void setData(List<Graffiti> data) {
		clear();
		if (data != null) {
			addAll(data);
		}
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		View view;

		if (convertView == null) {
			view = _inflater.inflate(R.layout.nearby_graffiti_item, parent,
					false);
		} else {
			view = convertView;
		}

		item = getItem(position);
		username = (TextView) view.findViewById(R.id.username);
		message = (TextView) view.findViewById(R.id.message);
		graffitiImage = (ImageView) view.findViewById(R.id.graffiti_image);

		username.setTypeface(null, Typeface.BOLD);
		username.setText(item.getUsername());
		username.setOnClickListener(new ProfileOnClickListener());
		message.setText(item.getText());
		message.setOnClickListener(new MessageOnClickListener());
		
		buttonLayout = (LinearLayout) view.findViewById(R.id.button_layout);
		
		likeButton = (Button) view.findViewById(R.id.like_button);
		likeButton.setOnClickListener(new LikeOnClickListener());
		flagButton = (Button) view.findViewById(R.id.flag_button);
		flagButton.setOnClickListener(new FlagOnClickListener());
		
		System.out.println("item image url: " + item.getImageURL());
		if (!item.getImageURL().equals("null")) {
			new DownloadImageTask(graffitiImage).execute(item.getImageURL());
			graffitiImage.setOnClickListener(new MessageOnClickListener());
		}

		// if(!item.getAvatar().equals("null")){
		// new DownloadImageTask((ImageView)
		// view.findViewById(R.id.profile_image))
		// .execute(MainActivity.getBaseServerURI() + item.getAvatar());
		// }

		return view;
	}

	private class ProfileOnClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			Intent intent = new Intent(getContext(), ProfileActivity.class);
			intent.putExtra("userid", item.getUserid());
			intent.putExtra("username", item.getUsername());
			intent.putExtra("imagePath", item.getAvatar());
			getContext().startActivity(intent);
		}
	}

	private class MessageOnClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			// Add functionality for likes
			if (buttonLayout.getVisibility() == 0) {
				buttonLayout.setVisibility(8);
			} else {
				buttonLayout.setVisibility(0);
			}
		}
	}
	
	private class LikeOnClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			
		}
		
	}
	
	private class FlagOnClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			
		}
		
	}
}
