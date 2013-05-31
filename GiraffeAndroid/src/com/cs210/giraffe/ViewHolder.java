package com.cs210.giraffe;

import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class ViewHolder {
	private TextView _username;
	private TextView _message;
	private TextView _distance;
	private ImageView _profileImageView;
	private ImageView _graffitiImage;
	private Button _likeButton;
	private Button _flagButton;
	private Graffiti _item;
	private int _position;
	
	private String _imageUrl;
	
	
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
	
	public Graffiti getItem() {
		return _item;
	}
	
	public void setItem(Graffiti item) {
		_item = item;
	}

	public int getPosition() {
		return _position;
	}

	public void setPosition(int position) {
		this._position = position;
	}

	public String getImageUrl() {
		return _imageUrl;
	}

	public void setImageUrl(String imageUrl) {
		this._imageUrl = imageUrl;
	}

	public ImageView getProfileImageView() {
		return _profileImageView;
	}

	public void setProfileImageView(ImageView profileImageView) {
		this._profileImageView = profileImageView;
	}

	public TextView getDistanceView() {
		return _distance;
	}

	public void setDistanceView(TextView distance) {
		this._distance = distance;
	}
}
