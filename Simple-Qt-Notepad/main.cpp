#include "notepad.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    //create a QApplication object.
    //constructs an object a, passing in command line arguments argc (argument count) and argv (argument vector).
    //it manages application-wide resources for a qt widgets based app
    QApplication a(argc, argv);

    //create object widgets from class Notepad.
    //class Notepad contains
    Notepad widgets;

    //widgets are not visible by default, so you must make it visible by calling the function from w object
    widgets.show();

    //returns an event loop from QApplication
    //when a qt application runs, events are sent to the widgets (i.e., keystokes, mouse clicks)
    return a.exec();
}
