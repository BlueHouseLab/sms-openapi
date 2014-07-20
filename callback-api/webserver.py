from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        print 'GET', self.path
        self.send_response(204)
        self.end_headers()

    def do_POST(self):
        print 'POST', self.path
        print self.rfile
        length = int(self.headers['content-length'])
        print self.rfile.read(length)
        self.send_response(204)
        self.end_headers()

def main(port):
    try:
        print 'Trying to listen with port', port
        server = HTTPServer(('', port), MyHandler)
        print 'Put "http://hostname:%d/sms/callback.cgi" into API Key issued list as Callback URL' % port
        print '\nStarted httpserver...'
        server.serve_forever()
    except KeyboardInterrupt:
        server.socket.close()

if __name__ == '__main__':
    import sys
    port = 8080
    if len(sys.argv) > 1:
        try:
            port = int(sys.argv[1])
        except ValueError:
            pass
    main(port)

