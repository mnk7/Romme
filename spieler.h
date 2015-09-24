#ifndef SPIELER_H
#define SPIELER_H

#include <QWidget>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPainter>
#include <QCheckBox>

#include <QVector>

class Spieler : public QWidget
{
    Q_OBJECT
public:
    explicit Spieler(QWidget *parent = 0);
    ~Spieler();
    void paintEvent(QPaintEvent *);

private:
    QHBoxLayout*           eingabelayout = new QHBoxLayout();
    QVBoxLayout*           horizontal = new QVBoxLayout();
    QHBoxLayout*           namenlayout = new QHBoxLayout();
    QVector<QLineEdit*>*   spielername = new QVector<QLineEdit*>();
    QVector<QSpinBox*>*    eingaben = new QVector<QSpinBox*>();
    QWidget*               space = new QWidget();
    QVector<int>*          punkte = new QVector<int>();
    QVector<int>*          letzte = new QVector<int>();

    QVector<Qt::GlobalColor> farben;

    bool istHand;

signals:
    void eingabe();

public slots:
    void addieren();
    void hand(bool);
    void zuruck();
    void neuerSpieler();
    void neuesSpiel();
    void sperren(bool);
};

#endif // SPIELER_H
