#ifndef DAYMODEL_H
#define DAYMODEL_H

#include <QAbstractListModel>

#include <DuiButton>
#include <duibuttongroup.h>

class DuiGrid;

#include <QString>


class DayModel : public QAbstractListModel
{
    Q_OBJECT

 	public:
		DayModel(int count, int actual = -1, int firstday = 1, QObject *parent = 0) :
		QAbstractListModel(parent),
		m_MaxDay(count),
		m_Actual(actual),
		m_FirstDay(firstday)
	    {
            m_ButtonGroup = new DuiButtonGroup(this);
            m_ButtonGroup->setExclusive(true);
        }
	
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role) const;
        void toggle(QString);

	public Q_SLOTS:
		
		void keySlot(QString);

	signals:
		void keySignal(QString);

	protected:
		int m_MaxDay;
		int m_Actual;
		int m_FirstDay;
        DuiButtonGroup *m_ButtonGroup;
};

#endif // MAINPAGE_H
