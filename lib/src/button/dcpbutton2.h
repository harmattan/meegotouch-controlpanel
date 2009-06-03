#ifndef DCPBUTTON2_H
#define DCPBUTTON2_H

#include <DuiButton>
class DuiLabel;
class DuiLinearLayoutPolicy;
class DuiLayout;

class DcpButton2: public DuiButton{
    Q_OBJECT
public:
	explicit DcpButton2(DuiWidget* parent = 0);

    virtual void setText1(const QString& text);
    virtual void setText2(const QString& text);

    virtual DuiLayout* createLayout();

protected:
    DcpButton2(DuiWidget* parent, bool);

private:
    void _setLabelText(DuiLabel*& label, int position, const QString& text);
    void _updateLabelSizes();
    DuiLabel* m_Label1;
    DuiLabel* m_Label2;
    DuiLinearLayoutPolicy* m_TextLayoutPolicy;
};


#endif // DCPBUTTON2_H
