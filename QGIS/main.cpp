//#include "widget.h"

#include <QtCore>

#include <qgsapplication.h>
#include <qgsproviderregistry.h>
#include <qgssinglesymbolrendererv2.h>
#include <qgsmaplayerregistry.h>
#include <qgsvectorlayer.h>
#include <qgsmapcanvas.h>

#include <iostream>

int main(int argc, char *argv[])
{
    QgsApplication app(argc, argv, true);

    QString myPluginsDir        = "C:/Program Files/QGIS 2.16/qgis-2.16.2/src";
    QString myLayerPath         = "D:/Volat/QGIS/projects";
    QString myLayerBaseName     = "runtastic_20150606_2200.gpx";
    QString myProviderName      = "ogr";

    // Instantiate Provider Registry
    QgsProviderRegistry * preg = QgsProviderRegistry::instance(myPluginsDir);

    QgsVectorLayer * mypLayer =  new QgsVectorLayer(myLayerPath, myLayerBaseName, myProviderName);

    QgsSingleSymbolRendererV2 *mypRenderer = new QgsSingleSymbolRendererV2(QgsSymbolV2::defaultSymbol(mypLayer->geometryType()));


    QList <QgsMapCanvasLayer> myLayerSet;

    mypLayer->setRendererV2(mypRenderer);
    if (mypLayer->isValid())
    {
        qDebug("Layer is valid");
    }
    else
    {
        qDebug("Layer is NOT valid");
    }

    // Add the Vector Layer to the Layer Registry
    QgsMapLayerRegistry::instance()->addMapLayer(mypLayer, TRUE);
    // Add the Layer to the Layer Set
    myLayerSet.append(QgsMapCanvasLayer(mypLayer, TRUE));

    // Create the Map Canvas
    QgsMapCanvas * mypMapCanvas = new QgsMapCanvas(0, 0);
    mypMapCanvas->setExtent(mypLayer->extent());
    mypMapCanvas->enableAntiAliasing(true);
    mypMapCanvas->setCanvasColor(QColor(255, 255, 255));
    mypMapCanvas->freeze(false);
    // Set the Map Canvas Layer Set
    mypMapCanvas->setLayerSet(myLayerSet);
    mypMapCanvas->setVisible(true);
    mypMapCanvas->refresh();

    return app.exec();
}
