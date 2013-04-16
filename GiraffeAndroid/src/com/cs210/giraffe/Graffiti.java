package com.cs210.giraffe;

public class Graffiti {

	private double _longitude;
	private double _latitude;
	private double _directionX;
	private double _directionY;
	private double _directionZ;
	private String _text;
	private String _imageURL;
	private int _likeCount;
	private boolean _flagged;
	private int _radius;
	
	public Graffiti() {
		// TODO Auto-generated constructor stub
	}

	public double getLongitude() {
		return _longitude;
	}

	public void setLongitude(double _longitude) {
		this._longitude = _longitude;
	}

	public double getLatitude() {
		return _latitude;
	}

	public void setLatitude(double _latitude) {
		this._latitude = _latitude;
	}

	public double getDirectionX() {
		return _directionX;
	}

	public void setDirectionX(double _directionX) {
		this._directionX = _directionX;
	}

	public double getDirectionY() {
		return _directionY;
	}

	public void setDirectionY(double _directionY) {
		this._directionY = _directionY;
	}

	public double getDirectionZ() {
		return _directionZ;
	}

	public void setDirectionZ(double _directionZ) {
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

	public int getRadius() {
		return _radius;
	}

	public void setRadius(int _radius) {
		this._radius = _radius;
	}
	
	

}
