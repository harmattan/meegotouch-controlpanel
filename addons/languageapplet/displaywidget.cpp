#include "displaywidget.h"

#include <duitheme.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilist.h>
#include <QStringListModel>
#include <QItemSelectionModel>
#include "dcplanguage.h"

DisplayWidget::DisplayWidget(QGraphicsWidget *parent)
              :DcpWidget(parent)
{
    setReferer(DcpLanguage::Main);
    initWidget();
}

DisplayWidget::~DisplayWidget()
{
    if (m_inDeviceList)
    {
        delete m_inDeviceList;
    }
}

void DisplayWidget::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(QColor(120, 120, 120, 240));
    QBrush brush(QColor(20, 20, 20, 240));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(0.0, 0.0,
                            size().width(),
                            size().height()));
}

void DisplayWidget::initWidget()
{
    m_inDeviceList = new DuiList(this);
    m_inDeviceList->setTopGroupHeader("Select display language");
    m_inDeviceList->addGroupHeader(0, "In-device language");
    m_inDeviceList->enableItemSelection(true);
    m_inDeviceList->setItemSize(QSize(200, 30));
    
    QString rushian = 
        QString("P%1cc").arg(QChar(0x0443)) + QChar(0x043A) + QChar(0x0438) + QChar(0x0439); 

    QStringList languageList;
    languageList << "Dansk" << "Deutsch" << "English GB" << "English US" 
            << QString("Fran%1ais (Canada)").arg(QChar(0x00e7)) 
            << QString("Fran%1ais (France)").arg(QChar(0x00e7)) 
            << "Italiaon"
            << QString("LA Espa%1ol").arg(QChar(0x00f1)) 
            << "Nederlands" << "Norks" 
            << QString("Portugu%1s").arg(QChar(0x00ea))
            << QString("Portugu%1s BR").arg(QChar(0x00ea)) 
            << rushian << "Suomi";

    QStringListModel *deviceListModel = new QStringListModel(languageList);
    m_inDeviceList->setItemModel(deviceListModel);
    
    // Layout
    m_mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(m_mainLayout, Qt::Vertical);
    m_mainLayout->setPolicy(mainLayoutPolicy);
    
    mainLayoutPolicy->setContentsMargins(12.0, 12.0, 12.0, 12.0);
    mainLayoutPolicy->setSpacing(15);

    mainLayoutPolicy->addItemAtPosition(m_inDeviceList, 0, Qt::AlignCenter);
}
