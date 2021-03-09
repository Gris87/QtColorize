#ifndef MAKEFILEPARSER_H
#define MAKEFILEPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class MakefileParser : public BaseParser
{
    Q_OBJECT

public:
    explicit MakefileParser(QObject *parent = nullptr);
    ~MakefileParser();

    QString singlelineComment() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // MAKEFILEPARSER_H
