
import socket 
import os
from sys import byteorder

IP = socket.gethostbyname(socket.gethostname())
PORT = 12345
ADDR = (IP,PORT)
buff = 1024

def main():
    #create socket
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    seq_num = 0
    end_of_file = b"END_OF_FILE"

    #connect to server
    try:
        client.connect(ADDR)
        print("[Connected]")
    except socket.gaierror:
        print("Address-related error connecting to server")
        exit()

    #open file
    try:
        file = open("input.txt")
    except OSError:
        print("Could not open/read file")
        exit()


    #send file name
    client.send("input.txt".encode())

    while True:
        data = file.read(buff)
        if not data:
            break

        #Append sequence number to the begining of packet
        packet = seq_num.to_bytes(4, byteorder='big') + data.encode()

        #send packet to server
        client.send(packet)

    #Wait for ACK to server
    while True:
        #server confirmation
        ack,addr = client.recvfrom(buff)
        print(f"[SERVER]: {ack}")

        ack_sequence_num = int.from_bytes(ack, byteorder = 'big')
        if ack_sequence_num == seq_num:
            seq_num += 1
            break

    #Send EOF marker
    client.send(seq_num.to_bytes(4, byteorder='big') + end_of_file)
    

    file.close()
    client.close()



if __name__ == "__main__":
    main()