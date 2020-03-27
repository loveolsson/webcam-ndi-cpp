#pragma once
#include <nlohmann/json.hpp>

class Settings {
private:
  nlohmann::json data;

public:
  Settings(/* args */);
  ~Settings();

  int GetInt(const std::string &name, int d = 0) const;
  void SetInt(const std::string &name, int val);

  int GetFloat(const std::string &name, float d = 0) const;
  void SetFloat(const std::string &name, float val);

  std::string GetString(const std::string &name,
                        const std::string &d = "") const;
  void SetString(const std::string &name, const std::string &val);
};
