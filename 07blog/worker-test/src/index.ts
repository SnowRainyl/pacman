/**
 * Welcome to Cloudflare Workers! This is your first worker.
 *
 * - Run `npm run dev` in your terminal to start a development server
 * - Open a browser tab at http://localhost:8787/ to see your worker in action
 * - Run `npm run deploy` to publish your worker
 *
 * Bind resources to your worker in `wrangler.jsonc`. After adding bindings, a type definition for the
 * `Env` object can be regenerated with `npm run cf-typegen`.
 *
 * Learn more at https://developers.cloudflare.com/workers/
 */

const instruction = `.^⋁^.
'. .'
  \`

dddddddddzzzz
OpenHeart protocol API

https://api.oh.dddddddddzzzz.org

Test with example.com as <domain>.

GET /<domain>/<uid> to look up reactions for <uid> under <domain>

POST /<domain>/<uid> to send an emoji

<uid> must not contain a forward slash.
<domain> owner has the right to remove data under its domain scope.

----- Test in CLI -----
Send emoji:
curl -d '<emoji>' -X POST 'https://api.oh.dddddddddzzzz.org/example.com/uid'

Get all emoji counts for /example.com/uid:
curl 'https://api.oh.dddddddddzzzz.org/example.com/uid'
`;

export default {
  async fetch(request, env) {
    if (request.method == 'OPTIONS') {
      return new Response(null, { headers });
    }
    if (request.method === 'GET') {
      if (url(request).pathname === '/') {
        return new Response(instruction, { headers });
      } else {
        return handleGet(request, env);
      }
    }
    if (request.method === 'POST') return handlePost(request, env);
  },
};

const headers = {
  "Access-Control-Allow-Origin": "*",
  "Access-Control-Allow-Methods": "GET,POST",
  "Access-Control-Max-Age": "86400",
};

function error(text, code = 400) {
  return new Response(text, { headers, status: code });
}

async function handleGet(request, env) {
  const [domain, ...uidParts] = url(request).pathname.slice(1).split('/');
  const uid = uidParts ? uidParts.join('/') : null;
  if (!domain || !uid) {
    return error('Domain or UID missing.');
  }

  const list = {};
  const emojis = ["❤️", "👍", "😂", "🎉"]; // Add expected emojis here

  // Fetch counts for each emoji directly
  for (const emoji of emojis) {
    const key = `${domain}:${uid}:${emoji}`;
    const value = await env.worker_test_kv.get(key);
    if (value) {
      list[emoji] = Number(value);
    }
  }

  return new Response(
    JSON.stringify(list, null, 2), // Return only the found counts
    { headers: { ...headers, "Content-Type": "application/json;charset=UTF-8" } }
  );
}

function url(request) {
  return new URL(request.url);
}

async function handlePost(request, env) {
  const urlObject = url(request);
  const path = urlObject.pathname.slice(1);
  if (path === '') return error('Pathname missing');

  const [domain, ...uidParts] = path.split('/');
  const uid = uidParts ? uidParts.join('/') : '';
  if (uid.length < 1) return error('UID required.');

  const id = [encodeURI(domain), uid].join(':');
  const emoji = ensureEmoji(await request.text());
  if (!emoji) return error('Request body should contain an emoji');

  const key = `${id}:${emoji}`;
  const currentCount = Number(await env.worker_test_kv.get(key) || 0);
  await env.worker_test_kv.put(key, (currentCount + 1).toString());

  const redirection = urlObject.searchParams.get('redirect');
  if (redirection !== null) {
    headers['Location'] = redirection || request.headers.get('Referer');
    return new Response('recorded', { headers, status: 303 });
  } else {
    return new Response('recorded', { headers });
  }
}

function ensureEmoji(emoji) {
  const segments = Array.from(
    new Intl.Segmenter({ granularity: 'grapheme' }).segment(emoji.trim())
  );
  const parsedEmoji = segments.length > 0 ? segments[0].segment : null;

  if (/\p{Emoji}/u.test(parsedEmoji)) return parsedEmoji;
}
