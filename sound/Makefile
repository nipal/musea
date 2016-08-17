t1 :
	g++ -D__LINUX_ALSA__ -D__LITTLE_ENDIAN -I /usr/include/stk test.cpp -lstk -lpthread -lasound -o t1 


t2 :
	g++ -D__LINUX_ALSA__ -D__LITTLE_ENDIAN -I /usr/include/stk controlbee.cpp -lstk -lpthread -lasound /usr/lib/x86_64-linux-gnu/librtaudio.so.4v5 -o t2

clean :
	rm -rf t1 t2
