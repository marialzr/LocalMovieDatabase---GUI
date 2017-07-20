#include "FilmGUI.h"
#include <QDebug>
#include <qcombobox.h>

FilmGUI::FilmGUI(Controller _films, QWidget * parent) : ctrl{ _films }, QWidget{ parent }
{
	this->initGUI();
	this->populateFilmsList();
	this->connectSignalsAndSlots();
}
	

FilmGUI::~FilmGUI(){}

void FilmGUI::initGUI()
{
	//General layout of the window
	QHBoxLayout* layout = new QHBoxLayout{ this };

	//left:
	QWidget* verticalLeft = new QWidget{};
	QVBoxLayout* verticalLeftLayout = new QVBoxLayout{ verticalLeft };

	this->combobox = new QComboBox{};
	this->combobox->addItem("Detailed");
	this->combobox->addItem("Short");
	verticalLeftLayout->addWidget(combobox);


	this->filmsList = new QListWidget{};
	this->filmsList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->filmsList);

	// middla: - gene information + buttons
	QWidget* middleleft = new QWidget{};
	QVBoxLayout* vLayout = new QVBoxLayout{ middleleft };

	// film information
	QWidget* filmDataWidget = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ filmDataWidget };
	this->titleEdit = new QLineEdit{};
	this->genreEdit = new QLineEdit{};
	this->yearEdit = new QLineEdit{};
	this->nrlikesEdit = new QLineEdit{};
	this->trailerEdit = new QLineEdit{};
	QFont f{ "Times New Roman", 12 };

	QLabel* titleLabel = new QLabel{ "Title:" };
	titleLabel->setBuddy(this->titleEdit);
	QLabel* genreLabel = new QLabel{ "Genre : " };
	titleLabel->setBuddy(this->genreEdit);
	QLabel* yearLabel = new QLabel{ "Year:" };
	yearLabel->setBuddy(this->yearEdit);
	QLabel* nrlikesLabel = new QLabel{ "No likes:" };
	nrlikesLabel->setBuddy(this->nrlikesEdit);
	QLabel* trailerLabel = new QLabel{ "Trailer:" };
	trailerLabel->setBuddy(this->trailerEdit);

	titleLabel->setFont(f);
	genreLabel->setFont(f);
	yearLabel->setFont(f);
	nrlikesLabel->setFont(f);
	trailerLabel->setFont(f);

	this->titleEdit->setFont(f);
	this->genreEdit->setFont(f);
	this->yearEdit->setFont(f);
	this->nrlikesEdit->setFont(f);
	this->trailerEdit->setFont(f);

	formLayout->addRow(titleLabel, this->titleEdit);
	formLayout->addRow(genreLabel, this->genreEdit);
	formLayout->addRow(yearLabel, this->yearEdit);
	formLayout->addRow(nrlikesLabel, this->nrlikesEdit);
	formLayout->addRow(trailerLabel, this->trailerEdit);

	vLayout->addWidget(filmDataWidget);

	// buttons
	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->addMovieButton = new QPushButton("Add");
	this->addMovieButton->setFont(f);
	this->deleteMovieButton = new QPushButton("Delete");
	this->deleteMovieButton->setFont(f);
	hLayout->addWidget(this->addMovieButton);
	hLayout->addWidget(this->deleteMovieButton);
	vLayout->addWidget(buttonsWidget);

	QWidget* buttonsWidget2 = new QWidget{};
	QHBoxLayout* hLayout2 = new QHBoxLayout{ buttonsWidget2 };
	this->updateMovieButton = new QPushButton("Update");
	this->updateMovieButton->setFont(f);
	this->filterMovieButton = new QPushButton("Filter");
	this->filterMovieButton->setFont(f);
	hLayout->addWidget(this->updateMovieButton);
	hLayout->addWidget(this->filterMovieButton);
	vLayout->addWidget(buttonsWidget2);

	verticalLeftLayout->addWidget(this->filmsList);
	verticalLeftLayout->addWidget(middleleft);	

	QWidget* arrow = new QWidget{};
	QVBoxLayout* layoutArrow = new QVBoxLayout{ arrow };
	this->arrowButton = new QPushButton("->");
	this->arrowButton->setFont(f);
	layoutArrow->addWidget(this->arrowButton);

	QWidget* right = new QWidget{};
	QVBoxLayout* rightLayout = new QVBoxLayout{ right };
	this->watchList = new QListWidget{};
	this->watchList->setSelectionMode(QAbstractItemView::SingleSelection);
	rightLayout->addWidget(watchList);


	QWidget* rghtButtons = new QWidget{};
	QHBoxLayout* rightLayoutButtons = new QHBoxLayout{ rghtButtons };
	this->playButton = new QPushButton("Play");
	this->playButton->setFont(f);
	this->nextButton = new QPushButton("Next");
	this->nextButton->setFont(f);
	this->saveToFileButton = new QPushButton("Save HTML File");
	this->saveToFileButton->setFont(f);
	rightLayoutButtons->addWidget(playButton);
	rightLayoutButtons->addWidget(nextButton);
	rightLayoutButtons->addWidget(saveToFileButton);

	rightLayout->addWidget(rghtButtons);

	layout->addWidget(verticalLeft);
	layout->addWidget(arrow);
	layout->addWidget(right);
}


void FilmGUI::connectSignalsAndSlots()
{
	// filter button connections
	QObject::connect(this->combobox, &QComboBox::currentTextChanged, this, &FilmGUI::comboboxHandler);
	//item selected changed
	QObject::connect(this->filmsList, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChanged(); });

	QObject::connect(this->addMovieButton, &QPushButton::clicked, this, &FilmGUI::addButtonHandler);
	QObject::connect(this->deleteMovieButton, &QPushButton::clicked, this, &FilmGUI::deleteButtonHandler);
	QObject::connect(this->updateMovieButton, &QPushButton::clicked, this, &FilmGUI::updateButtonHandler);
	QObject::connect(this->filterMovieButton, &QPushButton::clicked, this, &FilmGUI::filterButtonHandler);
	QObject::connect(this->arrowButton, &QPushButton::clicked, this, &FilmGUI::arrowButtonHandler);
	QObject::connect(this->playButton, &QPushButton::clicked, this, &FilmGUI::playButtonHandler);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &FilmGUI::nextButtonHandler);
	QObject::connect(this->saveToFileButton, &QPushButton::clicked, this, &FilmGUI::saveToFileButtonHandler);
}


void FilmGUI::populateFilmsList()
{
// clear the list, if there are elements in it
if (this->filmsList->count() > 0)
this->filmsList->clear();

for (auto g : this->ctrl.getRepo().getFilms())
{
QString itemInList = QString::fromStdString(g.getTitle() + " - " + g.getGenre()+" - "+std::to_string(g.getYear())+" - "+std::to_string(g.getNrLikes())+" - "+g.getTrailer());
QFont f{ "Verdana", 10 };
QListWidgetItem* item = new QListWidgetItem{ itemInList };
item->setFont(f);
this->filmsList->addItem(item);
}

// set the selection on the first item in the list
if (this->ctrl.getRepo().getFilms().size() > 0)
this->filmsList->setCurrentRow(0);
}

void FilmGUI::populateSimple()
{
	// clear the list, if there are elements in it
	if (this->filmsList->count() > 0)
		this->filmsList->clear();

	for (auto g : this->ctrl.getRepo().getFilms())
	{
		QString itemInList = QString::fromStdString(g.getTitle());
		QFont f{ "Verdana", 10 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		this->filmsList->addItem(item);
	}

	// set the selection on the first item in the list
	if (this->ctrl.getRepo().getFilms().size() > 0)
		this->filmsList->setCurrentRow(0);
}

void FilmGUI::comboboxHandler()
{
	if (this->combobox->currentText() == "Short")
		this->populateSimple();
	else
		this->populateFilmsList();
}

void FilmGUI::addButtonHandler()
{
	QString title = this->titleEdit->text();
	QString genre = this->genreEdit->text();
	QString year = this->yearEdit->text();
	QString nrlikes = this->nrlikesEdit->text();
	QString trailer = this->trailerEdit->text();
	this->ctrl.addFilm(Film(title.toStdString(), genre.toStdString(), year.toInt(), nrlikes.toInt(), trailer.toStdString()));
	this->populateFilmsList();
	this->titleEdit->clear();
	this->genreEdit->clear();
	this->yearEdit->clear();
	this->nrlikesEdit->clear();
	this->trailerEdit->clear();
}

void FilmGUI::deleteButtonHandler()
{
	int idx = this->getSelectedIndex();

	if (idx < 0 || idx >= this->ctrl.getRepo().getFilms().size())
		return;
	Film g = this->ctrl.getRepo().getFilms()[idx];
	std::string title = g.getTitle();

	this->ctrl.removeFilmCtrl(title);

	this->populateFilmsList();
	this->titleEdit->clear();
	this->genreEdit->clear();
	this->yearEdit->clear();
	this->nrlikesEdit->clear();
	this->trailerEdit->clear();
}

void FilmGUI::updateButtonHandler()
{
	QString title = this->titleEdit->text();
	QString genre = this->genreEdit->text();
	QString year = this->yearEdit->text();
	QString nrlikes = this->nrlikesEdit->text();
	QString trailer = this->trailerEdit->text();
	this->ctrl.updateFilmCtrl(Film(title.toStdString(), genre.toStdString(), year.toInt(), nrlikes.toInt(), trailer.toStdString()));
	this->populateFilmsList();
	this->titleEdit->clear();
	this->genreEdit->clear();
	this->yearEdit->clear();
	this->nrlikesEdit->clear();
	this->trailerEdit->clear();
}


void FilmGUI::filterButtonHandler()
{
	QString genre = this->genreEdit->text();
	std::vector<Film> films = this->ctrl.getByGenre(genre.toStdString());

	if (this->filmsList->count() > 0)
		this->filmsList->clear();

	for (auto g : films)
	{
		QString itemInList = QString::fromStdString(g.getTitle() + " - " + g.getGenre() + " - " + std::to_string(g.getYear()) + " - " + std::to_string(g.getNrLikes()) + " - " + g.getTrailer());
		QFont f{ "Verdana", 10 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		this->filmsList->addItem(item);
	}

	// set the selection on the first item in the list
	if (this->ctrl.getRepo().getFilms().size() > 0)
		this->filmsList->setCurrentRow(0);
	this->titleEdit->clear();
	this->genreEdit->clear();
	this->yearEdit->clear();
	this->nrlikesEdit->clear();
	this->trailerEdit->clear();
}


void FilmGUI::populateWatchList()
{
	// clear the list, if there are elements in it
	if (this->watchList->count() > 0)
		this->watchList->clear();

		std::vector<Film>v = this->ctrl.getWatchList()->getMovies();
		for (auto g:v)
		{
			QString itemInList = QString::fromStdString(g.getTitle() + " - " + g.getGenre() + " - " + std::to_string(g.getYear()) + " - " + std::to_string(g.getNrLikes()) + " - " + g.getTrailer());
			QFont f{ "Verdana", 10 };
			QListWidgetItem* item = new QListWidgetItem{ itemInList };
			item->setFont(f);
			this->watchList->addItem(item);
		}
}

void FilmGUI::arrowButtonHandler()
{
	QString title = this->titleEdit->text();
	QString genre = this->genreEdit->text();
	QString year = this->yearEdit->text();
	QString nrlikes = this->nrlikesEdit->text();
	QString trailer = this->trailerEdit->text();
	Film f(title.toStdString(), genre.toStdString(), year.toInt(), nrlikes.toInt(), trailer.toStdString());
	this->ctrl.addWatch(f);
	this->populateWatchList();
	this->titleEdit->clear();
	this->genreEdit->clear();
	this->yearEdit->clear();
	this->nrlikesEdit->clear();
	this->trailerEdit->clear();
}

void FilmGUI::playButtonHandler()
{
	if (this->ctrl.getWatchList()->isEmpty())
	{
		return;
	}
	this->ctrl.startWatchlist();
	Film f = this->ctrl.getWatchList()->getCurrentFilm();
}

void FilmGUI::nextButtonHandler()
{
	if (this->ctrl.getWatchList()->isEmpty())
	{
		return;
	}
	this->ctrl.nextMovieWatchlist();
	Film f = this->ctrl.getWatchList()->getCurrentFilm();
	int c = this->ctrl.getWatchList()->getCurrent();
	this->populateWatchList();
	if (!this->ctrl.getWatchList()->isEmpty())
		this->watchList->setCurrentRow(c);
}

void FilmGUI::saveToFileButtonHandler()
{
	if (this->ctrl.getWatchList()->isEmpty())
	{
		return;
	}
	this->ctrl.saveWatchlist("writeHTML.html");
	this->ctrl.openWatchlist();
}

int FilmGUI::getSelectedIndex()
{
	std::vector<Film> v = this->ctrl.getRepo().getFilms();
	if (v.size() == 0)
		return -1;

	// get selected index
	QModelIndexList index = this->filmsList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->titleEdit->clear();
		this->genreEdit->clear();
		this->yearEdit->clear();
		this->nrlikesEdit->clear();
		this->trailerEdit->clear();
		return -1;
	}

	int idx = index.at(0).row();
	return idx;
}

void FilmGUI::listItemChanged()
{
	int idx = this->getSelectedIndex();
	if (idx == -1)
		return;

	// get the song at the selected index
	if (idx >= this->ctrl.getRepo().getFilms().size())
		return;
	Film g = this->ctrl.getRepo().getFilms()[idx];
	int year = g.getYear();
	std::string y = std::to_string(year);
	int nrl = g.getNrLikes();
	std::string nl = std::to_string(nrl);
	
	this->titleEdit->setText(QString::fromStdString(g.getTitle()));
	this->genreEdit->setText(QString::fromStdString(g.getGenre()));
	this->yearEdit->setText(QString::fromStdString(y));
	this->nrlikesEdit->setText(QString::fromStdString(nl));
	this->trailerEdit->setText(QString::fromStdString(g.getTrailer()));

}

