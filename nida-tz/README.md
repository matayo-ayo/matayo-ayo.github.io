# nida-tz
Fetch Tanzania nida data

### installation
```bash
npm install nida-tz
```

For better result you need `axios and dotenv` dependencies installed

### usage
This library work with two addition dependency that are ` axios ` and ` dotenv ` modules installed. To install run both ` npm i axios dotenv `
- It uses asynchronous function to make a request ` async - await `
- Function takes two parameters that are nida number and http method ` post ` or ` get `
- functionName(nidaNumber, post)  or functionName(nidaNumber, get)

#### How to use the library

## 1 Syntax
```bash
# Syntax
async functionName(parameters);

# sample
const nidatz = require('nida-tz');
const nin = "12345123451234512345"; # define nida
async function mainFunction() => {
    const result = await nidatz.nidaData(nin);
}
```

---


## 2 Common Express Usage
```bash
# express usage
const express = require('express');
const app = expess();
const nidatz = require('nida-tz');

app.get('/route', async (req, res)=>{
    const nida = '123456789456123';
    const result = await nidatz.nidaData(nida);
    res.send(result);
})

app.listen(portNumber, ()=>{});
```

---

## 3 Express with Separate function
- Arrow function
```bash
# separate function usage
const express = require('express');
const app = express();
const nidatz = require('nida-tz');

# Arrow function usage
const nidaResult = async(nida)=>{
    return await nidatz.nidaData(nida);
};

# Express usage
app.get('/route', async (req, res)=>{
    const nida = '123456789456123';
    const result = await nidaResult(nida);
})
```
- Regular function
```bash
# separate function usage
const express = require('express');
const app = express();
const nidatz = require('nida-tz');

# Regular function
async function nidaResult(nida){
    return await nidatz.nidaData(nida);
};

# Express usage
app.get('/route', async (req, res)=>{
    const nida = '123456789456123';
    const result = await nidaResult(nida);
})
```