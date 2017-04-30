
QT += multimedia widgets

TEMPLATE = app
TARGET = project2
INCLUDEPATH += .

# Input
HEADERS += edge.h graphwidget.h node.h QMPButton.h \
    new_arbre.h
SOURCES += edge.cpp graphwidget.cpp main.cpp node.cpp QMPButton.cpp \
    new_arbre.cpp
RESOURCES += myresource.qrc
