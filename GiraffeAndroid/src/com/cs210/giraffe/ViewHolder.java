package com.cs210.giraffe;

import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class ViewHolder {
	private TextView _username;
	private TextView _message;
	private ImageView _graffitiImage;
	private Button _likeButton;
	private Button _flagButton;
	
	public ViewHolder(){
		
	}
	
	public TextView getUsernameView() {
		return _username;
	}
	
	public void setUsernameView(TextView username) {
		_username = username;
	}
	
	public TextView getMessageView() {
		return _message;
	}
	
	public void setMessageView(TextView message) {
		_message = message;
	}
	
	public ImageView getGraffitiImageView() {
		return _graffitiImage;
	}
	
	public void setGraffitiImageView(ImageView graffitiImage) {
		_graffitiImage = graffitiImage;
	}
	
	public Button getLikeButton() {
		return _likeButton;
	}
	
	public void setLikeButton(Button likeButton) {
		_likeButton = likeButton;
	}
	
	public Button getFlagButton() {
		return _flagButton;
	}
	
	public void setFlagButton(Button flagButton) {
		_flagButton = flagButton;
	}
}
