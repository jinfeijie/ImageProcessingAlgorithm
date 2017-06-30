#ifndef DCMMANAGER_H
#define DCMMANAGER_H

#include <QWidget>
#include <QtWidgets> 
#include <QFileDialog>
#include <QTextCodec>
#include <QImage>
#include <io.h>
#include <direct.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QString>
#include <QSlider>
#include <QLabel>
#include "Figure.h"
class CDcmManager : public QWidget
{
	Q_OBJECT

public:
	CDcmManager();
	~CDcmManager();

	void loadDcmBinary(std::vector<unsigned short> &img, int &w, int &h, int &minValue);
	void showDcmImage(std::vector<unsigned short> &img, int &w, int &h);
	int toDeltaDataNum(int &num, int &wheelNum);
	int getPointValue(const std::vector<unsigned short> &img, QPoint &seedPoint);
	void doRegionGrow(const std::vector<unsigned short> &img,std::vector<QPoint> &vecCandidateSeeds);
	void doRegionGrowFill(const std::vector<unsigned short> &img, std::vector<QPoint> &points, std::vector<int> &vecSeeds);
	void doRegionGrowArea(const std::vector<unsigned short> &img, QPoint seedpoint);
	void doRegionGrowNew(std::vector<QPoint> &p);
	bool isGrow(const std::vector<int> &vecSeeds, QPoint);
	bool isWaitGrow(const std::vector<int> &vecSeeds, QPoint point);
	void GrowAddColor(QImage &srcImage, std::vector<int> &vecSeeds);
	bool static ascsort(int &i, int &j);
protected:
	void paintEvent(QPaintEvent *paintevent);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
private slots:
	void New();
	void FreeLine();
	void SelectSeedPoints();
	void LoadDCM();
	void LoadDCMFolder();
	void RegionGrow();
	void RegionGrowFill();
	void RegionGrowArea();
	void RegionGrowNew();
	void SaveAs();
	void valueChange(int num);
	
private:
	QString FileName;
	QString FilePath;
	QImage *DeltaDcmPtr,*DeltaDcmBackUpPtr;
	QPoint g_point;
	CFree *cfree;
	vector<CFree *> vecFigurArray;

	int deltaWidth,deltaHeight,minValue;
	std::vector<int> vecSeeds; // 种子点
	std::vector<QPoint> vecCandidateSeeds; // 候选种子点
	std::vector<unsigned short> vecDeltaImage; // 原图
	std::vector<QPoint> vecStartPoint; //多个生长点同时生长
	std::vector<QPoint> vecFreePoint;

	int g_scal, g_num;
	int g_gradient;
	int g_pointValue;
	QString g_local;
	QPoint ctr_pt_;
	float r_;

	bool grow;
	bool growpoint;
	bool free;
	bool down;
	bool bgrow;
	bool bgrowfill;
	bool bgrowArea;

	QSlider *slider;

	QLabel *gradientValue;

};

#endif // DCMMANAGER_H
