#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>
#include <QChar>

bool clearTrigger=false;
bool EqualTrigger=false;
int pnum=0;
int initial=0;
int andnum=0;
int ornum=0;
QStack<int>num;
QStack<char>op;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(initial));
    QPushButton *numButtons[10];
    for(int i=0;i < 10 ; ++i)
    {
        QString  butName="Button"+ QString::number(i);
        numButtons[i]=Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,
                SLOT(NumPressed()));
    }
    connect(ui->Add,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->LeftParenthesis,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->RightParenthesis,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->And,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Or,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Not,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals,SIGNAL(released()),this,
            SLOT(EqualButtonPressed()));
    connect(ui->Clear,SIGNAL(released()),this,
            SLOT(ClearButtonPressed()));
}


Calculator::~Calculator()
{
    delete ui;
}

bool isnumber(QString s)
{
    if (s >= '0' && s <= '9')
        return true;
    else  return false;
}

bool isoperator(QString s)
{
    if (s == '+' || s == '-'||s == '*' || s == '/'||s == '&' || s =='|'||s == '!' || s == '(' || s == ')')
        return true;
    else  return false;
}
bool isoperator2(QString s)
{
    if (s == '+' || s == '-'||s == '*' || s == '/'||s == '&' || s =='|')
        return true;
    else  return false;
}

void Calculator::NumPressed()
{
    QPushButton *button =(QPushButton *) sender();
    QString butVal = button->text();
          s+=butVal;
          ui->Display->setText(s);
}

void Calculator::MathButtonPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal= button -> text();
    s=s+butVal;
    ui->Display->setText(s);
}

int Calculator::priority(char op)
{
    switch(op)
    {
        case '+':  case '-': return 0;  break;
        case '&': return 3;break;
        case '|': return 2;break;
        case '!': return 4;break;
        case '*':  case '/':  return 1;  break;
        case '(':  case ')':  return -1;  break;
        case '=':    return -2;break;

    default:break;
    }
}

int Calculator::Calculate(const QString& s)
{
        char top;
        int a,b;


        for(int i=0;i<s.size();i++)
        {
            if(isnumber(s[i]))
            {
                int T=0;
                QString temp;

                temp += s[i];
                         while (isnumber(s[++i]))
                             temp += s[i];
                         T=temp.toInt();
                         num.push(T);
                         temp.clear();

            }
           if(!isnumber(s[i]))
           {
                if(isoperator2(s[i])&&isoperator2(s[i+1]))
                {
                    if(!(s[i]=='&'&&s[i+1]=='&')&&!(s[i]=='|'&&s[i+1]=='|'))
                        return -1;
                }
                else if (op.empty())
                       {
                         if(num.empty()&&(s[i]=='*'||s[i]=='/'||s[i]=='&'||s[i]=='|'))
                                      return -1;

                          else {

                                   op.push(s[i].toLatin1());
                                   if(s[i]=='(')
                                       pnum++;
                               }
                        }

                else {

                                top=op.top();

                            if (priority(s[i].toLatin1())>priority(top) || s[i] == '(')
                            {
                                op.push(s[i].toLatin1());
                                if(s[i]=='(')
                                    pnum++;
                            }
                            else
                            {
                                while (priority(s[i].toLatin1()) <= priority(top))
                                {

                                    if (top == '('&&s[i] == ')')
                                    {
                                        pnum--;++i;
                                    }
                                    else if(top == '!')
                                    {
                                        int k=num.top();
                                        num.pop();
                                        if(k==0)
                                            num.push(1);
                                        else {
                                            num.push(0);
                                        }
                                    }
                                   else if (top == '+')
                                     {
                                        a=num.top();
                                        num.pop();
                                        if(num.empty())
                                            num.push(0);
                                        b=num.top();
                                        num.pop();
                                         b += a;
                                         num.push(b);


                                     }
                                    else if(top == '-')
                                    {
                                         a=num.top();
                                         num.pop();
                                         if(num.empty()||s[i-3]=='(')
                                            num.push(0);
                                         b=num.top();
                                         num.pop();
                                         b-=a;
                                         num.push(b);


                                    }
                                    else if (top == '&')
                                    {
                                       if(andnum==0)
                                          andnum++;

                                       else {
                                           a=num.top();

                                           num.pop();
                                           b=num.top();

                                           num.pop();
                                           if(b!=0&&a!=0)
                                              num.push(1);
                                           else num.push(0);
                                           andnum=0;
                                       }

                                    }
                                    else if (top == '|')
                                    {
                                        if(ornum==0)
                                           ornum++;

                                        else {
                                            a=num.top();
                                            num.pop();
                                            b=num.top();
                                            num.pop();
                                            if(b==0&&a==0)
                                                num.push(0);
                                             else num.push(1);

                                            ornum=0;
                                        }


                                    }
                                    else if(top == '*'||top == '/')
                                    {
                                        a=num.top();
                                        num.pop();
                                        b=num.top();
                                        num.pop();
                                        if (top == '*')
                                       {
                                           b *= a;
                                           num.push(b);
                                       }
                                       else if (top == '/')
                                       {
                                           if(a==0)
                                               return -1;
                                           else {
                                               b /= a;
                                              num.push(b);
                                           }
                                       }
                                    }


                                    op.pop();
                                    if(!op.empty())
                                      top=op.top();
                                    if(op.empty()) break;
                                }
                                op.push(s[i].toLatin1());

                                if(s[i]=='=')
                                 {
                                    if(pnum!=0)
                                    {
                                        return -1;
                                    }
                                     int  solution=0;
                                      op.pop();

                                      solution=num.top();
                                      num.pop();
                                      return solution;
                                 }
                        }
                    }
            }
        }
}
void Calculator::ClearButtonPressed()
{
    clearTrigger=false;
    QPushButton *button = (QPushButton *)sender();
    QString butVal= button -> text();

    if(QString::compare(butVal,"C",Qt::CaseInsensitive)==0)
    {
        clearTrigger=true;
    }
    s.clear();

    ui->Display->setText(s);

}

void Calculator::EqualButtonPressed()
{

    QPushButton *button = (QPushButton *)sender();
    QString butVal= button -> text();
    s=s+butVal;

    ui->Display->setText(s);

    int  solution=0;
    solution=Calculate(s);
    if(solution==-1)
        ui->Display->setText("ERROR!");


    else ui->Display->setText(QString::number(solution));
}
