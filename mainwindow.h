#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //----------------------------------------

    void on_pb_tableDay_clicked();

    void on_pb_tableCar_clicked();

    void on_pb_settings_clicked();

    //----------------------------------------

    void on_pb_Enter_clicked();

    void on_pb_Enter_2_clicked();

    void on_pb_Exit_clicked();

    void on_pb_Exit_2_clicked();

    //----------------------------------------

    void on_pb_date_clicked();

    void on_pb_0sh_clicked();

    void on_pb_1sh_clicked();

    void on_pb_2sh_clicked();

    void on_pb_3sh_clicked();

    void on_pb_4sh_clicked();

    void on_pb_5sh_clicked();

    void on_pb_Xsh_clicked();

    void on_pb_now_clicked();

    void on_pb_n5_clicked();

    void on_pb_n10_clicked();

    void on_pb_n15_clicked();

    void on_pb_5_clicked();

    void on_pb_10_clicked();

    void on_pb_15_clicked();

    void on_pb_save_clicked();

    //----------------------------------------

    void on_pb_date_2_clicked();

    void on_pb_0sh_2_clicked();

    void on_pb_1sh_2_clicked();

    void on_pb_2sh_2_clicked();

    void on_pb_3sh_2_clicked();

    void on_pb_4sh_2_clicked();

    void on_pb_5sh_2_clicked();

    void on_pb_Xsh_2_clicked();

    void on_pb_now_2_clicked();

    void on_pb_n5_2_clicked();

    void on_pb_n10_2_clicked();

    void on_pb_n15_2_clicked();

    void on_pb_5_2_clicked();

    void on_pb_10_2_clicked();

    void on_pb_15_2_clicked();

    void on_pb_officeAnd_clicked();

    void on_pb_office_clicked();

    void on_pb_save_2_clicked();

    //----------------------------------------

    void on_pb_newDay_clicked();

    void on_pb_editDay_clicked();

    void on_tv_days_clicked(const QModelIndex &index);

    //----------------------------------------

    void on_pb_newCar_clicked();

    void on_pb_editCar_clicked();

    void on_tv_cars_clicked(const QModelIndex &index);

    //----------------------------------------

    void on_pb_exitMoney_clicked();

    void on_pb_enterMoney_clicked();

    void on_pb_date_3_clicked();

    void on_pb_0sh_3_clicked();

    void on_pb_1sh_3_clicked();

    void on_pb_2sh_3_clicked();

    void on_pb_3sh_3_clicked();

    void on_pb_4sh_3_clicked();

    void on_pb_5sh_3_clicked();

    void on_pb_Xsh_3_clicked();

    void on_pb_save_3_clicked();

    //----------------------------------------

    void on_pb_exitMoney_2_clicked();

    void on_pb_enterMoney_2_clicked();

    void on_pb_date_4_clicked();

    void on_pb_0sh_4_clicked();

    void on_pb_1sh_4_clicked();

    void on_pb_2sh_4_clicked();

    void on_pb_3sh_4_clicked();

    void on_pb_4sh_4_clicked();

    void on_pb_5sh_4_clicked();

    void on_pb_Xsh_4_clicked();

    void on_pb_save_4_clicked();

    //----------------------------------------

    void on_pb_DelDB_clicked();

    void on_pb_write_clicked();

    //----------------------------------------

    void Shanbe(int day,QLineEdit *le_shanbe);

    QString shanbe(QString day);

    void setTime(QTime current,QLineEdit *time,QPushButton *now,QPushButton *n5,QPushButton *n10,
                 QPushButton *n15,QPushButton *p5,QPushButton *p10,QPushButton *p15);

    void on_calendarWidget_clicked(const QDate &date);

    int row(QString query);

    void Auto();

    //----------------------------------------



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
