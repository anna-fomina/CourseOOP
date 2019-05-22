#pragma once

#include <string>

class Printable {
public:
	virtual std::string print() const = 0;
};

class Named : Printable {
public:
	Named(std::string const & name) : name(name) {}
	std::string print() const {
		return name;
	}
private:
	std::string name;
};
