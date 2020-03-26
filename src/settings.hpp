#pragma once
#include <nlohmann/json.hpp>

class Settings {
private:
  nlohmann::json data;

public:
  Settings(/* args */);
  ~Settings();

  int GetInt(const std::string &name) const;
  void SetInt(const std::string &name, int val);

  int GetFloat(const std::string &name) const;
  void SetFloat(const std::string &name, float val);

  std::string GetString(const std::string &name) const;
  void SetString(const std::string &name, const std::string &val);
};
