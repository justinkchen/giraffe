package com.cs210.giraffe;

import java.io.InputStream;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.graphics.drawable.BitmapDrawable;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.ImageView;

public class ListViewDownloadImageTask extends AsyncTask<String, Void, Bitmap> {
	ViewHolder holder;
	int position;
	ImageView img;

	public ListViewDownloadImageTask(ViewHolder holder, int position,
			ImageView img) {
		this.holder = holder;
		this.position = position;
		this.img = img;
	}

	protected Bitmap doInBackground(String... urls) {
		String urldisplay = urls[0];
		Bitmap bitmap = MainActivity.getBitmapFromMemCache(urldisplay);

		if (bitmap == null) {
			try {
				final BitmapFactory.Options options = new BitmapFactory.Options();
				options.inJustDecodeBounds = true;

				InputStream in = new java.net.URL(urldisplay).openStream();
				BitmapFactory.decodeStream(in, null, options);

				if (options.outWidth > 500 || options.outHeight > 500) {
					float widthRatio = (float) options.outWidth / 500;
					float heightRatio = (float) options.outHeight / 500;
					float inratio = (widthRatio <= heightRatio) ? heightRatio
							: widthRatio;
					Log.i("ListViewDownloadImage",
							Integer.toString(options.outWidth));
					Log.i("ListViewDownloadImage",
							Integer.toString(options.outHeight));
					Log.i("ListViewDownloadImage", Float.toString(widthRatio));
					Log.i("ListViewDownloadImage", Float.toString(heightRatio));
					Log.i("ListViewDownloadImage", Float.toString(inratio));
					options.inSampleSize = Math.round(inratio);
				}
				options.inJustDecodeBounds = false;
				InputStream in2 = new java.net.URL(urldisplay).openStream();
				bitmap = BitmapFactory.decodeStream(in2, null, options);
				if (bitmap == null)
					Log.i("ListViewDownloadImage", "isnull");
				else
					Log.i("ListViewDownloadImage", "not null");

				MainActivity.addBitmapToMemoryCache(urldisplay, bitmap);
			} catch (Exception e) {
				Log.e("Error", e.getMessage());
				e.printStackTrace();
			}
		} else {
			Log.i("ListViewDownloadImage", "found in cache");
		}
		return bitmap;
	}

	protected void onPostExecute(Bitmap result) {
		if (result != null) {
			if (holder.getPosition() == this.position) {
				if (result.getWidth() > 500 || result.getHeight() > 500) {
					float widthRatio = (float) 500 / result.getWidth();
					float heightRatio = (float) 500 / result.getHeight();
					float ratio = (widthRatio <= heightRatio) ? widthRatio
							: heightRatio;
					Log.i("ListViewDownloadImage",
							Integer.toString(result.getWidth()));
					Log.i("ListViewDownloadImage",
							Integer.toString(result.getHeight()));
					Log.i("ListViewDownloadImage", Float.toString(widthRatio));
					Log.i("ListViewDownloadImage", Float.toString(heightRatio));
					Log.i("ListViewDownloadImage", Float.toString(ratio));
					Matrix matrix = new Matrix();
					matrix.postScale(ratio, ratio);
					result = Bitmap.createBitmap(result, 0, 0,
							result.getWidth(), result.getHeight(), matrix,
							false);
				} 
				img.setImageBitmap(result);
			}
		}
	}
}
