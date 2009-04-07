#ifndef LANGUAGELISTITEM_H
#define LANGUAGELISTITEM_H

#include <DuiWidget>

class LanguageListItem : public DuiWidget
{
    Q_OBJECT

public:
    LanguageListItem(const QString &text, 
                     bool checked = false,
                     DuiWidget *parent = 0);
    ~LanguageListItem();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    void checked(bool ok);
    bool isChecked();

protected:
    void initWidget();

private:
    QString m_labelText;
    bool    m_checked;
};
#endif // LANGUAGELISTITEM_H
