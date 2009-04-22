#include "keyboardwidget.h"
#include "dcpspaceritem.h"
#include "keyboardselectcontainer.h"
#include "languagelabelbuttoncontainer.h"
#include "dcplanguage.h"
#include "languagetranslation.h"

#include <duitheme.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duipannableviewport.h>
#include <QGraphicsSceneMouseEvent>

KeyboardWidget::KeyboardWidget(QGraphicsWidget *parent)
              :DcpWidget(parent), m_background(NULL)
{
    setReferer(DcpLanguage::Main);
    initWidget();
}

KeyboardWidget::~KeyboardWidget()
{
    if (m_background)
    {
        DuiTheme::releasePixmap(m_background);
    }
}

void KeyboardWidget::paint(QPainter *painter,
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

void KeyboardWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
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

void KeyboardWidget::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    DuiWidget::mousePressEvent(event);
    event->accept();
}

void KeyboardWidget::initWidget()
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
    DuiLabel *titleLabel = new DuiLabel(DcpLanguage::SelectKeyboardText);
    titleLabel->setObjectName("DisplayLanguageTitleLabel");
    titleLabel->setAcceptedMouseButtons(0);
    titleLayoutPolicy->addItemAtPosition(titleLabel, 1, Qt::AlignCenter);
    titleLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, 
                        QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignRight);
    mainLayoutPolicy->addItemAtPosition(titleLayout, 0, Qt::AlignCenter);

    // DonwloadedLanguage
    LanguageLabelButtonContainer *downloadedCont =
            new LanguageLabelButtonContainer(LanguageLabelButtonContainer::DOWNLOADED,
                                             this);

    // InstalledLanguage
    LanguageLabelButtonContainer *installedCont =
            new LanguageLabelButtonContainer(LanguageLabelButtonContainer::INSTALLED,
                                             this);

    // LanguageSelectContainer
    KeyboardSelectContainer *selectCont = 
            new KeyboardSelectContainer(DcpLanguage::InDeviceText,
                                        languageList, this);
    
    // contWidget
    DuiWidget *contWidget = new DuiWidget(this);
    DuiLayout *contLayout = new DuiLayout(contWidget);
    contLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *contLayoutPolicy =
            new DuiLinearLayoutPolicy(contLayout, Qt::Vertical);
    contLayout->setPolicy(contLayoutPolicy);

    contLayoutPolicy->addItemAtPosition(downloadedCont, 0, Qt::AlignCenter);
    contLayoutPolicy->addItemAtPosition(installedCont, 1, Qt::AlignCenter);
    contLayoutPolicy->addItemAtPosition(selectCont, 2, Qt::AlignCenter);
    contWidget->setLayout(contLayout);

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
