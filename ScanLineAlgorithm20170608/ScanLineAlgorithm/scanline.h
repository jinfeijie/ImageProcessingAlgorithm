#ifndef SCANLINE_H
#define SCANLINE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <vector>
#include <iostream>
#include <QwheelEvent>
#include <algorithm>
#include <QList>
#include "Free.h"
using namespace std;
class CScanLine : public QWidget
{
	Q_OBJECT

public:
	CScanLine();
	~CScanLine();

public:
	bool m_contour, m_drawSatus, m_scanLine;
	QPoint m_startPoint, m_endPoint, g_startPonit;
	vector<QPoint> vecContourPoints, vecPoints,vecStartPoint,vecEndPoint,vecUpPoint;
	vector<CFree *> vecFigurArray;
	int contourMinY, contourMaxY;
	vector<QPoint> FillPointStart,FillPointEnd;
	vector<QPoint> SpecialFillPoint, NormalFillPoint;
	vector<QPoint> NorMalPoints, SepcicalPoints;
	vector<QPoint> start, end;
	QList<QPoint> listPoints;
	vector<QPoint> scanSatrt, scanEnd;
	vector<QList<QPoint>> vecScanLinePoints;
public:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

	void scanLineInit(vector<QPoint> vecContourPoints);
	void dealSpecialPoints(vector<QPoint> vecContourPoints);
	void scanSpecalLines(vector<QPoint> startPoints, vector<QPoint> endPoints,vector<QPoint> upPoints);
	void scanNormalLines(vector<QPoint> startPoints, vector<QPoint> endPoints);
private:
	vector<QPoint> getVecStartPoint(vector<QPoint> vecContourPoints);
	vector<QPoint> getVecEndPoint(vector<QPoint> vecContourPoints);
	vector<QPoint> getVecUpPoint(vector<QPoint> vecContourPoints);
	vector<QPoint> getSpecalCrossPoint(QPoint, vector<QPoint>, vector<QPoint>);
	vector<QPoint> getNormalCrossPoint(int y, vector<QPoint>, vector<QPoint>);
	QPoint calculationCrossPoint(QPoint, QPoint, int y);
	struct MinMax
	{
		int min;
		int max;
	};
	MinMax getAllPointMinMax(vector<QPoint> vecContourPoints);
	bool is_HorizontalLine(QPoint, QPoint);
	bool static ascsort(QPoint i, QPoint j);
	bool static ascsortbyY(QPoint i, QPoint j);
private slots:
	void New();
	void Contour();
	void ScanLine();
private:
	
};

#endif // SCANLINE_H
