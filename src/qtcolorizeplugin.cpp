#include "qtcolorizeplugin.h"

#include <QAction>
#include <QCoreApplication>
#include <QMenu>
#include <QTranslator>

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/icore.h>
#include <texteditor/texteditorconstants.h>

#include "src/parsers/asmparser.h"
#include "src/parsers/bashparser.h"
#include "src/parsers/cppparser.h"
#include "src/parsers/gitignoreparser.h"
#include "src/parsers/makefileparser.h"
#include "src/parsers/markdownparser.h"
#include "src/parsers/phpparser.h"
#include "src/parsers/proparser.h"
#include "src/parsers/qrcparser.h"
#include "src/parsers/sqlparser.h"
#include "src/parsers/tsparser.h"
#include "src/parsers/virtualboxparser.h"
#include "src/parsers/xmlparser.h"
#include "src/qtcolorizeconstants.h"
#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



QtColorizePlugin::QtColorizePlugin()
    : IPlugin()
    , mQtColorizeCore(nullptr)
{
    COLORIZE_LOG(("QtColorizePlugin::QtColorizePlugin()"));
}

QtColorizePlugin::~QtColorizePlugin()
{
    COLORIZE_LOG(("QtColorizePlugin::~QtColorizePlugin()"));
}

bool QtColorizePlugin::initialize(const QStringList &arguments, QString *errorString)
{
    COLORIZE_LOG(("QtColorizePlugin::initialize(arguments = {%s}, errorString = \"%s\")", arguments.join(", ").toUtf8().constData(), errorString->toUtf8().constData()));



    Q_UNUSED(arguments)
    Q_UNUSED(errorString)



    mQtColorizeCore = new QtColorizeCore(this);



    // Create menu
    {
        Core::Context textContext(TextEditor::Constants::C_TEXTEDITOR);



        QAction *actionToggleColor = new QAction(tr("Toggle color between green/empty"), this);
        QAction *actionColorGreen  = new QAction(tr("Color to green"), this);
        QAction *actionColorRed    = new QAction(tr("Color to red"), this);
        QAction *actionRemoveColor = new QAction(tr("Remove color"), this);

        Core::Command *cmdToggle = Core::ActionManager::registerAction(actionToggleColor, Constants::ACTION_TOGGLE_ID, textContext);
        Core::Command *cmdGreen  = Core::ActionManager::registerAction(actionColorGreen,  Constants::ACTION_GREEN_ID,  textContext);
        Core::Command *cmdRed    = Core::ActionManager::registerAction(actionColorRed,    Constants::ACTION_RED_ID,    textContext);
        Core::Command *cmdRemove = Core::ActionManager::registerAction(actionRemoveColor, Constants::ACTION_REMOVE_ID, textContext);

        cmdToggle->setDefaultKeySequence(QKeySequence("Ctrl+Shift+Space"));
        cmdGreen->setDefaultKeySequence(QKeySequence("Ctrl+Alt+G"));
        cmdRed->setDefaultKeySequence(QKeySequence("Ctrl+Alt+R"));
        cmdRemove->setDefaultKeySequence(QKeySequence("Ctrl+Alt+E"));

        connect(actionToggleColor, SIGNAL(triggered()), mQtColorizeCore, SLOT(toggleColor()));
        connect(actionColorGreen,  SIGNAL(triggered()), mQtColorizeCore, SLOT(colorGreen()));
        connect(actionColorRed,    SIGNAL(triggered()), mQtColorizeCore, SLOT(colorRed()));
        connect(actionRemoveColor, SIGNAL(triggered()), mQtColorizeCore, SLOT(removeColor()));

        connect(mQtColorizeCore, SIGNAL(pluginSupported(bool)), actionToggleColor, SLOT(setEnabled(bool)));
        connect(mQtColorizeCore, SIGNAL(pluginSupported(bool)), actionColorGreen,  SLOT(setEnabled(bool)));
        connect(mQtColorizeCore, SIGNAL(pluginSupported(bool)), actionColorRed,    SLOT(setEnabled(bool)));
        connect(mQtColorizeCore, SIGNAL(pluginSupported(bool)), actionRemoveColor, SLOT(setEnabled(bool)));



        Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
        menu->menu()->setTitle(tr("Colorize"));
        menu->addAction(cmdToggle);
        menu->addAction(cmdGreen);
        menu->addAction(cmdRed);
        menu->addAction(cmdRemove);
        Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);



        Core::ActionContainer *contextMenu = Core::ActionManager::createMenu(Constants::CONTEXT_MENU_ID);
        contextMenu->menu()->setTitle(tr("Colorize"));
        contextMenu->addAction(cmdToggle);
        contextMenu->addAction(cmdGreen);
        contextMenu->addAction(cmdRed);
        contextMenu->addAction(cmdRemove);
        Core::ActionManager::actionContainer(TextEditor::Constants::M_STANDARDCONTEXTMENU)->addMenu(contextMenu);
    }



    // Create parsers
    {
        AsmParser        *asmParser        = new AsmParser(this);
        BashParser       *bashParser       = new BashParser(this);
        CppParser        *cppParser        = new CppParser(this);
        GitIgnoreParser  *gitIgnoreParser  = new GitIgnoreParser(this);
        MakefileParser   *makefileParser   = new MakefileParser(this);
        MarkdownParser   *markdownParser   = new MarkdownParser(this);
        PhpParser        *phpParser        = new PhpParser(this);
        ProParser        *proParser        = new ProParser(this);
        QrcParser        *qrcParser        = new QrcParser(this);
        SqlParser        *sqlParser        = new SqlParser(this);
        TsParser         *tsParser         = new TsParser(this);
        VirtualBoxParser *virtualBoxParser = new VirtualBoxParser(this);
        XmlParser        *xmlParser        = new XmlParser(this);

        mQtColorizeCore->addParser(cppParser);
        mQtColorizeCore->addParser(asmParser);
        mQtColorizeCore->addParser(markdownParser);
        mQtColorizeCore->addParser(bashParser);
        mQtColorizeCore->addParser(gitIgnoreParser);
        mQtColorizeCore->addParser(proParser);
        mQtColorizeCore->addParser(phpParser);
        mQtColorizeCore->addParser(qrcParser);
        mQtColorizeCore->addParser(tsParser);
        mQtColorizeCore->addParser(makefileParser);
        mQtColorizeCore->addParser(sqlParser);
        mQtColorizeCore->addParser(virtualBoxParser);
        mQtColorizeCore->addParser(xmlParser);
    }



    initLanguage();



    return true;
}

void QtColorizePlugin::initLanguage()
{
    COLORIZE_LOG(("QtColorizePlugin::initLanguage()"));



    const QString &language = Core::ICore::userInterfaceLanguage();

    if (language != "")
    {
        const QString &trFile     = "QtColorize_" + language;
        QTranslator   *translator = new QTranslator(this);



        QStringList paths;

        paths.append(Core::ICore::resourcePath().toString());
        paths.append(Core::ICore::userResourcePath().toString());

        for (qint64 i = 0; i < paths.size(); ++i)
        {
            if (translator->load(trFile, paths.at(i) + "/translations"))
            {
                qApp->installTranslator(translator);

                return;;
            }
        }



        delete translator;
    }
}
