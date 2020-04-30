#include <QApplication>

#include <examwindow.h>

int main(int argc, char *argv[])
{
    QApplication a (argc, argv);

    ExamWindow ew;
    ew.show ();

    return a.exec();
}
