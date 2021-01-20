// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <string>
#include <vector>
#include <any>
#include <ostream>

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

std::vector<Student> ParserJSON(const std::istream $jsonStream);

void print(const Student &student, std::ostream &out);


void print(const std::vector<Student> &student, std::ostream &out);



#endif // INCLUDE_HEADER_HPP_
