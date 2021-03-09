#ifndef QTCOLORIZEUTILS_H
#define QTCOLORIZEUTILS_H




#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class QtColorizeUtils
{
public:
    static QString regexpPattern(BaseParser *parser);
    static QString commentPattern(BaseParser *parser);
};



} // namespace Internal
} // namespace QtColorize



#endif // QTCOLORIZEUTILS_H
