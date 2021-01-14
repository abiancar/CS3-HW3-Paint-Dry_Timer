all:
	g++ -Wall TimeCodeTests.cpp TimeCode.cpp -o time-code
	g++ -Wall NasaLaunchAnalysis.cpp TimeCode.cpp -o nasa
	g++ -Wall PaintDryTimerStarter.cpp TimeCode.cpp -o pdt
run:
	./tCode
run2:
	./nasa
run3:
	./pdt

try: all run

try2: all run2

try3: all run3



