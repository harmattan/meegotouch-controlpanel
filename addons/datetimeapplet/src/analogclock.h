#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>
#include <DuiWidget>

#include <QTime>

const float PI = 3.1415926535;


class AnalogClock : public DuiWidget
{
     Q_OBJECT

public:
     AnalogClock(DuiWidget *parent = 0);

	float degToRad(int deg) {
    	return (float)deg * PI / 180.0f;
    }

    float radToDeg(float rad) {
    	return rad / PI * 180.0f;
    }

	void setClock(QGraphicsSceneMouseEvent * event);


protected:
  	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

public slots:
    void updateTime();

protected:
	QTime m_DiffTime;
};

#endif
