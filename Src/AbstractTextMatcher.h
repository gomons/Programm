#ifndef ABSTRACTTEXTMATCHER
#define ABSTRACTTEXTMATCHER

#include <QString>

class AbstractTextMatcher
{
public:
    ~AbstractTextMatcher() {}

    virtual bool isTextMatch(const QString& text) = 0;
};

#endif // ABSTRACTTEXTMATCHER

