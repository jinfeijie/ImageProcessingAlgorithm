#include "scanLine.h"

CScanLine::CScanLine()
{
	m_drawSatus = false;
	m_contour = false;
	m_scanLine = true;
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
	if (m_drawSatus)
	{
		m_startPoint = event->pos();
		m_endPoint = g_startPonit;
		vecPoints.push_back(m_startPoint);
		vecPoints.push_back(m_endPoint);
		CFree* current_figure_ = NULL;
		current_figure_ = new CFree(vecPoints);
		vecFigurArray.push_back(current_figure_);
		//vecPoints.clear();
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
	if (m_scanLine)
	{
		painter.setPen(Qt::black);
		painter.setBrush(Qt::red);
		QPainterPath myPath;
		myPath.addPolygon(myPolygon);
		painter.drawPath(myPath);
	}
	update();
}

void CScanLine::New()
{
	vecFigurArray.clear();
	vecPoints.clear();
	myPolygon.clear();
	m_contour = true;
	m_scanLine = false;
	update();
}

void CScanLine::Contour()
{
	m_contour = true;
}

void CScanLine::ScanLine()
{
	if (vecPoints.size())
	{
		m_contour = false;
		m_scanLine = true;		
		vector<QPoint>::iterator iter;
		for (iter = vecPoints.begin(); iter != vecPoints.end(); iter++)
		{
			myPolygon << QPointF((*iter).rx(), (*iter).ry());
		}
	}
	else{
		cout << "select area then ScanLine" << endl;
	}
}