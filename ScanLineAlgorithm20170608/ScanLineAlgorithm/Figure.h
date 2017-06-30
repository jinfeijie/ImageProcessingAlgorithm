
#include <QPainter>
#pragma once
class CFigure
{
public:
	int start_point_x_, start_point_y_, end_point_x_, end_point_y_;
	virtual void Draw(QPainter &paint){};
	virtual ~CFigure(){}
};

