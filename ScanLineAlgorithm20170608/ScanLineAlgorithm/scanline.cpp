#include "scanLine.h"
CScanLine::CScanLine()
{
	m_drawSatus = false;
	m_contour = false;
	m_scanLine = false;
	setMouseTracking(true);
}

CScanLine::~CScanLine()
{

}

void CScanLine::mousePressEvent(QMouseEvent *event)
{
	if (m_contour)
	{
		if (Qt::LeftButton == event->button())
		{
			m_drawSatus = true;
			g_startPonit = m_startPoint = event->pos();
			m_endPoint = event->pos();
			vecPoints.push_back(m_startPoint);
		}
	}

}

void CScanLine::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_contour)
	{
		m_startPoint = event->pos();
		m_endPoint = g_startPonit;
		vecPoints.push_back(m_startPoint);
		vecPoints.push_back(m_endPoint);
		CFree* current_figure_ = new CFree(vecPoints);
		vecFigurArray.push_back(current_figure_);
		vecContourPoints.insert(vecContourPoints.end(), vecPoints.begin(), vecPoints.end()); // save all contour points
		vecPoints.clear();
		m_drawSatus = false;
		m_startPoint = event->pos();
	}
}

void CScanLine::mouseMoveEvent(QMouseEvent *event)
{
	if (m_contour)
	{
		m_endPoint = event->pos();
		if (m_drawSatus)
		{
			vecPoints.push_back(m_endPoint);
		}
	}
}

void CScanLine::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	if (m_contour)
	{
		for (size_t i = 0; i < vecFigurArray.size(); i++)
		{
			vecFigurArray[i]->Draw(painter);
		}
		if (m_contour)
		{
			if (m_drawSatus)
			{
				for (size_t t = 1; t < vecPoints.size(); t++)
				{
					painter.drawLine(vecPoints[t - 1], vecPoints[t]);
				}
			}
		}
	}
	if (m_scanLine)
	{
		vector<QPoint>::iterator startiter, enditer;
		for (startiter = scanSatrt.begin(), enditer = scanEnd.begin();
			startiter != scanSatrt.end(), enditer != scanEnd.end();
			startiter++, enditer++)
		{
			painter.drawLine((*startiter), (*enditer));
		}
	}


	update();
}

//create new drawtable
void CScanLine::New()
{
	vecFigurArray.clear();
	vecContourPoints.clear();
	vecScanLinePoints.clear();
	SpecialFillPoint.clear();
	vecStartPoint.clear();
	vecUpPoint.clear();
	vecEndPoint.clear();
	NormalFillPoint.clear();
	m_contour = false;
	m_scanLine = false;
	update();
}

// Contour
void CScanLine::Contour()
{
	m_contour = true;
}



// scanline
void CScanLine::ScanLine()
{
	if (vecContourPoints.size())
	{
		m_scanLine = true;
		scanLineInit(vecContourPoints);
	}
	else{
		cout << "select area then ScanLine" << endl;
	}
}

void CScanLine::scanLineInit(vector<QPoint> vecContourPoints)
{
	// deal special points
	dealSpecialPoints(vecContourPoints);
	vector<QList<QPoint>>::iterator iterList;
	QList<QPoint> listPoint;
	vector<QPoint>::iterator siter, eiter;
	vector<QPoint> startPoint, endPoint;
	QPolygon a;
	for (iterList = vecScanLinePoints.begin(); iterList != vecScanLinePoints.end(); iterList++)
	{
		listPoint = *iterList;
		sort(listPoint.begin(), listPoint.end(), ascsort);
		int i;

		for (i = 0; i < listPoint.size(); i++)
		{
			if (i % 2 == 0)
			{
				startPoint.push_back(listPoint[i]);
			}
			else{
				endPoint.push_back(listPoint[i]);
			}
			//cout << "(" << (*aaa).rx() << "," << (*aaa).ry() << ")  ";
			for (siter = startPoint.begin(), eiter = endPoint.begin();
				siter != startPoint.end(), eiter != endPoint.end();
				siter++, eiter++)
			{
				scanSatrt.push_back(*siter);
				scanEnd.push_back(*eiter);
			}
		}
		//cout << endl;
	}
}

void CScanLine::dealSpecialPoints(vector<QPoint> vecContourPoints)
{
	vector<QPoint>::iterator iter,nextiter;
	vecStartPoint = getVecStartPoint(vecContourPoints);
	vecEndPoint = getVecEndPoint(vecContourPoints);
	vecUpPoint = getVecUpPoint(vecContourPoints);
	scanSpecalLines(vecStartPoint, vecEndPoint, vecUpPoint);
	scanNormalLines(vecStartPoint, vecEndPoint);
	FillPointStart.insert(FillPointStart.end(),SpecialFillPoint.begin(),SpecialFillPoint.end());
	FillPointStart.insert(FillPointStart.end(), NormalFillPoint.begin(), NormalFillPoint.end());
	sort(FillPointStart.begin(), FillPointStart.end(), ascsortbyY);
	int min, max;
	MinMax *mm = new MinMax();
	*mm = getAllPointMinMax(vecContourPoints);
	min = mm->min;
	max = mm->max;
	int i;
	for (i = min; i <= max;i++)
	{
		for (iter = FillPointStart.begin(); iter != FillPointStart.end();iter++)
		{
			if ((*iter).ry() == i)
			{
				listPoints.push_back((*iter));
			}
		}
		vecScanLinePoints.push_back(listPoints);
		listPoints.clear();
	}
	FillPointStart.clear();
	//cout << vecScanLinePoints.size() << endl;
}

// get StartPoint vector
vector<QPoint> CScanLine::getVecStartPoint(vector<QPoint> vecContourPoints)
{
	return vecContourPoints;
}

// get EndPoint vector
vector<QPoint> CScanLine::getVecEndPoint(vector<QPoint> vecContourPoints)
{
	vector<QPoint>::iterator vecTemp;
	vector<QPoint> vecEndPoint;
	for (vecTemp = vecContourPoints.begin()+1; vecTemp != vecContourPoints.end(); vecTemp++)
	{
		vecEndPoint.push_back(*vecTemp);
	}
	vecEndPoint.push_back((*vecContourPoints.begin()));
	return vecEndPoint;
}

// get UpPoint vector
vector<QPoint> CScanLine::getVecUpPoint(vector<QPoint> vecContourPoints)
{
	vector<QPoint>::iterator vecTemp;
	vector<QPoint> vecEndPoint;
	vecEndPoint.push_back(*(vecContourPoints.end() - 1));
	for (vecTemp = vecContourPoints.begin(); vecTemp != vecContourPoints.end()-1; vecTemp++)
	{
		vecEndPoint.push_back(*vecTemp);
	}
	return vecEndPoint;
}

// scan special lines 
void CScanLine::scanSpecalLines(vector<QPoint> startPoints, vector<QPoint> endPoints,vector<QPoint> upPoints)
{
	vector<QPoint>::iterator iter;
	QPoint startPoint, endPoint,upPoint;
	int i;
	vector<QPoint> fillPoints;
	for (i = 0; i < startPoints.size(); i++)
	{
		startPoint = startPoints[i];
		endPoint = endPoints[i];
		upPoint = upPoints[i];
		if (is_HorizontalLine(startPoint, endPoint))
		{
			int y = startPoint.ry();
			
			int MinX, MaxX;
			int i;
			MaxX = startPoint.rx() > endPoint.rx() ? startPoint.rx() : endPoint.rx();
			MinX = startPoint.rx() < endPoint.rx() ? startPoint.rx() : endPoint.rx();

			SpecialFillPoint.push_back(startPoint);
			for (i = MinX + 1; i < MaxX; i++)
			{
				SpecialFillPoint.push_back(QPoint(i, startPoint.ry()));
				SpecialFillPoint.push_back(QPoint(i, startPoint.ry()));
			}
			//FillPointStart.push_back(endPoint);
		}
		else{
			if ((startPoint.ry() > endPoint.ry() && startPoint.ry() > upPoint.ry())
				|| (startPoint.ry() < endPoint.ry() && ( startPoint.ry() < upPoint.ry())))
			{
				SpecialFillPoint.push_back(startPoint);
				SpecialFillPoint.push_back(startPoint);
			}
			else
			{
				SpecialFillPoint.push_back(startPoint);
			}
		}
	}
	//cout << "special points" << SpecialFillPoint.size() << endl;
}

void CScanLine::scanNormalLines(vector<QPoint> startPoints, vector<QPoint> endPoints)
{
	vector<QPoint> fillPoints;
	int i;
	MinMax *mm = new MinMax();
	*mm = getAllPointMinMax(vecContourPoints);
	int min, max;
	min = mm->min;
	max = mm->max;
	for (i = min; i < max;i++)
	{
		fillPoints = getNormalCrossPoint(i, startPoints, endPoints);
		sort(fillPoints.begin(), fillPoints.end(), ascsort);
		int i;
		for (i = 0; i < fillPoints.size(); i++)
		{
			NormalFillPoint.push_back(fillPoints[i]);
		}
	}
	//cout << "normal points" << NormalFillPoint.size() << endl;
}

CScanLine::MinMax CScanLine::getAllPointMinMax(vector<QPoint> vecContourPoints)
{
	int min = height(), max = 0;
	vector<QPoint>::iterator iter;
	for (iter = vecContourPoints.begin(); iter != vecContourPoints.end(); iter++)
	{
		min = min < (*iter).ry() ? min : (*iter).ry();
		max = max >(*iter).ry() ? max : (*iter).ry();
	}
	MinMax *mm = new MinMax();
	mm->min = min;
	mm->max = max;
	return *mm;
}

bool CScanLine::is_HorizontalLine(QPoint start, QPoint end)
{
	if (start.ry() == end.ry())
	{
		return true;
	}
	return false;
}

// get SpecalCrossPoints
vector<QPoint> CScanLine::getSpecalCrossPoint(QPoint point, vector<QPoint> startPoints, vector<QPoint> endPoints)
{
	int i;
	QPoint startPoint, endPoint;
	vector<QPoint> vecCrossPoints;
	for (i = 0; i < vecContourPoints.size(); i++)
	{
		startPoint = startPoints[i];
		endPoint = endPoints[i];
		int minY, maxY;
		minY = startPoint.ry() < endPoint.ry() ? startPoint.ry() : endPoint.ry();
		maxY = startPoint.ry() > endPoint.ry() ? startPoint.ry() : endPoint.ry();
		if (minY < point.ry() && maxY > point.ry())
		{
			vecCrossPoints.push_back(calculationCrossPoint(startPoint, endPoint, point.ry()));
		}
	}
	return vecCrossPoints;
}

// get NormalCrossPoints
vector<QPoint> CScanLine::getNormalCrossPoint(int y, vector<QPoint> startPoints, vector<QPoint> endPoints)
{
	vector<QPoint>::iterator startIter,endIter;
	vector<QPoint> normalFillPoint;
	QPoint startPoint, endPoint,point;
	int min, max;
	for (startIter = startPoints.begin(),endIter = endPoints.begin(); startIter != startPoints.end(),endIter != endPoints.end(); startIter++,endIter++)
	{
		startPoint = *startIter;
		endPoint = *endIter;
		max = startPoint.ry() > endPoint.ry() ? startPoint.ry() : endPoint.ry();
		min = startPoint.ry() < endPoint.ry() ? startPoint.ry() : endPoint.ry();
		if (y > min && y < max)
		{
			point = calculationCrossPoint(startPoint, endPoint, y);
			normalFillPoint.push_back(point);
		}
	}
	return normalFillPoint;
}

// calculation x value
QPoint CScanLine::calculationCrossPoint(QPoint start, QPoint end, int y)
{
	double sx = start.rx();
	double sy = start.ry();
	double ex = end.rx();
	double ey = end.ry();
	QVector2D equation;
	QVector2D T = QVector2D(end - start);
	double lambda = (y - sy) / T.y();
	double x = (sx + lambda * T.x());
	x = (x * 100 + 0.5) / 100.0;
	QPoint crossPoint(x,y);
	return crossPoint;
}

bool CScanLine::ascsort(QPoint i, QPoint j)
{
	return i.rx() < j.rx();
}

bool CScanLine::ascsortbyY(QPoint i, QPoint j)
{
	return i.ry() < j.ry();
}