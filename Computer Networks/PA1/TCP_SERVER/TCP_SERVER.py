import socket 

IP = socket.gethostbyname(socket.gethostname())
PORT = 12345
ADDR = (IP,PORT)

def main():
    #create server and bind the socket
    print("[Starting]")
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(ADDR)

    #listen for client
    server.listen()
    print("[Listening]")

    while True:
        #connect client
        conn,addr = server.accept()
        print(f"[Client Connected]")

        #recieve filename
        filename = conn.recv(1024).decode()
        print("[RECV] File name")

        #send confirmation to client
        conn.send("Filename received".encode())

        try:
            file = open(filename,"w")
        except:
            print("Could not open/read file: {filename}")
            exit()

        #recieve and save file data
        data = conn.recv(1024).decode()
        print(f"[RECV] File data")
        file.write(data)

        #send confirmation to client
        conn.send("File data recieved".encode())

        #disconnect
        file.close()

        conn.close()
        print(f"[Disconnected]")


if __name__ == '__main__':
    main()



