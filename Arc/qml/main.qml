
// Copyright 2015 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

import QtQuick 2.3
import QtQuick.Controls 1.2
import ArcGIS.Runtime 10.26

ApplicationWindow {
    id: appWindow
    width: 800
    height: 600
    title: "ArcGIS viewer"

    Map {
        focus: true
        id: map
        anchors.fill: parent
//        wrapAroundEnabled: true
        extent: sanFrancisco

//        ArcGISTiledMapServiceLayer {
//            url: "http://server.arcgisonline.com/ArcGIS/rest/services/World_Street_Map/MapServer"
//        }

        ArcGISLocalTiledLayer {
            path: ArcGISRuntime.installDirectory + "/sdk/samples/data/tpks/SanFrancisco.tpk"
        }

//        FeatureLayer {
//            id: featureLayer
//            featureTable: GeodatabaseFeatureTable {
//                geodatabase: gdb.valid ? gdb : null
//                featureServiceLayerId: 0
//            }
//        }


        Rectangle {
            id: controlsBackground
            color: "black"
            radius: 5
            opacity: 0.75
            anchors {
                fill: controls
                margins: -10
            }
        }

        Column {
            id: controls
            spacing: 20
            anchors {
                top: parent.top
                left: parent.left
                margins: 20
            }

            Button {
                id: startPointButton
                text: "Start Point"
                checkable: true
                exclusiveGroup: routeButtons
            }

            Button {
                id: endPointButton
                text: "End Point"
                width: startPointButton.width
                checkable: true
                exclusiveGroup: routeButtons
            }

            Button {
                id: solveButton
                text: "Solve"
                width: startPointButton.width

                onClicked: {
                    routeTaskParameters.stops = routePoints;
                    localRouteTask.solve(routeTaskParameters);
                }
            }

        }

        ExclusiveGroup {
            id: routeButtons
        }


        NAFeaturesAsFeature {
            id: routePoints
        }

        GraphicsLayer {
            id: startGraphics
            renderer: SimpleRenderer {
                SimpleMarkerSymbol {
                    style: Enums.SimpleMarkerSymbolStyleCircle
                    size: 10
                    color: "green"
                }
            }
        }

        GraphicsLayer {
            id: endGraphics
            renderer: SimpleRenderer {
                SimpleMarkerSymbol {
                    style: Enums.SimpleMarkerSymbolStyleCircle
                    size: 10
                    color: "red"
                }
            }
        }

        GraphicsLayer {
            id: routeGraphics
            renderer: SimpleRenderer {
                SimpleLineSymbol {
                    style: Enums.SimpleLineSymbolStyleSolid
                    width: 3
                    color: "turquoise"
                }
            }
        }

        onMouseClicked: {
            var graphic = ArcGISRuntime.createObject("Graphic");
            graphic.geometry = mouse.mapPoint;

            if (startPointButton.checked) {
                if (startGraphics.numberOfGraphics === 0)
                    startGraphics.addGraphic(graphic);
            }
            else if (endPointButton.checked) {
                if (endGraphics.numberOfGraphics === 0)
                    endGraphics.addGraphic(graphic);
            }
            var routeGraphic = graphic.clone();
            routePoints.addFeature(routeGraphic);
        }



        LocalRouteTask {
            id: localRouteTask
            network: "Streets_ND"
            database: ArcGISRuntime.installDirectory + "/sdk/samples/data/disconnected/route/SanFrancisco/RuntimeSanFrancisco.geodatabase"
            onSolveStatusChanged: {
                console.log("solving")
                if (solveStatus === Enums.SolveStatusCompleted){
                    for (var index = 0; index < solveResult.routes.length; index++)
                    {
                        var route = solveResult.routes[index];
                        var graphic = route.route;
                        routeGraphics.addGraphic(graphic);
                    }
                }
                else if (solveStatus === Enums.SolveStatusErrored){
                    console.log(solveError.message);
                }
            }
        }

        LocalRouteTaskParameters {
            id: routeTaskParameters
            task: localRouteTask
            returnDirections: true
            outSpatialReference: map.spatialReference
        }

    }

//    Geodatabase {
//         id: gdb
//         path: "D:\\Volat\\Qt\\projects\\Arc\\DamageInspection6.geodatabase"
//    }

    Envelope {
        id: sanFrancisco
        xMin: -122.520
        yMin: 37.8365
        xMax: -122.3023
        yMax: 37.6985
        spatialReference: map.spatialReference
    }
}
