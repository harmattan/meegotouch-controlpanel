#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include "dcpwidget.h" 

class DcpButton;
class UpdateButton;
class TimeZoneDialog;

class DateTimeWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	DateTimeWidget(QGraphicsWidget *parent = 0);
	virtual ~DateTimeWidget();
    //! \reimp
	virtual void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget);
    virtual bool back();
    //! \reimp_end

protected:
	void initWidget();
    
private:
	TimeZoneDialog *m_Dlg;
    DcpButton *m_DateButton;
	DcpButton *m_TimeButton;
	DcpButton *m_TimeZoneButton;
    UpdateButton *m_AutomaticUpdateButton;
    DcpButton *m_RegionFormatButton;

private slots:
    virtual void showTimeZoneDialog();
};
#endif // DATETIMEWIDGET_H

