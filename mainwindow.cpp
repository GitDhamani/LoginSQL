#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employeeinfo.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //No Resize on Main Logon Window.
    setFixedSize(width(), height());

    //Add Login Image
    ui->loginLabel->setPixmap(QPixmap(":/Images/LoginLogo.png"));
    ui->loginLabel->setScaledContents(true);

    //Make Sure Password Entry is Obscured
    ui->password->setEchoMode(QLineEdit::Password);

    //Create Connection to SQLite Database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Users.db3"); //Must be in same Directory as .exe

    //Report Status of Database through Statusbar
    if(db.open())
        ui->statusbar->showMessage("Connected to Database Successfully.");
    else
        ui->statusbar->showMessage("Error: Connection to Database Failed.");

    //Create Handler for the Log on Button
    connect(ui->logOnButton, &QPushButton::clicked, this, &MainWindow::logonClicked);

    //Quit if Cancel Pressed
    connect(ui->cancelButton, &QPushButton::clicked, [=](){ QApplication::quit();});
}

MainWindow::~MainWindow()
{
    delete ui;

    //Close connection to Database before exiting
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

void MainWindow::logonClicked()
{
    //Check if Database still Connected
    if (!db.open()) return;

    //Grab Entered Credentials
    QString username, password;
    username = ui->username->text();
    password = ui->password->text();

    //Create Query and Execute
    QSqlQuery query(db);
    query.prepare("select * from LogonDB where Username='"+username+"' and Password='"+password+"'");
    query.exec();

    //If No Match, Clear Input Fields and Return
    if(!query.next())
    {
        ui->statusbar->showMessage("Login Fail. Please Try Again");
        ui->username->clear();
        ui->password->clear();
        ui->username->setFocus();
        return;
    }

    this->hide();
    EmployeeInfo* employeeInfo = new EmployeeInfo(this, username);
    employeeInfo->exec();

    //Return from Employee Screen and Wipe previous Login Info
    ui->username->clear();
    ui->password->clear();
    ui->username->setFocus();
    this->show();
    ui->statusbar->showMessage("You have successfully logged out.");
}

