#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void attemptConnection();

signals:
    void connectOn(const QString& ipAddr, const std::uint_least16_t port);

private:
    QPushButton connectButton;
    QLineEdit portEdit;
    QLineEdit ipAddrEdit;
    QLineEdit debugField;
    QLabel ipAddrLabel;
    QLabel portLabel;
};
#endif // MAINWINDOW_H
