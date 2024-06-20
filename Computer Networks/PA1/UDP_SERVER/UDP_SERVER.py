import socket 
import os
from sys import byteorder

IP = socket.gethostbyname(socket.gethostname())
PORT = 12345
ADDR = (IP,PORT)
buff = 1024

def main():
    #used to track packet loss
    expected_sequence_num = 1

    #reasembled packets
    data = b""

    #end of file check
    end_of_file = False

    #create and bind the socket
    print("[Starting]")
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server.bind(ADDR)


    while True:
        conn, addr = server.recvfrom(buff)
        if not conn:
            break

        #recieve filename
        filename = server.recv(1024).decode()

        sequence_number = int.from_bytes(conn[:4], byteorder = 'big')
        packet_data = conn[4:]

        if sequence_number == expected_sequence_num:
            data += packet_data
            expected_sequence_num += 1

            #send ACK to client
            ack_packet = sequence_number.to_bytes(4, byteorder='big')
            server.sendto(ack_packet, addr)

            if packet_data.endswith(b"END_OF_FILE"):
                end_of_file = True
                break
        else:
            #Resend ACK for last correctly recieved packet
            ack_packet = (expected_sequence_num - 1).to_bytes(4, byteorder= 'big')
            server.sendto(ack_packet, addr)

    if end_of_file:
        #Save data
        try:
            file = open(filename,"w")
        except:
            print("Could not open/read file: {filename}")
            exit()

        file.write(data)
        print(f"File '{filename}' recieved and saved succefully")

    else:
        print("File reception failed: Did not recieve END_OF_FILE marker")

    file.close()
    conn.close()





if __name__ == "__main__":
    main()
