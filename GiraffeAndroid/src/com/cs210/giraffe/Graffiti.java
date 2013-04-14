package com.cs210.giraffe;

public class Graffiti {

	private float _longitude;
	private float _latitude;
	private float _directionX;
	private float _directionY;
	private float _directionZ;
	private String _text;
	private String _imageURL;
	private int _likeCount;
	private boolean _flagged;
	
	public Graffiti() {
		// TODO Auto-generated constructor stub
	}

	public float getLongitude() {
		return _longitude;
	}

	public void setLongitude(float _longitude) {
		this._longitude = _longitude;
	}

	public float getLatitude() {
		return _latitude;
	}

	public void setLatitude(float _latitude) {
		this._latitude = _latitude;
	}

	public float getDirectionX() {
		return _directionX;
	}

	public void setDirectionX(float _directionX) {
		this._directionX = _directionX;
	}

	public float getDirectionY() {
		return _directionY;
	}

	public void setDirectionY(float _directionY) {
		this._directionY = _directionY;
	}

	public float getDirectionZ() {
		return _directionZ;
	}

	public void setDirectionZ(float _directionZ) {
		this._directionZ = _directionZ;
	}

	public String getText() {
		return _text;
	}

	public void setText(String _text) {
		this._text = _text;
	}

	public String getImageURL() {
		return _imageURL;
	}

	public void setImageURL(String _imageURL) {
		this._imageURL = _imageURL;
	}

	public int getLikeCount() {
		return _likeCount;
	}

	public void setLikeCount(int _likeCount) {
		this._likeCount = _likeCount;
	}

	public boolean isFlagged() {
		return _flagged;
	}

	public void setFlagged(boolean _flagged) {
		this._flagged = _flagged;
	}
	
	

}
