package com.cs210.giraffe;

public class User {
	private int _id;
	private String _username = null;
	private String _email = null;
	private String _avatar = null;
	
	public int getId() {
		return _id;
	}
	
	public void setId(int id) {
		this._id = id;
	}
	
	public String getUsername() {
		return _username;
	}
	
	public void setUsername(String username) {
		this._username = username;
	}
	
	public String getEmail() {
		return _email;
	}
	
	public void setEmail(String email) {
		this._email = email;
	}

	public String getAvatar() {
		return _avatar;
	}

	public void setAvatar(String avatar) {
		this._avatar = avatar;
	}

	
}
