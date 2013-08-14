package com.cs210.giraffe;


import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

public class ProfileActivity extends FragmentActivity {

	private ProfileFragment _pf;
	private ChangePasswordFragment _df;
	TextView _passwordErrorMessage;
	private int _userid;
	private String _username;
	private String _imagePath;
	
	public ProfileActivity() {
	}

	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        _userid = getIntent().getExtras().getInt("userid");
        _username = getIntent().getExtras().getString("username");
        _imagePath = getIntent().getExtras().getString("imagePath");
        Log.i("Johan", "Current userid inside ProfileActivity" + _userid);
        Log.i("Johan", "Current username inside ProfileActivity" + _username);
        setContentView(R.layout.activity_profile);
        
        Log.i("Johan", "At the Activity start: " + _userid);
        getActionBar().setTitle(R.string.action_profile);
        getActionBar().setDisplayHomeAsUpEnabled(true);
    }
	
	
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                // This is called when the Home (Up) button is pressed
                // in the Action Bar.
//                Intent parentActivityIntent = new Intent(this, MainActivity.class);
//                parentActivityIntent.addFlags(
//                        Intent.FLAG_ACTIVITY_CLEAR_TOP |
//                        Intent.FLAG_ACTIVITY_NEW_TASK);
//                startActivity(parentActivityIntent);
                finish();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }
	
	public int getUserid() {
		Log.i("Johan", "At the Activity userid: " + _userid);
		return _userid;
	}
	
	public String getUsername() {
		Log.i("Johan", "At the Activity userid: " + _userid);
		return _username;
	}
	
	public String getImagePath() {
		Log.i("Johan", "At the Activity userid: " + _userid);
		return _imagePath;
	}
	
}
