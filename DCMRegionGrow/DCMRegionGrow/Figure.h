#ifndef FIGURE_H
#define FIGURE_H

#include <QPainter>
#include <vector>
using namespace std;
class CFigure
{
public:
	int start_point_x_, start_point_y_, end_point_x_, end_point_y_;
	virtual void Draw(QPainter &paint){};
	virtual ~CFigure(){}

private:
	
};
class CFree : public CFigure
{
public:
	CFree(void);
	CFree(vector <QPoint> points);
	void Draw(QPainter &paint);
	~CFree();
private:
	vector <QPoint> point;
};

#endif // FIGURE_H
