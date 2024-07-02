#pragma once
#include <concepts>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
class ArgumentParser {
public:
	ArgumentParser(int argc, const char* argv[]);
	ArgumentParser() = default;
	bool AddNewArgument(const std::string& key, const std::string& value);
	std::optional<std::string> GetValue(const std::string& key)const;

protected:
	std::unordered_map <std::string, std::string> _arguments;
};