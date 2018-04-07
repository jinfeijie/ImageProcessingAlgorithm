#ifndef SCANLINE_H
#define SCANLINE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Free.h"
using namespace std;
class CScanLine : public QWidget
{
	Q_OBJECT

public:
	CScanLine();
	~CScanLine();

	vector<QPoint> vecPoints;
	vector<CFree *> vecFigurArray;
	QPoint m_startPoint, m_endPoint, g_startPonit;
	QPolygonF myPolygon;
	bool m_contour, m_drawSatus, m_scanLine;

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

private slots:
	void New();
	void Contour();
	void ScanLine();
private:
	
};

#endif // SCANLINE_H
