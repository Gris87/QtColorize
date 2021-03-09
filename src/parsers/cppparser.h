#ifndef CPPPARSER_H
#define CPPPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class CppParser : public BaseParser
{
    Q_OBJECT

public:
    explicit CppParser(QObject *parent = nullptr);
    ~CppParser();

    QString singlelineComment() const override;
    QString multilineCommentBegin() const override;
    QString multilineCommentEnd() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // CPPPARSER_H
