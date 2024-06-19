#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTime>
#include <QFileDialog>

#include "xlsxdocument.h"
using namespace QXlsx;

//------------------------------

int pbPage = -1;
int buff = 0;

QCalendar convert(QCalendar::System::Jalali);

QDate today(QDate::currentDate());
QString todayYMD = today.toString("yyyy/MM/dd",convert);

//------------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_exitMoney->setFocus();
    ui->pb_exitMoney_2->setFocus();

    QFont f("seqoe ui", 22);
    ui->calendarWidget->setFont(f);

    ui->calendarWidget->setCalendar(convert);

    /////////////////////////////////////////////////////////////////////////////////////////

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if (!db.open())
        QMessageBox::critical(this,"not Open !","database not open !");

    /////////////////////////////////////////////////////////////////////////////////////////

    db.exec("create table Days(ID Text primary key, Day text, Date text unique, Login text, Exit text, Location text, Lock Text)"); //Total text
    db.exec("create table Cars(ID Text primary key, Day text, Date text unique, n1 Text, n2 Text, n3 Text, n4 Text)");
    db.exec("create table AddCars(ID Text primary key, Day text, Date text unique, n1 text, n2 Text, n3 Text, n4 Text)");
    db.exec("create table setting(Title text unique,value Text)");
    db.exec("insert into setting values('xlsxAddress','Empty/empty')");
    db.exec("insert into setting values('writeDate','E/Empty/E')");

    Auto();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//  Page_TOP  //
//###################################################################################################################################################

void MainWindow::on_pb_tableDay_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->le_editDay->clear();

    QSqlQuery q;
    q.exec("select * from Days");
    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(std::move(q));
    ui->tv_days->setModel(m);

    ui->tv_days->setColumnWidth(0,15);
    ui->tv_days->setColumnWidth(2,100);
    ui->tv_days->setColumnWidth(5,180);
    ui->tv_days->setColumnWidth(6,40);
}


void MainWindow::on_pb_tableCar_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->le_editCar->clear();

    QSqlQuery q;
    if (buff % 2 == 0)
        q.exec("select * from Cars");
    else
        q.exec("select * from AddCars");

    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(std::move(q));
    ui->tv_cars->setModel(m);
    ui->tv_cars->setColumnWidth(0,15);
    ui->tv_cars->setColumnWidth(1,75);
    ui->tv_cars->setColumnWidth(2,100);
    buff++;
}


void MainWindow::on_pb_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);

    QSqlQuery q("select value from setting where Title = 'writeDate'");
    q.next();
    ui->le_writeDate->setText(q.value(0).toString());
}

//###################################################################################################################################################


//  Page_Enter & Exit  //
//###################################################################################################################################################

void MainWindow::on_pb_Enter_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    if (ui->le_dayItem->text() == "new")
    {
        setTime(QTime::currentTime(),ui->le_time,ui->pb_now,ui->pb_n5,ui->pb_n10,ui->pb_n15,ui->pb_5,ui->pb_10,ui->pb_15);
        ui->le_date->setText(todayYMD);
        ui->le_Shanbe->setText(shanbe(today.toString("ddd")));
    }
}


void MainWindow::on_pb_Enter_2_clicked()
{
    on_pb_Enter_clicked();
}


void MainWindow::on_pb_Exit_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    if (ui->le_dayItem_2->text() == "new")
    {
        setTime(QTime::currentTime(),ui->le_time_2,ui->pb_now_2,ui->pb_n5_2,ui->pb_n10_2,ui->pb_n15_2,ui->pb_5_2,ui->pb_10_2,ui->pb_15_2);
        ui->le_date_2->setText(todayYMD);
        ui->le_Shanbe_2->setText(shanbe(today.toString("ddd")));
        ui->le_address->clear();
        ui->le_lock->clear();
    }
}


void MainWindow::on_pb_Exit_2_clicked()
{
    on_pb_Exit_clicked();
}

//###################################################################################################################################################


//  Page_Enter  //
//###################################################################################################################################################

void MainWindow::on_pb_date_clicked()
{
    ui->calendarWidget->setSelectedDate(today);
    ui->stackedWidget->setCurrentIndex(4);
    pbPage = 0;
}


void MainWindow::on_pb_0sh_clicked()
{
    Shanbe(0,ui->le_Shanbe);
}


void MainWindow::on_pb_1sh_clicked()
{
    Shanbe(1,ui->le_Shanbe);
}


void MainWindow::on_pb_2sh_clicked()
{
    Shanbe(2,ui->le_Shanbe);
}


void MainWindow::on_pb_3sh_clicked()
{
    Shanbe(3,ui->le_Shanbe);
}


void MainWindow::on_pb_4sh_clicked()
{
    Shanbe(4,ui->le_Shanbe);
}


void MainWindow::on_pb_5sh_clicked()
{
    Shanbe(5,ui->le_Shanbe);
}


void MainWindow::on_pb_Xsh_clicked()
{
    Shanbe(6,ui->le_Shanbe);
}


void MainWindow::on_pb_now_clicked()
{
    ui->le_time->setText(ui->pb_now->text());
}


void MainWindow::on_pb_n5_clicked()
{
    ui->le_time->setText(ui->pb_n5->text());
}


void MainWindow::on_pb_n10_clicked()
{
    ui->le_time->setText(ui->pb_n10->text());
}


void MainWindow::on_pb_n15_clicked()
{
    ui->le_time->setText(ui->pb_n15->text());
}


void MainWindow::on_pb_5_clicked()
{
    ui->le_time->setText(ui->pb_5->text());
}


void MainWindow::on_pb_10_clicked()
{
    ui->le_time->setText(ui->pb_10->text());
}


void MainWindow::on_pb_15_clicked()
{
    ui->le_time->setText(ui->pb_15->text());
}


void MainWindow::on_pb_save_clicked()
{
    QSqlQuery q;
    QString ID = ui->le_dayItem->text();
    QString IDNew = QString::number(row("select * from Days") +1);
    QString day = ui->le_Shanbe->text();
    QString date = ui->le_date->text();
    QString timeEnter = ui->le_time->text();
    QString timeExit = ui->le_time_2->text();
    QString location = ui->le_address->text();
    QString lock = ui->le_lock->text();


    if (ui->le_dayItem->text() == "new")
        q.exec("insert into Days values('"+IDNew+"','"+day+"','"+date+"','"+timeEnter+"','','','')");
    else
        q.exec("update Days set Day='"+day+"',Date='"+date+"',Login='"+timeEnter+"',""Exit='"+timeExit+"',Location='"+location+"',Lock='"+lock+"' where ID='"+ID+"' ");

    on_pb_tableDay_clicked();
}

//###################################################################################################################################################


//  Page_Exit  //
//###################################################################################################################################################

void MainWindow::on_pb_date_2_clicked()
{
    ui->calendarWidget->setSelectedDate(today);
    ui->stackedWidget->setCurrentIndex(4);
    pbPage = 1;
}


void MainWindow::on_pb_0sh_2_clicked()
{
    Shanbe(0,ui->le_Shanbe_2);
}


void MainWindow::on_pb_1sh_2_clicked()
{
    Shanbe(1,ui->le_Shanbe_2);
}


void MainWindow::on_pb_2sh_2_clicked()
{
    Shanbe(2,ui->le_Shanbe_2);
}


void MainWindow::on_pb_3sh_2_clicked()
{
    Shanbe(3,ui->le_Shanbe_2);
}


void MainWindow::on_pb_4sh_2_clicked()
{
    Shanbe(4,ui->le_Shanbe_2);
}


void MainWindow::on_pb_5sh_2_clicked()
{
    Shanbe(5,ui->le_Shanbe_2);
}


void MainWindow::on_pb_Xsh_2_clicked()
{
    Shanbe(6,ui->le_Shanbe_2);
}


void MainWindow::on_pb_now_2_clicked()
{
    ui->le_time_2->setText(ui->pb_now_2->text());
}


void MainWindow::on_pb_n5_2_clicked()
{
    ui->le_time_2->setText(ui->pb_n5_2->text());
}


void MainWindow::on_pb_n10_2_clicked()
{
    ui->le_time_2->setText(ui->pb_n10_2->text());
}


void MainWindow::on_pb_n15_2_clicked()
{
    ui->le_time_2->setText(ui->pb_n15_2->text());
}


void MainWindow::on_pb_5_2_clicked()
{
    ui->le_time_2->setText(ui->pb_5_2->text());
}


void MainWindow::on_pb_10_2_clicked()
{
    ui->le_time_2->setText(ui->pb_10_2->text());
}


void MainWindow::on_pb_15_2_clicked()
{
    ui->le_time_2->setText(ui->pb_15_2->text());
}


void MainWindow::on_pb_officeAnd_clicked()
{
    ui->le_address->setText("دفتر و ");
}


void MainWindow::on_pb_office_clicked()
{
    ui->le_address->setText("دفتر");
}


void MainWindow::on_pb_save_2_clicked()
{
    QSqlQuery q;
    QString ID = ui->le_dayItem_2->text();
    QString IDNew = QString::number(row("select * from Days") +1);
    QString day = ui->le_Shanbe_2->text();
    QString date = ui->le_date_2->text();
    QString timeEnter = ui->le_time->text();
    QString timeExit = ui->le_time_2->text();
    QString location = ui->le_address->text();
    QString lock = ui->le_lock->text();


    if (ui->le_dayItem->text() == "new")
        q.exec("insert into Days values('"+IDNew+"','"+day+"','"+date+"','','"+timeExit+"','"+location+"','"+lock+"')");
    else
        q.exec("update Days set Day='"+day+"',Date='"+date+"',Login='"+timeEnter+"',""Exit='"+timeExit+"',Location='"+location+"',Lock='"+lock+"' where ID='"+ID+"' ");

    on_pb_tableDay_clicked();
}

//###################################################################################################################################################


//  page_DayTable  //
//###################################################################################################################################################


void MainWindow::on_pb_newDay_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    setTime(QTime::currentTime(),ui->le_time,ui->pb_now,ui->pb_n5,ui->pb_n10,ui->pb_n15,ui->pb_5,ui->pb_10,ui->pb_15);
    ui->le_date->setText(todayYMD);
    ui->le_Shanbe->setText(shanbe(today.toString("ddd")));
    ui->le_dayItem->setText("new");
    ui->le_dayItem_2->setText("new");
}


void MainWindow::on_pb_editDay_clicked()
{
    QSqlQuery q;
    QString num = ui->le_editDay->text();
    if (num == "")
        QMessageBox::critical(this,"خالی است","یک ID وارد کنید ");
    else if (q.exec("select ID from Days where ID='"+num+"' "))
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->le_dayItem->setText(num);
        ui->le_dayItem_2->setText(num);

        QSqlQuery qq;
        qq.exec("select Day,Date,Login,Exit,Location,Lock from Days where ID='"+num+"' ");
        qq.next();

        ui->le_Shanbe->setText(qq.value(0).toString());
        ui->le_Shanbe_2->setText(qq.value(0).toString());
        ui->le_date->setText(qq.value(1).toString());
        ui->le_date_2->setText(qq.value(1).toString());
        ui->le_address->setText(qq.value(4).toString());
        if (qq.value(5).toString() == "0")
            ui->le_lock->setText("");
        else
            ui->le_lock->setText(qq.value(5).toString());

        if (qq.value(2).toString() == "")
            setTime(QTime::currentTime(),ui->le_time,ui->pb_now,ui->pb_n5,ui->pb_n10,ui->pb_n15,ui->pb_5,ui->pb_10,ui->pb_15);
        else
            setTime(qq.value(2).toTime(),ui->le_time,ui->pb_now,ui->pb_n5,ui->pb_n10,ui->pb_n15,ui->pb_5,ui->pb_10,ui->pb_15);

        if (qq.value(3).toString() == "")
            setTime(QTime::currentTime(),ui->le_time_2,ui->pb_now_2,ui->pb_n5_2,ui->pb_n10_2,ui->pb_n15_2,ui->pb_5_2,ui->pb_10_2,ui->pb_15_2);
        else
            setTime(qq.value(3).toTime(),ui->le_time_2,ui->pb_now_2,ui->pb_n5_2,ui->pb_n10_2,ui->pb_n15_2,ui->pb_5_2,ui->pb_10_2,ui->pb_15_2);

    }
}


void MainWindow::on_tv_days_clicked(const QModelIndex &index)
{
    ui->le_editDay->setText(QString::number(index.row()+1));
}

//###################################################################################################################################################


//  page_CarTable  //
//###################################################################################################################################################

void MainWindow::on_pb_newCar_clicked()
{
    if (buff % 2 != 0)
        ui->stackedWidget->setCurrentIndex(5);
    else
        ui->stackedWidget->setCurrentIndex(6);
    ui->le_moneyItem->setText("new");
    ui->le_moneyItem_2->setText("new");

    ui->le_date_3->setText(todayYMD);
    ui->le_date_4->setText(todayYMD);
    ui->le_Shanbe_3->setText(shanbe(today.toString("ddd")));
    ui->le_Shanbe_4->setText(shanbe(today.toString("ddd")));
    ui->le_car1->clear();
    ui->le_car2->clear();
    ui->le_car3->clear();
    ui->le_car4->clear();
    ui->le_car1_2->clear();
    ui->le_car2_2->clear();
    ui->le_car3_2->clear();
    ui->le_car4_2->clear();

    ui->pb_enterMoney->setEnabled(1);
    ui->pb_exitMoney_2->setEnabled(1);
}


void MainWindow::on_pb_editCar_clicked()
{
    QString num = ui->le_editCar->text();
    if (num == "")
        QMessageBox::critical(this,"خالی است","یک ID وارد کنید ");
    else if (buff % 2 != 0)
    {
        ui->stackedWidget->setCurrentIndex(5);
        ui->le_moneyItem->setText(num);

        QSqlQuery q;
        q.exec("select Day,Date,n1,n2,n3,n4 from Cars where ID='"+num+"' ");
        q.next();

        ui->le_Shanbe_3->setText(q.value(0).toString());
        ui->le_date_3->setText(q.value(1).toString());
        ui->le_car1->setText(q.value(2).toString());
        ui->le_car2->setText(q.value(3).toString());
        ui->le_car3->setText(q.value(4).toString());
        ui->le_car4->setText(q.value(5).toString());

        ui->pb_enterMoney->setDisabled(1);
    }
    else {
        ui->stackedWidget->setCurrentIndex(6);
        ui->le_moneyItem_2->setText(num);

        QSqlQuery q;
        q.exec("select Day,Date,n1,n2,n3,n4 from AddCars where ID='"+num+"' ");
        q.next();

        ui->le_Shanbe_4->setText(q.value(0).toString());
        ui->le_date_4->setText(q.value(1).toString());
        ui->le_car1_2->setText(q.value(2).toString());
        ui->le_car2_2->setText(q.value(3).toString());
        ui->le_car3_2->setText(q.value(4).toString());
        ui->le_car4_2->setText(q.value(5).toString());

        ui->pb_exitMoney_2->setDisabled(1);
    }
}


void MainWindow::on_tv_cars_clicked(const QModelIndex &index)
{
    ui->le_editCar->setText(QString::number(index.row()+1));
}

//###################################################################################################################################################


//  page_ExitCar & EnterCar  //
//###################################################################################################################################################

void MainWindow::on_pb_exitMoney_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    if (ui->le_moneyItem->text() == "new")
    {
        ui->le_date_3->setText(todayYMD);
        ui->le_Shanbe_3->setText(shanbe(today.toString("ddd")));
        ui->le_car1->clear();
        ui->le_car2->clear();
        ui->le_car3->clear();
        ui->le_car4->clear();
    }
}


void MainWindow::on_pb_exitMoney_2_clicked()
{
    on_pb_exitMoney_clicked();
}


void MainWindow::on_pb_enterMoney_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    if (ui->le_moneyItem_2->text() == "new")
    {
        ui->le_date_4->setText(todayYMD);
        ui->le_Shanbe_4->setText(shanbe(today.toString("ddd")));
        ui->le_car1_2->clear();
        ui->le_car2_2->clear();
        ui->le_car3_2->clear();
        ui->le_car4_2->clear();
    }
}


void MainWindow::on_pb_enterMoney_2_clicked()
{
    on_pb_enterMoney_clicked();
}

//###################################################################################################################################################


//  page_ExitCar  //
//###################################################################################################################################################

void MainWindow::on_pb_date_3_clicked()
{
    ui->calendarWidget->setSelectedDate(today);
    ui->stackedWidget->setCurrentIndex(4);
    pbPage = 5;
}


void MainWindow::on_pb_0sh_3_clicked()
{
    Shanbe(0,ui->le_Shanbe_3);
}


void MainWindow::on_pb_1sh_3_clicked()
{
    Shanbe(1,ui->le_Shanbe_3);
}


void MainWindow::on_pb_2sh_3_clicked()
{
    Shanbe(2,ui->le_Shanbe_3);
}


void MainWindow::on_pb_3sh_3_clicked()
{
    Shanbe(3,ui->le_Shanbe_3);
}


void MainWindow::on_pb_4sh_3_clicked()
{
    Shanbe(4,ui->le_Shanbe_3);
}


void MainWindow::on_pb_5sh_3_clicked()
{
    Shanbe(5,ui->le_Shanbe_3);
}


void MainWindow::on_pb_Xsh_3_clicked()
{
    Shanbe(6,ui->le_Shanbe_3);
}


void MainWindow::on_pb_save_3_clicked()
{
    QSqlQuery q;
    QString ID = ui->le_moneyItem->text();
    QString IDNew = QString::number(row("select * from Cars") +1);
    QString day = ui->le_Shanbe_3->text();
    QString date = ui->le_date_3->text();
    QString car1 = ui->le_car1->text();
    QString car2 = ui->le_car2->text();
    QString car3 = ui->le_car3->text();
    QString car4 = ui->le_car4->text();


    if (ID == "new")
        q.exec("insert into Cars values('"+IDNew+"','"+day+"','"+date+"','"+car1+"','"+car2+"','"+car3+"','"+car4+"')");
    else
        q.exec("update Cars set Day='"+day+"',Date='"+date+"',n1='"+car1+"',""n2='"+car2+"',n3='"+car3+"',n4='"+car4+"' where ID='"+ID+"' ");

    buff++;
    on_pb_tableCar_clicked();
}

//###################################################################################################################################################


//  page_EnterCar  //
//###################################################################################################################################################

void MainWindow::on_pb_date_4_clicked()
{
    ui->calendarWidget->setSelectedDate(today);
    ui->stackedWidget->setCurrentIndex(4);
    pbPage = 6;
}


void MainWindow::on_pb_0sh_4_clicked()
{
    Shanbe(0,ui->le_Shanbe_4);
}


void MainWindow::on_pb_1sh_4_clicked()
{
    Shanbe(1,ui->le_Shanbe_4);
}


void MainWindow::on_pb_2sh_4_clicked()
{
    Shanbe(2,ui->le_Shanbe_4);
}


void MainWindow::on_pb_3sh_4_clicked()
{
    Shanbe(3,ui->le_Shanbe_4);
}


void MainWindow::on_pb_4sh_4_clicked()
{
    Shanbe(4,ui->le_Shanbe_4);
}


void MainWindow::on_pb_5sh_4_clicked()
{
    Shanbe(5,ui->le_Shanbe_4);
}


void MainWindow::on_pb_Xsh_4_clicked()
{
    Shanbe(6,ui->le_Shanbe_4);
}


void MainWindow::on_pb_save_4_clicked()
{
    QSqlQuery q;
    QString ID = ui->le_moneyItem_2->text();
    QString IDNew = QString::number(row("select * from AddCars") +1);
    QString day = ui->le_Shanbe_4->text();
    QString date = ui->le_date_4->text();
    QString car1 = ui->le_car1_2->text();
    QString car2 = ui->le_car2_2->text();
    QString car3 = ui->le_car3_2->text();
    QString car4 = ui->le_car4_2->text();


    if (ID == "new")
        q.exec("insert into AddCars values('"+IDNew+"','"+day+"','"+date+"','"+car1+"','"+car2+"','"+car3+"','"+car4+"')");
    else
        q.exec("update AddCars set Day='"+day+"',Date='"+date+"',n1='"+car1+"',""n2='"+car2+"',n3='"+car3+"',n4='"+car4+"' where ID='"+ID+"' ");

    buff++;
    on_pb_tableCar_clicked();
}

//###################################################################################################################################################


//  Page_Calender  //
//###################################################################################################################################################

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    if (pbPage == 0)
    {
        ui->le_date->setText(date.toString("yyyy/MM/dd",convert));
        ui->le_Shanbe->setText(shanbe(date.toString("ddd")));
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (pbPage == 1)
    {
        ui->le_date_2->setText(date.toString("yyyy/MM/dd",convert));
        ui->le_Shanbe_2->setText(shanbe(date.toString("ddd")));
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (pbPage == 5)
    {
        ui->le_date_3->setText(date.toString("yyyy/MM/dd",convert));
        ui->le_Shanbe_3->setText(shanbe(date.toString("ddd")));
        ui->stackedWidget->setCurrentIndex(5);
    }
    else if (pbPage == 6)
    {
        ui->le_date_4->setText(date.toString("yyyy/MM/dd",convert));
        ui->le_Shanbe_4->setText(shanbe(date.toString("ddd")));
        ui->stackedWidget->setCurrentIndex(6);
    }
    pbPage = -1;
}

//###################################################################################################################################################


//  Page_End  //
//###################################################################################################################################################


void MainWindow::on_pb_DelDB_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this,"پاک کردن دیتابیس !!","دیتابیس حذف شود ؟؟",QMessageBox::Yes|QMessageBox::No);

    if (btn == QMessageBox::Yes)
    {
        QFile exist("data.db");
        if (exist.exists())
            if (exist.remove())
                QMessageBox::critical(this,"فایل پاک شد","");
            else
                QMessageBox::critical(this,"فایل پاک نشد","");
        else
            QMessageBox::critical(this,"فایل نیست","");

    }

}


void MainWindow::on_pb_write_clicked()
{
    QSqlQuery q("select value from setting where Title = 'xlsxAddress'");
    q.next();
    QString address = q.value(0).toString();

    Document xlsx(address);

    if (xlsx.save() == 0)
    {
        QString newAddress = QFileDialog::getSaveFileName(this,"","DayTime.xlsx");

        if (newAddress != "")
        {
            QSqlQuery("update setting set value = '"+newAddress+"' where title = 'xlsxAddress'");
            on_pb_write_clicked();
        }
        ui->le_writeDate->setText("Error Address");
    }
    else
    {
        QSqlQuery q2("select * from Days");
        int i = 1;
        while (q2.next())
        {
            xlsx.write("G"+QString::number(i),q2.value(0).toString());
            xlsx.write("F"+QString::number(i),q2.value(1).toString());
            xlsx.write("E"+QString::number(i),q2.value(2).toString());
            xlsx.write("D"+QString::number(i),q2.value(3).toString());
            xlsx.write("C"+QString::number(i),q2.value(4).toString());
            xlsx.write("B"+QString::number(i),q2.value(5).toString());
            xlsx.write("A"+QString::number(i),q2.value(6).toString());
            i++;
        }

        //---------------------------------------------------------------

        QSqlQuery q3("select * from AddCars");
        i = 1;
        while (q3.next())
        {
            xlsx.write("N"+QString::number(i),q3.value(0).toString());
            xlsx.write("M"+QString::number(i),q3.value(2).toString());
            xlsx.write("L"+QString::number(i),q3.value(3).toString());
            xlsx.write("K"+QString::number(i),q3.value(4).toString());
            xlsx.write("J"+QString::number(i),q3.value(5).toString());
            xlsx.write("I"+QString::number(i),q3.value(6).toString());
            i++;
        }

        //---------------------------------------------------------------

        QSqlQuery q4("select * from Cars");
        i = 1;
        while (q4.next())
        {
            xlsx.write("U"+QString::number(i),q4.value(0).toString());
            xlsx.write("T"+QString::number(i),q4.value(2).toString());
            xlsx.write("S"+QString::number(i),q4.value(3).toString());
            xlsx.write("R"+QString::number(i),q4.value(4).toString());
            xlsx.write("Q"+QString::number(i),q4.value(5).toString());
            xlsx.write("P"+QString::number(i),q4.value(6).toString());
            i++;
        }

        //---------------------------------------------------------------

        for (int i=1; i<=30; i++)
        {
            xlsx.write("H"+QString::number(i),"XXXXXX");
            xlsx.write("O"+QString::number(i),"XXXXXX");
            xlsx.write("V"+QString::number(i),"XXXXXX");
        }

        //---------------------------------------------------------------

        xlsx.setColumnWidth(1,6);
        xlsx.setColumnWidth(2,13);
        xlsx.setColumnWidth(5,13);
        xlsx.setColumnWidth(7,6);
        xlsx.setColumnWidth(9,6);
        xlsx.setColumnWidth(10,6);
        xlsx.setColumnWidth(11,6);
        xlsx.setColumnWidth(12,6);
        xlsx.setColumnWidth(13,13);
        xlsx.setColumnWidth(14,6);
        xlsx.setColumnWidth(16,6);
        xlsx.setColumnWidth(17,6);
        xlsx.setColumnWidth(18,6);
        xlsx.setColumnWidth(19,6);
        xlsx.setColumnWidth(20,13);
        xlsx.setColumnWidth(21,6);

        //---------------------------------------------------------------

        if (xlsx.save())
        {
            QString DateTime = todayYMD + "     " + QTime::currentTime().toString("HH:mm:ss");
            ui->le_writeDate->setText(DateTime);
            QSqlQuery("update setting set value = '"+DateTime+"' where title = 'writeDate'");
        }
        else
            ui->le_writeDate->setText("Error Save");
    }

}



//###################################################################################################################################################

//###################################################################################################################################################

void MainWindow::Shanbe(int day,QLineEdit *le_shanbe)
{
    switch (day) {
    case 0:
        le_shanbe->setText("شنبه");
        break;
    case 1:
        le_shanbe->setText("یکشنبه");
        break;
    case 2:
        le_shanbe->setText("دوشنبه");
        break;
    case 3:
        le_shanbe->setText("سه‌شنبه");
        break;
    case 4:
        le_shanbe->setText("چهارشنبه");
        break;
    case 5:
        le_shanbe->setText("پنجشنبه");
        break;
    case 6:
        le_shanbe->setText("جمعه");
        break;
    default:
        le_shanbe->setText("Error");
        break;
    }
}


QString MainWindow::shanbe(QString day)
{
    if (day == "Sat")
        return "شنبه";

    else if (day == "Sun")
        return "یکشنبه";

    else if (day == "Mon")
        return "دوشنبه";

    else if (day == "Tue")
        return "سه‌شنبه";

    else if (day == "Wed")
        return "چهارشنبه";

    else if (day == "Thu")
        return "پنجشنبه";

    else
        return "جمعه";
}


void MainWindow::setTime(QTime current,QLineEdit *time,QPushButton *now,QPushButton *n5,QPushButton *n10,
                         QPushButton *n15,QPushButton *p5,QPushButton *p10,QPushButton *p15)
{
    int min = (current.minute()+4)/5*5;
    if (min>=60)
        current = current.addSecs((60-current.minute())*60);
    else
        current = QTime(current.hour(),min);

    time->setText(current.toString("hh:mm"));
    now->setText(current.toString("hh:mm"));
    n5->setText(current.addSecs(-300).toString("hh:mm"));
    n10->setText(current.addSecs(-600).toString("hh:mm"));
    n15->setText(current.addSecs(-900).toString("hh:mm"));
    p5->setText(current.addSecs(300).toString("hh:mm"));
    p10->setText(current.addSecs(600).toString("hh:mm"));
    p15->setText(current.addSecs(900).toString("hh:mm"));
}

int MainWindow::row(QString query)
{
    QSqlQuery q;
    q.exec(query);
    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(std::move(q));
    return m->rowCount();
}

void MainWindow::Auto()
{
    QString end = QString::number(row("select * from Days"));
    QSqlQuery q;
    q.exec("select Date,Login,Exit from Days where ID='"+end+"' ");
    q.next();

    if (q.value(0).toString() == todayYMD)
        if (q.value(1).toString() != "")
            if (q.value(2).toString() != "")
                on_pb_tableDay_clicked();
            else {
                ui->le_editDay->setText(end);
                on_pb_editDay_clicked();
                on_pb_Exit_clicked();
            }
        else {
            ui->le_editDay->setText(end);
            on_pb_editDay_clicked();
            on_pb_Enter_clicked();
        }
    else {
        on_pb_newDay_clicked();

        q.exec("select Date from Days");
        while (q.next())
            if (q.value(0).toString() == todayYMD)
                on_pb_tableDay_clicked();
    }
}


//###################################################################################################################################################
