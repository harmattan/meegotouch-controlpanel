#ifndef DATEPICKER_H
#define DATEPICKER_H

#include <duiwidget.h>

class DuiGrid;
class QGraphicsLinearLayout;

class DatePicker : public DuiWidget {
	Q_OBJECT

public:
	DatePicker(DuiWidget *parent = 0);
    virtual ~DatePicker();
    //!reimp
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = 0);
    //!reimp_end
	void setDate(int year, int month, int day = -1);

public slots:
	virtual void left();
	virtual void right();

private:
	class DayModel *m_Model;
	DuiGrid *m_DayGrid;
    QGraphicsLinearLayout *m_MainLayout;
	int m_NewYear;
	int m_NewMonth;
};

#endif // DATEPICKER_H
