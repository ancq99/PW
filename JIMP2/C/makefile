src = $(wildcard src/*.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

LDFLAGS = -lm
CFLAGS = -O2

podlewanie: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) podlewanie out_bmp_txt.txt
	rm -f $(dep) out_bmp.bmp podlewaczki_txt.txt

open:
	xdg-open out_bmp.bmp
	xdg-open podlewaczki_txt.txt
