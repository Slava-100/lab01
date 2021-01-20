// Copyright 2020 Your Name <your_email>

#include <any>
#include <header.hpp>
#include <nlohmann/json.hpp>
#include <ostream>
#include <string>
#include <vector>

using nlohmann::json;

std::string GetName(const json& jsonData) {
  return jsonData.get<std::string>();
}

std::any GetDebt(const json& jsonData) {
  if (jsonData.is_null())
    return nullptr;
  else if (jsonData.is_string())
    return jsonData.get<std::string>();
  else
    return jsonData.get<std::vector<std::string>>();
}

std::any GetAvg(const json& jsonData) {
  if (jsonData.is_null())
    return nullptr;
  else if (jsonData.is_string())
    return jsonData.get<std::string>();
  else if (jsonData.is_number_float())
    return jsonData.get<float>();
  else
    return jsonData.get<int>();
}

std::any GetGroup(const json& jsonData) {
  if (jsonData.is_string())
    return jsonData.get<std::string>();
  else
    return jsonData.get<int>();
}

void from_json(const json& jsonData, Student& student) {
  student.name = GetName(jsonData.at("name"));
  student.group = GetGroup(jsonData.at("group"));
  student.avg = GetAvg(jsonData.at("avg"));
  student.debt = GetDebt(jsonData.at("debt"));
}

std::vector<Student> ParseJSON(std::istream& jsonStream) {
  json jsonData;
  jsonStream >> jsonData;

  std::vector<Student> result;

  for (const auto& item : jsonData.at("items")) {
    auto student = item.get<Student>();
    result.push_back(student);
  }

  return result;
}


