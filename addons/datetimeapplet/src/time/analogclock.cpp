 #include <QtGui>

 #include "analogclock.h"


static const int SIZE = 200;

static const QPoint hourHand[3] = {
	QPoint(7, 8),
	QPoint(-7, 8),
	QPoint(0, -SIZE/5)
};

static const QPoint minuteHand[3] = {
	QPoint(7, 8),
	QPoint(-7, 8),
	QPoint(0, -SIZE/3)
};

static const QPoint secundeHand[3] = {
	QPoint(7, 8),
	QPoint(-7, 8),
	QPoint(0, -SIZE*4/10)
};

QColor clockBigCircleColor(0, 0, 0, 16);
QColor clockSmallCircleColor(0, 0, 0, 32);

QColor hourColor(127, 0, 127);
QColor minuteColor(0, 127, 127, 191);
QColor secundeColor(127, 127, 127);


AnalogClock::AnalogClock(DuiWidget *parent)
     : DuiWidget(parent)
 {
     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
     timer->start(1000);
     resize(SIZE, SIZE);
 }

 //void AnalogClock::paintEvent(QPaintEvent *)
void AnalogClock::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{

	int side = qMin(geometry().width(), geometry().height());

	QTime currentTime = QTime::currentTime();


	int hour = currentTime.hour() + m_DiffTime.hour();
	int minute = currentTime.minute() + m_DiffTime.minute();

	if (hour<0)
		hour+=12;

	if (hour>=24)
		hour-=24;

	if (minute<0)
		minute+=60;

	if (minute>=60)
		minute-=60;

	QTime time = QTime(	hour,
						minute,
						currentTime.second(),
						currentTime.msec() );

//	qDebug() << "currentTime  " << currentTime.hour() << ":" << currentTime.minute() << ":" << currentTime.second();
//	qDebug() << "m_DiffTime   " << m_DiffTime.hour() << ":" << m_DiffTime.minute() << ":" << m_DiffTime.second();
//	qDebug() << "time         " << time.hour() << ":" << time.minute() << ":" << time.second();
	
	painter->setRenderHint(QPainter::Antialiasing);
	painter->translate(geometry().width() / 2, geometry().height() / 2);
	painter->scale(side / (float)SIZE, side / (float)SIZE);


	QPainterPath tmpPath;

/*
//rectangle
	painter->setBrush(clockRectangleColor);
	painter->setPen(clockRectangleColor);
	tmpPath.addRect(QRect(-100, -100, 200, 200));
	painter->drawPath(tmpPath);
*/

//circle
	painter->setBrush(clockSmallCircleColor);
	painter->setPen(clockSmallCircleColor);
	tmpPath.addEllipse(QRect(-SIZE/4, -SIZE/4, SIZE/2, SIZE/2));
	painter->drawPath(tmpPath);


	painter->setBrush(clockBigCircleColor);
	painter->setPen(clockBigCircleColor);
	tmpPath.addEllipse(QRect(-SIZE/2, -SIZE/2, SIZE, SIZE));
	painter->drawPath(tmpPath);

//hour
	painter->setPen(Qt::NoPen);
	painter->setBrush(hourColor);
	
	painter->save();
	painter->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
	painter->drawConvexPolygon(hourHand, 3);
	painter->restore();
	
	painter->setPen(hourColor);
	
	for (int i = 0; i < 12; ++i) {
		painter->drawLine(SIZE/2 -12, 0, SIZE/2 -4, 0);
		painter->rotate(30.0);
	}

//min
	painter->setPen(Qt::NoPen);
	painter->setBrush(minuteColor);

	painter->save();
	painter->rotate(6.0 * (time.minute() + time.second() / 60.0));
	painter->drawConvexPolygon(minuteHand, 3);
	painter->restore();

	painter->setPen(minuteColor);

	for (int j = 0; j < 60; ++j) {
		if ((j % 5) != 0)
			painter->drawLine(SIZE/2 -8, 0, SIZE/2 -4, 0);
		painter->rotate(6.0);
	}

//sec	
	painter->setPen(Qt::NoPen);
	painter->setBrush(secundeColor);

	painter->save();
	painter->rotate(6.0 * time.second());
	painter->drawConvexPolygon(secundeHand, 3);
	painter->restore();

 }

void AnalogClock::updateTime()
{
	update();
}


void AnalogClock::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
	setClock(event);
}

void AnalogClock::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	setClock(event);
}

void AnalogClock::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
	setClock(event);
}

void AnalogClock::setClock(QGraphicsSceneMouseEvent * event)
{
	float angle = atan2(	event->pos().x() - geometry().width() / 2,
							event->pos().y() - geometry().height() / 2);

	angle -= PI;
	angle = -angle;

	float length = sqrt( 	(event->pos().x() - geometry().width() / 2) * (event->pos().x() - geometry().width() / 2) +
							(event->pos().y() - geometry().height() / 2) * (event->pos().y() - geometry().height() / 2)	);

	if(SIZE/2 > (int)length)	{
		int selectTime = (int)radToDeg(angle)/30;
		int selectModTime = selectTime%12;
		int time = QTime::currentTime().hour()%12;

		int hour = selectModTime - QTime::currentTime().hour();
		if (hour<0)
			hour+=12;

		if (hour>=12)
			hour-=12;

		if (QTime::currentTime().hour()>12)
			m_DiffTime = QTime(hour+12, m_DiffTime.minute());
		else
			m_DiffTime = QTime(hour, m_DiffTime.minute());
	} else {
		int selectTime = (int)radToDeg(angle)/6;
		int time = QTime::currentTime().minute();

		int minute = selectTime - QTime::currentTime().minute();
		if (minute<0)
			minute+=60;

		if (minute>=60)
			minute-=60;

		int hour = m_DiffTime.hour();

		m_DiffTime = QTime(m_DiffTime.hour(), minute);
	}

	update();
}

