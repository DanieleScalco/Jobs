#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialog.h"
#include "dialog2.h"
#include "dialog3.h"
#include "dialog4.h"
#include "dialog5.h"
#include "dialog6.h"
#include "admin.h"

#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QString>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


// Controlla se la stringa è una mail del formato <testo>@<dominio>.it
bool MainWindow::eMail(const std::string &stringa) {

    // la lunghezza minima è a@b.it
    if (stringa.length() <= 5) {
        return false;
    }

    QString testo = "", dominioIt = "";
    bool chiocciolaTrovata = false, itTrovato = false;
    std::string::const_iterator inizio, fine;
    inizio = stringa.begin();
    fine = stringa.end();

    while (inizio != fine) {
        if (!chiocciolaTrovata) {
            if (*inizio == '@') {
                chiocciolaTrovata = true;
            } else {
                testo += *inizio;
            }
        } else {
            dominioIt += *inizio;
        }
        ++inizio;
    }


    // Dopo che ho finito di scorrere la stringa controllo che il testo non sia vuoto, che ci sia la chiocciola
    // e che dominioIt finisca con ".it" o ".com"

    if (!chiocciolaTrovata) {
       return false;
    }

    int lunghezzaDominioIt = dominioIt.length();

    std::string ultimeTre, ultimeQuattro;

    if (lunghezzaDominioIt > 3) {

        // Controla se .it
        ultimeTre = dominioIt.toStdString().substr(lunghezzaDominioIt - 3, lunghezzaDominioIt);
        if (ultimeTre == ".it") {
            itTrovato = true;
        }

    }

    if (lunghezzaDominioIt > 4) {

        // Controla se .com
        ultimeQuattro = dominioIt.toStdString().substr(lunghezzaDominioIt - 4, lunghezzaDominioIt);
        if (ultimeQuattro == ".com") {
            itTrovato = true;
        }

    }

    if (!itTrovato) {
        return false;
    }

    if (testo == "") {
        return false;
    }

    return true;

}


// Controlla se la stringa è un numero di telefono a 10 cifre
bool MainWindow::eNumero(const std::string &stringa) {

    // Si assume che un numero di telefono abbia 10 cifre
    if (stringa.length() != 10) {
        return false;
    }

    std::string::const_iterator inizio, fine;
    inizio = stringa.begin();
    fine = stringa.end();

    while (inizio != fine) {
        if (
            *inizio == '0' ||
            *inizio == '1' ||
            *inizio == '2' ||
            *inizio == '3' ||
            *inizio == '4' ||
            *inizio == '5' ||
            *inizio == '6' ||
            *inizio == '7' ||
            *inizio == '8' ||
            *inizio == '9'
                ) {
            inizio++;
        } else
            return false;
    }
    return true;

}

// Se tutti i campi sono compilati in modo corretto registra il nuovo utente se
// non già registrato (controlla mail/tel e password)
void MainWindow::on_pushButton_iscriviti_clicked()
{
    bool inputValido = true;

    // Controllo su tutti i campi

    if (!(ui->lineEdit_nome->isModified()) || ui->lineEdit_nome->text() == "") {
        ui->lineEdit_nome->setText("Inserisci il nome");
        inputValido = false;
    }

    if (!(ui->lineEdit_cognome->isModified()) || ui->lineEdit_cognome->text() == "") {
        ui->lineEdit_cognome->setText("Inserisci il cognome");
        inputValido = false;
    }

    if (!(ui->lineEdit_mail->isModified()) || ui->lineEdit_mail->text() == "") {
        ui->lineEdit_mail->setText("Inserisci una mail o un numero di telefono");
        inputValido = false;
    } else {

        // Controllo che sia formato mail o numero di telefono

        std::string mail_telefono = ui->lineEdit_mail->text().toStdString();
        if (!(eNumero(mail_telefono) || (eMail(mail_telefono)))) {
            ui->lineEdit_mail->setText("Inserisci una mail o un numero di telefono");
            inputValido = false;
        }
    }

    if (!(ui->lineEdit_password->isModified()) || ui->lineEdit_password->text() == "") {
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
        ui->lineEdit_password->setText("Inserisci la nuova password");
        inputValido = false;
    } else {
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }

    // Controllo che sia maggiorenne

    QDate data = ui->dateEdit->date();
    data = data.addYears(18);
    if (dataAttuale >= data) {
        ui->label_eta->setText("");
    }
    else {
        ui->label_eta->setText("Devi essere maggiorenne");
        inputValido = false;
    }

    if (!ui->radioButton_uomo->isChecked() && !ui->radioButton_donna->isChecked()) {
        ui->label_sesso->setText("Seleziona il tuo sesso");
        inputValido = false;
    }
    else {
        ui->label_sesso->setText("");
    }

    if (inputValido) {

        // Quindi tutti i campi sono stati inseriti e validi

        QString nome = ui->lineEdit_nome->text();
        QString cognome = ui->lineEdit_cognome->text();
        QString mail = ui->lineEdit_mail->text();
        QString password = ui->lineEdit_password->text();
        QString data= ui->dateEdit->date().toString("dd/MM/yyyy");
        QString sesso;
        if (ui->radioButton_uomo->isChecked()) {
            sesso = "M";
        } else {
            sesso = "F";
        }

        // Creo una nuova voce

        voce nuovaVoce(nome, cognome, mail, password, data, sesso);

        // Controllo se la voce è gia esistente

        // Ricarico il file .csv
        elenco.clear();
        leggiFile();

        if (esisteVoce(nuovaVoce)) {

            // Utente già presente nel database

            Dialog2 d;
            d.setModal(true);
            d.exec();
        } else {

            // Utente registrato

            elenco.push_back(nuovaVoce);
            Dialog d;
            d.setModal(true);
            d.exec();
            scriviFile();
        }
    } else {

        // Se tutti i campi non sono validi cancello eventuale password inserita

        ui->lineEdit_password->setText("Inserisci la nuova password");
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }
}


void MainWindow::on_lineEdit_password_textEdited(const QString &arg1)
{
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

// Carica il file .csv
void MainWindow::leggiFile() {

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

// Scrive il file .csv
void MainWindow::scriviFile() {

    QFile file("utenti_registrati.csv");

    if(!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Cannot open file for writing: "
                  << qPrintable(file.errorString())
                  << std::endl;
    }

    QTextStream out(&file);

    std::vector<voce>::iterator inizio, fine;
    inizio = elenco.begin();
    fine = elenco.end();

    // Per ogni voce presente in elenco la scrivo e vado a capo

    while (inizio != fine) {
        out << (*inizio).nome << ", "
            << (*inizio).cognome << ", "
            << (*inizio).mail_telefono << ", "
            << (*inizio).password << ", "
            << (*inizio).dataDiNascita << ", "
            << (*inizio).sesso
            << Qt::endl;
        inizio++;
    }
}

// Controllo se la voce v esiste nell'elenco
bool MainWindow::esisteVoce(const voce &v) {

    if (elenco.empty()) {
        return false;
    }
    std::vector<voce>::const_iterator inizio, fine;
    inizio = elenco.begin();
    fine = elenco.end();

    while (inizio != fine) {
        if (*inizio == v) {
            return true;
        } else {
            ++inizio;
        }
    }
    return false;
}

// Permette all'utente di accedere se registrato o se admin di accedere
// all'apposita schermata
void MainWindow::on_pushButton_accedi_clicked()
{
    if (ui->lineEdit_logMail->text() == "admin@pas.com" && ui->lineEdit_logPassword->text() == "admin") {

        // Se admin, si apre schermata a parte

        Admin a;
        a.setModal(true);
        a.exec();

    } else {

        leggiFile();

        QString mail_tel = ui->lineEdit_logMail->text();
        QString pass = ui->lineEdit_logPassword->text();

        voce v("", "", mail_tel, pass, "", "");

        if (esisteVoce(v)) {

            // Accesso eseguito

            Dialog3 d;
            d.setModal(true);
            d.exec();
        } else {

            // Credenziali errate
            Dialog4 d;
            d.setModal(true);
            d.exec();
        }

    }
}

// Permette di recuperare la password se mail/tel è presente nel database
void MainWindow::on_pushButton_recuperoPassword_clicked()
{
    if (ui->lineEdit_logMail->text() == "") {
        ui->lineEdit_logMail->setText("Inserisci mail o telefono");
    } else {
        leggiFile();

        std::vector<voce>::const_iterator inizio, fine;
        inizio = elenco.begin();
        fine = elenco.end();

        bool accountEsistente = false;

        while (inizio != fine) {
            if ((*inizio).mail_telefono == ui->lineEdit_logMail->text()) {
                accountEsistente = true;
            }
            ++inizio;
        }

        if (accountEsistente) {

            // Password recuperata

            Dialog5 d;
            d.setModal(true);
            d.exec();
        } else {

            // Account non registrato

            Dialog6 d;
            d.setModal(true);
            d.exec();
        }
    }
}
