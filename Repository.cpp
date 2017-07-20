#include "Repository.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "RepositoryException.h"
using namespace std;
Repository::Repository(string fn)
{
	this->filename = fn;
	this->readFromFile();
}


int Repository::find(const Film& f)
{
	for (int i = 0; i < this->_dynamicVector.size(); i++)
	{
		if (this->_dynamicVector[i].getTitle() == f.getTitle())
			return i;
	}
	return -1;
}


int Repository::finds(const std::string& s)
{
	for (int i = 0; i < this->_dynamicVector.size(); i++)
	{
		if (this->_dynamicVector[i].getTitle() == s)
			return i;
	}
	return -1;
}

void Repository::addFilm(const Film& f)
{
	if (find(f) != -1)
		throw DuplicateMovieException();
	for (auto s : this->_dynamicVector)
		cout << s.getTitle();
	this->_dynamicVector.push_back(f);
	this->writeToFile();
}

void Repository::removeFilm(const std::string& s)
{
	int pos = finds(s);
	if (pos == -1)
		throw RepositoryException("The element does not exist!\n");
	swap(this->_dynamicVector[pos], this->_dynamicVector.back());
	this->_dynamicVector.pop_back();
	this->writeToFile();
}


void Repository::updateFilm(const Film& f)
{
	int pos = find(f);
	if (pos == -1)
		throw RepositoryException("The movie with this title does not exist!\n");
	this->_dynamicVector[pos] = f;
	this->writeToFile();
}


vector<Film>& Repository::getFilms()
{
	return this->_dynamicVector;
}



void Repository::readFromFile()
{
	ifstream file(this->filename);

	if (!file.is_open())
		throw FileException("The file could not be opened!");
	cout << this->filename;
	Film m;
	while (file >> m)
		this->_dynamicVector.push_back(m);
	file.close();
}

void Repository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (auto s : this->_dynamicVector)
	{
		file << s;
	}

	file.close();
}