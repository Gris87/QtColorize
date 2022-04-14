#include "qtcolorizecore.h"

#include <QMessageBox>

#include <coreplugin/icore.h>
#include <utils/runextensions.h>

#include "src/qtcolorizeconstants.h"
#include "src/qtcolorizelog.h"
#include "src/qtcolorizeutils.h"



#define CHANGE_TIMER_INTERVAL 1000



using namespace QtColorize::Internal;



QtColorizeCore *QtColorizeCore::sInstance = nullptr;



QtColorizeCore::QtColorizeCore(QObject *parent)
    : QObject(parent)
    , mParsers()
    , mCurrentParser(nullptr)
    , mCurrentEditor(nullptr)
    , mQtColorizeCoreOptionsPage(nullptr)
    , mQtColorizeCoreSettings(nullptr)
    , mChangeTimer(nullptr)
    , mFuture(nullptr)
    , mFutureWatcher(nullptr)
    , mParsedRows()
{
    COLORIZE_LOG(("QtColorizeCore::QtColorizeCore(parent = %p)", parent));



    Q_ASSERT(sInstance == nullptr);
    sInstance = this;



    mQtColorizeCoreSettings = new QtColorizeCoreSettings(this);
    mQtColorizeCoreSettings->loadFromSettings(Core::ICore::settings());

    connect(mQtColorizeCoreSettings, SIGNAL(settingsChanged()), this, SLOT(settingsChanged()));



    mQtColorizeCoreOptionsPage = new QtColorizeCoreOptionsPage(mQtColorizeCoreSettings, this);



    Core::EditorManager *editorManager = Core::EditorManager::instance();

    connect(editorManager, SIGNAL(editorOpened(Core::IEditor *)),         this, SLOT(editorOpened(Core::IEditor *)));
    connect(editorManager, SIGNAL(currentEditorChanged(Core::IEditor *)), this, SLOT(managerEditorChanged(Core::IEditor *)));



    mChangeTimer = new QTimer(this);

    connect(mChangeTimer, SIGNAL(timeout()), this, SLOT(changeTimerTicked()));
}

QtColorizeCore::~QtColorizeCore()
{
    COLORIZE_LOG(("QtColorizeCore::~QtColorizeCore()"));



    mQtColorizeCoreSettings->saveToSettings(Core::ICore::settings());

    mChangeTimer->stop();
    cancelFuture();



    sInstance = nullptr;
}

QtColorizeCore* QtColorizeCore::instance()
{
    COLORIZE_LOG(("QtColorizeCore::instance()"));



    return sInstance;
}

void QtColorizeCore::addParser(BaseParser *parser)
{
    COLORIZE_LOG(("QtColorizeCore::addParser(parser = %p)", parser));



    mParsers.append(parser);
}

void QtColorizeCore::setCurrentParser(BaseParser *parser)
{
    COLORIZE_LOG(("QtColorizeCore::setCurrentParser(parser = %p)", parser));



    mCurrentParser = parser;
}

void QtColorizeCore::setCurrentEditor(TextEditor::BaseTextEditor *editor)
{
    COLORIZE_LOG(("QtColorizeCore::setCurrentEditor(editor = %p)", editor));



    if (mCurrentEditor != nullptr)
    {
        mChangeTimer->stop();
        cancelFuture();
    }



    mCurrentEditor = editor;



    if (mCurrentEditor != nullptr)
    {
        startFuture();
    }



    COLORIZE_LOG(("emit pluginSupported(%s)", mCurrentEditor != nullptr ? "true" : "false"));
    emit pluginSupported(mCurrentEditor != nullptr);
}

void QtColorizeCore::toggleColor()
{
    COLORIZE_LOG(("QtColorizeCore::toggleColor()"));



    updateSelectedRows(QtColorizeRowType::GREEN, true);
}

void QtColorizeCore::colorGreen()
{
    COLORIZE_LOG(("QtColorizeCore::colorGreen()"));



    updateSelectedRows(QtColorizeRowType::GREEN);
}

void QtColorizeCore::colorRed()
{
    COLORIZE_LOG(("QtColorizeCore::colorRed()"));



    updateSelectedRows(QtColorizeRowType::RED);
}

void QtColorizeCore::removeColor()
{
    COLORIZE_LOG(("QtColorizeCore::removeColor()"));



    updateSelectedRows(QtColorizeRowType::NONE);
}

void QtColorizeCore::settingsChanged()
{
    COLORIZE_LOG(("QtColorizeCore::settingsChanged()"));



    if (mCurrentEditor != nullptr)
    {
        updateRows();
    }
}

void QtColorizeCore::editorOpened(Core::IEditor *editor)
{
    COLORIZE_LOG(("QtColorizeCore::editorOpened(editor = %p)", editor));



    TextEditor::BaseTextEditor *textEditor = qobject_cast<TextEditor::BaseTextEditor *>(editor);

    if (textEditor != nullptr)
    {
        connect(textEditor->editorWidget()->document(), SIGNAL(contentsChanged()), this, SLOT(contentsChanged()));
    }
    else
    {
        COLORIZE_LOG(("textEditor is null"));
    }
}

void QtColorizeCore::managerEditorChanged(Core::IEditor *editor)
{
    COLORIZE_LOG(("QtColorizeCore::managerEditorChanged(editor = %p)", editor));



    BaseParser                 *selectedParser     = nullptr;
    TextEditor::BaseTextEditor *selectedTextEditor = nullptr;



    TextEditor::BaseTextEditor *textEditor = qobject_cast<TextEditor::BaseTextEditor *>(editor);

    if (textEditor != nullptr)
    {
        QString filePath = editor->document()->filePath().toString();

        for (qint64 i = 0; i < mParsers.size(); ++i)
        {
            BaseParser *parser = mParsers.at(i);

            if (parser->isValidFileExtension(filePath))
            {
                selectedParser     = parser;
                selectedTextEditor = textEditor;

                break;
            }
        }
    }
    else
    {
        COLORIZE_LOG(("textEditor is null"));
    }



    setCurrentParser(selectedParser);
    setCurrentEditor(selectedTextEditor);
}

void QtColorizeCore::contentsChanged()
{
    COLORIZE_LOG(("QtColorizeCore::contentsChanged()"));



    mChangeTimer->stop();
    mChangeTimer->start(CHANGE_TIMER_INTERVAL);
}

void QtColorizeCore::changeTimerTicked()
{
    COLORIZE_LOG(("QtColorizeCore::changeTimerTicked()"));



    mChangeTimer->stop();
    cancelFuture();
    startFuture();
}

void QtColorizeCore::futureFinished()
{
    COLORIZE_LOG(("QtColorizeCore::futureFinished()"));



    mParsedRows = mFutureWatcher->result();
    updateRows();



    delete mFuture;
    delete mFutureWatcher;

    mFuture        = nullptr;
    mFutureWatcher = nullptr;
}

void QtColorizeCore::updateSelectedRows(QtColorizeRowType type, bool toggle)
{
    COLORIZE_LOG(("QtColorizeCore::updateSelectedRows(type = %llu, toggle = %s)", (quint64)type, toggle ? "true" : "false"));



    QRegularExpression regexp(QtColorizeUtils::regexpPattern(mCurrentParser));



    TextEditor::TextEditorWidget *editorWidget = mCurrentEditor->editorWidget();
    QTextCursor                   cursor       = editorWidget->textCursor();

    qint64 initialPosition = cursor.position();
    qint64 selectionStart  = cursor.selectionStart();
    qint64 selectionEnd    = cursor.selectionEnd();

    cursor.setPosition(selectionEnd);
    QTextBlock endBlock         = cursor.block();
    qint64     endLine          = cursor.blockNumber();
    qint64     endBlockPosition = endBlock.position();

    cursor.setPosition(selectionStart);
    QTextBlock startBlock         = cursor.block();
    qint64     startLine          = cursor.blockNumber();
    qint64     startBlockPosition = startBlock.position();

    if (
        endLine > startLine
        &&
        endBlockPosition >= selectionEnd
       )
    {
        --endLine;
    }



    if (toggle)
    {
        type = QtColorizeRowType::NONE;



        QTextBlock block = startBlock;

        for (qint64 i = startLine; i <= endLine && block.isValid(); ++i, block = block.next())
        {
            QRegularExpressionMatch match = regexp.match(block.text());

            if (match.hasMatch())
            {
                QString color = match.captured(1);

                if (color == "green")
                {
                    // Nothing
                }
                else
                if (color == "red")
                {
                    type = QtColorizeRowType::GREEN;
                    break;
                }
                else
                {
                    type = QtColorizeRowType::GREEN;
                    break;
                }
            }
            else
            {
                type = QtColorizeRowType::GREEN;
                break;
            }
        }
    }



    QString colorText;

    switch (type)
    {
        case QtColorizeRowType::NONE:
        {
            // Nothing
        }
        break;

        case QtColorizeRowType::GREEN:
        {
            colorText = QtColorizeUtils::commentPattern(mCurrentParser).arg("green");
        }
        break;

        case QtColorizeRowType::RED:
        {
            colorText = QtColorizeUtils::commentPattern(mCurrentParser).arg("red");
        }
        break;

        default:
        {
            COLORIZE_LOG(("Unknown row type: %llu", (quint64)type));
        }
        break;
    }



    bool changed = false;

    QTextBlock block = startBlock;

    for (qint64 i = startLine; i <= endLine && block.isValid(); ++i, block = block.next())
    {
        QString blockTextOriginal = block.text();
        QString blockText         = blockTextOriginal;



        QRegularExpressionMatch match = regexp.match(blockText);

        if (match.hasMatch())
        {
            blockText.remove(match.capturedStart(), match.capturedLength());
        }

        if (colorText != "")
        {
            if (blockText.length() < mQtColorizeCoreSettings->alignment)
            {
                blockText.append(QString(mQtColorizeCoreSettings->alignment - blockText.length(), QChar(' ')));
            }

            blockText.append(colorText);
        }



        qint64 blockTextLength         = blockText.length();
        qint64 blockTextOriginalLength = blockTextOriginal.length();

        qint64 lastMatchedSymbol = 0;

        while (
               lastMatchedSymbol < blockTextLength
               &&
               lastMatchedSymbol < blockTextOriginalLength
               &&
               blockText.at(lastMatchedSymbol) == blockTextOriginal.at(lastMatchedSymbol)
              )
        {
            ++lastMatchedSymbol;
        }



        if (
            lastMatchedSymbol != blockTextLength
            ||
            lastMatchedSymbol != blockTextOriginalLength
           )
        {
            cursor.setPosition(block.position() + lastMatchedSymbol);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
            cursor.removeSelectedText();
            cursor.insertText(blockText.mid(lastMatchedSymbol));

            mParsedRows[i] = type;
            changed        = true;
        }
    }



    if (changed)
    {
        if (
            selectionEnd > selectionStart
            &&
            endBlockPosition >= selectionEnd
           )
        {
            endBlock = endBlock.next();
        }



        qint64 positionInStartBlock = selectionStart - startBlockPosition;
        qint64 positionInEndBlock   = selectionEnd   - endBlockPosition;
        qint64 startBlockLength     = startBlock.text().length();
        qint64 endBlockLength       = endBlock.text().length();



        if (positionInStartBlock > startBlockLength)
        {
            positionInStartBlock = startBlockLength;
        }

        if (positionInEndBlock > endBlockLength)
        {
            positionInEndBlock = endBlockLength;
        }



        if (initialPosition == selectionEnd)
        {
            cursor.setPosition(startBlock.position() + positionInStartBlock);
            cursor.setPosition(endBlock.position()   + positionInEndBlock, QTextCursor::KeepAnchor);
        }
        else
        {
            cursor.setPosition(endBlock.position()   + positionInEndBlock);
            cursor.setPosition(startBlock.position() + positionInStartBlock, QTextCursor::KeepAnchor);
        }

        editorWidget->setTextCursor(cursor);



        updateRows();
    }
}

void QtColorizeCore::cancelFuture()
{
    COLORIZE_LOG(("QtColorizeCore::cancelFuture()"));



    if (mFuture != nullptr)
    {
        Q_ASSERT(mFutureWatcher != nullptr);

        mFutureWatcher->cancel();
        mFutureWatcher->waitForFinished();

        delete mFuture;
        delete mFutureWatcher;

        mFuture        = nullptr;
        mFutureWatcher = nullptr;
    }
}

void QtColorizeCore::startFuture()
{
    COLORIZE_LOG(("QtColorizeCore::startFuture()"));



    Q_ASSERT(mFuture        == nullptr);
    Q_ASSERT(mFutureWatcher == nullptr);

    mFuture        = new QtColorizeFuture(mCurrentParser, mCurrentEditor, this);
    mFutureWatcher = new QFutureWatcher<QList<QtColorizeRowType>>(this);

    connect(mFutureWatcher, SIGNAL(finished()), this, SLOT(futureFinished()));

    QFuture<QList<QtColorizeRowType>> future = Utils::runAsync(QThread::HighPriority, &QtColorizeFuture::process, mFuture);
    mFutureWatcher->setFuture(future);
}

void QtColorizeCore::updateRows()
{
    COLORIZE_LOG(("QtColorizeCore::updateRows()"));



    QList<QTextEdit::ExtraSelection> selections;
    selections.reserve(mParsedRows.size());



    TextEditor::TextEditorWidget *editorWidget = mCurrentEditor->editorWidget();
    QTextBlock                    block        = editorWidget->document()->firstBlock();

    for (qint64 i = 0; i < mParsedRows.size() && block.isValid(); ++i, block = block.next())
    {
        switch (mParsedRows.at(i))
        {
            case QtColorizeRowType::NONE:
            {
                // Nothing
            }
            break;

            case QtColorizeRowType::GREEN:
            {
                QTextCursor cursor(block);

                cursor.movePosition(QTextCursor::StartOfBlock);
                cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

                QTextCharFormat format = cursor.charFormat();
                format.setBackground(QColor(mQtColorizeCoreSettings->greenColor));

                QTextEdit::ExtraSelection selection;
                selection.cursor = cursor;
                selection.format = format;
                selections.append(selection);
            }
            break;

            case QtColorizeRowType::RED:
            {
                QTextCursor cursor(block);

                cursor.movePosition(QTextCursor::StartOfBlock);
                cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

                QTextCharFormat format = cursor.charFormat();
                format.setBackground(QColor(mQtColorizeCoreSettings->redColor));

                QTextEdit::ExtraSelection selection;
                selection.cursor = cursor;
                selection.format = format;
                selections.append(selection);
            }
            break;

            default:
            {
                COLORIZE_LOG(("Unknown row type: %llu", (quint64)mParsedRows.at(i)));
            }
            break;
        }
    }



    editorWidget->setExtraSelections(Utils::Id(QtColorize::Constants::QTCOLORIZE_ROW_ID), selections);
}
