#include "IntRangeTextMatcher.h"

IntRangeTextMatcher::IntRangeTextMatcher(int gt, int lt) :
    from(gt), to(lt)
{
}

IntRangeTextMatcher::~IntRangeTextMatcher()
{
}

bool IntRangeTextMatcher::isTextMatch(const QString& text)
{
    int value = text.toInt();

    if (value >= from && value <= to)
        return true;
    else
        return false;
}
