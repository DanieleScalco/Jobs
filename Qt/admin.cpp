#include "admin.h"
#include "ui_admin.h"

#include <iostream>


Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    // Carico i dati
    leggiFile();

    int maschi, femmine;

    // Ricavo il numero dei maschi e delle femmine
    maschi = contaSesso(QString ("M"));
    femmine = contaSesso(QString ("F"));

    // Prepara grafico maschi/femmine
    QPieSeries *series = new QPieSeries();
    series->append("Maschi", maschi);
    series->append("Femmine", femmine);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Maschi e femmine");

    chartView = new QChartView(chart);
    chartView->setParent(ui->verticalFrame);
    chartView->setGeometry(0, 0, 400, 400);

    // Ricavo le eta delle varie fasce
    int da18a26 = contaEta(18, 26);
    int da27a35 = contaEta(27, 35);
    int da36a44 = contaEta(36, 44);
    int da45a53 = contaEta(45, 53);
    int da54a200 = contaEta(54, 200);

    // Prepara Grafico eta
    QPieSeries *series2 = new QPieSeries();
    series2->append("18-26", da18a26);
    series2->append("27-35", da27a35);
    series2->append("36-44", da36a44);
    series2->append("45-53", da45a53);
    series2->append("54+", da54a200);

    QChart *chart2 = new QChart();
    chart2->addSeries(series2);
    chart2->setTitle("Eta");

    chartView2 = new QChartView(chart2);
    chartView2->setParent(ui->verticalFrame);
    chartView2->setGeometry(0, 0, 400, 400);

    // Nascondo secondo grafico
    chartView2->hide();


    // Metto il file csv nel textEdit
    QString dati = "";

    std::vector<voce>::const_iterator i, ie;
    i = elenco.begin();
    ie = elenco.end();

    // Contatore linea
    int j = 1;
    QString jString;

    while (i != ie) {
        jString = std::to_string(j).c_str();
        dati += jString;
        dati += ") ";
        dati += (*i).nome;
        dati += ", ";
        dati += (*i).cognome;
        dati += ", ";
        dati += (*i).mail_telefono;
        dati += ", ";
        dati += (*i).password;
        dati += ", ";
        dati += (*i).dataDiNascita;
        dati += ", ";
        dati += (*i).sesso;
        dati += "\n";
        ++i;
        ++j;
    }

    ui->textEdit->setText(dati);


}

Admin::~Admin()
{
    delete ui;
}

// Alterna la visualizzazione dei grafici a torta
void Admin::on_pushButton_clicked()
{
    if (grafico1) {

        grafico1 = false;

        chartView->hide();
        chartView2->show();

    } else {

        grafico1 = true;

        chartView2->hide();
        chartView->show();
    }
}

// Carica il file .csv
void Admin::leggiFile() {

    QFile file("utenti_registrati.csv");
    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Cannot open file reading"
                  << qPrintable(file.errorString())
                  << std::endl;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {

        // Finchè il documento non è vuoto leggi una riga

        QString linea = in.readLine();
        QString parola = "";
        QString::ConstIterator i, ie;
        i = linea.begin();
        ie = linea.end();
        voce v;

        while (i != ie) {

            // Finchè non ha letto tutta la riga scorri carattere per carattere
            if (*i != ",") {
                parola += *i;
            } else {
                if (v.nome == "") {
                    v.nome = parola;
                } else if (v.cognome == "") {
                    v.cognome = parola;
                } else if (v.mail_telefono == "") {
                    v.mail_telefono = parola;
                } else if (v.password == "") {
                    v.password = parola;
                } else if (v.dataDiNascita == "") {
                    v.dataDiNascita = parola;
                }

                ++i;
                parola = "";
            }
            ++i;
        }

        v.sesso = parola;

        // Finita la riga aggiungo la voce all'elenco
        elenco.push_back(v);

    }

}

// Conto quante persone hanno sesso uguale a s ("M" o "F");
int Admin::contaSesso(const QString &s) {
    std::vector<voce>::const_iterator i, ie;
    i = elenco.begin();
    ie = elenco.end();

    int totale = 0;

    while (i != ie) {
        if ((*i).sesso == s) {
            ++totale;
        }
        ++i;
    }
    return totale;
}

// Conto quante persone hanno età compresa tra minAnni e maxAnni
int Admin::contaEta(int minAnni, int maxAnni) {
    int totale = 0;

    QDate dataAttuale = QDate().currentDate();
    QDate min = dataAttuale.addYears(-(maxAnni + 1));
    QDate max = dataAttuale.addYears(-minAnni);

    std::vector<voce>::const_iterator i, ie;
    i = elenco.begin();
    ie = elenco.end();


    while (i != ie) {
        int giorno, mese, anno;
        giorno = std::stoi((*i).dataDiNascita.toStdString().substr(0,2));
        mese = std::stoi((*i).dataDiNascita.toStdString().substr(3,5));
        anno = std::stoi((*i).dataDiNascita.toStdString().substr(6));

        QDate tmp(anno, mese, giorno);

        if (min <= tmp && tmp < max) {
            ++totale;
        }

        ++i;
    }

    return totale;

}

