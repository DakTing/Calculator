#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QStack>
#include <QMainWindow>
#include <QString>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    QString s;
    int priority(char op);
    int Calculate(const QString& s);
private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ClearButtonPressed();


};

#endif // CALCULATOR_H
