import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow
{
    id:root
    width: 800
    height: 250
    visible: true
    title: qsTr("TexttoSpeech")

    property string language:"tr"
    property string fileType:"mp3"

    ColumnLayout
    {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        TextField
        {
            id:speechtextTf
            font.bold: false
            font.pointSize: 16
            color: "grey"
            selectByMouse: true
            Layout.preferredWidth: root.width/1.2
            placeholderText: "Write text..."
        }

        SpinBox
        {
            id: speedSb
            property int decimals: 1
            property real realValue: 1.0
            property real realFrom: 0.0
            property real realTo: 2.0
            property real realStepSize: 0.1
            property real factor: Math.pow(10, decimals)
            stepSize: realStepSize*factor
            value: realValue*factor
            to : realTo*factor
            from : realFrom*factor
            validator: DoubleValidator
            {
                bottom: Math.min(speedSb.from, speedSb.to)*speedSb.factor
                top:  Math.max(speedSb.from, speedSb.to)*speedSb.factor
            }

            textFromValue: function(value, locale)
            {
                return parseFloat(value*1.0/factor).toFixed(decimals);
            }
        }
        RowLayout
        {
            ComboBox
            {
                id:languageCb
                model: ["Turkish","English","French","German","Russian"]
                onCurrentTextChanged:
                {
                    switch(languageCb.currentText)
                    {
                        case "Turkish":language="tr";break;
                        case "English":language="en";break;
                        case "French":language="fr";break;
                        case "German":language="de";break;
                        case "Russian":language="ru";break;
                    }
                }
            }
            TextField
            {
                id:filenameTf
                font.bold: false
                font.pointSize: 16
                color: "grey"
                selectByMouse: true
                Layout.preferredWidth: root.width/3
                placeholderText: "gtts"
            }
            ComboBox
            {
                id:typeCb
                model: ["mp3","wav"]
                onCurrentTextChanged:
                {
                    switch(typeCb.currentText)
                    {
                        case "mp3":fileType="mp3";break;
                        case "wav":fileType="wav";break;
                    }
                }
            }
        }


        RoundButton
        {
            id:btn_start
            Layout.alignment: Qt.AlignHCenter
            text:"Start"
            onClicked:
            {
                __dev.startSpeech(speechtextTf.text.toString(),language,speedSb.value/10,filenameTf.text.toString(),fileType)
            }
        }
    }
}
