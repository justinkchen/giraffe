package com.cs210.giraffe;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
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
