import BaseHTTPServer, SimpleHTTPServer

binding = ('localhost', 8000)

SimpleHTTPServer.SimpleHTTPRequestHandler.extensions_map['.wasm'] = 'application/wasm'

print("open http://%s:%d" % binding)

httpd = BaseHTTPServer.HTTPServer(binding, SimpleHTTPServer.SimpleHTTPRequestHandler)
httpd.serve_forever()
