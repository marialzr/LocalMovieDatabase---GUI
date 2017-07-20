#ifndef LMDBGUI_H
#define LMDBGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_lmdbgui.h"

class LMDBgui : public QMainWindow
{
	Q_OBJECT

public:
	LMDBgui(QWidget *parent = 0);
	~LMDBgui();

private:
	Ui::LMDBguiClass ui;
};

#endif // LMDBGUI_H
