#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <iterator>
#include "WebServer.h"
#include <string>

// Handler for when a message is received from the client
void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
	// Parse out the client's request string e.g. GET /index.html HTTP/1.1
	std::istringstream iss(msg);
	std::cout << msg;

	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	// Some defaults for output to the client (404 file not found 'page')
	std::string content = "<h1>404 Not Found</h1>";
	std::string htmlFile = "/index.html";
	int errorCode = 404;

	// If the GET request is valid, try and get the name
	if (strncmp(msg, "POST /home.html", 15) == 0) {
		std::string m(msg);
		int i = m.find_last_of("\n");
		std::string param = m.substr(i + 1);

		// username=asfdasdf&password=ádfasdfasf
		int ii = param.find_first_of("&");
		std::string user = param.substr(9, ii - 9);
		std::string pass = param.substr(ii + 10);
		std::cout << "login with: " << user.c_str() << ":" << pass.c_str();
		bool log = false;
		for (i = 0; i < num; i++)
		{
			if (strcmp(user.c_str(), username[i]) == 0)
				if (strcmp(pass.c_str(), password[i]) == 0) {
					std::cout << "\login sucess\n";
					log = true;
					break;
				}
		}
		if (log) htmlFile = "/home.html";
		else htmlFile = "/fail.html";
	}

	if (strncmp(msg, "GET /", 5) == 0)
	{
		htmlFile = parsed[1];

		// If the file is just a slash, use index.html. This should really
		// be if it _ends_ in a slash. I'll leave that for you :)
		if (htmlFile == "/")
		{
			htmlFile = "/index.html";
		}
	}


	// Open the document in the local file system
	std::ifstream f(".\\fileHTMl" + htmlFile);

	// Check if it opened and if it did, grab the entire contents
	if (f.good())
	{
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		content = str;
		errorCode = 200;
	}

	f.close();

	// Write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << errorCode << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();
	int size = output.size() + 1;

	sendToClient(clientSocket, output.c_str(), size);
}

void WebServer::openFile()
{
	FILE *f;
	char filePath[] = "E:\\Documents\\201802 6th\\Lap trinh mang\\BTVN\\ProjectLapTrinhMang-20182-WebServer_Socket_Cpp\\list.txt";
	f = fopen(filePath, "r");
	int ret = 0;
	while (true) {
		ret = fscanf(f, "%s%s", username[num], password[num]);
		if (ret < 0)break;
		num++;
	}
	std::cout << "List username and password: \n";
	for (int i = 0; i < num; i++)
	{
		std::cout << username[i] << ":" << password[i] << std::endl;
	}
}

// Handler for client connections
void WebServer::onClientConnected(int clientSocket)
{

}

// Handler for client disconnections
void WebServer::onClientDisconnected(int clientSocket)
{

}