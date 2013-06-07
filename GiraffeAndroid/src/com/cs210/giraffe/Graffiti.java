package com.cs210.giraffe;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import android.location.Location;
import android.util.Log;

public class Graffiti implements Comparable<Graffiti> {

	private int _id;
	private double _longitude;
	private double _latitude;
	private double _directionX;
	private double _directionY;
	private double _directionZ;
	private String _text;
	private String _imageURL;
	private String _avatar;
	private int _likeCount;
	private boolean _flagged;
	private int _radius;
	private String _username;
	private int _userid;
	private int _likes;
	private int _isLiked;
	private int _flags;
	private int _isFlagged;
	private String _dateCreated;

	public Graffiti() {
		// TODO Auto-generated constructor stub
	}

	public int getId() {
		return _id;
	}

	public void setId(int id) {
		this._id = id;
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

	public String getAvatar() {
		return _avatar;
	}

	public void setAvatar(String _avatar) {
		this._avatar = _avatar;
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

	public String getUsername() {
		return _username;
	}

	public void setUsername(String username) {
		this._username = username;
	}

	public int getUserid() {
		return _userid;
	}

	public void setUserid(int userid) {
		this._userid = userid;
	}

	public int getLikes() {
		return _likes;
	}

	public void setLikes(int likes) {
		this._likes = likes;
	}

	public int getIsLiked() {
		return _isLiked;
	}

	public void setIsLiked(int isLiked) {
		this._isLiked = isLiked;
	}

	public int getFlags() {
		return _flags;
	}

	public void setFlags(int flags) {
		this._flags = flags;
	}

	public int getIsFlagged() {
		return _isFlagged;
	}

	public void setIsFlagged(int isFlagged) {
		this._isFlagged = isFlagged;
	}

	public String getDateCreated() {
		return _dateCreated;
	}

	public void setDateCreated(String dateCreated) {
		this._dateCreated = dateCreated;
	}

	public float getDistanceFromUser(){
		Location currLocation = MainActivity.getGiraffeLocationListener().getCurrentLocation();
		return MainActivity.distFrom(currLocation.getLatitude(), currLocation.getLongitude(), this.getLatitude(), this.getLongitude());
	}

	@Override
	public int compareTo(Graffiti another) {
		Date date1 = null;
		Date date2 = null;
		Log.i("Johan2", this.getDateCreated());
		try {
			date1 = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'", Locale.ENGLISH).parse(this.getDateCreated());
			date2 = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'", Locale.ENGLISH).parse(another.getDateCreated());
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		float totalScore1 = this.getDistanceFromUser();
		float totalScore2 = another.getDistanceFromUser();
		// If distance less than 10 meters, go by dates, otherwise go by distance
		if(Math.abs(totalScore1 - totalScore2) < 10){
			if(date1.after(date2)){
				return -1;
			}else if(date2.after(date1)){
				return 1;
			}else{
				return 0;
			}
		}else{
			if(totalScore1 < totalScore2){
				return -1;
			}else if(totalScore1 > totalScore2){
				return 1;
			}else{
				return 0;
			}
		}
	}

}
