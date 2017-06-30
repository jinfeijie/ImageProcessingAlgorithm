#ifndef DCMREGIONGROW_H
#define DCMREGIONGROW_H

#include <QtWidgets/QMainWindow>
#include "ui_dcmRegionGrow.h"
#include "dcmManager.h"
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QPainter>
class CDCMRegionGrow : public QMainWindow
{
	Q_OBJECT

public:
	CDCMRegionGrow(QWidget *parent = 0);
	~CDCMRegionGrow();
	
	void Init();
	void createAction();
	void createMenu();
	void createToolBar();
	void CreateStatusBar();
private:
	CDcmManager *dcmmanager;

	QAction *A_LoadDCM;
	QAction *A_New;
	QAction *A_AsSave;
	QAction *A_FreeLine;
	QAction *A_SelectSeedPoints;
	QAction *A_RegionGrow;
	QAction *A_RegionGrowFill;
	QAction *A_RegionGrowArea;
	QAction *A_RegionGrowNew;
	QAction *A_LoadDCMFolder;
	QAction *A_Submit;

	QToolBar *ToolBar;
	
	QMenu *Menu;
	
private:
	Ui::CDCMRegionGrowClass ui;
};

#endif // DCMREGIONGROW_H
