TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    application.c \
    console.c \
    console_callbacks.c \
    gui.c \
    main.c \
    sf_console/sf_cmd_comms.c \
    sf_console/sf_console.c \

win32: LIBS += -L$$PWD/./ -ltx

INCLUDEPATH += $$PWD/. \
    $$PWD/sf_console \

DEPENDPATH += $$PWD/.

HEADERS += \
    application.h \
    console.h \
    gui.h \
    sf_console/sf_cmd_comms.h \
    sf_console/sf_comms_api.h \
    sf_console/sf_console.h \
    sf_console/sf_console_api.h \
    sf_console/sf_console_cfg.h \
    sf_console/sf_console_private_api.h \
    tx_api.h \
    tx_port.h

DISTFILES += \
    tx.lib
