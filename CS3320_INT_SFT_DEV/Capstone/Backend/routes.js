const express = require('express');
const router = express.Router();

// GET books based on status
router.get('/', async (req, res) => {
    const { status } = req.query;

    try
    {
        const query = status ? { status } : {};

        const books = await req.db.collection('Books').find(query).toArray();
        res.status(200).json(books);
    } catch (err)
    {
        res.status(500).json({ error: err.message});
    }
});

// GET specific books full details
router.get("/details", async (req, res) => {
    const { title } = req.query; 

    try 
    {
        const book = await req.db.collection("Books").findOne({ title });

        if (!book) 
        {
            return res.status(404).json({ error: "Book not found" });
        }

        res.json(book);
    } catch (err) 
    {
        res.status(500).json({ error: "Error fetching book details" });
    }
});

// POST checkin or out based on req.action
router.post('/', async (req, res) => {
    const { action, title, who} = req.body;

    try
    {   
        if (action === 'checkout')
        {
            const dueDate = new Date();
            dueDate.setDate(dueDate.getDate() + 7);

            const result = await req.db.collection('Books').updateOne(
                { title, status: 'available'},
                { $set: { status: 'checkedout', due: dueDate.toDateString(), who: who}}
            );

            // No matches
            if (result.matchedCount === 0)
            {
                res.status(404).json({ error: 'Book not available or not found'});
            }
            else // Match
            {
                res.status(200).json({ message: 'Book checked out', dueDate: dueDate.toDateString() })
            }
        }
        else if (action === 'checkin')
        {
            const result = await req.db.collection('Books').updateOne(
                { title, status: 'checkedout'},
                { $set: {status: 'available', due: "", who: "" }}
            );

            if (result.matchedCount === 0)
            {
                res.status(404).json({ error: 'Book available or not found'});
            }
            else
            {
                res.status(200).json({ message: 'Book checked in' });
            }
        }
        else
        {
            res.status(400).json({ error: 'Invalid action specified' });
        }
    } catch (err)
    {
        res.status(500).json({ error: err.message });
    }
});

module.exports = router;