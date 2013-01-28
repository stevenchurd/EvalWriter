import QtQuick 2.0

Rectangle {
    id: screenContainer
    width: 800
    height: 600


//    ListView {
//        anchors.fill: parent
//        model:5
//        delegate: Item {
//            height: itemRow.height
//            width: parent.width
//            CriteriaItemRow {
//                id: itemRow
//                text: "This is a test string"
//                criteriaLevelIndicator: 4
//            }
//        }
//    }

//    ListView {
//        anchors.fill: parent
//        model: 5
//        delegate: Item {
//            width: parent.width
//            height: parent.height
//            ListView {
//                model: 5
//                header: Item {
//                    height: itemHeader.height
//                    width: parent.width

//                    Text { id: itemHeader; text: "A really long string." }
//                }
//                delegate: Item {
//                    height: itemDelegate.height
//                    width: parent.width

//                    Text { id: itemDelegate; text: "A really long delegate string." }
//                }
//            }
//        }
//    }

    ListView {
        height: contentHeight
        width: parent.width
        model: 5
        delegate:
            ListView {
                height: contentHeight
                width: parent.width

                model: 5
                header: Item {
                    height: headerItem.height
                    width: parent.width
                    Text {
                        id: headerItem
                        text: "This is a really long string in the header"
                        wrapMode: Text.WordWrap
                    }
                }
                delegate: Item {
                    height: itemRow.height
                    width: parent.width
                    Text {
                        id: itemRow
                        text: "This is a really long string in the lists"
                        wrapMode: Text.WordWrap
                    }
                }
            }
    }

//    GradingCriteriaModelPrototype {
//        id: leftRect
//        height: parent.height
//        width:parent.width
//        anchors.left: parent.left
//    }

//    Column {
//        width: parent.width
//        GradingCriteriaRow{text: "This is a really long grading category name with a lot of stuff in it.  Blah blah blah, yadda, yadda, yadda.  Some more stuff that somehow needs to be displayed with some more things that probably should be accessable somehow."}
//        GradingCriteriaRow{text: "Short one"}
//    }
}
