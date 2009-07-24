#include "datepicker.h"
#include "daymodel.h"
#include "dcpspaceritem.h"

#include <DuiSceneManager>
#include <duibutton.h>
#include <duitextedit.h>
#include <duigrid.h>
#include <QGraphicsLinearLayout>
#include <QDate>
#include <QtDebug>

const int HEIGHT = 80;

DatePicker::DatePicker(DuiWidget *parent)
           :DuiWidget(parent)
{
	m_Model = NULL;
	m_DayGrid = NULL;

    m_MainLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    m_MainLayout->setContentsMargins(12.0, 0.0, 12.0, 0.0);
    m_MainLayout->setSpacing(1);

	m_NewYear = QDate::currentDate().year();
	m_NewMonth = QDate::currentDate().month();
	setDate(m_NewYear, m_NewMonth);
}

DatePicker::~DatePicker()
{
}

void DatePicker::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QColor(34, 34, 34, 235));
    painter->setBrush(QColor(34, 34, 34, 235));
    painter->drawRect(rect());
}

void DatePicker::left()
{
    qDebug() << "MainPage::left()";

	m_NewMonth--;

	if (m_NewMonth<1) {
		m_NewMonth = 12;
		m_NewYear--;
	}

	setDate(m_NewYear, m_NewMonth);
}

void DatePicker::right()
{

    qDebug() << "MainPage::right()";

	m_NewMonth++;

	if (m_NewMonth>12) {
		m_NewMonth = 1;
		m_NewYear++;
	}

	setDate(m_NewYear, m_NewMonth);
}

void DatePicker::setDate(int year, int month, int day)
{
    Q_UNUSED(year);
    Q_UNUSED(month);
    Q_UNUSED(day);
    
    if (m_DayGrid)
		delete m_DayGrid;

	m_DayGrid = new DuiGrid();
    m_DayGrid->setMinimumSize(650, 450);
    m_DayGrid->setPreferredSize(650, 450);
	m_DayGrid->setMaximumSize(650, 450);

	QDate tmpDate = QDate(m_NewYear, m_NewMonth, 1);

	if (m_Model) {
		delete m_Model;
	}

	m_Model = new DayModel(	tmpDate.daysInMonth(),
							-1,
							tmpDate.dayOfWeek() );

	m_DayGrid->setItemModel(0);
	m_DayGrid->setItemModel(m_Model);

    for (int i = m_MainLayout->count(); i >= 0; i--) {
            m_MainLayout->removeAt(i);
    }

	m_MainLayout->addItem(m_DayGrid);
    m_MainLayout->setAlignment(m_DayGrid, Qt::AlignCenter);
    m_MainLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Preferred, QSizePolicy::Expanding));
}

