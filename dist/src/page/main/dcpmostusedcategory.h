#ifndef MCPMOSTUSEDCATEGORY_H
#define MCPMOSTUSEDCATEGORY_H

#include <DcpMainCategory>

class DcpAppletMetadata;

class DcpMostUsedCategory  : public DcpMainCategory
{
    Q_OBJECT
public:
    DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent=0);

    void addComponent(DcpAppletMetadata *metadata, bool fullLine = false);

    virtual void onOrientationChange(const Dui::Orientation& orientation);
    virtual void reload();

protected:
    virtual void createContents();

};

#endif
