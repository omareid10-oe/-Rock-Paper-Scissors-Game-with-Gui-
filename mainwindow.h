#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRockClicked();
    void onPaperClicked();
    void onScissorsClicked();
    void resetGame();

private:
    void setupUI();
    void playRound(char userChoice);

    // متغيرات النتيجة واللعبة (نفس منطق كودك)
    int countme;
    int countc;
    bool gameOver;

    // عناصر الواجهة
    QLabel *playerScoreLabel;
    QLabel *compScoreLabel;
    QLabel *playerChoiceDisplay;
    QLabel *compChoiceDisplay;
    QLabel *resultLabel;

    QPushButton *rockBtn;
    QPushButton *paperBtn;
    QPushButton *scissorsBtn;
    QPushButton *resetBtn;
};

#endif // MAINWINDOW_H