TARGET 						= t
OBJS 						= main.c command.c command_pack.c command_ssh.c util.c

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ -lcurses

clean:
	rm -f $(TARGET) *.o
