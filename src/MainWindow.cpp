#include "MainWindow.h"

#include "DesktopEntryWriter.h"

#include <QCheckBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

namespace {
QString shellSingleQuote(const QString &value)
{
    QString quoted = value;
    quoted.replace("'", "'\\''");
    return "'" + quoted + "'";
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

void MainWindow::setupUi()
{
    setWindowTitle("StartupApp");
    resize(720, 420);

    auto *central = new QWidget(this);
    auto *rootLayout = new QVBoxLayout(central);

    auto *title = new QLabel("Ubuntu 桌面应用生成器", central);
    QFont titleFont = title->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    title->setFont(titleFont);

    appNameEdit = new QLineEdit(central);
    appNameEdit->setPlaceholderText("例如：clear");

    commandEdit = new QLineEdit(central);
    commandEdit->setPlaceholderText("例如：bash /home/slam/test.sh，或直接选择脚本文件");

    auto *commandRow = new QWidget(central);
    auto *commandRowLayout = new QHBoxLayout(commandRow);
    commandRowLayout->setContentsMargins(0, 0, 0, 0);
    commandRowLayout->addWidget(commandEdit, 1);
    auto *scriptButton = new QPushButton("选择脚本", commandRow);
    commandRowLayout->addWidget(scriptButton);

    iconPathEdit = new QLineEdit(central);
    iconPathEdit->setPlaceholderText("可选：选择 png/jpg/svg 等图片");

    auto *iconRow = new QWidget(central);
    auto *iconRowLayout = new QHBoxLayout(iconRow);
    iconRowLayout->setContentsMargins(0, 0, 0, 0);
    iconRowLayout->addWidget(iconPathEdit, 1);
    auto *iconButton = new QPushButton("选择图片", iconRow);
    iconRowLayout->addWidget(iconButton);

    autostartCheck = new QCheckBox("开机自启动", central);

    auto *form = new QFormLayout;
    form->addRow("应用名", appNameEdit);
    form->addRow("运行命令或脚本", commandRow);
    form->addRow("图片", iconRow);
    form->addRow("", autostartCheck);

    generateButton = new QPushButton("生成应用", central);
    generateButton->setMinimumHeight(36);

    outputText = new QTextEdit(central);
    outputText->setReadOnly(true);
    outputText->setMinimumHeight(120);

    rootLayout->addWidget(title);
    rootLayout->addSpacing(8);
    rootLayout->addLayout(form);
    rootLayout->addWidget(generateButton);
    rootLayout->addWidget(outputText, 1);

    setCentralWidget(central);

    connect(iconButton, &QPushButton::clicked, this, &MainWindow::chooseIcon);
    connect(scriptButton, &QPushButton::clicked, this, &MainWindow::chooseScript);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateApplication);
}

void MainWindow::chooseIcon()
{
    const QString path = QFileDialog::getOpenFileName(
        this,
        "选择应用图片",
        QString(),
        "Images (*.png *.jpg *.jpeg *.svg *.xpm);;All Files (*)");

    if (!path.isEmpty()) {
        iconPathEdit->setText(path);
    }
}

void MainWindow::chooseScript()
{
    const QString path = QFileDialog::getOpenFileName(
        this,
        "选择脚本或可执行文件",
        QString(),
        "Scripts and executables (*.sh *.bash *.py);;All Files (*)");

    if (!path.isEmpty()) {
        const QString suffix = QFileInfo(path).suffix().toLower();
        if (suffix == "sh" || suffix == "bash") {
            commandEdit->setText("bash " + shellSingleQuote(path));
        } else if (suffix == "py") {
            commandEdit->setText("python3 " + shellSingleQuote(path));
        } else {
            commandEdit->setText(shellSingleQuote(path));
        }
    }
}

void MainWindow::generateApplication()
{
    DesktopAppConfig config;
    config.appName = appNameEdit->text();
    config.command = commandEdit->text();
    config.iconPath = iconPathEdit->text();
    config.autostart = autostartCheck->isChecked();

    const QString validationError = DesktopEntryWriter::validate(config);
    if (!validationError.isEmpty()) {
        QMessageBox::warning(this, "输入不完整", validationError);
        return;
    }

    try {
        const DesktopAppResult result = DesktopEntryWriter::write(config);
        appendOutput("已生成应用：" + result.appId);
        appendOutput("应用入口：" + result.desktopFilePath);
        if (!result.installedIconPath.isEmpty()) {
            appendOutput("应用图片：" + result.installedIconPath);
        }
        if (config.autostart) {
            appendOutput("开机自启动：" + result.autostartFilePath);
        } else {
            appendOutput("开机自启动：未启用");
        }
        appendOutput("");
        QMessageBox::information(this, "完成", "桌面应用已生成。");
    } catch (const std::exception &error) {
        QMessageBox::critical(this, "生成失败", QString::fromUtf8(error.what()));
    }
}

void MainWindow::appendOutput(const QString &message)
{
    outputText->append(message);
}
