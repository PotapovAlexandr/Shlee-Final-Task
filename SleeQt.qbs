import qbs

Project {
    name: "Viewer"
    minimumQbsVersion: "1.7.1"

    CppApplication {
        name: "ModelView"
        Depends {name : "Qt"; submodules : ['core', 'gui', 'svg', 'widgets', 'network', 'multimedia', 'multimediawidgets']}

        cpp.cxxLanguageVersion: "c++11"

        cpp.defines: [
            // The following define makes your compiler emit warnings if you use
            // any feature of Qt which as been marked deprecated (the exact warnings
            // depend on your compiler). Please consult the documentation of the
            // deprecated API in order to know how to port your code away from it.
            "QT_DEPRECATED_WARNINGS",

            // You can also make your code fail to compile if you use deprecated APIs.
            // In order to do so, uncomment the following line.
            // You can also select to disable deprecated APIs only up to a certain version of Qt.
            //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
        ]

        files: [
            "MyListItemDelegate.cpp",
            "MyListItemDelegate.h",
            "MyListView.cpp",
            "MyListView.h",
            "MyProxiModel.cpp",
            "MyProxiModel.h",
            "Screen.cpp",
            "Screen.h",
            "resource.qrc",
            'main.cpp',
            'm_form.ui',
            'MainWindow.h',
            'MainWindow.cpp',
            'Model.h',
            'Model.cpp',
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
