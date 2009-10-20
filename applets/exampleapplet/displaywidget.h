#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <DcpWidget>
 
class DuiSlider;
class DuiLabel;
class DuiButton;

class DisplayWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	DisplayWidget(QGraphicsWidget *parent = 0);
	virtual ~DisplayWidget();

	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget);
protected:
	void initWidget();
    virtual void retranslateUi();
		
private:
	DuiLabel    *m_brightnessLabel;
	DuiLabel    *m_screenLabel;
	DuiLabel    *m_screenLightLabel;
	DuiLabel    *m_noteText;
    DuiButton   *m_screenToggleButton;
    DuiSlider   *m_sliderScreen;
    DuiSlider   *m_sliderBrightness;
		
private slots:
	virtual void setBrightnessLabel(int value);
	virtual void setScreenLabel(int value);
    void nextPage();
};

#endif // DISPLAYWIDGET_H

