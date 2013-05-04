package com.cs210.giraffe;

import android.content.Context;
import android.preference.ListPreference;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;

public class ChangePasswordListPreference extends ListPreference
{
    // Constructor called by the inflater
    public ChangePasswordListPreference(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }
    @Override
    protected View onCreateView(ViewGroup parent)
    {	
    	
    	ListView view = new ListView(getContext());
    	View returnView = view.findViewById(R.layout.password_dialog);
        return returnView;
    }
}