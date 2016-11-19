def parse_request(env):
	try:
		request_body_size = int(env.get('CONTENT_LENGTH', 0))
	except (ValueError):
		request_body_size = 0

	return 'Privet mir ili Hello World!\nRequest method: ' + env['REQUEST_METHOD'] + '\nQuery string: ' + env['QUERY_STRING'] + '\nWsgi input (post): ' + env['wsgi.input'].read(request_body_size) + '\n'

def application(environ, start_response):
	status = '200 OK'
	response_headers = [('Content-type','text/plain')]
	start_response(status, response_headers)

	return [parse_request(environ)]
