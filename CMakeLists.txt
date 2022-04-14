cmake_minimum_required(VERSION 3.16)

project(QtColorize LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)

find_package(QtCreator COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Widgets LinguistTools REQUIRED)
set(QtX Qt${QT_VERSION_MAJOR})

add_qtc_plugin(QtColorize
  PLUGIN_DEPENDS
    QtCreator::Core
    QtCreator::TextEditor
  DEPENDS
    ${QtX}::Widgets
    QtCreator::ExtensionSystem
    QtCreator::Utils
  SOURCES
    .github/workflows/build.yaml
    .gitignore
    QtColorize.json.in
    README.md
    Resources.qrc
    screenshot.png
)

extend_qtc_plugin(QtColorize
  SOURCES_PREFIX src
  SOURCES
    qtcolorizecore.cpp
    qtcolorizecore.h
    qtcolorizecoreoptionspage.cpp
    qtcolorizecoreoptionspage.h
    qtcolorizecoreoptionswidget.cpp
    qtcolorizecoreoptionswidget.h
    qtcolorizecoreoptionswidget.ui
    qtcolorizecoresettings.cpp
    qtcolorizecoresettings.h
    qtcolorizeconstants.h
    qtcolorizefuture.cpp
    qtcolorizefuture.h
    qtcolorizelog.h
    qtcolorizeplugin.cpp
    qtcolorizeplugin.h
    qtcolorizerowtype.h
    qtcolorizeutils.cpp
    qtcolorizeutils.h
)

extend_qtc_plugin(QtColorize
  SOURCES_PREFIX src/parsers
  SOURCES
    asmparser.cpp
    asmparser.h
    baseparser.cpp
    baseparser.h
    bashparser.cpp
    bashparser.h
    cppparser.cpp
    cppparser.h
    gitignoreparser.cpp
    gitignoreparser.h
    makefileparser.cpp
    makefileparser.h
    markdownparser.cpp
    markdownparser.h
    phpparser.cpp
    phpparser.h
    proparser.cpp
    proparser.h
    qrcparser.cpp
    qrcparser.h
    sqlparser.cpp
    sqlparser.h
    tsparser.cpp
    tsparser.h
    virtualboxparser.cpp
    virtualboxparser.h
    xmlparser.cpp
    xmlparser.h
)

set(TRANSLATION_FILES
    translation/QtColorize_en_US.ts
    translation/QtColorize_ru.ts
)

qt_add_lupdate(QtColorize TS_FILES ${TRANSLATION_FILES})
qt_add_lrelease(QtColorize
    TS_FILES ${TRANSLATION_FILES}
    QM_FILES_OUTPUT_VARIABLE qm_files)
