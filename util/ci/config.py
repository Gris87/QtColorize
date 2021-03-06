from os import getenv, path

qt_version = "5.15.2"
qtc_version = "4.14.0"
os_name = getenv('OS', 'linux')
qt_dir = path.abspath('qt')
qt_modules = ['qtbase', 'qttools', 'icu']
plugin_name = 'QtColorize'
pro_file = path.abspath(path.dirname(__file__) + '/../../QtColorize.pro')
ts_files_dir = path.abspath(path.dirname(__file__) + '/../../translation')
