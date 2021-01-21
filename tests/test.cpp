// Copyright 2020 Slava-100 <svat.strel.2001@gmail.com>

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <students_from_json.hpp>

TEST(FeaturesTesting, PrintingTable) {
  std::string jsonString = R"(
{
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
}
)";
  std::stringstream jsonStream;
  jsonStream << jsonString;

  auto students = ParseJSON(jsonStream);

  std::stringstream printTableOutput;
  Print(students, printTableOutput);

  std::string trueTable = R"(|name            |group   |avg |debt    |
|----------------|--------|----|--------|
|Ivanov Petr     |1       |4.25|none    |
|----------------|--------|----|--------|
|Sidorov Ivan    |31      |4   |C++     |
|----------------|--------|----|--------|
|Pertov Nikita   |IU8-31  |3.33|3 items |
|----------------|--------|----|--------|
)";
  EXPECT_EQ(trueTable, printTableOutput.str());
  Print(students,std::cout);
}

TEST(ErrorHandling, MismatchingArraySizeWithCount) {
  std::string jsonString = R"(
{
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 1
  }
}
)";
  std::stringstream jsonStream;
  jsonStream << jsonString;

  std::string exceptionString;
  try {
    auto students = ParseJSON(jsonStream);
  } catch (std::runtime_error &exception) {
    exceptionString = exception.what();
  }

  EXPECT_EQ(exceptionString,
            "Mismatching _meta:count with real items array size");
}

TEST(ErrorHandlig, ItemsIsNotArray) {
  std::string jsonString = R"(
{
  "items":
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
  "_meta": {
    "count": 1
  }
}
)";
  std::stringstream jsonStream;
  jsonStream << jsonString;

  std::string exceptionString;

  try {
    auto students = ParseJSON(jsonStream);
  } catch (std::runtime_error &exception) {
    exceptionString = exception.what();
  }

  EXPECT_EQ(exceptionString, "Items must be array");
}
