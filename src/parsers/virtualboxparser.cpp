#include "virtualboxparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



VirtualBoxParser::VirtualBoxParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("VirtualBoxParser::VirtualBoxParser(parent = %p)", parent));
}

VirtualBoxParser::~VirtualBoxParser()
{
    COLORIZE_LOG(("VirtualBoxParser::~VirtualBoxParser()"));
}

QString VirtualBoxParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("VirtualBoxParser::multilineCommentBegin()"));



    return "<!--";
}

QString VirtualBoxParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("VirtualBoxParser::multilineCommentEnd()"));



    return "-->";
}

bool VirtualBoxParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("VirtualBoxParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".vbox");
}
