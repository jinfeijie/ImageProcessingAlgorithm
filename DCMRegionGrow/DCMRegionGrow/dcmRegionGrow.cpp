#include "dcmRegionGrow.h"

CDCMRegionGrow::CDCMRegionGrow(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	setGeometry(450, 100, 1000, 750);
	dcmmanager = new CDcmManager();
	setCentralWidget(dcmmanager);
	setWindowTitle("DCMRegionGrow");
	Init();
}

CDCMRegionGrow::~CDCMRegionGrow()
{

}

// initialization all opreation
void CDCMRegionGrow::Init()
{
	createAction();
	createMenu();
	createToolBar();
	CreateStatusBar();
}

void CDCMRegionGrow::createAction()
{
	A_New = new QAction("New", this);
	A_New->setShortcut(QKeySequence::New);
	A_New->setStatusTip("New File");
	connect(A_New, SIGNAL(triggered()), dcmmanager, SLOT(New()));

	A_AsSave = new QAction("Save AS", this);
	A_AsSave->setShortcut(QKeySequence::SaveAs);
	A_AsSave->setStatusTip("Save As");
	connect(A_AsSave, SIGNAL(triggered()), dcmmanager, SLOT(SaveAs()));

	A_FreeLine = new QAction("Free Line", this);
	A_FreeLine->setStatusTip("Draw Free Line");
	connect(A_FreeLine, SIGNAL(triggered()), dcmmanager, SLOT(FreeLine()));

	A_LoadDCM = new QAction("Load", this);
	A_LoadDCM->setShortcut(QKeySequence::Open);
	A_LoadDCM->setStatusTip("Load DCM File");
	connect(A_LoadDCM, SIGNAL(triggered()), dcmmanager, SLOT(LoadDCM()));

	A_LoadDCMFolder = new QAction("Load Folder", this);
	A_LoadDCMFolder->setShortcut(QKeySequence::Find);
	A_LoadDCMFolder->setStatusTip("Load DCM File in Folder");
	connect(A_LoadDCMFolder, SIGNAL(triggered()), dcmmanager, SLOT(LoadDCMFolder()));

	A_SelectSeedPoints = new QAction("Select SeedPoints", this);
	A_SelectSeedPoints->setStatusTip("Region Grow");
	connect(A_SelectSeedPoints, SIGNAL(triggered()), dcmmanager, SLOT(SelectSeedPoints()));

	A_RegionGrow = new QAction("Region Grow", this);
	A_RegionGrow->setStatusTip("Region Grow");
	connect(A_RegionGrow, SIGNAL(triggered()), dcmmanager, SLOT(RegionGrow()));
	
	A_RegionGrowFill = new QAction("Region Grow Fill", this);
	A_RegionGrowFill->setStatusTip("Region Grow Fill");
	connect(A_RegionGrowFill, SIGNAL(triggered()), dcmmanager, SLOT(RegionGrowFill()));

	A_RegionGrowArea = new QAction("Region Grow Area", this);
	A_RegionGrowArea->setStatusTip("Region Grow Area");
	connect(A_RegionGrowArea, SIGNAL(triggered()), dcmmanager, SLOT(RegionGrowArea()));

	A_RegionGrowNew = new QAction("New Region Grow", this);
	A_RegionGrowNew->setStatusTip("New Region Grow");
	connect(A_RegionGrowNew, SIGNAL(triggered()), dcmmanager, SLOT(RegionGrowNew()));
}

void CDCMRegionGrow::createMenu()
{
	Menu = menuBar()->addMenu("Menu");
	Menu->setStatusTip("Some Operation");
	Menu->addAction(A_New);
	Menu->addAction(A_AsSave);
	Menu->addAction(A_FreeLine);
	Menu->addAction(A_LoadDCM);
	Menu->addAction(A_LoadDCMFolder);
	Menu->addAction(A_SelectSeedPoints);
	Menu->addAction(A_RegionGrow);
	Menu->addAction(A_RegionGrowFill);
	Menu->addAction(A_RegionGrowArea);
	Menu->addAction(A_RegionGrowNew);
}

void CDCMRegionGrow::createToolBar()
{
	ToolBar = addToolBar("ToolBar");
	ToolBar->addAction(A_New);
	ToolBar->addAction(A_AsSave);
	ToolBar->addAction(A_FreeLine);
	ToolBar->addAction(A_SelectSeedPoints);
	ToolBar->addAction(A_LoadDCM);
	ToolBar->addAction(A_LoadDCMFolder);
	ToolBar->addAction(A_RegionGrow);
	ToolBar->addAction(A_RegionGrowFill);
	ToolBar->addAction(A_RegionGrowArea);
	ToolBar->addAction(A_RegionGrowNew);
}

void CDCMRegionGrow::CreateStatusBar()
{
	statusBar()->showMessage("Ready");
}

