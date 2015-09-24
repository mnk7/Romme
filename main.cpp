#include "main.h"
#include "ui_main.h"

Main::Main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main)
{
    ui->setupUi(this);

    connect(ui->neuerspieler, SIGNAL(clicked()), ui->spieler, SLOT(neuerSpieler()));

    connect(ui->eingabe, SIGNAL(clicked()), ui->spieler, SLOT(addieren()));

    connect(ui->eingabe, SIGNAL(clicked()), this, SLOT(eingabe()));

    connect(ui->zuruck, SIGNAL(clicked()), ui->spieler, SLOT(zuruck()));

    connect(ui->neuesspiel, SIGNAL(clicked()), ui->spieler, SLOT(neuesSpiel()));

    connect(ui->hand, SIGNAL(toggled(bool)), ui->spieler, SLOT(hand(bool)));
}

Main::~Main()
{
    delete ui;
}

void Main::eingabe()
{
    ui->hand->setChecked(false);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main m;

    m.show();

    return a.exec();
}
