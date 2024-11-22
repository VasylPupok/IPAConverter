#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "translate/Translate.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_swapButton_clicked() {
    fromUkranianToIfa = !fromUkranianToIfa;
    QString temp = ui->fromLabel->text();
    ui->fromLabel->setText(ui->toLabel->text());
    ui->toLabel->setText(temp);
}

void MainWindow::on_translateButton_clicked() {
    Translate::StringType from = ui->inputField->toPlainText().toStdWString();
    if (fromUkranianToIfa) {
        ui->outputField->setText(QString::fromStdWString(Translate::toInternational(from)));
    } else {
        ui->outputField->setText(QString::fromStdWString(Translate::toUkranian(from)));
    }
}

