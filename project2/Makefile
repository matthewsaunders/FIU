all:	dns_resolver

CFLAGS = -Wall

dns_resolver:	dns_resolver.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o core *~ dns_resolver

