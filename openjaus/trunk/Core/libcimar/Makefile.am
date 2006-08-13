lib_LIBRARIES = libcimar.a
libcimar_a_SOURCES = src/bres.c \
                   src/datagramPacket.c \
                   src/datagramSocket.c \
                   src/greatCircle.c \
                   src/inetAddress.c \
                   src/logLib.c \
                   src/multicastSocket.c \
                   src/networkInterface.c \
                   src/pointGg.c \
                   src/pointLla.c \
                   src/pointUtm.c \
                   src/portLib.c \
                   src/properties.c \
                   src/queue.c \
                   src/timeLib.c \
                   src/torusBuffer.c \
                   src/vector.c \
                   src/utm/cproj.c \
                   src/utm/utmfor.c \
                   src/utm/utminv.c \
                   src/utm/utmLib.c
libcimar_a_LIBADD = $(INTLLIBS) $(ALLOCA)
INCLUDES = -I ./include/ -I ./include/cimar/ -I ./include/cimar/utm/
