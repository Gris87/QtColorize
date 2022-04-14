#ifndef XMLPARSER_H
#define XMLPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class XmlParser : public BaseParser
{
    Q_OBJECT

public:
    explicit XmlParser(QObject *parent = nullptr);
    ~XmlParser();

    QString multilineCommentBegin() const override;
    QString multilineCommentEnd() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // XMLPARSER_H
