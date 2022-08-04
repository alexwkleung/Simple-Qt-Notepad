#include "notepad.h"
#include "./ui_notepad.h"
#include <QString>
#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>
#include <QFontDialog>

//define Notepad constructor
Notepad::Notepad(QWidget *parent)
    //call QMainWindow constructor (base class for the Notepad class)
    : QMainWindow(parent)
    , ui(new Ui::Notepad) //creates a new Ui class instance on the heap and assigns it to the ui member
{
    ui->setupUi(this); //sets up ui
    setWindowTitle("Simple Notepad");
}

//deconstructor for Notepad
Notepad::~Notepad() {
    //delete ui from heap when finished
    delete ui;
}

//new document
void Notepad::on_actionNew_triggered() {
    //clear text buffer of currentFile QString (makes it null)
    this->currentFile.clear();

    //set window title when creating new document
    setWindowTitle("Simple Notepad");

    ui->textEdit->setText(QString()); //sets empty QString() into the buffer of the Ui wdget textEdit
}


//open document
void Notepad::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file");

    //check if selected file name is empty
    if(fileName.isEmpty()) {
        return;
    }

    //file object of QFile contains file name as the parameter
    QFile file(fileName);

    //assign global variable currentFile (current selected file) to the file name
    this->currentFile = fileName;

    //open selected file as a read only text file
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        //if it cannot open current selected file, then it outputs a warning
        QMessageBox::warning(this, "Warning: ", "Cannot open file " + file.errorString());

        return;
    }

    //set window title as the opened file name
    setWindowTitle(fileName);

    //create a QTextStream named instream that takes a reference of the QFile file
    QTextStream instream(&file);

    //text (QString) is assigned the contents of instream (QTextStream)
    QString text = instream.readAll();

    //sets the contents of QString text into the buffer of the Ui widget textEdit (editor)
    ui->textEdit->setText(text);

    //closes the file and calls QFileDevice::flush() to flush buffered data
    file.close();
}

//save as document
void Notepad::on_actionSave_As_triggered() {
    //create QString extension
    QString fileExtension{};

    //create QString fileName
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", fileExtension = ".txt");

    if(fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    //open selected file as write only
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        //if selected file cannot be opened, then it outputs a warning
        QMessageBox::warning(this, "Warning: ", "Cannot save file " + file.errorString());

        return;
    }

    //set window title to file name
    setWindowTitle(fileName);

    //create QTextStream outstream that takes the reference of Qfile file
    QTextStream outstream(&file);

    //create QString text and assign it the content of the buffer of the Ui widget textEdit, which is converted into plain text for saving
    QString text = ui->textEdit->toPlainText();

    //append text QString to outstream
    outstream << text;

    //closes the file and calls QFileDevice::flush() to flush buffered data
    file.close();
}

//push button - open document
void Notepad::on_pushButton_Open_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file");

    if(fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    this->currentFile = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning: ", "Cannot open file " + file.errorString());

        return;
    }

    setWindowTitle(fileName);

    QTextStream instream(&file);

    QString text = instream.readAll();

    ui->textEdit->setText(text);

    file.close();
}

//push button - save as document
void Notepad::on_pushButton_Save_clicked() {
    QString fileExtension{};

    QString fileName = QFileDialog::getSaveFileName(this, "Save as", fileExtension = ".txt");

    if(fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning: ", "Cannot save file " + file.errorString());

        return;
    }

    setWindowTitle(fileName);

    QTextStream outstream(&file);

    QString text = ui->textEdit->toPlainText();

    outstream << text;

    file.close();
}

//push button - new document
void Notepad::on_pushButton_New_clicked()
{
    this->currentFile.clear();

    setWindowTitle("Simple Notepad");

    ui->textEdit->setText(QString());
}

//push button - fonts
void Notepad::on_pushButton_Fonts_clicked()
{
    //declare fontSelect which is a bool
    bool fontSelect{};

    //declare QFont object font that is assigned a QFontDialog widget containing fonts to select
    //getFont takes in the reference of fontSelect (bool) and the Notepad constructor
    QFont font = QFontDialog::getFont(&fontSelect, this);

    //if fontSelect is true (if we select a font), then the selected font will be added to the Ui widget textEdit buffer (editor)
    if(fontSelect) {
        ui->textEdit->setFont(font);
    }
}
