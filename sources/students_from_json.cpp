// Copyright 2020 andreymuskat <andreymuskat@yandex.ru>

#include <any>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <string>
#include <students_from_json.hpp>
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

  if (!jsonData.at("items").is_array())
    throw std::runtime_error("Items must be array");

  if (jsonData.at("items").size() != jsonData.at("_meta").at("count"))
    throw std::runtime_error(
        "Mismatching _meta:count with real items array size");

  for (const auto& item : jsonData.at("items")) {
    auto student = item.get<Student>();
    result.push_back(student);
  }

  return result;
}

void Print(const Student& student, std::ostream& out) {
  out << "|" << std::left << std::setw(MaxNameWidth) << student.name;

  if (student.group.type() == typeid(int)) {
    out << "|" << std::setw(MaxGroupWidth) << std::left
        << std::any_cast<int>(student.group);
  } else {
    out << "|" << std::setw(MaxGroupWidth) << std::left
        << std::any_cast<std::string>(student.group);
  }

  if (student.avg.type() == typeid(float)) {
    out << "|" << std::setw(MaxAvgWidth) << std::left
        << std::any_cast<float>(student.avg);
  } else if (student.avg.type() == typeid(int)) {
    out << "|" << std::setw(MaxAvgWidth) << std::left
        << std::any_cast<int>(student.avg);
  } else {
    out << "|" << std::setw(MaxAvgWidth) << std::left
        << std::any_cast<std::string>(student.avg);
  }

  if (student.debt.type() == typeid(std::nullptr_t)) {
    out << "|" << std::setw(MaxDebtWidth) << std::left << "none" << std::right
        << "|";
  } else if (student.debt.type() == typeid(std::string)) {
    out << "|" << std::setw(MaxDebtWidth) << std::left
        << std::any_cast<std::string>(student.debt) << std::right << "|";
  } else {
    out << "|" << std::setw(MaxDebtWidth) << std::left
        << (std::to_string(
                std::any_cast<std::vector<std::string>>(student.debt).size()) +
            " items")
        << "|";
  }
}

void Print(const std::vector<Student>& students, std::ostream& out) {
  std::string tableSeparator;

  tableSeparator += "|";
  tableSeparator += std::string(MaxNameWidth, '-');
  tableSeparator += "|";
  tableSeparator += std::string(MaxGroupWidth, '-');
  tableSeparator += "|";
  tableSeparator += std::string(MaxAvgWidth, '-');
  tableSeparator += "|";
  tableSeparator += std::string(MaxDebtWidth, '-');
  tableSeparator += "|";

  out << "|" << std::left << std::setw(MaxNameWidth) << "name";
  out << "|" << std::left << std::setw(MaxGroupWidth) << "group";
  out << "|" << std::left << std::setw(MaxAvgWidth) << "avg";
  out << "|" << std::left << std::setw(MaxDebtWidth) << "debt";
  out << std::right << "|";
  out << std::endl << tableSeparator << std::endl;

  for (const auto& student : students) {
    Print(student, out);
    out << std::endl << tableSeparator << std::endl;
  }
}
