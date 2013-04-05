/*
 * JSONParser.cpp
 *
 *  Created on: Mar 21, 2013
 *      Author: kkhorimoto
 */

#include "JSONParser.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;

HashMap *JSONParser::dictionaryForJSONValue(IJsonValue *jsonValue)
{
	Object *obj = objectForJSONValue(jsonValue);
	HashMap *dictionary = static_cast<HashMap *>(obj);
	return dictionary;
}

Object *JSONParser::objectForJSONValue(IJsonValue *jsonValue)
{
	Object *obj = NULL;

	if (jsonValue) {
		JsonType type = jsonValue->GetType();
		if (type == JSON_TYPE_OBJECT) {
			// Create dictionary from json value
			HashMap *dictionary = new HashMap(SingleObjectDeleter);
			dictionary->Construct();
			obj = dictionary;

			// populate dictionary
			JsonObject *jsonObj = static_cast<JsonObject *>(jsonValue);
			IMapEnumeratorT<const String *, IJsonValue *> *iter = jsonObj->GetMapEnumeratorN();
			while (iter && iter->MoveNext() == E_SUCCESS) {
				// retrieve key
				const String *key = NULL;
				iter->GetKey(key);

				// parse value
				IJsonValue *value = NULL;
				iter->GetValue(value);
				Object *valueObj = objectForJSONValue(value);

				// add key and value to dictionary
				if (key && valueObj) {
					dictionary->Add(const_cast<String *>(key), valueObj);
				}
			}
		} else if (type == JSON_TYPE_ARRAY) {
			// Create array from json value
			ArrayList *array = new ArrayList(SingleObjectDeleter);
			array->Construct();
			obj = array;

			// populate array
			JsonArray *jsonArray = static_cast<JsonArray *>(jsonValue);
	        IEnumeratorT<IJsonValue *> *iter = jsonArray->GetEnumeratorN();
			while (iter && iter->MoveNext() == E_SUCCESS) {
				// parse values
                IJsonValue *value = NULL;
                iter->GetCurrent(value);
                Object *valueObj = objectForJSONValue(value);

                // add to array
                if (valueObj) {
                	array->Add(valueObj);
                }
			}
		} else if (type == JSON_TYPE_STRING) {
			// return string object
			JsonString *jsonStr = static_cast<JsonString *>(jsonValue);
			String *strValue = static_cast<String *>(jsonStr);
			obj = strValue;
		} else if (type == JSON_TYPE_NUMBER) {
			// return double object
			JsonNumber *jsonNum = static_cast<JsonNumber *>(jsonValue);
			Double *dblValue = static_cast<Double *>(jsonNum);
			obj = dblValue;
		} else if (type == JSON_TYPE_BOOL) {
			// return boolean object
			JsonBool *jsonBool = static_cast<JsonBool *>(jsonValue);
			Boolean *boolValue = static_cast<Boolean *>(jsonBool);
			obj = boolValue;
		} else if (type == JSON_TYPE_NULL) {
			// Allow obj to remain equal to NULL.
		}
	}

	return obj;
}
