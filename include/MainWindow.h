#pragma once

#include <QMainWindow>

class QCheckBox;
class QComboBox;
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
    void refreshGeneratedApplications();
    void deleteSelectedApplication();

private:
    QLineEdit *appNameEdit = nullptr;
    QLineEdit *commandEdit = nullptr;
    QLineEdit *iconPathEdit = nullptr;
    QCheckBox *autostartCheck = nullptr;
    QComboBox *generatedAppsCombo = nullptr;
    QTextEdit *outputText = nullptr;
    QPushButton *generateButton = nullptr;
    QPushButton *deleteButton = nullptr;

    void setupUi();
    void appendOutput(const QString &message);
};
