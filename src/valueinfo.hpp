#pragma once

#include <map>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

struct ValueInfo {
  std::optional<int> numInt;
  std::optional<int> minInt;
  std::optional<int> maxInt;
  std::optional<float> numFloat;
  std::optional<float> minFloat;
  std::optional<float> maxFloat;
  std::optional<std::string> str;
  std::optional<std::map<std::string, std::string>> opt;
};

namespace nlohmann {
// template <typename T> struct adl_serializer<std::optional<T>> {

//   static void to_json(json &j, const std::optional<T> &opt) {
//     if (opt.has_value()) {
//       j = *opt;
//     } else {
//       j = json::;
//     }
//   }

//   static void from_json(const json &j, std::optional<T> &opt) {
//     if (j.is_null()) {
//       opt = {};
//     } else {
//       opt = j.get<T>();
//     }
//   }
// };

template <> struct adl_serializer<ValueInfo> {
  static void to_json(json &j, const ValueInfo &i) {
    using namespace nlohmann;
    j = json::object();

    if (i.numInt.has_value()) {
      j["numInt"] = *i.numInt;
    }

    if (i.minInt.has_value()) {
      j["minInt"] = *i.minInt;
    }

    if (i.maxInt.has_value()) {
      j["maxInt"] = *i.maxInt;
    }

    if (i.numFloat.has_value()) {
      j["numFloat"] = *i.numFloat;
    }

    if (i.minFloat.has_value()) {
      j["minFloat"] = *i.minFloat;
    }

    if (i.maxFloat.has_value()) {
      j["maxFloat"] = *i.maxFloat;
    }

    if (i.str.has_value()) {
      j["str"] = *i.str;
    }

    if (i.opt.has_value()) {
      j["opt"] = *i.opt;
    }
  }
};
} // namespace nlohmann