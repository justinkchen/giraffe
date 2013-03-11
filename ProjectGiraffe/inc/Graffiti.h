/*
 * Graffiti.h
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#ifndef GRAFFITI_H_
#define GRAFFITI_H_

#include <FBase.h>
#include "Date.h"
#include "User.h"

class Graffiti {
public:
	Graffiti();
	virtual ~Graffiti();

	// Accessors
    Tizen::Base::String text() { return _text; }
    void setText(Tizen::Base::String text) { _text = text; }
    Tizen::Base::String imageURL() { return _imageURL; }
    void setImageURL(Tizen::Base::String imageURL) { _imageURL = imageURL; }
    float latitude() { return _latitude; }
    void setLatitude(float latitude) { _latitude = latitude; }
    float longitude() { return _longitude; }
    void setLongitude(float longitude) { _longitude = longitude; }
    float directionX() { return _directionX; }
    void setDirectionX(float directionX) { _directionX = directionX; }
    float directionY() { return _directionY; }
    void setDirectionY(float directionY) { _directionY = directionY; }
    float directionZ() { return _directionZ; }
    void setDirectionZ(float directionZ) { _directionZ = directionZ; }
    int likeCount() { return _likeCount; }
    void setLikeCount(int likeCount) { _likeCount = likeCount; }
    Date dateCreated() { return _dateCreated; }
    void setDateCreated(Date dateCreated) { _dateCreated = dateCreated; }
    User *user() { return _user; }
    void setUser(User *user) { _user = user; }

private:
    Tizen::Base::String _text;
    Tizen::Base::String _imageURL;
    float _longitude;
    float _latitude;
    float _directionX;
    float _directionY;
    float _directionZ;
    int _likeCount;
    Date _dateCreated;
    User *_user;
};

#endif /* GRAFFITI_H_ */
