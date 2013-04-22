/*
 * User.h
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#ifndef USER_H_
#define USER_H_

#include <FApp.h>
#include <FBase.h>
class Date;

class User :
	public Tizen::Base::Object
{
public:
	// Current user
	static User *currentUser(void);

	// Constructors
	User();
	virtual ~User();

	result updateFromDictionary(Tizen::Base::Collection::HashMap *dictionary);
	void logout(void);

	// User listener class
	class UserListener :
		public Tizen::Base::Object
	{
	public :
		virtual void onUserUpdate(User *user) = 0;
	};

	// Accessors
	unsigned int id() { return _id; }
	void setId(unsigned int id) { _id = id; }
	Tizen::Base::String fullname() { return _fullname; }
	void setFullname(Tizen::Base::String fullname) { _fullname = fullname; }
	Tizen::Base::String username() { return _username; }
	void setUsername(Tizen::Base::String username) { _username = username; }
	Tizen::Base::String email() { return _email; }
	void setEmail(Tizen::Base::String email) { _email = email; }
	Date *dateCreated() { return _dateCreated; }
	void setDateCreated(Date *dateCreated) { _dateCreated = dateCreated; }

	Tizen::Base::Collection::HashMap *parameterDictionary();
	void addListener(UserListener *listener);
	void removeListener(UserListener *listener);

	static void saveUser(void);
	static void loadUser(void);


private:
	unsigned int _id;
	Tizen::Base::String _fullname;
	Tizen::Base::String _username;
	Tizen::Base::String _email;
	Tizen::Base::String _avatarUrl;
	Date *_dateCreated;
	Tizen::Base::Collection::ArrayList *_listeners;
};

#endif /* USER_H_ */
