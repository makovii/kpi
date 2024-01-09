const uuid = require('uuid');
const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const dotenv = require('dotenv');
const port = 3000;
const jwt = require('jsonwebtoken');
const axios = require('axios');
const request = require('async-request')

dotenv.config();
const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

const GrantTypes = {
    PASSWORD: 'password',
    AUTHORIZATION_CODE: 'authorization_code',
    CLIENT_CREDENTIALS: 'client_credentials',
    IMPLICIT: 'implicit',
    REFRESH_TOKEN: 'refresh_token',
    PASSWORD_REALM: 'http://auth0.com/oauth/grant-type/password-realm',
};

app.get('/create-user', (req, res) => {
    return res.sendFile(path.join(__dirname + '/create-user.html'));
});

app.get('/', verifyToken, (req, res) => {
    res.json({
        username: req.user,
        exp: req.exp,
        logout: 'http://localhost:3000/logout'
    });
})

app.get('/logout', (req, res) => {
    res.redirect('/');
});

app.post('/api/login', async (req, res) => {
    const { username, password } = req.body;
    try {
        const response = await axios.post(`${process.env.MY_DOMAIN}oauth/token`, {
            grant_type: GrantTypes.PASSWORD_REALM,
            audience: process.env.MY_AUDIENCE,
            client_id: process.env.MY_ClientID,
            client_secret: process.env.MY_ClientSecret,
            scope: 'offline_access',
            realm: 'Username-Password-Authentication',
            username: username,
            password: password,
        }, {
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json'
            }
        });
        res.status(201).json({ access_token: response.data.access_token, refresh_token: response.data.refresh_token, username: username });
    } catch (error) {
        console.log(error)
        res.status(401).json({ error: error.response.data });

    }
});

app.post('/api/create', async (req, res) => {
    const { email, password } = req.body;
    try {
      const options = { 
        method: 'POST',
        url: `https://${process.env.MY_DOMAIN}/oauth/token`,
        headers: { 'content-type': 'application/json' },
        body: JSON.stringify({
          "client_id":`${process.env.MY_ClientID}`,
          "client_secret":`${process.env.MY_ClientSecret}`,
          "audience":`${process.env.MY_AUDIENCE}`,
          "grant_type":"client_credentials"
        })
      };
      
      await request(options, function (error, response, body) {
        if (error) throw new Error(error);
      
        console.log(body);
      });

      console.log(response)
      const response2 = await axios.post(`${process.env.MY_AUDIENCE}users`, {
        email: email,
        password: password,
        connection: 'Username-Password-Authentication'
    }, {
        headers: {
            'Content-Type': 'application/json',
            'Accept': 'application/json',
            'Authorization': `Bearer ${response.data.access_token}`
        }
    });
      res.status(201).json({ message: 'User created' });
    } catch (error) {
        res.status(401).json({ error });

    }
});

app.post('/api/refresh', async (req, res) => {
    const { refresh_token } = req.body;
    try {
        const response = await axios.post(`${process.env.API_URL}oauth/token`, {
            grant_type: GrantTypes.REFRESH_TOKEN,
            audience: process.env.AUDIENCE_URL,
            client_id: process.env.CLIENT_ID,
            client_secret: process.env.CLIENT_SECRET,
            refresh_token: refresh_token,
            scope: 'offline_access',
            realm: 'Username-Password-Authentication',
        }, {
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json'
            }
        });
        res.json({ access_token: response.data.access_token, refresh_token: response.data.refresh_token });
    } catch (error) {
        res.status(401).json({ error: error.response.data });

    }
});

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})

async function verifyToken(req, res, next) {
    const token = req.header('Authorization');
    if (!token) {
        return res.sendFile(path.join(__dirname + '/index.html'));
    }

    decoded = jwt.decode(token);

    if (!decoded) {
        return res.sendFile(path.join(__dirname + '/index.html'));
    }
    const currentTimestampInSeconds = Math.floor(Date.now() / 1000);
    if (decoded.exp > currentTimestampInSeconds) {
        const response = await axios.get(`${process.env.AUDIENCE_URL}users/${decoded.sub}`, {
            headers: {
                'Authorization': `Bearer ${token}`
            }
        });
        req.user = response.data.name;
        req.exp = decoded.exp;
    }
    next();
}
