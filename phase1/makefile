
a.out: main.o jeeker.o user.o text.o comment.o jeek.o interface.o func.o notification.o
	g++ main.o jeeker.o user.o text.o comment.o jeek.o interface.o func.o notification.o
notification.o: notification.cpp
	g++ -c notification.cpp
func.o: func.cpp
	g++ -c func.cpp
main.o: main.cpp
	g++ -c main.cpp
jeeker.o: jeeker.cpp
	g++ -std=c++11 -c jeeker.cpp
user.o: user.cpp
	g++ -c user.cpp
text.o: text.cpp
	g++ -c text.cpp
comment.o: comment.cpp
	g++ -c comment.cpp
jeek.o : jeek.cpp
	g++ -c jeek.cpp
interface.o : interface.cpp
	g++ -c interface.cpp
clean:
	rm -f *.o a.out
