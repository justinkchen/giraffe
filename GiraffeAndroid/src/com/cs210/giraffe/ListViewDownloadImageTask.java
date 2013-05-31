package com.cs210.giraffe;

import java.io.InputStream;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.ImageView;

public class ListViewDownloadImageTask extends AsyncTask<String, Void, Bitmap> {
	ViewHolder holder;
	int position;
	ImageView img;

	public ListViewDownloadImageTask(ViewHolder holder, int position, ImageView img) {
		this.holder = holder;
		this.position = position;
		this.img = img;
	}

	protected Bitmap doInBackground(String... urls) {
		String urldisplay = urls[0];
		Bitmap bitmap = MainActivity.getBitmapFromMemCache(urldisplay);

		if(bitmap == null){
			try {
				InputStream in = new java.net.URL(urldisplay).openStream();
				bitmap = BitmapFactory.decodeStream(in);

				if(bitmap.getWidth() > 500 || bitmap.getHeight() > 500) {
					float widthRatio = (float) 500 / bitmap.getWidth();
					float heightRatio = (float) 500 / bitmap.getHeight();
					float ratio = (widthRatio <= heightRatio) ? widthRatio : heightRatio;
					Log.i("ListViewDownloadImage", Integer.toString(bitmap.getWidth()));
					Log.i("ListViewDownloadImage", Integer.toString(bitmap.getHeight()));
					Log.i("ListViewDownloadImage", Float.toString(widthRatio));
					Log.i("ListViewDownloadImage", Float.toString(heightRatio));
					Log.i("ListViewDownloadImage", Float.toString(ratio));
					Matrix matrix = new Matrix();
					matrix.postScale(ratio, ratio);
					bitmap = Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), matrix, false);
				}
				MainActivity.addBitmapToMemoryCache(urldisplay, bitmap);
			} catch (Exception e) {
				Log.e("Error", e.getMessage());
				e.printStackTrace();
			}
		}
		return bitmap;
	}

	protected void onPostExecute(Bitmap result) {
		if(result != null){
			if(holder.getPosition() == this.position){
				if(result.getWidth() > 500 || result.getHeight() > 500) {
					float widthRatio = (float) 500 / result.getWidth();
					float heightRatio = (float) 500 / result.getHeight();
					float ratio = (widthRatio <= heightRatio) ? widthRatio : heightRatio;
					Log.i("ListViewDownloadImage", Integer.toString(result.getWidth()));
					Log.i("ListViewDownloadImage", Integer.toString(result.getHeight()));
					Log.i("ListViewDownloadImage", Float.toString(widthRatio));
					Log.i("ListViewDownloadImage", Float.toString(heightRatio));
					Log.i("ListViewDownloadImage", Float.toString(ratio));
					Matrix matrix = new Matrix();
					matrix.postScale(ratio, ratio);
					result = Bitmap.createBitmap(result, 0, 0, result.getWidth(), result.getHeight(), matrix, false);
				}


				img.setImageBitmap(result);
			}
		}
	}
}
