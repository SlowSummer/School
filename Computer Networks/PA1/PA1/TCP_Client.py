import socket

IP = socket.gethostbyname(socket.gethostname())
PORT = 12345
ADDR = (IP,PORT)

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    #connect to server
    try:
        client.connect(ADDR)
    except socket.gaierror:
        print("Address-related error connecting to server")
        exit()


    #open file
    try:
        file = open("input.txt")
    except OSError:
        print("Could not open/read file")
        exit()

    data = file.read()

    #send file name
    client.send("input.txt".encode())

    #server confirmation
    msg = client.recv(1024).decode()
    print(f"[SERVER]: {msg}")

    #send file data
    try:
        client.send(data.encode())
    except socket.error:
        print("Error sending data")
        exit()

    #server confirmation
    msg = client.recv(1024).decode()
    print(f"[SERVER]: {msg}")

    #disconnect
    file.close()
    client.close()
    print(f"[Disconnected]")

if __name__ == "__main__":
    main()
    