#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include "dcpwidget.h" 

class DcpButton;
class UpdateButton;

class DateTimeWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	DateTimeWidget(QGraphicsWidget *parent = 0);
	virtual ~DateTimeWidget();

	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget);

protected:
	void initWidget();
private:
	DcpButton *m_DateButton;
	DcpButton *m_TimeButton;
	DcpButton *m_TimeZoneButton;
    UpdateButton *m_AutomaticUpdateButton;
    DcpButton *m_RegionFormatButton;
};
#endif // DATETIMEWIDGET_H
