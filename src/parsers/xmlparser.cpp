#include "xmlparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



XmlParser::XmlParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("XmlParser::XmlParser(parent = %p)", parent));
}

XmlParser::~XmlParser()
{
    COLORIZE_LOG(("XmlParser::~XmlParser()"));
}

QString XmlParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("XmlParser::multilineCommentBegin()"));



    return "<!--";
}

QString XmlParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("XmlParser::multilineCommentEnd()"));



    return "-->";
}

bool XmlParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("XmlParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".xml");
}
