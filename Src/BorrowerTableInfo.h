#ifndef TABLEINFO_H
#define TABLEINFO_H

#include <QString>
#include <QMap>
#include "AbstractFilterWidget.h"

class BorrowerTableInfo
{
public:
    BorrowerTableInfo();
    ~BorrowerTableInfo();

    QList<int> getIds() const;
    QStringList getNames() const;
    QStringList getAliases() const;

    QMap<int, QString> getIdNameMap() const;
    QMap<QString, QString> getNameAliasMap() const;
    QMap<QString, QString> getNameTypeMap() const;


    const QString tableName;

    const int idFieldID;
    const int nameFieldID;
    const int surnameFieldID;
    const int patronymicFieldID;
    const int photoFieldID;
    const int activityFieldID;
    const int loanGuaranteeFieldID;
    const int belongingFieldID;
    const int amountFieldID;
    const int regionFieldID;
    const int placeFieldID;
    const int contactFieldID;

    const QString idFieldAlias;
    const QString nameFieldAlias;
    const QString surnameFieldAlias;
    const QString patronymicFieldAlias;
    const QString photoFieldAlias;
    const QString activityFieldAlias;
    const QString loanGuaranteeFieldAlias;
    const QString belongingFieldAlias;
    const QString amountFieldAlias;
    const QString regionFieldAlias;
    const QString placeFieldAlias;
    const QString contactFieldAlias;

    const QString idFieldName;
    const QString nameFieldName;
    const QString surnameFieldName;
    const QString patronymicFieldName;
    const QString photoFieldName;
    const QString activityFieldName;
    const QString loanGuaranteeFieldName;
    const QString belongingFieldName;
    const QString amountFieldName;
    const QString regionFieldName;
    const QString placeFieldName;
    const QString contactFieldName;

    const QString textType;
    const QString integerType;

private:
    QMap<int, QString> idNameMap;
    QMap<QString, QString> nameAliasMap;
    QMap<QString, QString> nameTypeMap;
};

#endif // TABLEINFO_H
