TARGET 						= t
OBJS 							= main.c param.c

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

clean:
	rm -f $(TARGET) *.o
