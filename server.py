import SocketServer
import shelve
import os

FILE = '/tmp/CO_log'
HOST = ""
PORT = 2323

class cologger(SocketServer.BaseRequestHandler):

    def handle(self):
        reading = '0'
        data = self.request[0].strip().split(":")
        db = shelve.open(FILE)
        if not 'readings' in s:
            db['readings'] = []
        readings = db['readings']

        if data[0] >= 0 and len(data) > 1:
            levels.append(data[0], data[1])
            reading = str(data[1])

        db['readings'] = ci
        db.close()

        socket = self.request[1]
        socket.sendto(reading, self.client_address)

if __name__ == "__main__":
    print "Starting server..."
    server = SocketServer.UDPServer((HOST, PORT), cologger)
    server.serve_forever()
