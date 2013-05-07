package com.cs210.giraffe;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

public class RegisterActivity extends FragmentActivity {
	private RegisterFragment _registerFragment;

	public RegisterActivity() {
		// TODO Auto-generated constructor stub
	}

	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActionBar().setTitle(R.string.action_register);
        _registerFragment = new RegisterFragment();
        
        this.getSupportFragmentManager().beginTransaction().replace(android.R.id.content, _registerFragment).commit();
//        getFragmentManager().beginTransaction()
//    		.replace(android.R.id.content, _registerFragment)
//    		.commit();
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
}
