COMMON_OBJECTS = main.o buzzer.o
CPU = msp430g2553
CFLAGS = -mmcu=$(CPU) -I../h
LDFLAGS = -L/opt/ti/msp430_gcc/include

CC = msp430-elf-gcc
AS = msp430-elf-as

all: led.elf

led.elf: $(COMMON_OBJECTS) buzzer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@^ ./lib/libTimer.a

load: led.elf
	msp430loader.sh led.elf

clean:
	rm -f *.o *.elf *~ *.c#

main.o: led.h buzzer.h

buzzer.o: led.h

wdInterruptHandler.o: led.h
