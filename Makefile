TARGET 						= t
OBJS 						= main.c command.c

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

clean:
	rm -f $(TARGET) *.o
