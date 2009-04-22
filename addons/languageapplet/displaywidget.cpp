#include "displaywidget.h"
#include "dcpspaceritem.h"
#include "languageselectcontainer.h"
#include "dcplanguage.h"
#include "languagetranslation.h"
#include "languagelabelbuttoncontainer.h"

#include <duitheme.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
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
    m_mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(m_mainLayout, Qt::Vertical);
    m_mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(2.0, 10.0, 2.0, 10.0);

    // titleLayout
    DuiLayout *titleLayout = new DuiLayout(NULL);
    titleLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *titleLayoutPolicy = 
            new DuiLinearLayoutPolicy(titleLayout, Qt::Horizontal);
    titleLayout->setPolicy(titleLayoutPolicy);
    
    titleLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5,
                            QSizePolicy::Expanding, QSizePolicy::Fixed),
                    0, Qt::AlignLeft);
    DuiLabel* titleLabel = new DuiLabel(DcpLanguage::SelectDisplayText);
    titleLabel->setObjectName("DisplayLanguageTitleLabel");
    titleLabel->setAcceptedMouseButtons(0);
    titleLayoutPolicy->addItemAtPosition(titleLabel, 1, Qt::AlignCenter);
    titleLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, 
                        QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignRight);
    DuiWidget* titleWidget = new DuiWidget(this);
    titleWidget->setLayout(titleLayout);
    mainLayoutPolicy->addItemAtPosition(titleWidget, 0, Qt::AlignCenter);

    // DonwloadedLanguage
    LanguageLabelButtonContainer *downloadedCont =
            new LanguageLabelButtonContainer(LanguageLabelButtonContainer::DOWNLOADED,
                                             this);
    connect(downloadedCont, SIGNAL(removeMe(LanguageLabelButtonContainer*)),
            this, SLOT(removeContainer(LanguageLabelButtonContainer*)));

    // InstalledLanguage
    LanguageLabelButtonContainer *installedCont =
            new LanguageLabelButtonContainer(LanguageLabelButtonContainer::INSTALLED,
                                             this);
    connect(installedCont, SIGNAL(removeMe(LanguageLabelButtonContainer*)),
            this, SLOT(removeContainer(LanguageLabelButtonContainer*)));

    // LanguageSelectContainer
    LanguageSelectContainer *selectCont = 
            new LanguageSelectContainer(DcpLanguage::InDeviceText,
                                        languageList, this);
    connect(selectCont, SIGNAL(changeBackToMain()), this, SIGNAL(clicked()));
    
    // contWidget
    DuiWidget *contWidget = new DuiWidget(this);
    m_contLayout = new DuiLayout(contWidget);
    m_contLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *contLayoutPolicy =
            new DuiLinearLayoutPolicy(m_contLayout, Qt::Vertical);
    m_contLayout->setPolicy(contLayoutPolicy);

    contLayoutPolicy->addItemAtPosition(downloadedCont, 0, Qt::AlignCenter);
    contLayoutPolicy->addItemAtPosition(installedCont, 1, Qt::AlignCenter);
    contLayoutPolicy->addItemAtPosition(selectCont, 2, Qt::AlignCenter);
    contWidget->setLayout(m_contLayout);
    
    DuiPannableViewport* viewport = new DuiPannableViewport(this);
    viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    viewport->setWidget(contWidget);
    viewport->setObjectName("LanguageViewport");

    mainLayoutPolicy->addItemAtPosition(viewport, 1, Qt::AlignCenter);
                                            
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignCenter);
    setContentsMargins(15,20,15,20);
}

void DisplayWidget::removeContainer(LanguageLabelButtonContainer *cont)
{
    cont->hide();
    int index = m_contLayout->findIndexForItem(static_cast<QGraphicsItem*>(cont));
    m_contLayout->removeAt(index);
}
