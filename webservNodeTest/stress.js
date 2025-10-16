const http = require('http');

const TOTAL_REQUESTS = 20000;
const HOST = 'localhost';
const PORT = 4242;
const PATH = '/';

function sendRequest(id) {
  return new Promise((resolve, reject) => {
    const options = {
      hostname: HOST,
      port: PORT,
      path: PATH,
      method: 'GET',
    };

    const req = http.request(options, (res) => {
      let data = '';

      res.on('data', (chunk) => {
        data += chunk;
      });

      res.on('end', () => {
        console.log(`Request #${id} completed with status: ${res.statusCode}`);
        resolve(data);
      });
    });

    req.on('error', (e) => {
      console.error(`Request #${id} failed: ${e.message}`);
      reject(e);
    });

    req.end();
  });
}

async function main() {
  const requests = [];
  for (let i = 0; i < TOTAL_REQUESTS; i++) {
    requests.push(sendRequest(i + 1));
  }

  try {
    await Promise.all(requests);
    console.log('All requests completed.');
  } catch (err) {
    console.error('One or more requests failed.');
  }
}

main();
