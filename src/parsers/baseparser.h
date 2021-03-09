#ifndef BASEPARSER_H
#define BASEPARSER_H



#include <QObject>

#include <texteditor/texteditor.h>



namespace QtColorize
{
namespace Internal
{



class BaseParser : public QObject
{
    Q_OBJECT

public:
    explicit BaseParser(QObject *parent = nullptr);
    ~BaseParser();

    virtual QString singlelineComment() const;
    virtual QString multilineCommentBegin() const;
    virtual QString multilineCommentEnd() const;
    virtual bool isValidFileExtension(const QString &filePath) const;
};



} // namespace Internal
} // namespace QtColorize



#endif // BASEPARSER_H
