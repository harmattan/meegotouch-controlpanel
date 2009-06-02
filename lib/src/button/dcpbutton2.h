#ifndef DCPBUTTON2_H
#define DCPBUTTON2_H

#include <DuiButton>
class DuiLabel;
class DuiLinearLayoutPolicy;

class DcpButton2: public DuiButton{
    Q_OBJECT
public:
	DcpButton2(DuiWidget* parent = 0);

    void setText1(const QString& text);
    void setText2(const QString& text);

protected:
    DuiLinearLayoutPolicy* m_LayoutPolicy;

private:
    void _setLabelText(DuiLabel*& label, int position, const QString& text);
    DuiLabel* m_Label1;
    DuiLabel* m_Label2;
};


#endif // DCPBUTTON2_H
