// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <any>
#include <ostream>
#include <string>
#include <vector>

const std::size_t MaxNameWidth = 16;
const std::size_t MaxGroupWidth = 8;
const std::size_t MaxAvgWidth = 4;
const std::size_t MaxDebtWidth = 8;

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

std::vector<Student> ParseJSON(std::istream &jsonStream);

void Print(const Student &student, std::ostream &out);

void Print(const std::vector<Student> &students, std::ostream &out);

#endif  // INCLUDE_HEADER_HPP_

