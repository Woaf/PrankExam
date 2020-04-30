#ifndef EXAMWINDOW_H
#define EXAMWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <fstream>
#include <thread>
#include <iostream>

#define TITLE_PL        0, 0, 1, 3
#define TIMETEXT_PL     0, 3, 1, 1
#define TIME_PL         1, 3, 1, 1
#define NAMEFORM_PL     1, 0, 1, 2
#define STARTBT_PL      1, 2, 1, 1
#define DESCQ_PL        2, 0, 1, 3
#define PTS_PL          2, 3, 1, 1
#define ANSFORM_PL      3, 0, 1, 1
#define NEXTBT_PL       3, 3, 1, 1

#define ONE "1. We want to determine the height of a tree in our garden. The tree is 6 m away from a fence \
which is 2 m tall. On the other side of the fence, at a distance of 2 m there is a rod of height 1.5 m. The top \
of the rod, the fence and the tree are perfectly aligned.\n\
Hint: Draw a horizontal line at the top of the rod.\n\n\
A: How tall is the tree?\n\
B: What is the distance between the top of the rod and the top of the fence?\n\
C: What is the distance between the top of the fence and the top of the tree?\n\
D: How far away from the rod does the line connecting the tops of the rod, the fence and the tree reach the ground?"


#define TWO "2. One of the angle bisectors of an isosceles triangle divides the opposite side into two pieces of lengths 3 cm and 4.5 cm.\n\n\
A: How long is one of the legs of this isosceles triangle?\n\
B: How long is the base?\n\
C: How long is the height corresponding to the base?\n\
D: How long are the two line segments formed on the height by the angle-bisector of one of the base angles?"

#define THREE "3. One of the legs of a right-angled triangle is 24 cm long. Its projection onto the hypotenuse is 19.2 cm. \
A second triangle, similar to this one, has an area of 1944 cm^2.\n\n\
A: How long is the hypotenuse of the original triangle?\n\
B: How long is the altitude corresponding to the hypotenuse in the original triangle?\n\
C: How long is the other leg in the original triangle?\n\
D: What is the length of the shortest side of the second triangle?"

class ExamWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ExamWindow(QWidget *parent = nullptr);
private:
    int trials;

    QWidget* contentHolder          = new QWidget;

    QGridLayout* gridLayout         = new QGridLayout;

    QLabel* examWindowTitle         = new QLabel;
    QFormLayout* nameForm           = new QFormLayout;
    QLineEdit* lastNameField        = new QLineEdit;
    QLineEdit* firstNameField       = new QLineEdit;
    QPushButton* startButton        = new QPushButton ("Start");

    QTime* time                     = new QTime (0, 45, 0);
    QTimer* timer                   = new QTimer;
    QLabel* timeText                = new QLabel ("Time");
    QLabel* timeLabel               = new QLabel;

    QLabel* questionDescription     = new QLabel;
    QLabel* pointsLabel             = new QLabel;

    QFormLayout* answerForm         = new QFormLayout;
    QLineEdit* answerField_1        = new QLineEdit;
    QLineEdit* answerField_2        = new QLineEdit;
    QLineEdit* answerField_3        = new QLineEdit;
    QLineEdit* answerField_4        = new QLineEdit;

    /*IMAGE*/
    QWidget* iwidget                = new QWidget;
    QVBoxLayout* ilayout            = new QVBoxLayout;
    QLabel* iframe                  = new QLabel;
    QPixmap* image                  = new QPixmap ("qwidets.png");

    QPushButton* nextQuestionButton = new QPushButton ("Next question");
    int questionCounter             = 0;

    void EnableAllAnswerFields (bool enable);
    void SetQuestion (const char* questionText, int points);
    void SpamWindow () const;


signals:

private slots:
    void IsLineFilled ();
    void LockAndInitExam ();
    void UpdateTimer ();
    void NextQuestion ();
};

#endif // EXAMWINDOW_H
