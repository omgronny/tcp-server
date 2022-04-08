all:
	g++ client_folder/*.c -pthread -o client_folder/client
	g++ server_folder/*.c -pthread -o server_folder/server

clean:
	rm -f client_folder/client
	rm -f server_folder/server