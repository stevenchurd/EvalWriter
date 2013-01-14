import QtQuick 2.0

Component {
    id: courseListDelegate

    Item {
        width: 50
        height: 50

        Rectangle {
            Text { text: name }
        }
    }
}
