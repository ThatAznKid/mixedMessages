signals.out: main.c
	gcc main.c -o signals.out

run: signals.out
	./signals.out

clean:
	rm signals.out
	rm test