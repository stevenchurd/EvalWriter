import QtQuick 2.0

Rectangle {
    id: screenContainer
    width: 800
    height: 600

    GradingCriteriaModelPrototype {
        id: leftRect
        height: parent.height
        width:parent.width
        anchors.left: parent.left
    }

//    Column {
//        width: parent.width
//        GradingCriteriaRow{text: "This is a really long grading category name with a lot of stuff in it.  Blah blah blah, yadda, yadda, yadda.  Some more stuff that somehow needs to be displayed with some more things that probably should be accessable somehow."}
//        GradingCriteriaRow{text: "Short one"}
//    }
}
