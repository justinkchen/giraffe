package com.cs210.giraffe;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.security.cert.Certificate;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLPeerUnverifiedException;

import android.os.AsyncTask;
import android.util.Log;

public class HttpsTask extends AsyncTask<String, Integer, String> {

	public String doInBackground(String... arg) {
		URL url;

		try {
			Log.d("Johan", "Attempting to post");
			url = new URL(arg[0]);
			HttpsURLConnection con = (HttpsURLConnection) url.openConnection();

			// dumpl all cert info
			print_https_cert(con);

			// dump all the content
			print_content(con);

		} catch (MalformedURLException e) {
			Log.d("Johan", "Malformed URL");
			e.printStackTrace();
		} catch (IOException e) {
			Log.d("Johan", "IOException");
			e.printStackTrace();
		}

		return null;
	}

	private void print_https_cert(HttpsURLConnection con) {
		Log.d("Johan", "print_https_cert");
		if (con != null) {

			try {

				Log.d("Johan", "Response Code : " + con.getResponseCode());
				Log.d("Johan", "Cipher Suite : " + con.getCipherSuite());
				Log.d("Johan", "\n");

				Certificate[] certs = con.getServerCertificates();
				for (Certificate cert : certs) {
					Log.d("Johan", "Cert Type : " + cert.getType());
					Log.d("Johan", "Cert Hash Code : " + cert.hashCode());
					Log.d("Johan", "Cert Public Key Algorithm : "
							+ cert.getPublicKey().getAlgorithm());
					Log.d("Johan", "Cert Public Key Format : "
							+ cert.getPublicKey().getFormat());
					Log.d("Johan", "\n");
				}

			} catch (SSLPeerUnverifiedException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}

		}

	}

	private void print_content(HttpsURLConnection con) {
		Log.d("Johan", "print_content");
		if (con != null) {

			try {

				Log.d("Johan", "****** Content of the URL ********");
				BufferedReader br = new BufferedReader(new InputStreamReader(
						con.getInputStream()));

				String input;

				while ((input = br.readLine()) != null) {
					Log.d("Johan", input);
				}
				br.close();

			} catch (IOException e) {
				e.printStackTrace();
			}

		}

	}
}
