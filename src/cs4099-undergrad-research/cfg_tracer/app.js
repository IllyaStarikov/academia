const express = require('express')
const app = express()

app.use(express.static('public'))

app.get('/', (req, res) => res.sendFile(__dirname + '/public/ui.html'))

app.listen(3000, () => console.log('Example app listening on 3000'))
