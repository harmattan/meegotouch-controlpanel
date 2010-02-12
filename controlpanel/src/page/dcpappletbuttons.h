/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef MCPMOSTUSEDCATEGORY_H
#define MCPMOSTUSEDCATEGORY_H

#include <DcpMainCategory>

#include "maintranslations.h"

class DcpAppletMetadata;
class PanningDetector;

class DcpAppletButtons :
    public DcpMainCategory
{
    Q_OBJECT
    Q_PROPERTY (QString mattiID READ mattiID WRITE setMattiID)

public:
    DcpAppletButtons (
            const QString&   logicalId,
            const QString&   categoryName,
            const QString&   title,
            QGraphicsWidget *parent = 0);

    DcpAppletButtons (
            const DcpCategoryInfo  *categoryInfo,
            const QString          &title,
            QGraphicsWidget        *parent = 0);

    void addComponent (
            DcpAppletMetadata *metadata);

    void addComponent (
        const QString       &briefTitleText,
        const QString       &briefSecondaryText,
        const PageHandle    &pageHandle);


    virtual void reload();
    void startLoading();
    bool hasLoadingItems();

    QString mattiID ();
    void setMattiID (const QString &mattiID);

signals:
    void loadingFinished();

protected:
    virtual void createContents();
    void stopLoading();

protected slots:
    void continueLoading();

private:
    QString                 m_CategoryName;
    QString                 m_LogicalId;
    const DcpCategoryInfo  *m_CategoryInfo;
    QString                 m_mattiID;

    // stores the metadatas to be loaded until loading completed:
    int m_LoadPosition;
    QList<DcpAppletMetadata*>* m_LoadingMetadatas;

    // detects panning when loading
    PanningDetector        *m_PanningDetector;
};

#endif

