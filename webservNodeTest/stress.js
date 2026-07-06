const http = require('http');

const DEFAULT_TOTAL_REQUESTS = 1000;
const DEFAULT_HOST = 'localhost';
const DEFAULT_PORT = 4242;
const DEFAULT_PATH = '/';

function showHelp() {
  console.log(`Usage: node stress.js [options] [totalRequests host port path]

Options:
  -h, --help              Show this help message
  --requests <number>     Total number of requests to send
  --host <hostname>       Hostname to target
  --port <number>         Port to target
  --path <path>           Request path to target

Positional arguments are also supported in this order:
  totalRequests host port path

Defaults:
  totalRequests: ${DEFAULT_TOTAL_REQUESTS}
  host: ${DEFAULT_HOST}
  port: ${DEFAULT_PORT}
  path: ${DEFAULT_PATH}`);
}

function parseArgs(argv) {
  const config = {
    totalRequests: DEFAULT_TOTAL_REQUESTS,
    host: DEFAULT_HOST,
    port: DEFAULT_PORT,
    path: DEFAULT_PATH,
  };

  const positional = [];

  for (let i = 2; i < argv.length; i++) {
    const arg = argv[i];

    if (arg === '-h' || arg === '--help') {
      showHelp();
      process.exit(0);
    }

    if (arg === '--requests' && argv[i + 1]) {
      config.totalRequests = Number(argv[++i]);
      continue;
    }

    if (arg === '--host' && argv[i + 1]) {
      config.host = argv[++i];
      continue;
    }

    if (arg === '--port' && argv[i + 1]) {
      config.port = Number(argv[++i]);
      continue;
    }

    if (arg === '--path' && argv[i + 1]) {
      config.path = argv[++i];
      continue;
    }

    positional.push(arg);
  }

  if (positional[0]) {
    config.totalRequests = Number(positional[0]);
  }

  if (positional[1]) {
    config.host = positional[1];
  }

  if (positional[2]) {
    config.port = Number(positional[2]);
  }

  if (positional[3]) {
    config.path = positional[3];
  }

  if (!Number.isInteger(config.totalRequests) || config.totalRequests <= 0) {
    throw new Error('totalRequests must be a positive integer.');
  }

  if (!Number.isInteger(config.port) || config.port <= 0) {
    throw new Error('port must be a positive integer.');
  }

  return config;
}

const config = parseArgs(process.argv);

function sendRequest(id) {
  return new Promise((resolve, reject) => {
    const options = {
      hostname: config.host,
      port: config.port,
      path: config.path,
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
  for (let i = 0; i < config.totalRequests; i++) {
    requests.push(sendRequest(i + 1));
  }

  const results = await Promise.allSettled(requests);
  const failedRequests = results.filter((result) => result.status === 'rejected').length;

  if (failedRequests === 0) {
    console.log('All requests completed.');
    return;
  }

  console.error(`${failedRequests}/${config.totalRequests} requests failed.`);
}

main();
