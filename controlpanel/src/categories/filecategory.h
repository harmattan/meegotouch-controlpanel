#ifndef FILECATEGORY_H
#define FILECATEGORY_H

#include "category.h"
class QSettings;

class FileCategory: public Category
{
public:
    FileCategory(const QString& fileName);
    ~FileCategory();

    bool isValid() const;

protected:
    virtual QString value (int key) const;

private:
    static const char* keys[KeyIdMax];
    QSettings* m_Settings;
};


#endif // FILECATEGORY_H

