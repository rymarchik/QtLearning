import QtQuick 2.5

MessageForm {
    property string title
    property string message
    property variant backPage

    signal closeForm(variant backPage)

    button.onClicked: {
        closeForm(backPage)
    }

    Component.onCompleted: {
        messageText.text = message
        messageTitle.text = title
    }
}
