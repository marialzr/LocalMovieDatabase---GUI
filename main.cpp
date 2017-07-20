#include "lmdbgui.h"
#include "CSVWatchlist.h"
#include <QtWidgets/QApplication>
#include <vector>
#include "Repository.h"
#include "Controller.h"
#include "Film.h"
#include "Watchlist.h"
#include "HTMLWatchlist.h"
#include "FilmGUI.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	Repository repo("readFilm.txt");
	FileWatchList *p = new HTMLWatchlist{};
	Controller ctrl(repo, p, FilmValidator{});

	FilmGUI ui(ctrl);
	ui.show();

	return a.exec();
}