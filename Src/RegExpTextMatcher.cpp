#include "RegExpTextMatcher.h"

RegExpTextMatcher::RegExpTextMatcher(const QRegExp &regExp) :
    regExp(regExp)
{
}

RegExpTextMatcher::~RegExpTextMatcher()
{
}

bool RegExpTextMatcher::isTextMatch(const QString& text)
{
    return regExp.exactMatch(text);
}
