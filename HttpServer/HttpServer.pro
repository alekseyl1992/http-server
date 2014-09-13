TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server/Server.cpp \
    server/config/ConfigParser.cpp \
    server/fs/FileSupplier.cpp \
    server/fs/File.cpp \
    server/http/request/RequestParser.cpp \
    server/http/response/ResponseBuilder.cpp \
    TestRunner.cpp \
    test/http/request/RequestParserTest.cpp \
    server/http/response/Response.cpp \
    server/ServicePool.cpp

HEADERS += \
    Config.h \
    ConfigParser.h \
    Server.h \
    ConfigOpenError.h \
    ConfigParseError.h \
    server/Server.h \
    server/config/Config.h \
    server/config/ConfigOpenError.h \
    server/config/ConfigParseError.h \
    server/config/ConfigParser.h \
    server/fs/FileSupplier.h \
    server/fs/File.h \
    server/fs/FileNotFoundError.h \
    server/fs/FileNotInRootError.h \
    server/http/request/RequestParser.h \
    server/http/request/Request.h \
    server/http/request/RequestParseError.h \
    server/http/response/Response.h \
    server/http/response/ResponseBuilder.h \
    server/ServicePool.h


QMAKE_CXXFLAGS += -std=c++14 \
		    -pthread \
		    -Wno-unused-local-typedefs \
		    -Wno-unused-variable \
		    -Wno-unused-parameter

QMAKE_LFLAGS += -std=c++14 \
		-pthread

unix {
    LIBS += -L/usr/local/lib \
            -lboost_system \
            -lboost_filesystem \
            -lboost_test_exec_monitor
}

win32 {
    INCLUDEPATH += C:/Projects/Qt/boost_1_56_0
    LIBS += -LC:/Projects/Qt/boost_1_56_0/stage/lib/ \
	-lws2_32
    LIBS += C:/Projects/Qt/boost_1_56_0/stage/lib/libboost_system-mgw49-mt-1_56.a \
	    C:/Projects/Qt/boost_1_56_0/stage/lib/libboost_filesystem-mgw49-mt-1_56.a \
	    C:/Projects/Qt/boost_1_56_0/stage/lib/libboost_test_exec_monitor-mgw49-mt-1_56.a
}

CONFIG(debug, debug|release) {
    DEFINES += _DEBUG
}
