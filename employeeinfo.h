#ifndef EMPLOYEEINFO_H
#define EMPLOYEEINFO_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class EmployeeInfo;
}

class EmployeeInfo : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeInfo(QWidget *parent, QString username);
    ~EmployeeInfo();

private:
    Ui::EmployeeInfo *ui;
};

#endif // EMPLOYEEINFO_H
