import bb.cascades 1.0;

Page {
    Container {
        id: root
        layout: StackLayout { orientation: StackLayout.TopToBottom }
        Label {
            text: qsTr("Countly Tests")
            textStyle.base: SystemDefaults.TextStyles.BigText
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
        }
        Button {
            text: "eventFromCPP: one"
            onClicked: {
                _base.eventFromCpp("cppClick", "one");
            }
        }
        Button {
            text: "eventFromCPP: two"
            onClicked: {
                _base.eventFromCpp("cppClick", "two");
            }
        }
    }
}

