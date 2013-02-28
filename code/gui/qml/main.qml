import QtQuick 2.0

Rectangle {
    id: screenContainer
    width: 800
    height: 600

    Focus {
    }

    // this is expected to be globally accessable as a means of loading wizard pages
    WizardLoader {
        id: wizardContent
    }
}
