#ifndef SKELETONWIDGET_H
#define SKELETONWIDGET_H

#include <DcpWidget>
 
class MLabel;

class SkeletonWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	SkeletonWidget(QGraphicsWidget *parent = 0);
	virtual ~SkeletonWidget();

protected:
	void initWidget();
		
private:
	MLabel    *m_aboutLabel;
		
};
#endif // SKELETONWIDGET_H
