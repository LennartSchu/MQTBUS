#include "mainwindow.h"

#include <QDebug>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QVBoxLayout>

#include <climits>

namespace {
constexpr int Height { 420 };
constexpr int Width { 860 };

const QString Localhost { "127.0.0.1" };

constexpr std::uint_least16_t MaxPort { std::numeric_limits<std::uint_least16_t>::max() };
constexpr std::uint_least16_t ModbusPort { 502 };
} // namespace

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{
    resize(Width, Height);

    debugField.setReadOnly(true);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* connectionLayout = new QHBoxLayout;

    ipAddrLabel.setText("IP-Address");
    portLabel.setText("Port");

    ipAddrEdit.setText(Localhost);
    ipAddrEdit.setInputMask("000.000.000.000; ");

    portEdit.setValidator(new QIntValidator(0, MaxPort, this));
    portEdit.setText(QString::fromStdString(std::to_string(ModbusPort)));

    QVBoxLayout* ipAddrLayout = new QVBoxLayout;
    QGroupBox* ipAddrBox = new QGroupBox;
    ipAddrLayout->addWidget(&ipAddrLabel);
    ipAddrLayout->addWidget(&ipAddrEdit);
    ipAddrBox->setLayout(ipAddrLayout);

    QVBoxLayout* portLayout = new QVBoxLayout;
    QGroupBox* portBox = new QGroupBox;
    portLayout->addWidget(&portLabel);
    portLayout->addWidget(&portEdit);
    portBox->setLayout(portLayout);

    connectionLayout->addWidget(&connectButton);
    connectionLayout->addWidget(ipAddrBox);
    connectionLayout->addWidget(portBox);

    mainLayout->addLayout(connectionLayout);

    mainLayout->addWidget(&debugField);

    connectButton.setText("Connect");

    connect(&connectButton, &QPushButton::clicked, this, &MainWindow::attemptConnection);
    connect(this, &MainWindow::connectOn, [this](const QString& ip, const std::uint16_t port) {
        // TODO: this should invoke a seperate connection
        debugField.setText(ip);
    });

    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::attemptConnection()
{
    const QString portStr = portEdit.text();
    const QString ipAddr = ipAddrEdit.text();

    try {
        const auto port = static_cast<std::uint_least16_t>(std::stol(portStr.toStdString()));

        emit connectOn(ipAddr, port);
    } catch (const std::exception& exc) {
        qDebug() << "Cannot read port '" + portStr + "': " + QString(exc.what());
    }
}
