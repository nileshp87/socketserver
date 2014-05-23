var express = require('express');
var app = express();
app.use(express.urlencoded());

var SerialPort = require("serialport").SerialPort;
var serialport = new SerialPort("/dev/ttyACM1");
serialport.on('open', function(){
  console.log('Serial Port Opend');
  serialport.on('data', function(data){
      console.log(data[0]);
  });
});
app.get('/', function(req, res){
    res.sendfile('index.html');
});

var status = [0,0,0,0];

app.get('/status', function(req,res){
	res.send(status);
});

app.post('/setPlug', function(req, res){
	console.log(req.body);
	status[parseInt(req.body.plug)] = parseInt(req.body.state);
	var mod = parseInt(req.body.state) == 0 ? 5 : 1;
	mod += parseInt(req.body.plug);
	serialport.write(mod+"");
	res.send(true);
});

app.listen(8080);