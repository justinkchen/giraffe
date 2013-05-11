package com.cs210.giraffe;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.CookieHandler;
import java.net.CookieManager;
import java.net.HttpCookie;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.Locale;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;

import android.app.ActionBar;
import android.app.AlertDialog;
import android.app.FragmentTransaction;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.location.Criteria;
import android.location.LocationManager;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.app.NavUtils;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends FragmentActivity implements
		ActionBar.TabListener {
	public static final String PREFS_NAME = "GiraffePrefs";
	static final int NUM_TABS = 3;
	private static GiraffeLocationListener locationListener = null;
	private static CookieManager cookieManager = null;
	private static String baseServerURI = "http://thegiraffeapp.com";
	private static User currentUser = null;

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
	ViewPager mViewPager;


	protected static boolean isLoggedIn(){
		if(currentUser != null){
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

		// Restore preferences
//		SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
//		String cookieStr = settings.getString("cookie", null);
//		if(cookieStr != null){
//			HttpCookie cookie = new HttpCookie(cookieStr.substring(0, cookieStr.indexOf('=')), cookieStr.substring(cookieStr.indexOf('='), cookieStr.length()));
//			cookie.setDomain(MainActivity.getBaseServerURI());
//			cookie.setPath("/");
//			cookie.setVersion(0);
//			try {
//				MainActivity.getCookieManager().getCookieStore().add(new URI(MainActivity.getBaseServerURI()), cookie);
//			} catch (URISyntaxException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
//		}
		

		setContentView(R.layout.activity_main);

		// Set up the action bar.
		final ActionBar actionBar = getActionBar();
		actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

		// Create the adapter that will return a fragment for each of the three
		// primary sections of the app.
		mSectionsPagerAdapter = new SectionsPagerAdapter(
				getSupportFragmentManager());

		// Set up the ViewPager with the sections adapter.
		mViewPager = (ViewPager) findViewById(R.id.pager);
		mViewPager.setAdapter(mSectionsPagerAdapter);

		// When swiping between different sections, select the corresponding
		// tab. We can also use ActionBar.Tab#select() to do this if we have
		// a reference to the Tab.
		mViewPager
				.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
					@Override
					public void onPageSelected(int position) {
						actionBar.setSelectedNavigationItem(position);
					}
				});

		// For each of the sections in the app, add a tab to the action bar.
		for (int i = 0; i < mSectionsPagerAdapter.getCount(); i++) {
			// Create a tab with text corresponding to the page title defined by
			// the adapter. Also specify this Activity object, which implements
			// the TabListener interface, as the callback (listener) for when
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

		// Acquire a reference to the system Location Manager
		LocationManager locationManager = (LocationManager) this
				.getSystemService(Context.LOCATION_SERVICE);
		Criteria criteria = new Criteria();
		String bestProvider = locationManager.getBestProvider(criteria, false);

		// Register the listener with the Location Manager to receive location
		// updates
		locationListener = new GiraffeLocationListener(locationManager,
				bestProvider);

		if (bestProvider == null || !locationListener.isLocationFound()) {
			new AlertDialog.Builder(this)
					.setIcon(R.drawable.ic_device_access_location_off)
					.setTitle("No location provider accessible")
					.setMessage(
							"Please turn on GPS location services and try again")
					.setCancelable(false)
					.setPositiveButton("Close App",
							new DialogInterface.OnClickListener() {
								@Override
								public void onClick(DialogInterface dialog,
										int which) {
									finish();
								}
							}).show();
		}

		locationManager.requestLocationUpdates(bestProvider, 0, 0,
				locationListener);

		setCookieManager(new CookieManager());
		CookieHandler.setDefault(cookieManager);

		HttpsTask.setContext(getApplicationContext());


		// Retrieve persistent login stuff
		SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
		String cookieStr = "connect.sid=" + settings.getString("cookie", null);
		if(settings.getString("cookie", null) != null){
			Log.w("MainActivity", "retrieving saved cookie: " + cookieStr);
			HttpCookie cookie = new HttpCookie(cookieStr.substring(0, cookieStr.indexOf('=')), cookieStr.substring(cookieStr.indexOf('=')+1, cookieStr.length()));
			cookie.setDomain(MainActivity.getBaseServerURI());
			cookie.setPath("/");
			cookie.setVersion(0);
			try {
				MainActivity.getCookieManager().getCookieStore().removeAll();
				MainActivity.getCookieManager().getCookieStore().add(new URI(MainActivity.getBaseServerURI()), cookie);
			} catch (URISyntaxException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		String currentUsername = settings.getString("username", null);
		if(currentUsername != null){
			User currentUser = new User();
			currentUser.setEmail(settings.getString("email", ""));
			currentUser.setAvatar(settings.getString("avatar", null));
			currentUser.setId(settings.getInt("id", 0));
			currentUser.setUsername(settings.getString("username", ""));
			MainActivity.setCurrentUser(currentUser);
		}

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		menu.getItem(0).setIcon(R.drawable.ic_action_user);
		return true;
	}

	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		// Handle disabling or enabling menu based on user login
		if (!isLoggedIn()) {
			menu.getItem(0).setVisible(false);
			menu.getItem(1).setVisible(true);
		}else{
			menu.getItem(0).setVisible(true);
			menu.getItem(1).setVisible(false);
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
			startActivity(intent);
			return true;
		case R.id.action_login:
			// Start settings activity
			LoginFragment loginFragment = new LoginFragment();
			loginFragment.show(getFragmentManager(), "loginFragment");
			return true;
		case R.id.action_settings:
			// Start settings activity
			intent = new Intent(this, SettingsActivity.class);
			startActivity(intent);
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

	// We need an Editor object to make preference changes.
	// All objects are from android.context.Context

	// SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
	// SharedPreferences.Editor editor = settings.edit();
	//
	// String value;
	// try {
	// value = MainActivity.getCookieManager().getCookieStore().get(new
	// URI(MainActivity.getBaseServerURI())).get(0).toString();
	// editor.putString("cookie", value);
	// } catch (URISyntaxException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// }
	// // Commit the edits!
	// editor.commit();

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

	// SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
	// SharedPreferences.Editor editor = settings.edit();
	//
	// String value;
	// try {
	// value = MainActivity.getCookieManager().getCookieStore().get(new
	// URI(MainActivity.getBaseServerURI())).get(0).toString();
	// editor.putString("cookie", value);
	// } catch (URISyntaxException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// }
	// // Commit the edits!
	// editor.commit();

	// SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
	// SharedPreferences.Editor editor = settings.edit();
	//
	// String cookieValue;
	// if(!MainActivity.isLoggedIn()){
	// editor.clear();
	// }else{
	// try {
	// if(MainActivity.getCookieManager().getCookieStore().get(new
	// URI(MainActivity.getBaseServerURI())).size() > 0){
	// Log.w("MainActivity", "Saving cookie");
	// cookieValue = MainActivity.getCookieManager().getCookieStore().get(new
	// URI(MainActivity.getBaseServerURI())).get(0).getValue();
	// Log.w("MainActivity", "saved cookie value: " + cookieValue);
	// editor.putString("cookie", cookieValue);
	// }
	// } catch (URISyntaxException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// }
	//
	// Log.w("MainActivity", "Saving user");
	// editor.putInt("id", MainActivity.getCurrentUser().getId());
	// editor.putString("email", MainActivity.getCurrentUser().getEmail());
	// editor.putString("username",
	// MainActivity.getCurrentUser().getUsername());
	// if(MainActivity.getCurrentUser().getAvatar() != null){
	// editor.putString("avatar", MainActivity.getCurrentUser().getAvatar());
	// }
	//
	// }
	// // Commit the edits!
	// editor.commit();

	// SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
	// SharedPreferences.Editor editor = settings.edit();
	//
	// String value;
	// try {
	// value = MainActivity.getCookieManager().getCookieStore().get(new
	// URI(MainActivity.getBaseServerURI())).get(0).toString();
	// editor.putString("cookie", value);
	// } catch (URISyntaxException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// }
	// // Commit the edits!
	// editor.commit();

	@Override
	protected void onStop() {
		super.onStop();
		Log.w("MainActivity", "Saving Preferences");
		// We need an Editor object to make preference changes.
		// All objects are from android.context.Context
		SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();

		String cookieValue;
		if(!MainActivity.isLoggedIn()){
			editor.clear();
		}else{
			try {
				if(MainActivity.getCookieManager().getCookieStore().get(new URI(MainActivity.getBaseServerURI())).size() > 0){
					Log.w("MainActivity", "Saving cookie");
					cookieValue = MainActivity.getCookieManager().getCookieStore().get(new URI(MainActivity.getBaseServerURI())).get(0).getValue();
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
			editor.putString("username", MainActivity.getCurrentUser().getUsername());
			if(MainActivity.getCurrentUser().getAvatar() != null){
				editor.putString("avatar", MainActivity.getCurrentUser().getAvatar());
			}

		}
		// Commit the edits!
		editor.commit();
	}

}
