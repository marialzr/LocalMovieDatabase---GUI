#pragma once
#pragma once
#include <qwidget.h>
#include "Film.h"
#include "Controller.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <string.h>
#include <qcombobox.h>

class FilmGUI : public QWidget
{
	Q_OBJECT

public:
	FilmGUI(Controller ctrl, QWidget *parent = 0);
	~FilmGUI();

private:
	Controller ctrl;

	QComboBox* combobox;
	QListWidget* filmsList;
	QListWidget* watchList;
	QLineEdit* titleEdit;
	QLineEdit* genreEdit;
	QLineEdit* yearEdit;
	QLineEdit* nrlikesEdit;
	QLineEdit* trailerEdit;
	QPushButton* addMovieButton;
	QPushButton* deleteMovieButton;
	QPushButton* updateMovieButton;
	QPushButton* filterMovieButton;
	QPushButton* playButton;
	QPushButton* nextButton;
	QPushButton* arrowButton;
	QPushButton* saveToFileButton;

	void initGUI();
	void connectSignalsAndSlots();

	void populateFilmsList();
	void FilmGUI::populateSimple();
	void FilmGUI::comboboxHandler();
	void addButtonHandler();
	int getSelectedIndex();
	void listItemChanged();
	void deleteButtonHandler();
	void FilmGUI::updateButtonHandler();
	void FilmGUI::filterButtonHandler();
	void FilmGUI::populateWatchList();
	void FilmGUI::arrowButtonHandler();
	void playButtonHandler();
	void nextButtonHandler();
	void saveToFileButtonHandler();
};

