package com.cs210.giraffe;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;

import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.os.AsyncTask;
import android.util.Log;

public class UpdateProfilePictureTask extends AsyncTask<Bitmap, Void, String> {

	private Bitmap image;

	private String attachmentName = "bitmap";
	private String attachmentFileName = "bitmap.bmp";
	private String crlf = "\r\n";
	private String twoHyphens = "--";
	private String boundary = "*****";

	public String doInBackground(Bitmap... bitmaps) {

		Log.i("Johan", "Starting image upload.");
		image = bitmaps[0];

		try {
			HttpURLConnection httpUrlConnection = null;
			Log.i("Johan", MainActivity.getBaseServerURI() + "/users/avatarupdate");
			URL url = new URL(
					MainActivity.getBaseServerURI() + "/users/avatarupdate");
			httpUrlConnection = (HttpURLConnection) url.openConnection();
			httpUrlConnection.setUseCaches(false);
			httpUrlConnection.setDoOutput(true);
			// httpUrlConnection.setDoInput(true);
			Log.i("Johan", "Set parameters.");
			httpUrlConnection.setRequestMethod("POST");

			//httpUrlConnection.connect();
			httpUrlConnection.setRequestProperty("Connection", "Keep-Alive");
			httpUrlConnection.setRequestProperty("Cache-Control", "no-cache");
			httpUrlConnection.setRequestProperty("Content-Type",
					"multipart/form-data;boundary=" + this.boundary);

			Log.i("Johan", "Completed setup.");

//			OutputStreamWriter wr = new OutputStreamWriter(
//					httpUrlConnection.getOutputStream());
//			// this is were we're adding post data to the request
//			wr.write("userid=5");
//			wr.flush();
//			wr.close();
//			
			Log.i("Johan", "Wrote body.");
//			OutputStream output = httpUrlConnection.getOutputStream();
			DataOutputStream request = new DataOutputStream(
					httpUrlConnection.getOutputStream());
			
			
			request.writeBytes(this.twoHyphens + this.boundary + this.crlf);
			request.writeBytes("Content-Disposition: form-data; name=\""
					+ "userid\"" + this.crlf);
			request.writeBytes(this.crlf);
			
			String userid = Integer.toString(MainActivity.getCurrentUser().getId());
			byte[] bytes = userid.getBytes();
			request.write(bytes);
			
			request.writeBytes(this.crlf);
			request.writeBytes(this.twoHyphens + this.boundary
					+ this.crlf);
			
			request.writeBytes("Content-Disposition: form-data; name=\""
					+ this.attachmentName + "\";filename=\""
					+ this.attachmentFileName + "\"" + this.crlf);
			request.writeBytes(this.crlf);

			Log.i("Johan", "Completed write prepare.");

			ByteArrayOutputStream stream = new ByteArrayOutputStream();
			image.compress(Bitmap.CompressFormat.PNG, 100, stream);
			byte[] byteArray = stream.toByteArray();

			request.write(byteArray);

			Log.i("Johan", "Completed write.");
			request.writeBytes(this.crlf);
			request.writeBytes(this.twoHyphens + this.boundary
					+ this.twoHyphens + this.crlf);

			Log.i("Johan", "Completed post-write.");
			request.flush();
			request.close();

			// OutputStream output = httpUrlConnection.getOutputStream();
			//
			// // compress and write the image to the output stream
			// image.compress(CompressFormat.JPEG, 50, output);
			// output.close();

			Log.i("Johan", "Response code incoming");
			Log.i("Johan",
					Integer.toString(httpUrlConnection.getResponseCode()));
			Log.i("Johan", "Ready to read.");
			InputStream responseStream = new BufferedInputStream(
					httpUrlConnection.getInputStream());

			BufferedReader responseStreamReader = new BufferedReader(
					new InputStreamReader(responseStream));
			String line = "";
			StringBuilder stringBuilder = new StringBuilder();
			while ((line = responseStreamReader.readLine()) != null) {
				stringBuilder.append(line).append("\n");
			}
			responseStreamReader.close();

			Log.i("Johan", "Completed read.");

			String response = stringBuilder.toString();
			Log.i("Johan", "Response incoming");
			Log.i("Johan", response);

			responseStream.close();

			httpUrlConnection.disconnect();
			
			MainActivity.getCurrentUser().setAvatar(response);

		} catch (Exception e) {
			Log.i("Johan", "Got an error.");
			e.printStackTrace();
		}

		return null;
	}
}
