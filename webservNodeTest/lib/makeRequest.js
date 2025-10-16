const http = require('http');

function makeRequest({ path, method = 'GET', headers = {}, body = null}, callback){
	const options = {
		hostname: 'localhost',
		port: 4242,
		path,
		method,
		headers,
	}

	const req = http.request(options, (res) => {
		let data = '';
		res.on('data', chunk => (data += chunk));
		res.on('end', () => {
			callback(null, {
				status: res.statusCode,
				body: data,
				headers: res.headers,
			});
		});
	});

	req.on('error', callback);
	if (body)
			req.write(body);
	req.end();
}

module.exports = makeRequest;