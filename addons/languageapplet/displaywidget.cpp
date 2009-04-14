#include "displaywidget.h"
#include "dcpspaceritem.h"
#include "languageselectcontainer.h"

#include <duitheme.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include "dcplanguage.h"
#include <duipannableviewport.h>

DisplayWidget::DisplayWidget(QGraphicsWidget *parent)
              :DcpWidget(parent)
{
    setReferer(DcpLanguage::Main);
    initWidget();
}

DisplayWidget::~DisplayWidget()
{
    if (m_background)
    {
        DuiTheme::releasePixmap(m_background);
    }
}

void DisplayWidget::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_background)
    {  
        painter->drawPixmap(0, 0, *m_background);
    }
#if 0
    // draw line below the title
    int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0x80, 0x80, 0x80);
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);

    qreal y = m_titleLabel->y() + m_titleLabel->size().height();
    painter->drawLine(borderWidth, y,
                      geometry().size().width() - 2 * borderWidth, y);
#endif
}

void DisplayWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    QSize size = this->size().toSize();
    static const int border = 30;
    m_background = DuiTheme::boxedPixmap("Mashup-container", size,
                                         border, border, border, border);
}

void DisplayWidget::initWidget()
{
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

    
    // Layout
    DuiLayout *m_mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(m_mainLayout, Qt::Vertical);
    m_mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(2.0, 10.0, 2.0, 10.0);

    // titleLayout
    DuiLayout *titleLayout = new DuiLayout(NULL);
    DuiLinearLayoutPolicy *titleLayoutPolicy = 
            new DuiLinearLayoutPolicy(titleLayout, Qt::Horizontal);
    titleLayout->setPolicy(titleLayoutPolicy);
    
    titleLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5,
                            QSizePolicy::Expanding, QSizePolicy::Fixed),
                    0, Qt::AlignLeft);
    DuiLabel* titleLabel = new DuiLabel("Select display language");
    titleLabel->setObjectName("DisplayLanguageTitleLabel");
    titleLabel->setAcceptedMouseButtons(0);
    titleLayoutPolicy->addItemAtPosition(titleLabel, 1, Qt::AlignCenter);
    titleLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, 
                        QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignRight);
    mainLayoutPolicy->addItemAtPosition(titleLayout, 0, Qt::AlignCenter);

    // LanguageSelectContainer
    LanguageSelectContainer *selectCont = 
            new LanguageSelectContainer("In-device language",
                                        languageList, this);
    connect(selectCont, SIGNAL(changeBackToMain()), this, SLOT(changeBack()));
    DuiPannableViewport* viewport = new DuiPannableViewport(this);
    viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    viewport->setWidget(selectCont);
    viewport->setObjectName("LanguageViewport");

    mainLayoutPolicy->addItemAtPosition(viewport, 1, Qt::AlignCenter);
                                            
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignCenter);
}

void DisplayWidget::changeBack()
{
    emit clicked();
}
