#include "spieler.h"
#include <QPalette>

Spieler::Spieler(QWidget *parent) : QWidget(parent)
{    
    connect(this, SIGNAL(eingabe()), this, SLOT(addieren()));

    this->setLayout(horizontal);

    horizontal->addItem(eingabelayout);

    space->setMinimumHeight(100);
    space->setMinimumWidth(100);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::white);
    space->setPalette(palette);
    space->setVisible(true);
    horizontal->addWidget(space, 10, 0);

    horizontal->addItem(namenlayout);

    neuerSpieler();
    neuerSpieler();

    //Farben der einzelnen Diagramme
    farben.push_back(Qt::red);
    farben.push_back(Qt::yellow);
    farben.push_back(Qt::darkCyan);
    farben.push_back(Qt::darkGreen);
    farben.push_back(Qt::darkMagenta);
    farben.push_back(Qt::gray);
    farben.push_back(Qt::darkRed);
    farben.push_back(Qt::darkYellow);

    istHand = false;
}

Spieler::~Spieler()
{
    delete(eingabelayout);
    delete(horizontal);
    delete(spielername);
    delete(eingaben);
    delete(punkte);
}

/**
 * @brief Spieler::addieren
 * Addiert die eingetragene Punktzahl
 */
void Spieler::addieren()
{
    int value;
    for(int i = 0; i < eingaben->size(); ++i)
    {
        value = eingaben->at(i)->value();
        if(istHand)
        {
            value *= 2;
        }
        letzte->replace(i, value);
        punkte->replace(i, value + punkte->at(i));
        //Negative Spielstände nicht gestattet, die Möglichkeit negative Werte einzugeben
        //sollte nur für Korrekturen genutzt werden
        if(punkte->at(i) < 0)
        {
            punkte->replace(i, 0);
        }

        eingaben->at(i)->setValue(0);
    }

    this->update();
}

/**
 * @brief Spieler::hand
 * @param istHand
 * zeigt an, ob ein Romme Hand gespielt wurde.
 */
void Spieler::hand(bool istHand)
{
    this->istHand = istHand;
}

/**
 * @brief Spieler::zuruck
 * Macht letzten Zug rückgängig
 */
void Spieler::zuruck()
{
    for(int i = 0; i < punkte->size(); ++i)
    {
        punkte->replace(i, punkte->at(i) - letzte->at(i));
        letzte->replace(i, 0);
    }

    this->update();
}

/**
 * @brief Spieler::neuerSpieler
 * Fügt einen neuen Spieler hinzu
 */
void Spieler::neuerSpieler()
{
    punkte->push_back(0);
    letzte->push_back(0);

    QSpinBox* neuI = new QSpinBox();
    eingabelayout->addWidget(neuI);

    neuI->setParent(this);
    neuI->setValue(0);
    neuI->setMaximum(1000);
    neuI->setMinimum(-1000);
    neuI->setMinimumHeight(20);
    neuI->setMinimumWidth(40);
    neuI->setVisible(true);
    eingaben->push_back(neuI);


    QLineEdit* neuN = new QLineEdit;
    namenlayout->addWidget(neuN, 0, 0);

    neuN->setParent(this);
    neuN->setText("Name");
    neuN->setMinimumHeight(20);
    neuN->setMinimumWidth(40);
    neuN->setVisible(true);
    spielername->push_back(neuN);

    this->layout();
    this->update();
}

/**
 * @brief Spieler::neuesSpiel
 * setzt das Spiel zurück
 */
void Spieler::neuesSpiel()
{
    for(int i = spielername->size() - 1; i >= 0; --i)
    {
        namenlayout->removeWidget(spielername->at(i));
        delete(spielername->at(i));

        eingabelayout->removeWidget(eingaben->at(i));
        delete(eingaben->at(i));
    }

    spielername->clear();
    eingaben->clear();
    punkte->clear();
    letzte->clear();

    neuerSpieler();
    neuerSpieler();
    this->layout();
    this->update();
}

void Spieler::sperren(bool lock)
{
    if(lock)
    {
        for(int i = 0; i < spielername->size(); ++i)
        {
            spielername->at(i)->setFocusPolicy(Qt::StrongFocus);
        }
    }
    else
    {
        for(int i = 0; i < spielername->size(); ++i)
        {
            spielername->at(i)->setFocusPolicy(Qt::ClickFocus);
        }
    }
}

void Spieler::paintEvent(QPaintEvent* event)
{
    int width = 0;
    int height;
    if(spielername->size() == 0)
    {
        width = this->width();
    }
    else
    {
        width = spielername->first()->width();
    }
    height = spielername->first()->y()
              - (eingaben->first()->y() + eingaben->first()->height() + 10);

    int stretchfactor = 1;
    int maxval = 0;
    for(int i = 0; i < punkte->size(); i++)
    {
        if(punkte->at(i) > punkte->at(maxval))
        {
            maxval = i;
        }
    }
    stretchfactor = (punkte->at(maxval) / height) + 1;

    QPainter diagram(this);
    diagram.setPen(Qt::black);

    for(int i = 0; i < eingaben->size(); ++i)
    {
        diagram.setBrush(farben[i%farben.size()]);
        diagram.drawRect(eingaben->at(i)->x(),
                         eingaben->at(i)->y()
                                + eingaben->at(i)->height()
                                + height - punkte->at(i) / stretchfactor,
                         width,
                         punkte->at(i) / stretchfactor);
        diagram.drawText(eingaben->at(i)->x() + 10, height, QString::number(punkte->at(i)));
    }
}
