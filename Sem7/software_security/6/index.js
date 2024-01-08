const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const { AuthenticationClient, UserInfoClient } = require('auth0');
const { auth } = require('express-oauth2-jwt-bearer');
require('dotenv').config();

const serverPort = 3000;
const credentials = {
    domain: process.env.MY_DOMAIN,
    clientId: process.env.MY_CLIENT_ID,
    clientSecret: process.env.MY_CLIENT_SECRET,
    audience: process.env.MY_AUDIENCE,
    username: process.env.USER_NAME_OAUTH,
    password: process.env.PASSWORD_OAUTH,
  }

const authClient = new AuthenticationClient({
    domain: credentials.domain,
    clientId: credentials.clientId,
    clientSecret: credentials.clientSecret,
});

const userInfo = new UserInfoClient({
    domain: credentials.domain,
});

const AUTH_HEADER = 'Authorization';

const checkJwt = auth({
    audience: credentials.audience,
    issuerBaseURL: `https://${credentials.domain}/`,
});

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.get('/api/redirect', (_, res) => {
    return res.redirect(301,new URL(`https://${credentials.domain}/authorize?client_id=${credentials.clientId}&redirect_uri=http%3A%2F%2Flocalhost%3A3000&response_type=code&response_mode=query&scope=offline_access+openid+profile&audience=${credentials.audience}&prompt=login`));
})


app.get('/api/callback', async (req, res) => {
    const code = req.query['code'];
    if (code) {
        const data = await authClient.oauth.authorizationCodeGrant({
            code,
            redirect_uri: 'http://localhost:3000/',
            grant_type: 'authorization_code'
        });
        return res.json(data.data);
    }
    return res.status(403).json({ error: 'Forbidden' });
});


app.get('/api/profile', checkJwt, async (req, res) => {
    const auth = req.auth;
    if (auth) {
        const token = auth.token;
        const { data } = await userInfo.getUserInfo(token);
        return res.json(data);
    }
    return res.status(401).json({ 'error': 'unauthorized' });
});

app.get('/', (_, res) => {
    res.sendFile(path.join(__dirname + '/index.html'));
});


app.post('/api/refresh', async (req, res) => {
    const refresh_token = req.get(AUTH_HEADER);
    const { data } = await authClient.oauth.refreshTokenGrant({ refresh_token });
    res.json(data).send();
});

app.listen(serverPort, () => {
    console.log(`listening on port ${serverPort}`)
})
