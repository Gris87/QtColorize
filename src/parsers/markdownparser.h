#ifndef MARKDOWNPARSER_H
#define MARKDOWNPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class MarkdownParser : public BaseParser
{
    Q_OBJECT

public:
    explicit MarkdownParser(QObject *parent = nullptr);
    ~MarkdownParser();

    QString singlelineComment() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // MARKDOWNPARSER_H
