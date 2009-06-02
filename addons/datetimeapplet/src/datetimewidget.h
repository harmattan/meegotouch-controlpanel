#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include "dcpwidget.h" 

class DcpButton2;
class DuiButton;
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
    DcpButton2 *m_DateButton;
	DcpButton2 *m_TimeButton;
	DcpButton2 *m_TimeZoneButton;
    UpdateButton *m_AutomaticUpdateButton;
    DuiButton *m_RegionFormatButton;

private slots:
    virtual void showTimeZoneDialog();
    virtual void updateTimeText();
    virtual void updateDateText();
};
#endif // DATETIMEWIDGET_H

