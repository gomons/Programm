#include "BorrowerTableInfo.h"
#include "TextFilterWidget.h"

BorrowerTableInfo::BorrowerTableInfo() :
    tableName("borrower"),

    idFieldID(0),
    nameFieldID(1),
    surnameFieldID(2),
    patronymicFieldID(3),
    photoFieldID(4),
    activityFieldID(5),
    loanGuaranteeFieldID(6),
    belongingFieldID(7),
    amountFieldID(8),
    regionFieldID(9),
    placeFieldID(10),
    contactFieldID(11),

    idFieldAlias(QObject::tr("ID")),
    nameFieldAlias(QObject::tr("Name")),
    surnameFieldAlias(QObject::tr("Surname")),
    patronymicFieldAlias(QObject::tr("Patronymic")),
    photoFieldAlias(QObject::tr("Photo")),
    activityFieldAlias(QObject::tr("Activity")),
    loanGuaranteeFieldAlias(QObject::tr("Loan guarantee")),
    belongingFieldAlias(QObject::tr("Belonging")),
    amountFieldAlias(QObject::tr("Amount")),
    regionFieldAlias(QObject::tr("Region")),
    placeFieldAlias(QObject::tr("Place")),
    contactFieldAlias(QObject::tr("Contact")),

    idFieldName("id"),
    nameFieldName("name"),
    surnameFieldName("surname"),
    patronymicFieldName("patronymic"),
    photoFieldName("photo"),
    activityFieldName("activity"),
    loanGuaranteeFieldName("loan_guarantee"),
    belongingFieldName("belonging_id"),
    amountFieldName("amount"),
    regionFieldName("region_id"),
    placeFieldName("place"),
    contactFieldName("contact"),

    textType("TEXT"),
    integerType("INTEGER")
{
    idNameMap.insert(idFieldID, idFieldName);
    idNameMap.insert(nameFieldID, nameFieldName);
    idNameMap.insert(surnameFieldID, surnameFieldName);
    idNameMap.insert(patronymicFieldID, patronymicFieldName);
    idNameMap.insert(photoFieldID, photoFieldName);
    idNameMap.insert(activityFieldID, activityFieldName);
    idNameMap.insert(loanGuaranteeFieldID, loanGuaranteeFieldName);
    idNameMap.insert(belongingFieldID, belongingFieldName);
    idNameMap.insert(amountFieldID, amountFieldName);
    idNameMap.insert(regionFieldID, regionFieldName);
    idNameMap.insert(placeFieldID, placeFieldName);
    idNameMap.insert(contactFieldID, contactFieldName);

    nameAliasMap.insert(idFieldName, idFieldAlias);
    nameAliasMap.insert(nameFieldName, nameFieldAlias);
    nameAliasMap.insert(surnameFieldName, surnameFieldAlias);
    nameAliasMap.insert(patronymicFieldName, patronymicFieldAlias);
    nameAliasMap.insert(photoFieldName, photoFieldAlias);
    nameAliasMap.insert(activityFieldName, activityFieldAlias);
    nameAliasMap.insert(loanGuaranteeFieldName, loanGuaranteeFieldAlias);
    nameAliasMap.insert(belongingFieldName, belongingFieldAlias);
    nameAliasMap.insert(amountFieldName, amountFieldAlias);
    nameAliasMap.insert(regionFieldName, regionFieldAlias);
    nameAliasMap.insert(placeFieldName, placeFieldAlias);
    nameAliasMap.insert(contactFieldName, contactFieldAlias);

    nameTypeMap.insert(idFieldName, integerType);
    nameTypeMap.insert(nameFieldName, textType);
    nameTypeMap.insert(surnameFieldName, textType);
    nameTypeMap.insert(patronymicFieldName, textType);
    nameTypeMap.insert(photoFieldName, textType);
    nameTypeMap.insert(activityFieldName, textType);
    nameTypeMap.insert(loanGuaranteeFieldName, textType);
    nameTypeMap.insert(belongingFieldName, textType);
    nameTypeMap.insert(amountFieldName, integerType);
    nameTypeMap.insert(regionFieldName, textType);
    nameTypeMap.insert(placeFieldName, textType);
    nameTypeMap.insert(contactFieldName, textType);
}

BorrowerTableInfo::~BorrowerTableInfo()
{
}

QList<int> BorrowerTableInfo::getIds() const
{
    return idNameMap.keys();
}

QStringList BorrowerTableInfo::getNames() const
{
    return idNameMap.values();
}

QStringList BorrowerTableInfo::getAliases() const
{
    return nameAliasMap.values();
}

QMap<int, QString> BorrowerTableInfo::getIdNameMap() const
{
    return idNameMap;
}

QMap<QString, QString> BorrowerTableInfo::getNameAliasMap() const
{
    return nameAliasMap;
}

QMap<QString, QString> BorrowerTableInfo::getNameTypeMap() const
{
    return nameTypeMap;
}
