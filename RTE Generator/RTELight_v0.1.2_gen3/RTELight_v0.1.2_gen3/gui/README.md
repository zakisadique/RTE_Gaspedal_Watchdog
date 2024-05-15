### RTE Generator GUI

This application provides an easy to use GUI for the h_da RTE generator

This software requires python3 and the following modules to work:
- PySide2
- beautifulsoup4 
- lxml

To install them simpy run
```
python -m pip install -r requirements.txt
```

### Inner workings, maintenance, extensions

For easy maintainability, the GUI automatically generates Editor-Widgets from object definitions (see ```GUI/EditorWidget.py```). Python3 type annotations are to specify the types of data fields and other information like default values, data sources and value-mappings


| Key        | Function                                                                                                                          |
| ---------- | --------------------------------------------------------------------------------------------------------------------------------- |
| type       | type of the field (e.g. bool, float, int, str or "choice(\|editable)" for DropDown-Menu, "list(\|checkable)" for List of Entries) |
| default    | default value                                                                                                                     |
| valuemap   | mapping values for conversion (e.g. {True:"on",False:"off"})                                                                      |
| values     | list of values for DropDown-Menu                                                                                                  |
| joiner     | joiner for widgets which allow multiple selections (e.g. checkable lists)                                                         |
| value_from | value source for DropDown-Menu (e.g. "event.name" to use the "name" field from all entries in the "event" tab)                    |
| base       | base for integer values                                                                                                           |
| prefix     | prefix for integer values                                                                                                         |
| suffix     | suffix for integer values                                                                                                         |

The tabs within the MainWindow can be configured in ```tabs``` dictionary in the ```GUI/MainWindow.py``` file.

| Key      | Function                                          |
| -------- | ------------------------------------------------- |
| title    | title of the tab                                  |
| objname  | object name display in the "New {objname}" button |
| objtype  | object type (class)                               |
| mode     | list or editor                                    |
| datapath | datapath within the XML file (or None)            |


This project uses some external libraries

| Lib            | What it's good for             | Website                                  | Documentation                                                        |
| -------------- | ------------------------------ | ---------------------------------------- | -------------------------------------------------------------------- |
| PySide2        | GUI / Qt5 Bindings for Python3 | https://pypi.org/project/PySide2/        | https://doc.qt.io/qt-5/index.html (Python-API is basically the same) |
| LXML           | XML Parser, used by BS4        | -                                        | -                                                                    |
| beautifulsoup4 | HTML and XML parser            | https://pypi.org/project/beautifulsoup4/ | https://www.crummy.com/software/BeautifulSoup/bs4/doc/               |


