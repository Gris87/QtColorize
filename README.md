# Qt Creator colorize plugin

![Build status](https://github.com/Gris87/QtColorize/workflows/Plugin%20build/badge.svg)

## Introduction
Plugin allows to colorize your code lines with specific comments.

![Screen](screenshot.png?raw=true)

## Downloads
Binaries can be downloaded from [github releases](https://github.com/Gris87/QtColorize/releases).

## Installation
IMPORTANT: plugin's version must match Qt Creator's version (difference in last digit is acceptable)

### How to install from binaries
1. Extract/copy files from archive into Qt Creator's dir (archive already contains proper paths).
2. Enable the `QtColorize` plugin (Help -> About Plugins...)

### How to Build from binaries

Create a build directory and run

    cmake -DCMAKE_PREFIX_PATH=<path_to_qtcreator> -DCMAKE_BUILD_TYPE=RelWithDebInfo <path_to_plugin_source>
    cmake --build .

where `<path_to_qtcreator>` is the relative or absolute path to a Qt Creator build directory, or to a
combined binary and development package (Windows / Linux), or to the `Qt Creator.app/Contents/Resources/`
directory of a combined binary and development package (macOS), and `<path_to_plugin_source>` is the
relative or absolute path to this plugin directory.

### How to Run from sources

Run a compatible Qt Creator with the additional command line argument

    -pluginpath <path_to_plugin>

where `<path_to_plugin>` is the path to the resulting plugin library in the build directory
(`<plugin_build>/lib/qtcreator/plugins` on Windows and Linux,
`<plugin_build>/Qt Creator.app/Contents/PlugIns` on macOS).

You might want to add `-temporarycleansettings` (or `-tcs`) to ensure that the opened Qt Creator
instance cannot mess with your user-global Qt Creator settings.

When building and running the plugin from Qt Creator, you can use

    -pluginpath "%{buildDir}/lib/qtcreator/plugins" -tcs

on Windows and Linux, or

    -pluginpath "%{buildDir}/Qt Creator.app/Contents/PlugIns" -tcs

for the `Command line arguments` field in the run settings.
