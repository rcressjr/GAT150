#pragma once
#include "document.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <string>

#define JSON_READ(value, data) rj::json::Get(value, #data, data);

namespace rj {
	namespace json {
		bool Load(const std::string& filename, rapidjson::Document& document);

		bool Get(const rapidjson::Value& value, const std::string& name, int& key);
		bool Get(const rapidjson::Value& value, const std::string& name, float& data);
		bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Color& data);
	}
}