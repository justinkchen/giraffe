package com.cs210.giraffe;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpCookie;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.charset.Charset;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;

public class JSONHandler {

	public static JSONArray getJsonArrayFromURL(URL url, String arrayName){
		String urlInputString = "";
		try {
			HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
			InputStream in = urlConnection.getInputStream();

			System.out.println("Response message: " + urlConnection.getResponseMessage());

			String headerfields = urlConnection.getHeaderField(0);
			int i = 1;
			while ((headerfields = urlConnection.getHeaderField(i)) != null) {
				String key = urlConnection.getHeaderFieldKey(i);
				System.out.println(((key==null) ? "" : key + ": ") + headerfields);
				i++;
			}
			String cookieStr = urlConnection.getHeaderField("Set-Cookie");
			if (cookieStr != null){
				cookieStr = cookieStr.substring(0, cookieStr.indexOf(';'));
				System.out.println("Nearby"); 
				System.out.println("Key: " + cookieStr.substring(0, cookieStr.indexOf('=')));
				System.out.println("Value: " + cookieStr.substring(cookieStr.indexOf('=')+1, cookieStr.length()));
				HttpCookie cookie = new HttpCookie(cookieStr.substring(0, cookieStr.indexOf('=')), cookieStr.substring(cookieStr.indexOf('=')+1, cookieStr.length()));
				cookie.setDomain(MainActivity.getBaseServerURI());
				cookie.setPath("/");
				cookie.setVersion(0);
				System.out.println("Cookie Value: " + cookie.getValue());
				try {
					if(MainActivity.getCookieManager().getCookieStore().get(new URI(MainActivity.getBaseServerURI())).size() == 0){
						MainActivity.getCookieManager().getCookieStore().add(new URI(MainActivity.getBaseServerURI()), cookie);
					}
				} catch (URISyntaxException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}

			System.out.println("cookie store: " + MainActivity.getCookieManager().getCookieStore().getCookies().get(0).getValue());

			urlInputString = convertStreamToString(in);
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

		try {
			JSONObject returnObject = new JSONObject(urlInputString);
			JSONArray returnArray = returnObject.getJSONArray(arrayName);
			return returnArray;
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}

	public static String convertStreamToString(InputStream is) throws IOException {
		//	    java.util.Scanner s = new java.util.Scanner(is, "UTF-8").useDelimiter("\\A");
		//	    return s.hasNext() ? s.next() : "";
		StringBuilder inputStringBuilder = new StringBuilder();
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(is, "UTF-8"));
		String line = bufferedReader.readLine();
		while(line != null){
			System.out.println("Line: " + line);
			inputStringBuilder.append(line);
			inputStringBuilder.append('\n');
			line = bufferedReader.readLine();
		}
		String outputString = inputStringBuilder.toString();
		System.out.println("Stream string: " + outputString);
		return outputString;
	}

}
