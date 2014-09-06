TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++14 \
		    -pthread \
		    -Wno-unused-local-typedefs \
		    -Wno-unused-variable \
		    -Wno-unused-parameter

QMAKE_LFLAGS += -std=c++14 \
		-pthread

unix {
    LIBS += -L/usr/local/lib \
	    -lboost_system

}

win32 {
    INCLUDEPATH += C:/Projects/Qt/boost_1_56_0
    LIBS += -LC:/Projects/Qt/boost_1_56_0/stage/lib/ \
	-lws2_32
    LIBS += C:/Projects/Qt/boost_1_56_0/stage/lib/libboost_system-mgw49-mt-1_56.a
}

CONFIG(debug, debug|release) {
    DEFINES += _DEBUG
}
