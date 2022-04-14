#ifndef PROPARSER_H
#define PROPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class ProParser : public BaseParser
{
    Q_OBJECT

public:
    explicit ProParser(QObject *parent = nullptr);
    ~ProParser();

    QString singlelineComment() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // PROPARSER_H
