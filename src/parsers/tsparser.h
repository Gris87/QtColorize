#ifndef TSPARSER_H
#define TSPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class TsParser : public BaseParser
{
    Q_OBJECT

public:
    explicit TsParser(QObject *parent = nullptr);
    ~TsParser();

    QString multilineCommentBegin() const override;
    QString multilineCommentEnd() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // TSPARSER_H
