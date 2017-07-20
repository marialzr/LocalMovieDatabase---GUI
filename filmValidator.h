#pragma once
#include "Film.h"
#include <string>

class ValidatorException
{
private:
	std::string msg;
public:
	ValidatorException(std::string m);
	std::string getMessage() const;
};


class FilmValidator
{
public:
	static void validate(const Film& m);
};
