#include "employeeinfo.h"
#include "ui_employeeinfo.h"
#include <QDebug>

EmployeeInfo::EmployeeInfo(QWidget *parent, QString username) :
    QDialog(parent),
    ui(new Ui::EmployeeInfo)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    //Load Picture of Logged in User
    ui->Photo->setPixmap(QPixmap(QString("./IDPHOTO/" + username + ".png")));
    ui->Photo->setScaledContents(true);

    //Destroy Window upon Logout
    connect(ui->logOut, &QPushButton::clicked, [=](){ delete(this); });

    //Query Database
    QSqlQuery query;
    query.prepare("select * from LogonDB where username='"+username+"'");
    query.exec();
    query.next();

    //Populate Fields
    ui->firstname->setText(query.value(2).toString());
    ui->lastname->setText(query.value(3).toString());
    ui->age->setText(query.value(4).toString());
    ui->role->setText(query.value(5).toString());
}

EmployeeInfo::~EmployeeInfo()
{
    delete ui;
}
