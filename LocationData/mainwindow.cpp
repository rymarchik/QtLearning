#include <QtPositioning>

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow()
        : QObject()
    {
        QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
        if (source) {
            connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), SLOT(positionUpdated(QGeoPositionInfo)));
            source->startUpdates();
        }
    }

private slots:
    void positionUpdated(const QGeoPositionInfo &info) {
        qDebug() << "Position updated:" << info;
    }

};
