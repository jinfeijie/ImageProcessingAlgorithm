#pragma once
#include "Figure.h"
#include <vector>
using namespace std;
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