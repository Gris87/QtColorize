#ifndef VIRTUALBOXPARSER_H
#define VIRTUALBOXPARSER_H



#include "src/parsers/baseparser.h"



namespace QtColorize
{
namespace Internal
{



class VirtualBoxParser : public BaseParser
{
    Q_OBJECT

public:
    explicit VirtualBoxParser(QObject *parent = nullptr);
    ~VirtualBoxParser();

    QString multilineCommentBegin() const override;
    QString multilineCommentEnd() const override;
    bool isValidFileExtension(const QString &filePath) const override;
};



} // namespace Internal
} // namespace QtColorize



#endif // VIRTUALBOXPARSER_H
