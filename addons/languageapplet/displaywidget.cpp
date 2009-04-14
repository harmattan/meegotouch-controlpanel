#include "displaywidget.h"
#include "dcpspaceritem.h"
#include "languageselectcontainer.h"

#include <duitheme.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include "dcplanguage.h"
#include <duipannableviewport.h>
#include <QGraphicsSceneMouseEvent>

DisplayWidget::DisplayWidget(QGraphicsWidget *parent)
              :DcpWidget(parent), m_background(NULL)
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
    // TODO generalize this with own view?
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QColor::fromRgb(0,0,0,128));
    painter->drawRect(rect());

    if (m_background)
    {  
        qreal left, top;
        getContentsMargins(&left, &top, NULL, NULL);
        painter->drawPixmap(left, top, *m_background);
    }
}

void DisplayWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    QSize size = this->size().toSize();
    static const int border = 30;
    if (m_background) {
        DuiTheme::releasePixmap(m_background);
    }
    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    size.setWidth(size.width()-left-right);
    size.setHeight(size.height()-top-bottom);
    m_background = DuiTheme::boxedPixmap("Mashup-container", size,
                                         border, border, border, border);
}

void DisplayWidget::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    DuiWidget::mousePressEvent(event);
    event->accept();
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
    setContentsMargins(15,20,15,20);
}

void DisplayWidget::changeBack()
{
    emit clicked();
}
