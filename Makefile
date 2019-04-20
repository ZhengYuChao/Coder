SRC_C = $(wildcard *.c)
SRC_H = $(wildcard *.h)
OBJS = $(patsubst %.c,%.o,$(SRC_C))

TARGET = main

all: $(TARGET)

$(OBJS): %.o: %.c $(SRC_H)
	$(CC) $(TARGET_CFLAGS)  -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(TARGET_LDFLAGS)  -o $@ $^

clean:
	@echo "Cleaning..."
	$(RM) $(OBJS) $(TARGET)
