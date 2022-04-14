#ifndef PHPPARSER_H
#define PHPPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class PhpParser : public BaseParser
{
    Q_OBJECT

public:
    explicit PhpParser(QObject *parent = nullptr);
    ~PhpParser();

    QString singlelineComment() const override;
    QString multilineCommentBegin() const override;
    QString multilineCommentEnd() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // PHPPARSER_H
