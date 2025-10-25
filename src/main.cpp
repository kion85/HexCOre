#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QProcess>
#include <QDir>

class ShellWidget : public QWidget {
    Q_OBJECT
public:
    ShellWidget(QWidget *parent = nullptr) : QWidget(parent) {
        auto layout = new QVBoxLayout(this);
        
        dirLabel = new QLabel(this);
        commandLine = new QLineEdit(this);
        runButton = new QPushButton("Выполнить", this);
        outputArea = new QTextEdit(this);
        outputArea->setReadOnly(true);
        
        layout->addWidget(new QLabel("Текущая директория:"));
        layout->addWidget(dirLabel);
        layout->addWidget(new QLabel("Команда:"));
        layout->addWidget(commandLine);
        layout->addWidget(runButton);
        layout->addWidget(new QLabel("Результат:"));
        layout->addWidget(outputArea);
        
        currentDir = QDir::currentPath();
        updateDirLabel();
        
        connect(runButton, &QPushButton::clicked, this, &ShellWidget::executeCommand);
    }

private slots:
    void executeCommand() {
        QString cmd = commandLine->text().trimmed();
        if (cmd.isEmpty()) return;

        // Обработка cd
        if (cmd.startsWith("cd ")) {
            QString dir = cmd.section(" ", 1, 1);
            QDir newDir(currentDir);
            if (newDir.cd(dir)) {
                currentDir = newDir.absolutePath();
                updateDirLabel();
                outputArea->append("> " + cmd);
                outputArea->append("Перейдено в: " + currentDir);
            } else {
                outputArea->append("> " + cmd);
                outputArea->append("Ошибка: директория не найдена");
            }
        } else if (cmd == "ls") {
            // Вывод содержимого текущей директории
            QDir dir(currentDir);
            QStringList list = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);
            outputArea->append("> " + cmd);
            for (const QString &entry : list) {
                outputArea->append(entry);
            }
        } else {
            // Выполнение произвольной команды
            QProcess process;
            process.setWorkingDirectory(currentDir);
            process.start(cmd);
            process.waitForFinished(3000);
            QString result = process.readAllStandardOutput();
            outputArea->append("> " + cmd);
            outputArea->append(result);
        }
        commandLine->clear();
    }

private:
    void updateDirLabel() {
        dirLabel->setText(currentDir);
    }

    QLabel *dirLabel;
    QLineEdit *commandLine;
    QPushButton *runButton;
    QTextEdit *outputArea;
    QString currentDir;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ShellWidget shell;
    shell.show();
    return app.exec();
}

#include "main.moc"
