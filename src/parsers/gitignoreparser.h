#ifndef GITIGNOREPARSER_H
#define GITIGNOREPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class GitIgnoreParser : public BaseParser
{
    Q_OBJECT

public:
    explicit GitIgnoreParser(QObject *parent = nullptr);
    ~GitIgnoreParser();

    QString singlelineComment() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // GITIGNOREPARSER_H
