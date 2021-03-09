CONFIG += c++17



DEFINES += \
    QTCOLORIZE_LIBRARY



RESOURCES += Resources.qrc



# Warnings as errors - BEGIN
win32-msvc* {
    QMAKE_CXXFLAGS += /WX
} else {
    QMAKE_CXXFLAGS += -Werror -Wno-address-of-packed-member -Wno-trigraphs
}
# Warnings as errors - END

# Release optimization - BEGIN
QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -O3

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
# Release optimization - END

# Target dirs - BEGIN
DESTDIR     = build/
OBJECTS_DIR = build/gen
MOC_DIR     = build/gen
RCC_DIR     = build/gen
UI_DIR      = build/gen
# Target dirs - END



INCLUDEPATH += .



include(src/src.pri)



TRANSLATIONS += \
    translation/QtColorize_en_US.ts \
    translation/QtColorize_ru.ts

OTHER_FILES += \
    .github/workflows/build.yml \
    .gitignore \
    QtColorize.json.in \
    README.md \
    util/ci/build.py \
    util/ci/common.py \
    util/ci/config.py \
    util/ci/get_qtc.py \
    util/ci/get_qt.py \
    util/screen.png



# Qt Creator linking
exists(QtColorize_local_paths.pri) {
    include(QtColorize_local_paths.pri)
}

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=$${LOCAL_QTCREATOR_SOURCES}

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=$${LOCAL_IDE_BUILD_TREE}



include(QtColorize_dependencies.pri)



!include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri) {
    error("Could not include QtCreator Plugin PRI File, make sure the correct paths are specified.")
}
