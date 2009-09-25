#ifndef DCPTABLEDELEGATEIF_H
#define DCPTABLEDELEGATEIF_H

#include <QObject>
class QModelIndex;
class QPainter;

class DcpTableDelegate: public QObject
{
    Q_OBJECT
public:
    virtual ~DcpTableDelegate(){}

    virtual void paint ( QPainter * painter, const QModelIndex & index ) const = 0;
    virtual void setHeight (int height) {m_Height = height;} // user sets it
    virtual void setWidth (int width) {m_Width = width;} // table sets it, TODO put a little concept in it :)
    int width() const;
    int height() const;

protected:
    int m_Height;
    int m_Width;
};


inline int DcpTableDelegate::width() const
{
    return m_Width;
}

inline int DcpTableDelegate::height() const
{
    return m_Height;
}


#endif // DCPTABLEDELEGATEIF_H

