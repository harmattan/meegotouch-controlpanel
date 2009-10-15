#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <DcpWidget> 

class DcpButton2;
class DuiButton;
class UpdateButton;
class DuiLayout;
class DuiLinearLayoutPolicy;
class DuiLabel;

class DateTimeWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	DateTimeWidget(QGraphicsWidget *parent = 0);
	virtual ~DateTimeWidget();
    //! \reimp
	virtual bool back();
    //! \reimp_end

protected:
	void initWidget();
    
private:
    DuiLayout *m_DateTimeLayout;
    DuiLinearLayoutPolicy *m_DateTimeHLayoutPolicy;
    DuiLinearLayoutPolicy *m_DateTimeVLayoutPolicy;
    DcpButton2 *m_DateButton;
	DcpButton2 *m_TimeButton;
	DcpButton2 *m_TimeZoneButton;
    UpdateButton *m_AutomaticUpdateButton;
    DuiButton *m_RegionFormatButton;
    DuiLabel *m_SimpleLabel;

private slots:
    virtual void orientationChanged();
    virtual void showTimeZoneView();
    virtual void updateTimeText();
    virtual void updateDateText();
    virtual void updateTimeZoneText();
    virtual void showDateView();
    virtual void showTimeView();
    void onLocaleChanged();
};
#endif // DATETIMEWIDGET_H

