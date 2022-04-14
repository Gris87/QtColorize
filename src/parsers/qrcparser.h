#ifndef QRCPARSER_H
#define QRCPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class QrcParser : public BaseParser
{
    Q_OBJECT

public:
    explicit QrcParser(QObject *parent = nullptr);
    ~QrcParser();

    QString multilineCommentBegin() const override;
    QString multilineCommentEnd() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // QRCPARSER_H
