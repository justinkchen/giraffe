package com.cs210.giraffe;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.List;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.graphics.Typeface;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
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
		// message.setOnClickListener(new MessageOnClickListener());
		buttonLayout = (LinearLayout) view.findViewById(R.id.button_layout);
		
		likeButton = (Button) view.findViewById(R.id.like_button);
		likeButton.setOnClickListener(new LikeOnClickListener());
		flagButton = (Button) view.findViewById(R.id.flag_button);
		flagButton.setOnClickListener(new FlagOnClickListener());
		System.out.println("item image url: " + item.getImageURL());
		if (!item.getImageURL().equals("null")) {
			new DownloadImageTask(graffitiImage).execute(item.getImageURL());
			// graffitiImage.setOnClickListener(new MessageOnClickListener());
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
			Log.i("Johan", "Userid for this item:" + item.getUserid());
			intent.putExtra("username", item.getUsername());
			intent.putExtra("imagePath", item.getAvatar());
			getContext().startActivity(intent);
		}
	}

	private class MessageOnClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			// Add functionality for likes
			v.findViewById(R.id.button_layout).setVisibility(0);

			// if (buttonLayout.getVisibility() == 0) {
			// buttonLayout.setVisibility(8);
			// } else {
			// buttonLayout.setVisibility(0);
			// }
		}
	}

	private class LikeOnClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			Log.i("Johan", "Clicked Like Button");

		}

	}

	private class FlagOnClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			Log.i("Johan", "Clicked Flag Button");

		}

	}

	private class LikeTask extends
			AsyncTask<String, Void, Boolean> {

		String error_message;
		boolean success = false;

		@Override
		protected Boolean doInBackground(String... urls) {
			URL url;
			HttpURLConnection conn = null;
			StringBuilder sb = new StringBuilder();
			try {
				url = new URL(urls[0]);
				conn = (HttpURLConnection) url.openConnection();
				conn.setDoOutput(true);
				conn.setRequestMethod("POST");
				OutputStreamWriter wr = new OutputStreamWriter(
						conn.getOutputStream());
				// this is were we're adding post data to the request
				wr.write(sb.toString());
				wr.flush();

			} catch (ProtocolException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}

			InputStream myInputStream = null;
			try {
				myInputStream = conn.getInputStream();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			JSONObject returnJSONObject = null;
			try {
				if (myInputStream != null) {
					returnJSONObject = new JSONObject(
							JSONHandler.convertStreamToString(myInputStream));
					System.out.println("JSONObject: "
							+ returnJSONObject.toString());
					if (returnJSONObject.has("error")) {
						error_message = (String) returnJSONObject.get("error");
						success = false;
						return success;
					} else {

						success = true;
						return success;
					}
				}
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return success;

		}

		protected void onPostExecute(Boolean success) {
			if (success) {
			}

		}
	}

}
