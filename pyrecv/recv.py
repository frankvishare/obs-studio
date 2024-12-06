import socket

def udp_server(host='0.0.0.0', port=50000):
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    # Bind the socket to the address and port
    sock.bind((host, port))
    
    print(f"Listening on UDP port {port}...")

    filename = 'recv.bit'

    with open(filename, 'wb') as f:  # Open file in binary append mode
        while True:
            # Receive data from the socket
            data, addr = sock.recvfrom(1024)  # Buffer size is 1024 bytes
            #print(data)
            print(f"Received {len(data)} bytes from {addr}")

            # Write the received data to the file
            f.write(data)  # Save the raw bytes to the file
            f.flush()  # Optional: flush the file buffer after each write

def tcp_server(host='127.0.0.1', port=50000):
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the address and port
    sock.bind((host, port))
    sock.listen(1)  # Listen for incoming connections
    print(f"Server listening on {host}:{port}")

    while True:
        # Wait for a connection
        client_socket, client_address = sock.accept()
        print(f"Connection from {client_address}")

        try:
            filename = 'recv.bit'

            with open(filename, 'wb') as f:  # Open file in binary append mode
                while True:
                    # Receive data from the socket
                    data = client_socket.recv(1024)  # Buffer size is 1024 bytes
                    #print(data)
                    print(f"Received {len(data)} bytes")

                    # Write the received data to the file
                    f.write(data)  # Save the raw bytes to the file
                    f.flush()  # Optional: flush the file buffer after each write
            
        finally:
            # Clean up the connection
            client_socket.close()
            print("Connection closed")

if __name__ == "__main__":
    #udp_server()
    tcp_server()