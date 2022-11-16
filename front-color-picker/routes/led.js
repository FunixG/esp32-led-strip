const express = require('express');
const router = express.Router();

const mqtt = require('mqtt');
const host = 'broker.emqx.io';
const port = '1883';
const topic = 'funix/led/salon';

const client = mqtt.connect('mqtt://' + host + ':' + port, {
    clean: true,
    connectTimeout: 4000,
    reconnectPeriod: 1000
});

client.on('connect', () => {
    client.subscribe(topic);
});

router.post('/', function(req, res, next) {
    const body = req.body;
    const red = body.r;
    const green = body.g;
    const blue = body.b;

    const str = 'r=' + red + ',g=' + green + ',b=' + blue;
    console.log('setColor: ' + str);
    client.publish(topic, str);
    res.send("{success: true}");
});

module.exports = router;
