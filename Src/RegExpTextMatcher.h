#ifndef REGEXPTEXTMATCHER_H
#define REGEXPTEXTMATCHER_H

#include <QRegExp>
#include "AbstractTextMatcher.h"

class RegExpTextMatcher: public AbstractTextMatcher
{
public:
    RegExpTextMatcher(const QRegExp &regExp);
    ~RegExpTextMatcher();

    bool isTextMatch(const QString& text) override;

private:
    QRegExp regExp;
};

#endif // REGEXPTEXTMATCHER_H
