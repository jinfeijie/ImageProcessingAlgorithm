#ifndef SCANLINEALGORITHM_H
#define SCANLINEALGORITHM_H

#include <QtWidgets/QMainWindow>
#include "ui_scanlinealgorithm.h"
#include "scanline.h"
#include <QAction>
#include <QToolBar>
class CScanLineAlgorithm : public QMainWindow
{
	Q_OBJECT

public:
	CScanLineAlgorithm(QWidget *parent = 0);
	~CScanLineAlgorithm();
	CScanLine *scanline;

	void init();
	void createAction();
	void createToolBar();

	QAction *ANew_;
	QAction *AContour_;
	QAction *AScanLines_;
	QAction *ALines_;

	QToolBar *TNew_;


private:
	Ui::CScanLineAlgorithmClass ui;
};

#endif // SCANLINEALGORITHM_H
