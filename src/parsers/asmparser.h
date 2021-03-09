#ifndef ASMPARSER_H
#define ASMPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class AsmParser : public BaseParser
{
    Q_OBJECT

public:
    explicit AsmParser(QObject *parent = nullptr);
    ~AsmParser();

    QString singlelineComment() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // ASMPARSER_H
