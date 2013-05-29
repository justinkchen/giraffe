package com.cs210.giraffe;

import java.io.InputStream;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.ImageView;

public class ListViewDownloadImageTask extends AsyncTask<String, Void, Bitmap> {
	ViewHolder holder;
	int position;

	public ListViewDownloadImageTask(ViewHolder holder, int position) {
		this.holder = holder;
		this.position = position;
	}

	protected Bitmap doInBackground(String... urls) {
		String urldisplay = urls[0];
		Bitmap bitmap = MainActivity.getBitmapFromMemCache(urldisplay);

		if(bitmap == null){
			try {
				InputStream in = new java.net.URL(urldisplay).openStream();
				bitmap = BitmapFactory.decodeStream(in);
				MainActivity.addBitmapToMemoryCache(urldisplay, bitmap);
			} catch (Exception e) {
				Log.e("Error", e.getMessage());
				e.printStackTrace();
			}
		}
		return bitmap;
	}

	protected void onPostExecute(Bitmap result) {
		if(holder.getPosition() == this.position){
			holder.getGraffitiImageView().setImageBitmap(result);
		}
	}
}
