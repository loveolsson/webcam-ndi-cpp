#include "settings.hpp"

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

using namespace nlohmann;

static const char *settingsFile = "settings.json";

Settings::Settings() : data(json::object()) {
  using itr = std::istreambuf_iterator<char>;
  std::ifstream t(settingsFile);

  if (t.is_open()) {
    std::string fileContents((itr(t)), itr());

    try {
      this->data = json::parse(fileContents);
    } catch (json::exception &e) {
      std::cout << "Could not parse settings file: " << e.what() << std::endl;
    }
  }
}

Settings::~Settings() {
  std::ofstream t(settingsFile);
  t << std::setw(4) << this->data;
  std::cout << "Saved settings file" << std::endl;
}

int Settings::GetInt(const std::string &name, int d) const {
  auto find = this->data.find(name);
  if (find == this->data.end()) {
    return d;
  } else if (!find->is_number_integer()) {
    return d;
  }

  return find->get<int>();
}

void Settings::SetInt(const std::string &name, int val) {
  this->data[name] = val;
}

int Settings::GetFloat(const std::string &name, float d) const {
  auto find = this->data.find(name);
  if (find == this->data.end()) {
    return d;
  } else if (!find->is_number_float()) {
    return d;
  }

  return find->get<float>();
}

void Settings::SetFloat(const std::string &name, float val) {
  this->data[name] = val;
}

std::string Settings::GetString(const std::string &name,
                                const std::string &d) const {
  auto find = this->data.find(name);
  if (find == this->data.end()) {
    return d;
  } else if (!find->is_string()) {
    return d;
  }

  return find->get<std::string>();
}

void Settings::SetString(const std::string &name, const std::string &val) {
  this->data[name] = val;
}