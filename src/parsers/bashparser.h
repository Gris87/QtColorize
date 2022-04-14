#ifndef BASHPARSER_H
#define BASHPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class BashParser : public BaseParser
{
    Q_OBJECT

public:
    explicit BashParser(QObject *parent = nullptr);
    ~BashParser();

    QString singlelineComment() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // BASHPARSER_H
