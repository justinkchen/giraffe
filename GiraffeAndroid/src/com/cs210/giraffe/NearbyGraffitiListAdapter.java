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
import android.location.Location;
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
			holder.setDistanceView((TextView) view.findViewById(R.id.distance));
			holder.setDateCreatedView((TextView) view
					.findViewById(R.id.date_created));
			holder.setTimeCreatedView((TextView) view
					.findViewById(R.id.time_created));
			holder.setGraffitiImageView((ImageView) view
					.findViewById(R.id.graffiti_image));
			holder.setProfileImageView((ImageView) view
					.findViewById(R.id.profile_image));
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
		Log.w("ListPositions", "text: " + holder.getMessageView().getText()
				+ ", holder position: " + holder.getPosition() + " position: "
				+ position);

		if (holder.getPosition() == position) {
			// username = (TextView) view.findViewById(R.id.username);
			// message = (TextView) view.findViewById(R.id.message);
			// graffitiImage = (ImageView)
			// view.findViewById(R.id.graffiti_image);
			holder.getUsernameView().setTypeface(null, Typeface.BOLD);
			holder.getUsernameView().setText(item.getUsername());
			holder.getUsernameView().setOnClickListener(
					new ProfileOnClickListener(holder));
			holder.getMessageView().setText(item.getText());
			holder.getDistanceView().setText(
					String.format("%.2f", item.getDistanceFromUser())
							+ " m away");
			setDate(holder);
			setTime(holder);
			// message.setOnClickListener(new MessageOnClickListener());
			buttonLayout = (LinearLayout) view.findViewById(R.id.button_layout);

			// likeButton.setOnClickListener(new LikeOnClickListener(position));
			holder.getLikeButton().setOnClickListener(
					new LikeOnClickListener(holder));
			// flagButton = (Button) view.findViewById(R.id.flag_button);
			holder.getFlagButton().setOnClickListener(
					new FlagOnClickListener(holder));
			// System.out.println("item image url: " + item.getImageURL());

			// holder.setItem(item);
			if (holder.getItem().getIsLiked() == 1) {
				// holder.getLikeButton().setText("Liked");
				holder.getLikeButton().setBackgroundResource(R.drawable.heart);
			} else {
				// holder.getLikeButton().setText("Like");
				holder.getLikeButton().setBackgroundResource(
						R.drawable.blackheart);
			}
			holder.getLikeButton().setText(
					String.valueOf(holder.getItem().getLikes()));
			if (holder.getImageUrl() != null
					&& !holder.getImageUrl().equals("null")) {
				new ListViewDownloadImageTask(holder, position,
						holder.getGraffitiImageView()).executeOnExecutor(
						AsyncTask.THREAD_POOL_EXECUTOR,
						MainActivity.getBaseServerURI() + holder.getImageUrl());
				// graffitiImage.setOnClickListener(new
				// MessageOnClickListener());
			}
			if (!holder.getItem().getAvatar().equals("null")) {
				new ListViewDownloadImageTask(holder, position,
						holder.getProfileImageView()).executeOnExecutor(
						AsyncTask.THREAD_POOL_EXECUTOR,
						MainActivity.getBaseServerURI()
								+ holder.getItem().getAvatar());
			}
		} else {
			holder = new ViewHolder();
			view = _inflater.inflate(R.layout.nearby_graffiti_item, parent,
					false);
			holder.setUsernameView((TextView) view.findViewById(R.id.username));
			holder.setMessageView((TextView) view.findViewById(R.id.message));
			holder.setGraffitiImageView((ImageView) view
					.findViewById(R.id.graffiti_image));
			holder.setDistanceView((TextView) view.findViewById(R.id.distance));
			holder.setDateCreatedView((TextView) view.findViewById(R.id.date_created));
			holder.setTimeCreatedView((TextView) view.findViewById(R.id.time_created));
			holder.setLikeButton((Button) view.findViewById(R.id.like_button));
			holder.setFlagButton((Button) view.findViewById(R.id.flag_button));
			holder.setPosition(position);
			holder.setItem(getItem(position));
			holder.setProfileImageView((ImageView) view
					.findViewById(R.id.profile_image));
			holder.setImageUrl(getItem(position).getImageURL());
			view.setTag(holder);

			item = holder.getItem();

			if (holder.getPosition() == position) {
				// username = (TextView) view.findViewById(R.id.username);
				// message = (TextView) view.findViewById(R.id.message);
				// graffitiImage = (ImageView)
				// view.findViewById(R.id.graffiti_image);
				holder.getUsernameView().setTypeface(null, Typeface.BOLD);
				holder.getUsernameView().setText(item.getUsername());
				holder.getUsernameView().setOnClickListener(
						new ProfileOnClickListener(holder));
				holder.getMessageView().setText(item.getText());
				setDate(holder);
				setTime(holder);
				holder.getDistanceView().setText(
						String.format("%.2f", item.getDistanceFromUser())
								+ " m away");
				// message.setOnClickListener(new MessageOnClickListener());
				buttonLayout = (LinearLayout) view
						.findViewById(R.id.button_layout);

				// likeButton.setOnClickListener(new
				// LikeOnClickListener(position));
				holder.getLikeButton().setOnClickListener(
						new LikeOnClickListener(holder));
				// flagButton = (Button) view.findViewById(R.id.flag_button);
				holder.getFlagButton().setOnClickListener(
						new FlagOnClickListener(holder));
				// System.out.println("item image url: " + item.getImageURL());

				// holder.setItem(item);
				if (holder.getItem().getIsLiked() == 1) {
					// holder.getLikeButton().setText("Liked");
					holder.getLikeButton().setBackgroundResource(
							R.drawable.heart);
				} else {
					// holder.getLikeButton().setText("Like");
					holder.getLikeButton().setBackgroundResource(
							R.drawable.blackheart);
				}
				holder.getLikeButton().setText(
						String.valueOf(holder.getItem().getLikes()));
				if (holder.getImageUrl() != null
						&& !holder.getImageUrl().equals("null")) {
					new ListViewDownloadImageTask(holder, position,
							holder.getGraffitiImageView()).executeOnExecutor(
							AsyncTask.THREAD_POOL_EXECUTOR,
							MainActivity.getBaseServerURI()
									+ holder.getImageUrl());
					// graffitiImage.setOnClickListener(new
					// MessageOnClickListener());
				}
				if (!holder.getItem().getAvatar().equals("null")) {
					new ListViewDownloadImageTask(holder, position,
							holder.getProfileImageView()).executeOnExecutor(
							AsyncTask.THREAD_POOL_EXECUTOR,
							MainActivity.getBaseServerURI()
									+ holder.getItem().getAvatar());
				}
			}
		}
		return view;
	}

	private class ProfileOnClickListener implements OnClickListener {

		ViewHolder holder;

		public ProfileOnClickListener(ViewHolder currHolder) {
			holder = currHolder;
		}

		@Override
		public void onClick(View v) {
			Intent intent = new Intent(getContext(), ProfileActivity.class);
			intent.putExtra("userid", holder.getItem().getUserid());
			Log.i("Johan", "Userid for this item:"
					+ holder.getItem().getUserid());
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
			Log.i("Johan", "Clicked Like Button");
			if (MainActivity.isLoggedIn()) {
				LikeTask likeTask = new LikeTask();
				likeTask.execute(MainActivity.getBaseServerURI()
						+ "/graffiti/like", _holder);
			}

		}
	}

	private class FlagOnClickListener implements OnClickListener {

		private ViewHolder _holder;

		public FlagOnClickListener(ViewHolder holder) {
			_holder = holder;
		}

		@Override
		public void onClick(View v) {
			Log.i("Johan", "Clicked Flag Button");
			if (MainActivity.isLoggedIn()) {
				// TODO: FlagTask
				FlagTask flagTask = new FlagTask();
				flagTask.execute(MainActivity.getBaseServerURI()
						+ "/graffiti/flag", _holder);
			}
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
						+ URLEncoder.encode(
								String.valueOf(_viewHolder.getItem().getId()),
								"UTF-8"));
				sb.append("&isLiked="
						+ URLEncoder.encode(String.valueOf(1 - _viewHolder
								.getItem().getIsLiked()), "UTF-8"));
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
				Log.i("Johan", "Like successful");
				if (_viewHolder.getItem().getIsLiked() == 0) {
					_viewHolder.getItem().setLikes(
							_viewHolder.getItem().getLikes() + 1);
					_viewHolder.getLikeButton().setBackgroundResource(
							R.drawable.heart);
				} else {
					_viewHolder.getItem().setLikes(
							_viewHolder.getItem().getLikes() - 1);
					_viewHolder.getLikeButton().setBackgroundResource(
							R.drawable.blackheart);
				}
				_viewHolder.getItem().setIsLiked(
						1 - _viewHolder.getItem().getIsLiked());
				_viewHolder.getLikeButton().setText(
						String.valueOf(_viewHolder.getItem().getLikes()));
			}

		}
	}

	private class FlagTask extends AsyncTask<Object, Void, Boolean> {
		// TODO: Implement this on server and client side
		String error_message;
		boolean success = false;
		private ViewHolder _viewHolder;

		@Override
		protected Boolean doInBackground(Object... params) {
			// TODO: implement this
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
				wr.write(sb.toString());
				// wr.flush();
			} catch (ProtocolException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			success = true;
			return success;
		}

		protected void onPostExecute(Boolean success) {
			if (success) {
				Log.i("Johan", "Flag successful");
				_viewHolder.getFlagButton().setBackgroundResource(
						R.drawable.thumbsdown);
			}

		}
	}

	public void setDate(ViewHolder holder) {

		String fullDate = holder.getItem().getDateCreated();

		String year = fullDate.substring(0, 4);
		String month = fullDate.substring(5, 7);

		if (month.equals("01"))
			month = "Jan";
		else if (month.equals("02"))
			month = "Feb";
		else if (month.equals("03"))
			month = "Mar";
		else if (month.equals("04"))
			month = "Apr ";
		else if (month.equals("05"))
			month = "May ";
		else if (month.equals("06"))
			month = "June ";
		else if (month.equals("07"))
			month = "July ";
		else if (month.equals("08"))
			month = "Aug ";
		else if (month.equals("09"))
			month = "Sep ";
		else if (month.equals("10"))
			month = "Oct ";
		else if (month.equals("11"))
			month = "Nov ";
		else
			month = "Dec ";

		String day = fullDate.substring(8, 10);
		String suffix = "th ";
		if (day.equals("01") || day.equals("21") || day.equals("31"))
			suffix = "st ";
		else if (day.equals("02") || day.equals("22"))
			suffix = "nd ";
		else if (day.equals("03") || day.equals("23"))
			suffix = "rd ";

		if (day.substring(0, 1).equals("0"))
			day = day.substring(1, 2);

		holder.getDateCreatedView().setText(month + day + suffix + year);
	}

	public void setTime(ViewHolder holder) {
		String fullDate = holder.getItem().getDateCreated();
		String hour = fullDate.substring(11, 13);
		String minute = fullDate.substring(13, 16);
		int inthour = Integer.parseInt(hour);

		String AMPM = " AM";

		if (inthour > 11)
			AMPM = " PM";
		if (inthour > 12)
			inthour -= 12;
		else if (inthour == 0)
			inthour = 12;

		holder.getTimeCreatedView().setText(inthour + minute + AMPM);
	}
}
