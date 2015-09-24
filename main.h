#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>

namespace Ui {
class Main;
}

class Main : public QMainWindow
{
    Q_OBJECT

public:
    explicit Main(QWidget *parent = 0);
    ~Main();

public slots:
    void eingabe();
    void sperren();

signals:
    void lock(bool);

private:
    Ui::Main *ui;
    bool locked;
};

#endif // MAIN_H
