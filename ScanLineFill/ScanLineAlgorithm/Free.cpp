#include "Free.h"


CFree::CFree(void)
{
}

CFree::CFree(vector<QPoint> points)
{
	point = points;
}

CFree::~CFree()
{
}

void CFree::Draw(QPainter &paint)
{
	for (size_t i = 1; i < point.size(); i++)
	{
		paint.drawLine(point[i - 1], point[i]);
	}
}