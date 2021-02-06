#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

#include "voce.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_pushButton_iscriviti_clicked();

    void on_lineEdit_password_textEdited(const QString &arg1);

    void on_pushButton_accedi_clicked();

    void on_pushButton_recuperoPassword_clicked();

private:

    QDate dataAttuale = QDate().currentDate();

    std::vector<voce> elenco;

    bool eNumero(const std::string &stringa);

    bool eMail(const std::string &stringa);

    bool esisteVoce(const voce &v);

    void leggiFile();

    void scriviFile();

};
#endif // MAINWINDOW_H
