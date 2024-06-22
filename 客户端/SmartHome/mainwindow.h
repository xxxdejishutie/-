#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"doordialog.h"
#include"timer.h"
#include"cwarning.h"
#include"temprature.h"

extern udp* pNet;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_pb_door_clicked();

    void on_pb_light_clicked();

    void on_pb_chuang_clicked();

    void on_pb_morning_clicked();

    void slot_showpic();

private slots:
    void on_pb_night_clicked();
    void on_pb_du_clicked();

public:

private:
    Ui::MainWindow *ui;
    doorDialog* m_pdoor;
    CWarning* m_pwarning;
    Timer* m_ptimedlg;
    temprature* m_ptem;
    //timer* m_ptime;

};

#endif // MAINWINDOW_H
