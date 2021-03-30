#ifndef MANIFESTPARSER_H
#define MANIFESTPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class ManifestParser : public BaseParser
{
    Q_OBJECT

public:
    explicit ManifestParser(QObject *parent = nullptr);
    ~ManifestParser();

    QString multilineCommentBegin() const override;
    QString multilineCommentEnd() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // MANIFESTPARSER_H
