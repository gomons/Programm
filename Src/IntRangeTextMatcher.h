#ifndef INTRANGETEXTMATCHER_H
#define INTRANGETEXTMATCHER_H

#include "AbstractTextMatcher.h"

class IntRangeTextMatcher: public AbstractTextMatcher
{
public:
    IntRangeTextMatcher(int from, int to);
    ~IntRangeTextMatcher();

    bool isTextMatch(const QString& text) override;

private:
    int from;
    int to;
};

#endif // INTRANGETEXTMATCHER_H
