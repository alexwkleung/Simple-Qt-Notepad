#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
//namespace Ui is the standard namespace for all ui classes generated by the uic tool
//forward declare class Notepad
namespace Ui {
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow {
    //Q_Object macro declares class as a QObject
    Q_OBJECT

public:
    //declares a Notepad constructor
    //it has a default argument called parent, which is a pointer
    //*parent is assigned a nullptr, meaning that the widget has no parent (top-level widget)
    explicit Notepad(QWidget *parent = nullptr);

    //declares a virtual deconstructor of Notepad to free the resources from the object
    //in QObject, the deconstructors are virtual so that the deconstructors of the derived classs are invoked properly
    //when an object is deleted through a pointer-to-base-class
    ~Notepad();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_pushButton_Open_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_New_clicked();

    void on_pushButton_Fonts_clicked();

private:
    //delcares a member which is a pointer to the Notepad Ui class
    Ui::Notepad *ui;

    //declares a QString named currentFile
    QString currentFile;
};
#endif // NOTEPAD_H
