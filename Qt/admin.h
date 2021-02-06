#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QChartView>
#include <QtCharts>
#include <QPieSeries>

#include "voce.h"

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();   

private slots:
    void on_pushButton_clicked();

private:
    Ui::Admin *ui;

    QChartView *chartView;

    QChartView *chartView2;

    bool grafico1 = true;

    std::vector<voce> elenco;

    void leggiFile();

    int contaSesso(const QString &s);

    int contaEta(int minAnni, int maxAnni);



};

#endif // ADMIN_H
