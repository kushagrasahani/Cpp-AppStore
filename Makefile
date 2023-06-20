all: clean myAppStore

clean:
	rm -f myAppStore core*
myAppStore:
	g++ -g -Wall main.cc -o myAppStore
