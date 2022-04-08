all:
	g++ client_folder/*.c -o client_folder/client
	g++ server_folder/*.c -o server_folder/server

clean:
	rm -f client_folder/client
	rm -f server_folder/server