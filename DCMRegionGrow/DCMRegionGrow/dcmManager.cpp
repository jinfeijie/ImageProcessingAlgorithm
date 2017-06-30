#include "dcmManager.h"
#include <stdio.h>
#include <QDebug>
CDcmManager::CDcmManager()
{
	DeltaDcmPtr = new QImage();
	DeltaDcmBackUpPtr = new QImage();
	g_scal = 1;
	g_gradient = 0;
	g_pointValue = 23;
	g_local = "(0,0)";
	grow = false;
	growpoint = false;
	free = false;
	down = false;
	bgrow = false;
	bgrowfill = false;
	bgrowArea = false;
	setMouseTracking(true);
	r_ = 50;
	
	slider = new QSlider(Qt::Vertical, this);
	slider->setGeometry(width()- 3, height() / 2 + 40, 20, 150);

	gradientValue = new QLabel(QString("%1").arg(slider->value()), this);
	gradientValue->setGeometry(width() - 3, height() / 2 + 200, 20, 20);

	slider->setStatusTip("Change Gradient");
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(valueChange(int)));

}

CDcmManager::~CDcmManager()
{

}

/**********************************/
/********       SLOTS   ***********/
/**********************************/
void CDcmManager::New()
{

}

void CDcmManager::FreeLine()
{
	if (!FileName.isEmpty())
	{
		free = true;
		growpoint = false;
	}
	else
	{
		std::cout << "-1" << std::endl;
	}
}

void CDcmManager::SelectSeedPoints()
{
	if (!FileName.isEmpty())
	{
		growpoint = true;
		free = false;
	}
	else
	{
		std::cout << "-1" << std::endl;
	}
}

void CDcmManager::LoadDCM()
{
	FileName.clear();
	// Open file
	QString fileName = QFileDialog::getOpenFileName(this, "Load CM", "C://Users/Jin_fj/Desktop/DeltaMedRec/dcm_bin_tp/", tr("Images(*.delta)"));
	FileName = fileName;
	// Load file
	int idx = 0;
	if (!fileName.isEmpty())
	{
		loadDcmBinary(vecDeltaImage, deltaWidth, deltaHeight, minValue);
		showDcmImage(vecDeltaImage, deltaWidth, deltaHeight);
	}
	update();
}

void CDcmManager::LoadDCMFolder()
{
	// Open file
	FilePath = QFileDialog::getExistingDirectory(NULL, tr("Select Folder"), "C://Users/Jin_fj/Desktop/DeltaMedRec/dcm_bin_tp", QFileDialog::ShowDirsOnly);
	QDir *dir = new QDir(FilePath);
	QStringList filter;
	filter << "*.delta";
	dir->setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	g_num = fileInfo->count();
	QString fileName = FilePath + "/1.delta";
	if (!fileName.isEmpty())
	{
		FileName.clear();
		FileName = fileName;
		loadDcmBinary(vecDeltaImage, deltaWidth, deltaHeight, minValue);
		showDcmImage(vecDeltaImage, deltaWidth, deltaHeight);
	}
	update();


}

void CDcmManager::RegionGrow()
{
	if (!FileName.isEmpty())
	{
		bgrow = true;
		bgrowfill = false;
		vecSeeds.clear();
		for (int i = 0; i < deltaWidth; i++)
		{
			for (int j = 0; j < deltaHeight; j++)
			{
				vecSeeds.push_back(0);
			}
		}
		
		std::vector<QPoint>::iterator itor;

		for (itor = vecStartPoint.begin(); itor != vecStartPoint.end(); itor++)
		{
			vecSeeds[deltaWidth*(*itor).ry() + (*itor).rx()] = 1;
			vecCandidateSeeds.push_back(*itor);
			std::cout << vecSeeds.size() << std::endl;
			ctr_pt_ = (*itor);
			doRegionGrow(vecDeltaImage,vecCandidateSeeds);
			(*DeltaDcmPtr) = (*DeltaDcmBackUpPtr);
			GrowAddColor(*DeltaDcmPtr, vecSeeds);
		}
		
		grow = true;
		update();
	}
	else{
		std::cout << "-1" << std::endl;
	}
}

void CDcmManager::RegionGrowFill()
{
	if (!FileName.isEmpty())
	{
		vecSeeds.clear();
		bgrow = false;
		bgrowfill = true;
		for (int i = 0; i < deltaWidth; i++)
		{
			for (int j = 0; j < deltaHeight; j++)
			{
				vecSeeds.push_back(0);
			}
		}
		doRegionGrowFill(vecDeltaImage, vecStartPoint, vecSeeds);
		(*DeltaDcmPtr) = (*DeltaDcmBackUpPtr);
		GrowAddColor(*DeltaDcmPtr, vecSeeds);
		grow = true;
		update();
	}
	else{
		std::cout << "-1" << std::endl;
	}
}

void CDcmManager::RegionGrowArea()
{
	if (!FileName.isEmpty())
	{
		vecSeeds.clear();
		bgrow = false;
		bgrowfill = false;
		bgrowArea = true;

		for (int i = 0; i < deltaWidth; i++)
		{
			for (int j = 0; j < deltaHeight; j++)
			{
				vecSeeds.push_back(0);
			}
		}

		std::vector<QPoint>::iterator itor;

		for (itor = vecStartPoint.begin(); itor != vecStartPoint.end(); itor++)
		{
			doRegionGrowArea(vecDeltaImage, *itor);
		}
		(*DeltaDcmPtr) = (*DeltaDcmBackUpPtr);
		GrowAddColor(*DeltaDcmPtr, vecSeeds);
		grow = true;
		update();
	}
	else{
		std::cout << "-1" << std::endl;
	}
}

void CDcmManager::RegionGrowNew()
{
	std::vector<QPoint> p;
	doRegionGrowNew(p);
	for (int i = 0; i < p.size(); i++)
	{
		(*DeltaDcmPtr).setPixel(p[i].rx(), p[i].ry(), qRgb(153, 255, 102));
	}
}

void CDcmManager::SaveAs()
{
	if (!DeltaDcmPtr->isNull())
	{
		QString filename = QFileDialog::getSaveFileName(this, "Save Image", ".", tr("Images(*.bmp *.png *.jpg)"));
		if (filename.isNull())
		{
			return;
		}
		DeltaDcmPtr->save(filename);
	}
}

void CDcmManager::valueChange(int num){

	g_gradient = num;
	gradientValue->setText(QString("%1").arg(num));
	if (bgrow)
	{
		RegionGrow();
	}
	if (bgrowfill)
	{
		RegionGrowFill();
	}
	update();

}

/**********************************/
/********       SLOTS   ***********/
/**********************************/



void CDcmManager::paintEvent(QPaintEvent *paintevent)
{
	QPainter painter;
	painter.begin(this);

	painter.setBrush(Qt::lightGray);
	QRect back_rect(0, 0, width()-70, height());
	painter.drawRect(back_rect);

	QRect Navicat = QRect(width() - 69, 0, 69, height()/2);
	painter.drawText(QPoint(width() - 68, 20), QString::number(g_pointValue));

	QRect Local =   QRect(width() - 69, height()/2, 69, height() / 2);
	painter.drawText(QPoint(width() - 68, height() / 2 + 20), g_local);


	QRect rect = QRect(0, 0, DeltaDcmPtr->width(), DeltaDcmPtr->height());
	painter.drawImage(rect, *DeltaDcmPtr);

	for (size_t i = 0; i < vecFigurArray.size(); i++)
	{
		QPen pen;
		pen.setWidth(7);
		pen.setColor(QColor(255, 0, 0));
		painter.setPen(pen);
		vecFigurArray[i]->Draw(painter);
	}
	if (free)
	{
		for (size_t t = 1; t < vecFreePoint.size(); t++)
		{
			QPen pen;
			pen.setWidth(7);
			pen.setColor(QColor(255, 0, 0));
			painter.setPen(pen);
			painter.drawLine(vecFreePoint[t - 1], vecFreePoint[t]);
		}
	}
	painter.end();
}

void CDcmManager::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		g_point = event->pos();
		if (free)
		{
			down = true;
			// 自由画线
			vecFreePoint.push_back(g_point);
		}
		if (growpoint)
		{
			// 选择生长点
			std::cout << "(" << g_point.rx() << "," << g_point.ry() << ")" << endl;
			std::cout << getPointValue(vecDeltaImage, g_point) << std::endl;
			vecStartPoint.push_back(g_point);
		}
	}
	if (event->button() == Qt::RightButton)
	{
		vecStartPoint.clear();
		vecFigurArray.clear();
		vecFreePoint.clear();
		update();
	}
}

void CDcmManager::mouseReleaseEvent(QMouseEvent *event)
{
	if (free)
	{
		free = false;
		down = false;
		vecFreePoint.push_back(event->pos());
		cfree = new CFree(vecFreePoint);
		vecFigurArray.push_back(cfree);
	}
}

void CDcmManager::mouseMoveEvent(QMouseEvent *event)
{
	QPoint mousePoint = event->pos();
	if (free)
	{
		if (down)
		{
			vecFreePoint.push_back(mousePoint);
		}
	}
	if (growpoint)
	{
		if (!FileName.isEmpty())
		{
			//g_pointValue = getPointValue(vecDeltaImage, mousePoint);
			g_local = "(" + QString::number(mousePoint.rx()) + "," + QString::number(mousePoint.ry()) + ")";
		}
	}
	update();
}

void CDcmManager::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0)
	{
		g_scal -= 1;
	}
	else
	{
		g_scal += 1;
	}

	if (!FilePath.isEmpty())
	{
		// calculate the num of DCM
		int DcmNum = toDeltaDataNum(g_num, g_scal);
		g_pointValue = DcmNum;
		QString qstrNum = QString::number(DcmNum);
		QString fileName = FilePath + "/" + qstrNum + ".delta";
		if (!fileName.isEmpty())
		{
			FileName.clear();
			FileName = fileName;
			loadDcmBinary(vecDeltaImage, deltaWidth, deltaHeight, minValue);
			showDcmImage(vecDeltaImage, deltaWidth, deltaHeight);
		}
		if (grow)
		{
			vecSeeds.clear();
			if (bgrow)
			{
				RegionGrow();
			}
			if (bgrowfill)
			{
				RegionGrowFill();
			}
		}
		update();
	}
}

void CDcmManager::loadDcmBinary(std::vector<unsigned short> &img, int &w, int &h, int &minValue)
{
	std::string path = FileName.toStdString();
	img.clear();
	w = h = 0;
	minValue = 0;
	std::ifstream f;
	f.open(path, std::ios::binary);
	if (!f.is_open()) return;
	unsigned short t;
	f.read((char *)(&t), sizeof(unsigned short)); w = t;
	f.read((char *)(&t), sizeof(unsigned short)); h = t;
	f.read((char *)(&t), sizeof(unsigned short)); int s = t;
	f.read((char *)(&t), sizeof(unsigned short));
	if (0 == s)
	{
		minValue = t*(-1);
	}
	else
	{
		minValue = t;
	}
	img.resize(w*h);
	f.read((char *)img.data(), w*h*sizeof(unsigned short));
	f.close();
}

int CDcmManager::toDeltaDataNum(int &num, int &wheelNum)
{
	if (wheelNum >0)
	{
		return wheelNum % num;
	}
	return num + wheelNum % num;
}

void CDcmManager::showDcmImage(std::vector<unsigned short> &img, int &w, int &h)
{
	std::vector<int> normalImage;
	std::vector<unsigned short>::iterator imgPtr;
	for (imgPtr = img.begin(); imgPtr != img.end(); imgPtr++)
	{
		normalImage.push_back(((*imgPtr) + 1024) / 20);
	}
	QImage ret(w, h, QImage::Format_ARGB32);

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			int color = normalImage[j*w + i];
			ret.setPixel(QPoint(i, j), qRgb(color, color, color));
		}
	}
	(*DeltaDcmBackUpPtr) = (*DeltaDcmPtr) = ret;
}

int CDcmManager::getPointValue(const std::vector<unsigned short> &img, QPoint &seedPoint)
{
 	int x = seedPoint.rx();
 	int y = seedPoint.ry();
 	int local;
 	int max = -1024;
 	int min = 4096;
 	int color = 0;
 	int temp = 0;
 	int growPointNum = 0;
 	for (int i = -1; i <= 1; i++)
 	{
 		for (int j = -1; j <= 1; j++)
 		{
 			local = deltaWidth*(y + j) + (x + i);
 			if (local >= 0)
 			{
 				temp = img[deltaWidth*(y + j) + (x + i)];
 				min = min < temp ? min : temp;
 				max = max > temp ? max : temp;
 				color += temp;
 				growPointNum++;
 			}
 		}
 	}
 	color = (color - max - min) / (growPointNum - 2);
 	return color;
// 	int x = seedPoint.rx();
// 	int y = seedPoint.ry();
// 	return img[deltaWidth*y + x];
}

void CDcmManager::doRegionGrow(const std::vector<unsigned short> &img, std::vector<QPoint> &vecCandidateSeeds)
{

//  递归
//	int x = seedPoint.rx();
// 	int y = seedPoint.ry();
// 	int srcSeedColor = getPointValue(img, seedPoint);
// 	for (int i = -1; i <= 1; i++)
// 	{
// 		for (int j = -1; j <= 1; j++)
// 		{
// 			if (x + i >= 0 && x + i < deltaWidth &&
// 				y + j >= 0 && y + j < deltaHeight &&
// 				abs(srcSeedColor - getPointValue(img, QPoint(x + i, y + j)) < g_gradient))
// 			{
// 				if (!(i == 0 && j == 0) &&
// 					!is_Grow(vecSeeds, QPoint(x + i, y + j)))
// 				{
// 					QPoint tp = QPoint(x + i, y + j) - ctr_pt_;
// 					if ( QPoint::dotProduct(tp,tp)>r_*r_ )
// 					{
// 						continue;
// 					}
// 					vecSeeds[deltaWidth*(y + j) + (x + i)] = 1;
// 					//std::cout << "(" << x + i << "," << y + j << ")" << std::endl;
// 					doRegionGrow(img, QPoint(x + i, y + j));
// 				}
// 			}
// 		}
// 	}
	
	// 非递归
	while (vecCandidateSeeds.size())
	{
		std::vector<QPoint> vecTempCandidateSeeds;
		vecTempCandidateSeeds.clear();
		for (int i = 0; i < vecCandidateSeeds.size(); i++)
		{
			int x = vecCandidateSeeds[i].rx();
			int y = vecCandidateSeeds[i].ry();
			int srcSeedColor = getPointValue(img, vecCandidateSeeds[i]);
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (x + i >= 0 && x + i < deltaWidth &&
						y + j >= 0 && y + j < deltaHeight &&
						abs(srcSeedColor - getPointValue(img, QPoint(x + i, y + j)) < g_gradient))
					{
						if (!(i == 0 && j == 0) &&
							!isGrow(vecSeeds, QPoint(x + i, y + j)))
						{
// 							QPoint tp = QPoint(x + i, y + j) - ctr_pt_;
// 							if (QPoint::dotProduct(tp, tp)>r_*r_)
// 							{
// 								continue;
// 							}
							vecSeeds[deltaWidth *(y + j) + (x + i)] = 1;
							vecSeeds[deltaWidth *y + x] = 2;
							vecTempCandidateSeeds.push_back(QPoint(x+i,y+j));
						}
					}
				}
			}
		}
		vecCandidateSeeds.clear();
		vecCandidateSeeds.insert(vecCandidateSeeds.end(), vecTempCandidateSeeds.begin(), vecTempCandidateSeeds.end());
		vecTempCandidateSeeds.clear();
	}
}

void CDcmManager::doRegionGrowFill(const std::vector<unsigned short> &img, std::vector<QPoint> &points, std::vector<int> &vecSeeds)
{

	for (int num = 0; num < points.size(); num++)
	{
		int srcSeedColor = getPointValue(img, points[num]);
		for (int i = 0; i < deltaWidth; i++)
		{
			for (int j = 0; j < deltaHeight; j++)
			{
				if (getPointValue(img, QPoint(i, j)) >= srcSeedColor)
				{
					vecSeeds[deltaWidth*j + i] = 1;
				}
			}
		}
	}
}

void CDcmManager::doRegionGrowArea(const std::vector<unsigned short> &img, QPoint seed)
{
	std::vector<QPoint> vecGrown;
	std::vector<int> lableImage;
	for (int i = 0; i < deltaWidth; i++)
	{
		for (int j = 0; j < deltaHeight; j++)
		{
			lableImage.push_back(0);
		}
	}
	float diff = 0;
	do 
	{
		int x = seed.rx();
		int y = seed.ry();
		vecGrown.push_back(seed);
		lableImage[deltaWidth * y + x] = 2;


		std::vector<QPoint> vecTempWaitGrow;
		vecTempWaitGrow.clear();
		for (int i = 0; i < vecGrown.size(); i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				for (int k = -1; k <= 1; k++)
				{
					if (x + j >= 0 && x + j < deltaWidth &&
						y + k >= 0 && y + k < deltaHeight &&
						!(j == 0 && k == 0) &&
						lableImage[deltaWidth *(vecGrown[i].ry() + k) + (vecGrown[i].rx() + j)] != 2)
					{
						vecTempWaitGrow.push_back(QPoint(vecGrown[i].rx() + j, vecGrown[i].ry() + k));
					}
				}
			}
		}

		// calculate grown point 
		float color = 0;
		for (int i = 0; i < vecGrown.size(); i++)
		{
			color += img[deltaWidth*vecGrown[i].ry() + vecGrown[i].rx()];
		}
		color /= vecGrown.size();

		// calculate min abs(color value)
		float minabs = 10000;
		QPoint nextSeedpoint;
		for (int i = 0; i < vecTempWaitGrow.size(); i++)
		{
			diff = abs(color - img[deltaWidth * vecTempWaitGrow[i].ry() + vecTempWaitGrow[i].rx()]);
			if (diff < minabs)
			{
				minabs = diff;
				nextSeedpoint = vecTempWaitGrow[i];
			}
		}
		diff = minabs;
		seed = nextSeedpoint;
	} while (diff < g_gradient && vecGrown.size() < vecSeeds.size());

	vecSeeds = lableImage;
}

void CDcmManager::doRegionGrowNew(std::vector<QPoint> &p){

	
}

bool CDcmManager::isGrow(const std::vector<int> &vecSeeds, QPoint point)
{
	int x = point.rx();
	int y = point.ry();
	//std::cout << "(" << x << "," << y << ")" << std::endl;
	if (vecSeeds[deltaWidth*y + x] != 0 )
	{
		return true;
	}
	return false;
}

bool CDcmManager::isWaitGrow(const std::vector<int> &vecSeeds, QPoint point){
	int x = point.rx();
	int y = point.ry();
	//std::cout << "(" << x << "," << y << ")" << std::endl;
	if (vecSeeds[deltaWidth*y + x] == 1)
	{
		return true;
	}
	return false;
}

void CDcmManager::GrowAddColor(QImage &srcImage, std::vector<int> &vecSeeds)
{
	for (int i = 0; i < deltaWidth; i++)
	{
		for (int j = 0; j < deltaHeight; j++)
		{
			if (vecSeeds[deltaWidth*j + i] != 0)
			{
				srcImage.setPixel(i, j, qRgb(153,255,102));
			}
		}
	}
	(*DeltaDcmPtr) = srcImage;
}

bool CDcmManager::ascsort(int &i, int &j)
{
	return i < j;
}