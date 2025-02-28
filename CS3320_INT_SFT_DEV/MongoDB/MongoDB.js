const express = require('express');
const {MongoClient} = require('mongodb');

const app = express();
const port = 3000;

const url = 'mongodb+srv://andrewbracken08:7QfjYmy9bFV4XTW0@expressrestdb.ockra.mongodb.net/?retryWrites=true&w=majority&appName=ExpressRestDB';


// CORS handler
app.use(function (req, res, next) {
  res.header('Access-Control-Allow-Origin', '*');
  res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,PATCH,DELETE,OPTIONS');
  res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization, Content-Length, X-Requested-With');
  if (req.method === 'OPTIONS') res.sendStatus(200);
  else next();
});

// mongo client
let db;

// Connect
const client = new MongoClient(url);
client.connect().then(() => {
    console.log('Connected to MongoDB');
    db = client.db('ExpressRestDB');
}).catch(error => console.error('Error connecting to MongoDB: ', error));;


// Helper function
const parseRequestBody = (req) =>
    new Promise((resolve, reject) => {
        let body = '';

        req.on('data', chunk =>{
            body += chunk.toString();
        });

        req.on('end', () => {
            resolve(JSON.parse(body));
        });
    });

// Routes
// GET books, query for availability
app.get('/books', async (req, res) => {
    const { avail } = req.query;

    // return blank for unfiltered list
    const query = avail === 'true' || avail === 'false' ? {avail: avail === 'true' } : {};

    //exclude mongodb _id with project
    const books = await db.collection('Books').find(query).project({_id: 0, id: 1, title: 1 }).toArray();
    res.status(200).json(books);
});

// GET book by id
app.get('/books/:id', async (req, res) => {
    const book = await db.collection('Books').findOne({ id: req.params.id }, { projection: { _id: 0}});

    if (book) 
    {
        res.status(200).json(book);
    } else 
    {
        res.status(404).json({ error: 'Book not found' });
    }
});

// POST new book
app.post('/books', async (req, res) => {

    const newBook = await parseRequestBody(req);
    const existingBook = await db.collection('Books').findOne({ id: newBook.id })

    // check if id already exists
    if (existingBook) 
    {
        res.status(403).json({ error: 'Book with this ID already exists' });
    } else // add book
    {
        await db.collection('Books').insertOne(newBook);
        res.status(201).json({ message: 'Book added successfully', book: newBook });
    }
});
    
// PUT update book
app.put('/books/:id', async (req, res) => {

    const updates = await parseRequestBody(req);
    const result = await db.collection('Books').updateOne(
        { id: req.params.id },
        { $set: updates},
    );

    if (result.matchedCount > 0) 
    {
        const updatedBook = await db.collection('Books').findOne({ id: req.params.id }, {projection: { _id: 0 }});
        res.status(200).json({ message: 'Book updated successfully', book: updatedBook });
    } else 
    {
        res.status(404).json({ error: 'Book not found' });
    }

});

// DELETE book
app.delete('/books/:id', async (req, res) => {
    const result = await db.collection('Books').deleteOne({ id: req.params.id });

    if (result.deletedCount > 0) 
    {
        res.status(200).json({ message: 'Book deleted successfully' });
    } else 
    {
        res.status(204).end();
    }
});

// Start server
app.listen(port, () => {
  console.log(`Library REST API running at http://localhost:${port}`);
});
