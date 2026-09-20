#include "mainwindow.h"
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    std::srand(std::time(nullptr)); // تجهيز الـ Random
    setupUI();
    resetGame();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    this->setWindowTitle("Rock Paper Scissors - Neon Arena");
    this->setFixedSize(420, 620);

    QWidget *central = new QWidget(this);
    this->setCentralWidget(central);

    // تصميم النيون والستايل الخرافي
    this->setStyleSheet(R"(
        QMainWindow { background-color: #080714; }

        QLabel#titleLabel {
            color: #ff007f;
            font-size: 22px;
            font-weight: bold;
            border: 2px solid #ff007f;
            border-radius: 12px;
            padding: 8px;
            background-color: #120f29;
        }

        /* كروت النتائج */
        QFrame#scoreFrame {
            background-color: #120f29;
            border: 1px solid #1f1b40;
            border-radius: 15px;
        }
        QLabel#scoreNumPlayer { color: #00f0ff; font-size: 32px; font-weight: bold; }
        QLabel#scoreNumComp { color: #ff007f; font-size: 32px; font-weight: bold; }
        QLabel#scoreText { color: #a0a0c0; font-size: 13px; font-weight: bold; }

        /* ساحة المواجهة VS */
        QLabel#choiceCard {
            background-color: #1a1638;
            border: 2px solid #2b255e;
            border-radius: 20px;
            font-size: 60px;
        }
        QLabel#vsLabel { color: #ffcc00; font-size: 24px; font-weight: 900; font-style: italic; }

        /* نص النتيجة */
        QLabel#resultLabel {
            font-size: 16px;
            font-weight: bold;
            background-color: #120f29;
            border-radius: 10px;
            padding: 10px;
            border: 1px solid #00f0ff;
        }

        /* أزرار اختيار الطوبة والورقة والمقص */
        QPushButton#actionBtn {
            background-color: #120f29;
            border: 2px solid #00f0ff;
            border-radius: 15px;
            font-size: 30px;
        }
        QPushButton#actionBtn:hover {
            background-color: #00f0ff;
            border-color: #ffffff;
        }
        QPushButton#actionBtn:disabled {
            border-color: #333355;
            background-color: #0a0818;
        }

        /* زر إعادة اللعب */
        QPushButton#resetBtn {
            background-color: #2b003b;
            color: #ff007f;
            border: 2px solid #ff007f;
            border-radius: 12px;
            font-size: 15px;
            font-weight: bold;
        }
        QPushButton#resetBtn:hover {
            background-color: #ff007f;
            color: #ffffff;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // 1. العنوان العلوي
    QLabel *titleLabel = new QLabel("⚡ ROCK PAPER SCISSORS ⚡", this);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // 2. شريط النتيجة (First to 3)
    QHBoxLayout *scoreLayout = new QHBoxLayout();

    // لاعب
    QVBoxLayout *pScoreBox = new QVBoxLayout();
    QLabel *pText = new QLabel("YOU", this); pText->setObjectName("scoreText"); pText->setAlignment(Qt::AlignCenter);
    playerScoreLabel = new QLabel("0", this); playerScoreLabel->setObjectName("scoreNumPlayer"); playerScoreLabel->setAlignment(Qt::AlignCenter);
    pScoreBox->addWidget(pText); pScoreBox->addWidget(playerScoreLabel);

    QLabel *targetText = new QLabel("FIRST TO 3\nWINS", this);
    targetText->setObjectName("scoreText");
    targetText->setAlignment(Qt::AlignCenter);

    // كمبيوتر
    QVBoxLayout *cScoreBox = new QVBoxLayout();
    QLabel *cText = new QLabel("COMPUTER", this); cText->setObjectName("scoreText"); cText->setAlignment(Qt::AlignCenter);
    compScoreLabel = new QLabel("0", this); compScoreLabel->setObjectName("scoreNumComp"); compScoreLabel->setAlignment(Qt::AlignCenter);
    cScoreBox->addWidget(cText); cScoreBox->addWidget(compScoreLabel);

    scoreLayout->addLayout(pScoreBox);
    scoreLayout->addWidget(targetText);
    scoreLayout->addLayout(cScoreBox);

    QFrame *scoreFrame = new QFrame(this);
    scoreFrame->setObjectName("scoreFrame");
    scoreFrame->setLayout(scoreLayout);
    mainLayout->addWidget(scoreFrame);

    // 3. ساحة المواجهة (VS Display)
    QHBoxLayout *arenaLayout = new QHBoxLayout();

    playerChoiceDisplay = new QLabel("❓", this);
    playerChoiceDisplay->setObjectName("choiceCard");
    playerChoiceDisplay->setFixedSize(110, 110);
    playerChoiceDisplay->setAlignment(Qt::AlignCenter);

    QLabel *vsLabel = new QLabel("VS", this);
    vsLabel->setObjectName("vsLabel");
    vsLabel->setAlignment(Qt::AlignCenter);

    compChoiceDisplay = new QLabel("❓", this);
    compChoiceDisplay->setObjectName("choiceCard");
    compChoiceDisplay->setFixedSize(110, 110);
    compChoiceDisplay->setAlignment(Qt::AlignCenter);

    arenaLayout->addWidget(playerChoiceDisplay);
    arenaLayout->addWidget(vsLabel);
    arenaLayout->addWidget(compChoiceDisplay);
    mainLayout->addLayout(arenaLayout);

    // 4. نص نتيجة الجولة
    resultLabel = new QLabel("CHOOSE YOUR MOVE!", this);
    resultLabel->setObjectName("resultLabel");
    resultLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(resultLabel);

    // 5. أزرار الاختيار (طوبة، ورقة، مقص)
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(10);

    rockBtn = new QPushButton("✊", this);
    rockBtn->setObjectName("actionBtn");
    rockBtn->setFixedHeight(70);
    connect(rockBtn, &QPushButton::clicked, this, &MainWindow::onRockClicked);

    paperBtn = new QPushButton("✋", this);
    paperBtn->setObjectName("actionBtn");
    paperBtn->setFixedHeight(70);
    connect(paperBtn, &QPushButton::clicked, this, &MainWindow::onPaperClicked);

    scissorsBtn = new QPushButton("✌️", this);
    scissorsBtn->setObjectName("actionBtn");
    scissorsBtn->setFixedHeight(70);
    connect(scissorsBtn, &QPushButton::clicked, this, &MainWindow::onScissorsClicked);

    buttonsLayout->addWidget(rockBtn);
    buttonsLayout->addWidget(paperBtn);
    buttonsLayout->addWidget(scissorsBtn);
    mainLayout->addLayout(buttonsLayout);

    // 6. زر إعادة اللعبة
    resetBtn = new QPushButton("RESTART GAME", this);
    resetBtn->setObjectName("resetBtn");
    resetBtn->setFixedHeight(45);
    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::resetGame);
    mainLayout->addWidget(resetBtn);
}

void MainWindow::resetGame()
{
    countme = 0;
    countc = 0;
    gameOver = false;

    playerScoreLabel->setText("0");
    compScoreLabel->setText("0");
    playerChoiceDisplay->setText("❓");
    compChoiceDisplay->setText("❓");

    resultLabel->setText("CHOOSE YOUR MOVE!");
    resultLabel->setStyleSheet("color: #00f0ff; border: 1px solid #00f0ff;");

    rockBtn->setEnabled(true);
    paperBtn->setEnabled(true);
    scissorsBtn->setEnabled(true);
}

void MainWindow::onRockClicked()     { playRound('R'); }
void MainWindow::onPaperClicked()    { playRound('P'); }
void MainWindow::onScissorsClicked() { playRound('S'); }

void MainWindow::playRound(char userChoice)
{
    if (gameOver) return;

    // 1. اختيار الكمبيوتر العشوائي (نفس كودك بالظبط)
    int randNum = std::rand() % 3;
    char compChoice;
    if (randNum == 0) compChoice = 'R';
    else if (randNum == 1) compChoice = 'P';
    else compChoice = 'S';

    // تحديث الإيموجي على الشاشة
    if (userChoice == 'R') playerChoiceDisplay->setText("✊");
    else if (userChoice == 'P') playerChoiceDisplay->setText("✋");
    else if (userChoice == 'S') playerChoiceDisplay->setText("✌️");

    if (compChoice == 'R') compChoiceDisplay->setText("✊");
    else if (compChoice == 'P') compChoiceDisplay->setText("✋");
    else if (compChoice == 'S') compChoiceDisplay->setText("✌️");

    // 2. تطبيق منطق الـ Score الخاص بكودك
    if (userChoice == compChoice) {
        resultLabel->setText("IT'S A DRAW! 🤝");
        resultLabel->setStyleSheet("color: #ffcc00; border: 1px solid #ffcc00;");
    }
    else if ((userChoice == 'R' && compChoice == 'S') ||
             (userChoice == 'P' && compChoice == 'R') ||
             (userChoice == 'S' && compChoice == 'P')) {
        countme++;
        resultLabel->setText("YOU WIN THIS ROUND! 🔥");
        resultLabel->setStyleSheet("color: #00f0ff; border: 1px solid #00f0ff;");
    }
    else {
        countc++;
        resultLabel->setText("COMPUTER WINS THIS ROUND! ⚡");
        resultLabel->setStyleSheet("color: #ff007f; border: 1px solid #ff007f;");
    }

    // تحديث النتيجة
    playerScoreLabel->setText(QString::number(countme));
    compScoreLabel->setText(QString::number(countc));

    // 3. فحص الفائز باللعبة (الوصول لـ 3 نقاط)
    if (countme == 3) {
        resultLabel->setText("🎉 VICTORY! YOU BEAT THE COMPUTER!");
        resultLabel->setStyleSheet("color: #00ff88; border: 2px solid #00ff88; font-size: 17px;");
        gameOver = true;
    } else if (countc == 3) {
        resultLabel->setText("💀 GAME OVER! COMPUTER WINS!");
        resultLabel->setStyleSheet("color: #ff0055; border: 2px solid #ff0055; font-size: 17px;");
        gameOver = true;
    }

    if (gameOver) {
        rockBtn->setEnabled(false);
        paperBtn->setEnabled(false);
        scissorsBtn->setEnabled(false);
    }
}