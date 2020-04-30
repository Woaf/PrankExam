#include "examwindow.h"

ExamWindow::ExamWindow (QWidget *parent) : QMainWindow (parent)
{

    setFixedSize (960, 680);
    setStyleSheet ("QWidget{background-color: rgb (255, 244, 234)}");

    // FIRST ROW ON THE LAYOUT
    examWindowTitle->setText ("Geometria dolgozat");
    examWindowTitle->setStyleSheet ("QLabel{font: 36pt; font-family: Arial}");
    gridLayout->addWidget (examWindowTitle, TITLE_PL, Qt::AlignTop | Qt::AlignHCenter);

    timeText->setStyleSheet ("QLabel{color: red; font-family: Arial; font: 36pt}");
    gridLayout->addWidget (timeText, TIMETEXT_PL, Qt::AlignCenter);

    // SECOND ROW ON THE LAYOUT
    lastNameField->setMaximumWidth (250);
    firstNameField->setMaximumWidth (250);
    nameForm->addRow ( (tr ("&Vezetéknév")), lastNameField);
    nameForm->addRow ( (tr ("&Keresztnév")), firstNameField);
    gridLayout->addLayout (nameForm, NAMEFORM_PL, Qt::AlignHCenter);

        // connecting input boxes to callback
        connect (lastNameField, SIGNAL (textChanged (QString)), this, SLOT (IsLineFilled ()));
        connect (firstNameField, SIGNAL (textChanged (QString)), this, SLOT (IsLineFilled ()));

    startButton->setFont (QFont ("Arial", 14));
    startButton->setDisabled (true);
    gridLayout->addWidget (startButton, STARTBT_PL, Qt::AlignHCenter);

        connect (startButton, SIGNAL (released()), this, SLOT (LockAndInitExam ()));

    timeLabel->setText (time->toString ("mm:ss"));
    timeLabel->setStyleSheet ("QLabel{color: red; font-family: Arial; font: 36pt}");
    gridLayout->addWidget (timeLabel, TIME_PL, Qt::AlignCenter);

        connect (timer, SIGNAL (timeout ()), this, SLOT (UpdateTimer ()));

    // THIRD ROW ON THE LAYOUT
    questionDescription->setText ("Teszt ismertető / kérdések helye");
    questionDescription->setFont(QFont ("Arial", 12));
    questionDescription->setWordWrap (true);
    questionDescription->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget (questionDescription, DESCQ_PL, Qt::AlignCenter);

    pointsLabel->setFont (QFont ("Arial", 14));
    pointsLabel->setText ("/pts");
    gridLayout->addWidget (pointsLabel, PTS_PL, Qt::AlignCenter);

    // FOURTH ROW ON THE LAYOUT
    answerForm->addRow (new QLabel ("A:"), answerField_1);
    answerForm->addRow (new QLabel ("B:"), answerField_2);
    answerForm->addRow (new QLabel ("C:"), answerField_3);
    answerForm->addRow (new QLabel ("D:"), answerField_4);
    EnableAllAnswerFields (false);
    gridLayout->addLayout (answerForm, ANSFORM_PL, Qt::AlignBottom);

    nextQuestionButton->setFont (QFont ("Arial", 14));
    nextQuestionButton->setDisabled (true);
    gridLayout->addWidget (nextQuestionButton, NEXTBT_PL, Qt::AlignLeft);

        connect (nextQuestionButton, SIGNAL (released ()), this, SLOT (NextQuestion()));

    // DISABLE TEST IF CORRUPTED
    /*
    if (!FirstTimeOpened ()) {
        lastNameField->setDisabled (true);
        firstNameField->setDisabled (true);
        startButton->setDisabled (true);
    }
    */

    contentHolder->setLayout (gridLayout);

    // EZZEL MEGY ÁT A FRISSSÍTÉS
    setCentralWidget (contentHolder);
}

void ExamWindow::EnableAllAnswerFields(bool enable)
{
    answerField_1->setEnabled (enable);
    answerField_2->setEnabled (enable);
    answerField_3->setEnabled (enable);
    answerField_4->setEnabled (enable);
}

void ExamWindow::SetQuestion(const char *questionText, int points)
{
    questionCounter++;
    answerField_1->clear (); answerField_2->clear (); answerField_3->clear (); answerField_4->clear ();
    questionDescription->setText (questionText);
    pointsLabel->setText (QString::number (points) + "/pts");
}

void ExamWindow::IsLineFilled ()
{
    startButton->setEnabled(
                !lastNameField->text ().isEmpty () &&
                !firstNameField->text ().isEmpty ()
                );
}

void ExamWindow::LockAndInitExam ()
{
    firstNameField->setDisabled (true);
    lastNameField->setDisabled (true);
    startButton->setDisabled (true);
    nextQuestionButton->setEnabled (true);
    EnableAllAnswerFields (true);
    NextQuestion ();

    timer->start (1000);
}

void ExamWindow::UpdateTimer ()
{
    if (time->minute () != 0) {
        *time = time->addSecs (-1);
        timeLabel->setText (time->toString ("mm:ss"));
    }

    if (time->minute () == 0) {
        if (time->second () != 0) {
            *time = time->addSecs (-1);
            timeLabel->setText (time->toString ("mm:ss"));
        } else {
            nextQuestionButton->setDisabled (true);
            EnableAllAnswerFields (false);
        }
    }
}

void ExamWindow::SpamWindow () const {
    for(int i = 0; i < 20; ++i) {
        QMessageBox::warning(nullptr, ("RickRoll'd"),
                                       ("Szünetre nem rakunk dolgozatot! lol"),
                                       QMessageBox::Ok);
    }

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system ("start https://youtu.be/oHg5SJYRHA0?autoplay=1");
        system ("start https://youtu.be/2Z4m4lnjxkY?autoplay=1");
        system ("start https://people.inf.elte.hu/bfazekas/qwidgets.png");
    #else
        system ("open https://youtu.be/oHg5SJYRHA0?autoplay=1");
        system ("open https://youtu.be/2Z4m4lnjxkY?autoplay=1");
        system ("open https://people.inf.elte.hu/bfazekas/qwidgets.png");
    #endif

}

void ExamWindow::NextQuestion()
{
    switch (questionCounter) {
        case 0:
            SetQuestion (ONE, 12);
            break;
        case 1:
            SetQuestion (TWO, 12);
            break;
        case 2:
            SetQuestion (THREE, 12);
            break;
        default:
                timer->stop ();
                EnableAllAnswerFields (false);
                nextQuestionButton->setDisabled (true);
                SpamWindow ();
            break;
    }
}
