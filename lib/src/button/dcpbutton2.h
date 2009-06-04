#ifndef DCPBUTTON2_H
#define DCPBUTTON2_H

#include <DuiButton>
class DuiLabel;
class DuiGridLayoutPolicy;
class DuiLayout;

class DcpButton2: public DuiButton{
    Q_OBJECT
public:
	explicit DcpButton2(DuiWidget* parent = 0);

    void setText(const QString& text1, const QString& text2);
    virtual void setText1(const QString& text);
    virtual void setText2(const QString& text);

    virtual DuiLayout* createLayout();

protected:
    DcpButton2(DuiWidget* parent, bool);

private:
    void updateLabelSizes();
    DuiLabel* m_Label1;
    DuiLabel* m_Label2;
    DuiWidget* m_Triangle;
    DuiLayout* m_TextLayout;
    DuiGridLayoutPolicy* m_TextLayoutPolicy1;
};


#endif // DCPBUTTON2_H
