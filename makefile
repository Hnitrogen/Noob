output: boss.o employee.o manager.o wm.o workerManager.o 
	g++ boss.o employee.o manager.o wm.o workerManager.o

boss.o: boss.cpp Boss.h
	g++ -c boss.cpp

employee.o: employee.cpp Employee.h
	g++ -c employee.cpp

workerManager.o: workerManager.cpp WorkerManager.h
	g++ -c workerManager.cpp

manager.o: manager.cpp manager.h
	g++ -c manager.cpp

wm.o: wm.cpp Worker.h manager.h Employee.h Boss.h
	g++ -c wm.cpp


clean:
	rm *.o
