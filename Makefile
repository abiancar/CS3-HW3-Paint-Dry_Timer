all:
	g++ -Wall TimeCodeTests.cpp TimeCode.cpp -o tCode

run:
	./tCode

try: all run



