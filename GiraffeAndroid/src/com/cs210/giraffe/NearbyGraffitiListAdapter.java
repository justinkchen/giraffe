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
	private Graffiti item;
	private LinearLayout buttonLayout;
	private ViewHolder holder;

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
		holder = null;

		if (convertView == null) {
			holder = new ViewHolder();
			view = _inflater.inflate(R.layout.nearby_graffiti_item, parent,
					false);
			holder.setUsernameView((TextView) view.findViewById(R.id.username));
			holder.setMessageView((TextView) view.findViewById(R.id.message));
			holder.setGraffitiImageView((ImageView) view
					.findViewById(R.id.graffiti_image));
			holder.setProfileImageView((ImageView) view.findViewById(R.id.profile_image));
			holder.setLikeButton((Button) view.findViewById(R.id.like_button));
			holder.setFlagButton((Button) view.findViewById(R.id.flag_button));
			holder.setPosition(position);
			holder.setItem(getItem(position));
			holder.setImageUrl(holder.getItem().getImageURL());
			view.setTag(holder);
		} else {
			view = convertView;
			holder = (ViewHolder) convertView.getTag();
		}
		item = holder.getItem();
		Log.w("ListPositions", "text: " + holder.getMessageView().getText() + ", holder position: " + holder.getPosition() + " position: " + position);

		if(holder.getPosition() == position){
			// username = (TextView) view.findViewById(R.id.username);
			// message = (TextView) view.findViewById(R.id.message);
			// graffitiImage = (ImageView) view.findViewById(R.id.graffiti_image);
			holder.getUsernameView().setTypeface(null, Typeface.BOLD);
			holder.getUsernameView().setText(item.getUsername());
			holder.getUsernameView().setOnClickListener(
					new ProfileOnClickListener(holder));
			holder.getMessageView().setText(item.getText());
			// message.setOnClickListener(new MessageOnClickListener());
			buttonLayout = (LinearLayout) view.findViewById(R.id.button_layout);

			// likeButton.setOnClickListener(new LikeOnClickListener(position));
			holder.getLikeButton().setOnClickListener(
					new LikeOnClickListener(holder));
			// flagButton = (Button) view.findViewById(R.id.flag_button);
			holder.getFlagButton().setOnClickListener(new FlagOnClickListener());
			// System.out.println("item image url: " + item.getImageURL());

			//holder.setItem(item);
			if (holder.getItem().getIsLiked() == 1){
				holder.getLikeButton().setText("Liked");
			}
			if (holder.getImageUrl() != null && !holder.getImageUrl().equals("null")) {
				new ListViewDownloadImageTask(holder, position, holder.getGraffitiImageView()).executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, MainActivity.getBaseServerURI() + holder.getImageUrl());
				// graffitiImage.setOnClickListener(new MessageOnClickListener());
			}
			if (!holder.getItem().getAvatar().equals("null")){
				new ListViewDownloadImageTask(holder, position, holder.getProfileImageView()).executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,  MainActivity.getBaseServerURI() + holder.getItem().getAvatar());
			}
		}else{
			holder = new ViewHolder();
			view = _inflater.inflate(R.layout.nearby_graffiti_item, parent,
					false);
			holder.setUsernameView((TextView) view.findViewById(R.id.username));
			holder.setMessageView((TextView) view.findViewById(R.id.message));
			holder.setGraffitiImageView((ImageView) view
					.findViewById(R.id.graffiti_image));
			holder.setLikeButton((Button) view.findViewById(R.id.like_button));
			holder.setFlagButton((Button) view.findViewById(R.id.flag_button));
			holder.setPosition(position);
			holder.setItem(getItem(position));
			holder.setProfileImageView((ImageView) view.findViewById(R.id.profile_image));
			holder.setImageUrl(getItem(position).getImageURL());
			view.setTag(holder);

			item = holder.getItem();
			
			if(holder.getPosition() == position){
				// username = (TextView) view.findViewById(R.id.username);
				// message = (TextView) view.findViewById(R.id.message);
				// graffitiImage = (ImageView) view.findViewById(R.id.graffiti_image);
				holder.getUsernameView().setTypeface(null, Typeface.BOLD);
				holder.getUsernameView().setText(item.getUsername());
				holder.getUsernameView().setOnClickListener(
						new ProfileOnClickListener(holder));
				holder.getMessageView().setText(item.getText());
				// message.setOnClickListener(new MessageOnClickListener());
				buttonLayout = (LinearLayout) view.findViewById(R.id.button_layout);

				// likeButton.setOnClickListener(new LikeOnClickListener(position));
				holder.getLikeButton().setOnClickListener(
						new LikeOnClickListener(holder));
				// flagButton = (Button) view.findViewById(R.id.flag_button);
				holder.getFlagButton().setOnClickListener(new FlagOnClickListener());
				// System.out.println("item image url: " + item.getImageURL());

				//holder.setItem(item);
				if (holder.getItem().getIsLiked() == 1){
					holder.getLikeButton().setText("Liked");
				}
				if (holder.getImageUrl() != null && !holder.getImageUrl().equals("null")) {
					new ListViewDownloadImageTask(holder, position, holder.getGraffitiImageView()).executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, MainActivity.getBaseServerURI() + holder.getImageUrl());
					// graffitiImage.setOnClickListener(new MessageOnClickListener());
				}
				if (!holder.getItem().getAvatar().equals("null")){
					new ListViewDownloadImageTask(holder, position, holder.getProfileImageView()).executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,  MainActivity.getBaseServerURI() + holder.getItem().getAvatar());
				}
			}
		}
		return view;
	}

	private class ProfileOnClickListener implements OnClickListener {

		ViewHolder holder;

		public ProfileOnClickListener (ViewHolder currHolder) {
			holder = currHolder;
		}

		@Override
		public void onClick(View v) {
			Intent intent = new Intent(getContext(), ProfileActivity.class);
			intent.putExtra("userid", holder.getItem().getUserid());
			Log.i("Johan", "Userid for this item:" + holder.getItem().getUserid());
			intent.putExtra("username", holder.getItem().getUsername());
			intent.putExtra("imagePath", holder.getItem().getAvatar());
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

		private ViewHolder _holder;

		public LikeOnClickListener(ViewHolder holder) {
			_holder = holder;
		}

		@Override
		public void onClick(View v) {
			// §View view = v.findViewWithTag(_position);
			// if (_holder.getLikeButton().getText().equals("Like"))
			// _holder.getLikeButton().setText("Liked");
			// else
			// _holder.getLikeButton().setText("Like");

			Log.i("Johan", "Clicked Like Button");
			if (MainActivity.isLoggedIn()) {
				LikeTask loginTask = new LikeTask();
				loginTask.execute(MainActivity.getBaseServerURI()
						+ "/graffiti/like", _holder);
			}

		}
	}

	private class FlagOnClickListener implements OnClickListener {

		@Override
		public void onClick(View v) {
			Log.i("Johan", "Clicked Flag Button");

		}

	}

	private class LikeTask extends AsyncTask<Object, Void, Boolean> {

		String error_message;
		boolean success = false;
		private ViewHolder _viewHolder;

		@Override
		protected Boolean doInBackground(Object... params) {
			_viewHolder = (ViewHolder) params[1];
			URL url;
			HttpURLConnection conn = null;
			StringBuilder sb = new StringBuilder();
			try {
				url = new URL((String) params[0]);
				conn = (HttpURLConnection) url.openConnection();
				MainActivity.addSessionCookie(conn);
				conn.setDoOutput(true);
				conn.setRequestMethod("POST");
				OutputStreamWriter wr = new OutputStreamWriter(
						conn.getOutputStream());
				// this is were we're adding post data to the request
				sb.append("id="
						+ URLEncoder.encode(String.valueOf(_viewHolder.getItem().getId()),
								"UTF-8"));
				sb.append("&isLiked="
						+ URLEncoder.encode(
								String.valueOf(1 - _viewHolder.getItem().getIsLiked()), "UTF-8"));
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
				_viewHolder.getItem().setIsLiked(1 - _viewHolder.getItem().getIsLiked());
				Log.i("Johan", "Like successful");
				if (_viewHolder.getLikeButton().getText().equals("Like"))
					_viewHolder.getLikeButton().setText("Liked");
				else
					_viewHolder.getLikeButton().setText("Like");
			}

		}
	}

}
