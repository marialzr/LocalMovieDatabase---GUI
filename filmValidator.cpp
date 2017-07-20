#include "filmValidator.h"
#include <string>

ValidatorException::ValidatorException(std::string m)
{
	this->msg = m;
}

std::string ValidatorException::getMessage() const
{
	return this->msg;
}

void FilmValidator::validate(const Film& m)
{
	std::string errors;
	if (m.getTitle().size() < 3)
		errors += "The title should contain at least 3 characters\n";
	if (m.getGenre().size() <3)
		errors += "The genre should contain at least 3 characters!\n";
	std::string trailer = m.getTrailer();
	if (errors.size() > 0)
		throw ValidatorException(errors);
}