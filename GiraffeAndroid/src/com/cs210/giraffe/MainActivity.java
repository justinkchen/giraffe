package com.cs210.giraffe;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.CookieHandler;
import java.net.CookieManager;
import java.net.CookiePolicy;
import java.net.HttpCookie;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.List;
import java.util.Locale;

import org.json.JSONException;
import org.json.JSONObject;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;

import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.FragmentTransaction;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.location.Criteria;
import android.location.LocationManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.app.NavUtils;
import android.support.v4.util.LruCache;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends FragmentActivity implements
ActionBar.TabListener {
	public static final String PREFS_NAME = "GiraffePrefs";
	static final int NUM_TABS = 3;
	private static GiraffeLocationListener locationListener = null;
	private static CookieManager cookieManager = null;
	private static String baseServerURI = /*"http://thegiraffeapp.com";  */"http://ec2-54-224-185-156.compute-1.amazonaws.com";
	private static User currentUser = null;
	private static Menu mainActivityMenu = null;
	private static boolean hasLocation = false;
	private static boolean hasConnection = false;
	private static boolean serverDown = false;
	private static LruCache<String, Bitmap> memoryBitmapCache;

	/**
	 * The {@link android.support.v4.view.PagerAdapter} that will provide
	 * fragments for each of the sections. We use a
	 * {@link android.support.v4.app.FragmentPagerAdapter} derivative, which
	 * will keep every loaded fragment in memory. If this becomes too memory
	 * intensive, it may be best to switch to a
	 * {@link android.support.v4.app.FragmentStatePagerAdapter}.
	 */
	SectionsPagerAdapter mSectionsPagerAdapter;

	/**
	 * The {@link ViewPager} that will host the section contents.
	 */
	CustomViewPager mViewPager;

	protected static boolean isLoggedIn() {
		if (currentUser != null) {
			System.out.println("User: " + currentUser.getUsername());
			return true;
		}
		System.out.println("Not logged in");
		return false;
	}

	protected static void loginUser(User user) {
		currentUser = user;
	}

	@Override
	protected void onResume() {
		super.onResume();

		System.out.println("onResume MainActivity");
		int result = GooglePlayServicesUtil.isGooglePlayServicesAvailable(this
				.getApplicationContext());
		Log.w("GraffitiMap", "Checking Google Play Services status");
		switch (result) {
		case ConnectionResult.SUCCESS:
			// toast =
			// Toast.makeText(this.getActivity().getApplicationContext(),
			// "Google Play Services Found",Toast.LENGTH_LONG);
			// toast.show();
			Log.w("MainActivity", "Google Play Services Found");
			break;
		case ConnectionResult.SERVICE_MISSING:
			// toast =
			// Toast.makeText(this.getActivity().getApplicationContext(),
			// "Need Google Play Services: SERVICE_MISSING",Toast.LENGTH_LONG);
			// toast.show();
			Log.e("MainActivity", "Need Google Play Services: SERVICE_MISSING");
			GooglePlayServicesUtil.getErrorDialog(result, this, result).show();
			// TODO: Set the Error Dialog:
			// GooglePlayServicesUtil.getErrorDialog(result, arg1, arg2)
			break;
		case ConnectionResult.SERVICE_VERSION_UPDATE_REQUIRED:
			// toast =
			// Toast.makeText(this.getActivity().getApplicationContext(),
			// "Need Google Play Services: SERVICE_VERSION_UPDATE_REQUIRED"
			// ,Toast.LENGTH_LONG);
			// toast.show();
			Log.e("MainActivity",
					"Need Google Play Services: SERVICE_VERSION_UPDATE_REQUIRED");
			GooglePlayServicesUtil.getErrorDialog(result, this, result).show();
			// TODO: Set the Error Dialog:
			// GooglePlayServicesUtil.getErrorDialog(result, arg1, arg2)
			break;
		case ConnectionResult.SERVICE_DISABLED:
			// toast =
			// Toast.makeText(this.getActivity().getApplicationContext(),
			// "Need Google Play Services: SERVICE_DISABLED",Toast.LENGTH_LONG);
			// toast.show();
			Log.e("MainActivity", "Need Google Play Services: SERVICE_DISABLED");
			GooglePlayServicesUtil.getErrorDialog(result, this, result).show();
			// TODO: Set the Error Dialog:
			// GooglePlayServicesUtil.getErrorDialog(result, arg1, arg2)
			break;
		}
	}

	@Override
	protected void onResumeFragments() {
		super.onResumeFragments();
		System.out.println("onResumeFragments MainActivity");
		this.invalidateOptionsMenu();
	}

	@Override
	protected void onSaveInstanceState(Bundle outState) {
		outState.putString("WORKAROUND_FOR_BUG_19917_KEY",
				"WORKAROUND_FOR_BUG_19917_VALUE");
		super.onSaveInstanceState(outState);
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Get max available VM memory, exceeding this amount will throw an
		// OutOfMemory exception. Stored in kilobytes as LruCache takes an
		// int in its constructor.
		final int maxMemory = (int) (Runtime.getRuntime().maxMemory() / 1024);
		// Use 1/8th of the available memory for this memory cache.
		final int cacheSize = maxMemory / 8;

		setMemoryBitmapCache(new LruCache<String, Bitmap>(cacheSize) {
			@Override
			protected int sizeOf(String key, Bitmap bitmap) {
				// The cache size will be measured in kilobytes rather than
				// number of items.
				return bitmap.getByteCount() / 1024;
			}
		});

		// Restore preferences
		setPersistentLogin();

		// Acquire a reference to the system Location Manager
		LocationManager locationManager = (LocationManager) this
				.getSystemService(Context.LOCATION_SERVICE);
		Criteria criteria = new Criteria();
		String bestProvider = locationManager.getBestProvider(criteria, false);

		// Register the listener with the Location Manager to receive location
		// updates
		locationListener = new GiraffeLocationListener(locationManager,
				bestProvider);
		hasLocation = checkLocationExists(bestProvider);
		locationManager.requestLocationUpdates(bestProvider, 0, 0,
				locationListener);
		setContentView(R.layout.activity_main);

		hasConnection = checkConnection();
		if (hasLocation && hasConnection && !serverDown) {
			setContentView(R.layout.activity_main);

			// Set up the action bar.
			final ActionBar actionBar = getActionBar();
			actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

			// Create the adapter that will return a fragment for each of the
			// three
			// primary sections of the app.
			mSectionsPagerAdapter = new SectionsPagerAdapter(
					getSupportFragmentManager());

			// Set up the ViewPager with the sections adapter.
			mViewPager = (CustomViewPager) findViewById(R.id.pager);
			mViewPager.setPagingEnabled(false);
			mViewPager.setAdapter(mSectionsPagerAdapter);

			// When swiping between different sections, select the corresponding
			// tab. We can also use ActionBar.Tab#select() to do this if we have
			// a reference to the Tab.
			mViewPager
			.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
				@Override
				public void onPageSelected(int position) {
					actionBar.setSelectedNavigationItem(position);
					if(getCurrentFocus() != null){
						InputMethodManager imm = (InputMethodManager) getSystemService(Activity.INPUT_METHOD_SERVICE);
						imm.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), 0);
					}
				}
			});

			// For each of the sections in the app, add a tab to the action bar.
			for (int i = 0; i < mSectionsPagerAdapter.getCount(); i++) {
				// Create a tab with text corresponding to the page title
				// defined by
				// the adapter. Also specify this Activity object, which
				// implements
				// the TabListener interface, as the callback (listener) for
				// when
				// this tab is selected.
				actionBar.addTab(actionBar.newTab().setTabListener(this));
				// .setText(mSectionsPagerAdapter.getPageTitle(i))
				switch (i) {
				case 0:
					actionBar.getTabAt(i).setIcon(
							R.drawable.ic_collections_view_as_list_holodark);
					break;
				case 1:
					actionBar.getTabAt(i).setIcon(
							R.drawable.ic_content_new_event_holodark);
					break;
				case 2:
					actionBar.getTabAt(i).setIcon(
							R.drawable.ic_location_map_holodark);
					break;
				default:
					break;
				}
			}
		} else {
			showErrorView();
		}
		HttpsTask.setContext(getApplicationContext());

		// Log.i("Johan", "Checking server cookie");
		GetUserTask getUserTask = new GetUserTask();
		getUserTask.execute(getBaseServerURI() + "/session/connect");

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		MainActivity.setMainActivityMenu(menu);
		menu.getItem(0).setIcon(R.drawable.ic_action_user);
		return true;
	}

	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {

		// Handle disabling or enabling menu based on user login
		if (!hasConnection || serverDown) {
			menu.getItem(0).setVisible(false);
			menu.getItem(1).setVisible(false);
			menu.getItem(3).setVisible(false);
		} else if (!isLoggedIn()) {
			menu.getItem(0).setVisible(false);
			menu.getItem(1).setVisible(true);
			menu.getItem(3).setVisible(false);
		} else {
			menu.getItem(0).setVisible(true);
			menu.getItem(1).setVisible(false);
			menu.getItem(3).setVisible(true);
		}
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle item selection
		Intent intent;
		switch (item.getItemId()) {
		case R.id.action_profile:
			// Show current user profile
			intent = new Intent(this, ProfileActivity.class);
			intent.putExtra("userid", MainActivity.getCurrentUser().getId());
			intent.putExtra("username", MainActivity.getCurrentUser()
					.getUsername());
			intent.putExtra("imagePath", MainActivity.getCurrentUser()
					.getAvatar());
			startActivity(intent);
			return true;
		case R.id.action_login:
			// Start settings activity
			LoginSupportFragment loginFragment = new LoginSupportFragment();
			loginFragment.show(getSupportFragmentManager(), "loginFragment");
			return true;
		case R.id.action_settings:
			// Start settings activity
			intent = new Intent(this, SettingsActivity.class);
			startActivity(intent);
			return true;
		case R.id.action_logout:
			// Start logout activity
			LogoutTask logoutTask = new LogoutTask();
			logoutTask.execute(getBaseServerURI() + "/users/logout");
			return true;
		case R.id.action_help:
			showHelp();
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}

	@Override
	public void onTabSelected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
		// When the given tab is selected, switch to the corresponding page in
		// the ViewPager.
		mViewPager.setCurrentItem(tab.getPosition());

	}

	@Override
	public void onTabUnselected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
	}

	@Override
	public void onTabReselected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
	}

	public static GiraffeLocationListener getGiraffeLocationListener() {
		return locationListener;
	}

	public static User getCurrentUser() {
		return currentUser;
	}

	public static void setCurrentUser(User currentUser) {
		MainActivity.currentUser = currentUser;
	}

	public static CookieManager getCookieManager() {
		return cookieManager;
	}

	public static void setCookieManager(CookieManager cookieManager) {
		MainActivity.cookieManager = cookieManager;
	}

	public static String getBaseServerURI() {
		return baseServerURI;
	}

	public static void setBaseServerURI(String baseServerURI) {
		MainActivity.baseServerURI = baseServerURI;
	}

	/**
	 * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
	 * one of the sections/tabs/pages.
	 */
	public class SectionsPagerAdapter extends FragmentPagerAdapter {

		public SectionsPagerAdapter(FragmentManager fm) {
			super(fm);
		}

		@Override
		public Fragment getItem(int position) {
			// getItem is called to instantiate the fragment for the given page.
			// Return a DummySectionFragment (defined as a static inner class
			// below) with the page number as its lone argument.
			Fragment fragment = new DummySectionFragment();
			Bundle args = new Bundle();
			switch (position) {
			case 0:
				fragment = new NearbyGraffitiFragment();
				break;
			case 1:
				fragment = new AddGraffitiFragment();
				break;
			case 2:
				fragment = new GraffitiMapFragment();
				break;
			}
			return fragment;
		}

		@Override
		public int getCount() {
			// Show NUM_TABS total pages.
			return NUM_TABS;
		}

		@Override
		public CharSequence getPageTitle(int position) {
			Locale l = Locale.getDefault();
			switch (position) {
			case 0:
				return getString(R.string.action_nearby).toUpperCase(l);
			case 1:
				return getString(R.string.action_addgraffiti).toUpperCase(l);
			case 2:
				return getString(R.string.action_map).toUpperCase(l);
			}
			return null;
		}
	}

	/**
	 * A dummy fragment representing a section of the app, but that simply
	 * displays dummy text.
	 */
	public static class DummySectionFragment extends Fragment {
		/**
		 * The fragment argument representing the section number for this
		 * fragment.
		 */
		public static final String ARG_SECTION_NUMBER = "section_number";

		public DummySectionFragment() {
		}

		@Override
		public View onCreateView(LayoutInflater inflater, ViewGroup container,
				Bundle savedInstanceState) {
			View rootView = inflater.inflate(R.layout.fragment_main_dummy,
					container, false);
			TextView dummyTextView = (TextView) rootView
					.findViewById(R.id.section_label);
			dummyTextView.setText(Integer.toString(getArguments().getInt(
					ARG_SECTION_NUMBER)));
			return rootView;
		}
	}

	private void showHelp() {
		AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);

		// set title
		alertDialogBuilder.setTitle("Help dialog");

		// set dialog message
		alertDialogBuilder.setMessage(R.string.help_text).setNegativeButton(
				"Cancel", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int id) {
						// if this button is clicked, just close
						// the dialog box and do nothing
						dialog.cancel();
					}
				});
		// create alert dialog
		AlertDialog alertDialog = alertDialogBuilder.create();
		// show it
		alertDialog.show();
	}

	@Override
	protected void onStop() {
		super.onStop();
		Log.w("MainActivity", "Saving Preferences");
		// We need an Editor object to make preference changes.
		// All objects are from android.context.Context
		SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();

		String cookieValue;
		if (!MainActivity.isLoggedIn()) {
			editor.clear();
		} else {
			editor.clear();
			try {
				if (MainActivity.getCookieManager().getCookieStore()
						.get(new URI(MainActivity.getBaseServerURI())).size() > 0) {
					Log.w("MainActivity", "Saving cookie");
					cookieValue = MainActivity.getCookieManager()
							.getCookieStore()
							.get(new URI(MainActivity.getBaseServerURI()))
							.get(0).toString();
					Log.w("MainActivity", "saved cookie value: " + cookieValue);
					editor.putString("cookie", cookieValue);
				}
			} catch (URISyntaxException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			Log.w("MainActivity", "Saving user");
			editor.putInt("id", MainActivity.getCurrentUser().getId());
			editor.putString("email", MainActivity.getCurrentUser().getEmail());
			editor.putString("username", MainActivity.getCurrentUser()
					.getUsername());
			if (MainActivity.getCurrentUser().getAvatar() != null) {
				editor.putString("avatar", MainActivity.getCurrentUser()
						.getAvatar());
			}

		}
		// Commit the edits!
		editor.commit();

	}

	public static Menu getMainActivityMenu() {
		return mainActivityMenu;
	}

	public static void setMainActivityMenu(Menu mainActivityMenu) {
		MainActivity.mainActivityMenu = mainActivityMenu;
	}

	private class LogoutTask extends AsyncTask<String, Void, InputStream> {
		private String error_message = null;
		private boolean success = false;

		@Override
		protected InputStream doInBackground(String... urls) {
			URL url = null;
			JSONObject returnJSONObject = null;
			InputStream myInputStream = null;
			try {
				Log.i("Johan", "About to post");
				url = new URL(urls[0]);
				HttpURLConnection conn = (HttpURLConnection) url
						.openConnection();
				MainActivity.addSessionCookie(conn);
				conn.setDoOutput(true);
				conn.setRequestMethod("POST");
				conn.connect();
				Log.i("Johan", "Posted");
				myInputStream = conn.getInputStream();

			} catch (Exception e) {
				// handle the exception !
				System.out.println("Error Message: " + e.getMessage());
			}

			returnJSONObject = null;
			try {
				if (myInputStream != null) {
					returnJSONObject = new JSONObject(
							JSONHandler.convertStreamToString(myInputStream));
					System.out.println("JSONObject Response: "
							+ returnJSONObject.toString());
					if (returnJSONObject.has("error")) {
						error_message = (String) returnJSONObject.get("error");
						success = false;
					} else {
						success = true;
					}
				}
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return myInputStream;
		}

		protected void onPostExecute(InputStream responseStream) {
			if (success) {
				MainActivity.getCookieManager().getCookieStore().removeAll();
				MainActivity.setCurrentUser(null);
				Menu menu = MainActivity.getMainActivityMenu();
				menu.getItem(0).setVisible(false);
				menu.getItem(1).setVisible(true);
				menu.getItem(3).setVisible(false);
				
				NearbyListFragment nearbyListFrag = (NearbyListFragment) getSupportFragmentManager()
						.findFragmentById(R.id.nearbyListFragment);
			
				getSupportLoaderManager().restartLoader(0, null, nearbyListFrag);
			} else {
			}
		}
	}

	private class GetUserTask extends AsyncTask<String, Void, JSONObject> {

		String error_message;
		boolean success = false;
		boolean expired = false;

		@Override
		protected JSONObject doInBackground(String... urls) {
			URL url;
			HttpURLConnection conn = null;
			try {
				url = new URL(urls[0]);
				conn = (HttpURLConnection) url.openConnection();
				conn.setDoInput(true);
				conn.setRequestMethod("GET");
			} catch (ProtocolException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			addSessionCookie(conn);
			InputStream myInputStream = null;
			try {
				myInputStream = conn.getInputStream();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				Log.i("Johan2", "This is where server down pans out");
				serverDown = true;
				e1.printStackTrace();
				return null;
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
					} else {
						success = true;
					}
					Log.w("GetUserTask", "Current User in Session: " + returnJSONObject.getString("user"));
					if (returnJSONObject.getString("user").equals("null")){
						expired = true;
					}
					return returnJSONObject;
				}
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return returnJSONObject;

		}

		protected void onPostExecute(JSONObject returnJSONObject) {
			if(expired){
				// Logout the user
				Log.w("GetUserTask", "Logging out");
				LogoutTask logoutTask = new LogoutTask();
				logoutTask.execute(getBaseServerURI() + "/users/logout");
			}

			if (success) {
				Log.i("Johan", "Successful cookie get or whatever");
				serverDown = false;
			} else { 
				showErrorView();
			}
		}
	}

	public static void addSessionCookie(HttpURLConnection conn) {
		List<HttpCookie> cookies = MainActivity.getCookieManager()
				.getCookieStore().getCookies();
		StringBuffer cookieHeaderBuffer = new StringBuffer();
		for (HttpCookie cookie : cookies) {
			Log.w("MainActivity", "Number of cookies: " + cookies.size());
			cookieHeaderBuffer.append(cookie.toString());
		}
		conn.setRequestProperty("Cookie", cookieHeaderBuffer.toString());
	}

	private void setPersistentLogin() {
		setCookieManager(new CookieManager(null, CookiePolicy.ACCEPT_NONE));
		CookieHandler.setDefault(cookieManager);
		// Retrieve persistent login stuff
		SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
		String cookieStr = settings.getString("cookie", null);
		if (settings.getString("cookie", null) != null) {
			Log.w("MainActivity", "retrieving saved cookie: " + cookieStr);
			HttpCookie cookie = new HttpCookie(cookieStr.substring(0,
					cookieStr.indexOf('=')), cookieStr.substring(
							cookieStr.indexOf('=') + 1, cookieStr.length()));
			cookie.setDomain(MainActivity.getBaseServerURI());
			cookie.setPath("/");
			cookie.setVersion(0);
			try {
				MainActivity.getCookieManager().getCookieStore().removeAll();
				MainActivity.getCookieManager().getCookieStore()
				.add(new URI(MainActivity.getBaseServerURI()), cookie);
			} catch (URISyntaxException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		String currentUsername = settings.getString("username", null);
		if (currentUsername != null) {
			User currentUser = new User();
			currentUser.setEmail(settings.getString("email", ""));
			currentUser.setAvatar(settings.getString("avatar", null));
			currentUser.setId(settings.getInt("id", 0));
			currentUser.setUsername(settings.getString("username", ""));
			MainActivity.setCurrentUser(currentUser);
		}
	}

	public boolean checkLocationExists(String bestProvider) {

		if (bestProvider == null || !locationListener.isLocationFound())
			return false;
		else
			return true;
	}

	public boolean checkConnection() {
		ConnectivityManager conMgr =  (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo i = conMgr.getActiveNetworkInfo();
		if (i == null)
			return false;
		if (!i.isConnected())
			return false;
		if (!i.isAvailable())
			return false;
		return true;
	}


	public void showErrorView () {
		setContentView(R.layout.activity_error);
		LinearLayout errorLayout = (LinearLayout) findViewById(R.id.error_layout);
		if (!hasLocation)
			((TextView) findViewById(R.id.no_gps)).setVisibility(0);
		if (!hasConnection) {
			((TextView) findViewById(R.id.no_connection)).setVisibility(0);
		}
		if (serverDown) {
			((TextView) findViewById(R.id.server_down)).setVisibility(0);
		}
		errorLayout.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				//Inform the user the button has been clicked
				finish();
			}
		});
	}

	public static LruCache<String, Bitmap> getMemoryBitmapCache() {
		return memoryBitmapCache;
	}

	public static void setMemoryBitmapCache(LruCache<String, Bitmap> memoryBitmapCache) {
		MainActivity.memoryBitmapCache = memoryBitmapCache;
	}

	public static void addBitmapToMemoryCache(String key, Bitmap bitmap) {
		if (getBitmapFromMemCache(key) == null) {
			MainActivity.getMemoryBitmapCache().put(key, bitmap);
		}
	}

	public static Bitmap getBitmapFromMemCache(String key) {
		return MainActivity.getMemoryBitmapCache().get(key);
	}

	public static float distFrom(double d, double e, double f, double g) {
		double earthRadius = 3958.75;
		double dLat = Math.toRadians(f-d);
		double dLng = Math.toRadians(g-e);
		double a = Math.sin(dLat/2) * Math.sin(dLat/2) +
				Math.cos(Math.toRadians(d)) * Math.cos(Math.toRadians(f)) *
				Math.sin(dLng/2) * Math.sin(dLng/2);
		double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
		double dist = earthRadius * c;

		int meterConversion = 1609;
		float distance = Float.valueOf((float)dist*meterConversion);
		Log.w("MainActivity", "Distance from: " + distance);
		return distance;
	}

	public static int calculateInSampleSize(
			BitmapFactory.Options options, int reqWidth, int reqHeight) {
		// Raw height and width of image
		final int height = options.outHeight;
		final int width = options.outWidth;
		int inSampleSize = 1;

		if (height > reqHeight || width > reqWidth) {

			// Calculate ratios of height and width to requested height and width
			final int heightRatio = Math.round((float) height / (float) reqHeight);
			final int widthRatio = Math.round((float) width / (float) reqWidth);

			// Choose the smallest ratio as inSampleSize value, this will guarantee
			// a final image with both dimensions larger than or equal to the
			// requested height and width.
			inSampleSize = heightRatio < widthRatio ? heightRatio : widthRatio;
		}

		return inSampleSize;
	}
	
	public static Bitmap decodeSampledBitmapFromStream(InputStream in, int reqWidth, int reqHeight) {

	    // First decode with inJustDecodeBounds=true to check dimensions
	    final BitmapFactory.Options options = new BitmapFactory.Options();
	    options.inJustDecodeBounds = true;
	    BitmapFactory.decodeStream(in, null, options);

	    // Calculate inSampleSize
	    options.inSampleSize = calculateInSampleSize(options, reqWidth, reqHeight);

	    // Decode bitmap with inSampleSize set
	    options.inJustDecodeBounds = false;
	    return BitmapFactory.decodeStream(in, null, options);
	}
}
