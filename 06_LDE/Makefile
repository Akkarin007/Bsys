#Ismail Zeybek
# Erstellt am: 11.10.2019
#
CC = gcc -g -fno-stack-protector
CFLAGS = -W -Wall -std=$(STD) -pedantic
CPPCHECK = cppcheck --enable=all --std=$(STD)
STD=c11
SET = filesize

TARGET = api_task1

.PHONY: all clean cppcheck

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).o

cppcheck: $(TARGET).c
	$(CPPCHECK) $<
