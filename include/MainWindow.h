#pragma once

#include <QMainWindow>

class QCheckBox;
class QLineEdit;
class QPushButton;
class QTextEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void chooseIcon();
    void chooseScript();
    void generateApplication();

private:
    QLineEdit *appNameEdit = nullptr;
    QLineEdit *commandEdit = nullptr;
    QLineEdit *iconPathEdit = nullptr;
    QCheckBox *autostartCheck = nullptr;
    QTextEdit *outputText = nullptr;
    QPushButton *generateButton = nullptr;

    void setupUi();
    void appendOutput(const QString &message);
};
