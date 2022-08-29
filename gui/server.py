import socket

HOST = '127.0.0.1'
PORT = 5555

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()

    while True: 
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                request = conn.recv(32)
                if not request:
                    break
                
                # dekodowanie
                request = str(request, 'ascii')

                # budowanie odpowiedzi
                response = "SERWER " + request
                response = bytes(response, 'ascii')
                response += bytes(1024 - len(response))

                conn.sendall(response)