#ifndef SERVICESBUTTONBLOCK_H
#define SERVICESBUTTONBLOCK_H

#include <DuiWidget>
class ServicesButton;
class DuiGridLayout;
class DuiLabel;

class ServicesButtonBlock : public DuiWidget
{
    Q_OBJECT

public:
    ServicesButtonBlock(QGraphicsWidget *parent = 0);
    virtual ~ServicesButtonBlock();

    void addServicesButton(const QString &name);

protected:
    void initWidget();

private:
    QVector<ServicesButton*> m_buttonVector;
    DuiLabel                *m_header;
    DuiGridLayout           *m_buttonLayout;
};
#endif // SERVICESBUTTONBLOCK_H
