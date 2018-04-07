#include "scanlinealgorithm.h"

CScanLineAlgorithm::CScanLineAlgorithm(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	setGeometry(450, 150, 400, 400);
	scanline = new CScanLine();
	setCentralWidget(scanline);
	setWindowTitle("ScanLine");
	init();
}

CScanLineAlgorithm::~CScanLineAlgorithm()
{

}


void CScanLineAlgorithm::init()
{
	createAction();
	createToolBar();
}


void CScanLineAlgorithm::createToolBar()
{
	TNew_ = addToolBar("New");
	TNew_->addAction(ANew_);
	TNew_->addAction(AContour_);
	TNew_->addAction(AScanLines_);
}


void CScanLineAlgorithm::createAction()
{
	ANew_ = new QAction(tr("New"), this);
	AContour_ = new QAction(tr("Contour"), this);
	AScanLines_ = new QAction(tr("ScanLine"), this);
	connect(ANew_, SIGNAL(triggered()), scanline, SLOT(New()));
	connect(AContour_, SIGNAL(triggered()), scanline, SLOT(Contour()));
	connect(AScanLines_, SIGNAL(triggered()), scanline, SLOT(ScanLine()));

}