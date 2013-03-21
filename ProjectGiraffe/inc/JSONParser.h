/*
 * JSONParser.h
 *
 *  Created on: Mar 21, 2013
 *      Author: kkhorimoto
 */

#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include <FBase.h>
#include <FWebJson.h>

class JSONParser {
public:
	static Tizen::Base::Collection::HashMap *dictionaryForJSONValue(Tizen::Web::Json::IJsonValue *jsonValue);
private:
	// Private constructors so that only static methods can be used
	JSONParser();
	virtual ~JSONParser();

	// Private helper function
	static Tizen::Base::Object *objectForJSONValue(Tizen::Web::Json::IJsonValue *jsonValue);
};

#endif /* JSONPARSER_H_ */
