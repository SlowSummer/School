const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const { MongoClient } = require('mongodb');
const booksRoutes = require('./routes.js');

const app = express();

// Middleware
app.use(cors());
app.use(bodyParser.json());


let db;
const client = new MongoClient('mongodb+srv://andrewbracken08:ajb286@library.uiytn.mongodb.net/?retryWrites=true&w=majority&appName=Library');
client.connect().then(() => {
    console.log('Connected to MongoDB');
    db = client.db('CapstoneDB');
}).catch(error => console.error('Error connecting to MongoDB: ', error));;

app.use((req, res, next) =>{
    req.db = db;
    next();
});

// Mount Routes
app.use('/books', booksRoutes);


// Start Server
const PORT = 3000;
app.listen(PORT, () => console.log(`Server running on http://localhost:${PORT}`));