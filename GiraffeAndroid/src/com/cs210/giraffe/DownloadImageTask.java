package com.cs210.giraffe;

import java.io.InputStream;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.ImageView;

public class DownloadImageTask extends AsyncTask<String, Void, Bitmap> {
	ImageView bmImage;

	public DownloadImageTask(ImageView imageView) {
		this.bmImage = imageView;
	}

	protected Bitmap doInBackground(String... urls) {
		String urldisplay = urls[0];
		Bitmap bitmap = MainActivity.getBitmapFromMemCache(urldisplay);
		
		try {
			InputStream in = new java.net.URL(urldisplay).openStream();
			bitmap = BitmapFactory.decodeStream(in);
			MainActivity.addBitmapToMemoryCache(urldisplay, bitmap);
		} catch (Exception e) {
			Log.e("Error", e.getMessage());
			e.printStackTrace();
		}
		return bitmap;
	}

	protected void onPostExecute(Bitmap result) {
		bmImage.setImageBitmap(result);
	}
}
