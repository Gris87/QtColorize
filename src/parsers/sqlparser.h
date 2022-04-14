#ifndef SQLPARSER_H
#define SQLPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class SqlParser : public BaseParser
{
    Q_OBJECT

public:
    explicit SqlParser(QObject *parent = nullptr);
    ~SqlParser();

    QString singlelineComment() const override;
    QString multilineCommentBegin() const override;
    QString multilineCommentEnd() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // SQLPARSER_H
