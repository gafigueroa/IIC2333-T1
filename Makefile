all:
	gcc -o simulator main.c FileReader.c Scheduler.c Queue.c Process.c -lm