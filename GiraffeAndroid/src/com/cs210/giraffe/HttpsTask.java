package com.cs210.giraffe;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.security.KeyStore;
import java.security.cert.Certificate;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLPeerUnverifiedException;
import javax.net.ssl.TrustManagerFactory;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.conn.ClientConnectionManager;
import org.apache.http.conn.scheme.PlainSocketFactory;
import org.apache.http.conn.scheme.Scheme;
import org.apache.http.conn.scheme.SchemeRegistry;
import org.apache.http.conn.ssl.SSLSocketFactory;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.impl.conn.SingleClientConnManager;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;

public class HttpsTask extends AsyncTask<String, Integer, String> {
	
	static Context context;
	
	public HttpsTask() {
		
	}
	
	public static void setContext(Context currContext) {
		context = currContext;
	}
	
	
	public String doInBackground(String... arg) {
		URL url;

		
		
		try {
			Log.d("Johan", "Attempting to post");
			char[] password = "mysecret".toCharArray();
			InputStream in;
			in = context.getResources().openRawResource(R.raw.giraffekeystore);       
			KeyStore keyStore = KeyStore.getInstance("BKS");
			keyStore.load(in, password);
		    TrustManagerFactory tmf = TrustManagerFactory.getInstance("X509");
		    tmf.init(keyStore);
		
		    SSLContext context = SSLContext.getInstance("TLS");
		    context.init(null, tmf.getTrustManagers(), null);
		
		    url = new URL(arg[0]);
		    HttpsURLConnection urlConnection = (HttpsURLConnection) url.openConnection();
		    urlConnection.setSSLSocketFactory(context.getSocketFactory());
		    //InputStream in = urlConnection.getInputStream();
			
		

			// dumpl all cert info
			print_https_cert(urlConnection);

			// dump all the content
			print_content(urlConnection);

		} catch (MalformedURLException e) {
			Log.d("Johan", "Malformed URL");
			e.printStackTrace();
		} catch (IOException e) {
			Log.d("Johan", "IOException");
			e.printStackTrace();
		} catch (Exception e) {
		Log.d("Johan", "Exception");
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
				Log.d("Johan", "SSLPeerUnverifiedException");
				e.printStackTrace();
			} catch (IOException e) {
				Log.d("Johan", "IOException");
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
				Log.d("Johan", "IOException");
				e.printStackTrace();
			}

		}

	}

}
