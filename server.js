var express = require('express');
var app = express();
var fs = require('fs');
var config = ["Socket 1", "Socket 2", "Socket 3", "Socket 4"];
function configLoad(){
	fs.exists('config.json', function(exists){
	if(exists)
		config = JSON.parse(fs.readFileSync('config.json'));
	else
		fs.writeFileSync('config.json', JSON.stringify(config));
	});
}
configLoad();
app.use(express.urlencoded());
var sp = require("serialport");
var SerialPort = sp.SerialPort;
var serialport = new SerialPort("/dev/ttyACM0", { parser: sp.parsers.readline("\n")});
serialport.on('open', function(){
  console.log('Serial Port Opened');
  serialport.on('data', function(data){
      console.log(i + ": " + data[0]);
      status[i] = parseInt(data[0]);
      defaults[i] = parseInt(data[0]);
      i++;
      if(i < 4)
      	getNext();
      else{
      	app.listen(8080);
      	console.log("Now Listening on port 8080...");
      }
  });
});
var i = 0;
setTimeout(getNext, 3000);
function getNext(){
	serialport.write(String.fromCharCode('r'.charCodeAt(0) + i));
}
app.get('/', function(req, res){
    res.sendfile('index.html');
});

var status = [0,0,0,0];
var defaults = [0,0,0,0];

app.get('/status', function(req,res){
	res.send(status);
});

app.get('/config', function(req,res){
	res.send(config);
});

app.post('/setPlug', function(req, res){
	status[parseInt(req.body.plug)] = parseInt(req.body.state);
	var mod = parseInt(req.body.state) == 0 ? 5 : 1;
	mod += parseInt(req.body.plug);
	serialport.write(mod+"");
	res.send(true);
});

app.post('/setDefault', function(req, res){
	defaults[parseInt(req.body.plug)] = parseInt(req.body.state);
	var mod = parseInt(req.body.state) == 0 ? 4 : 0;
	mod += parseInt(req.body.plug);
	serialport.write(String.fromCharCode('a'.charCodeAt(0) + mod));
	res.send(true);
});

app.post('/toggleSocket', function(req, res){
	status[parseInt(req.body.plug)] = status[parseInt(req.body.plug)] == 0 ? 1 : 0;
	var mod = status[parseInt(req.body.plug)] == 0 ? 5 : 1;
	mod += parseInt(req.body.plug);
	serialport.write(mod+"");
	res.send(true);
});

app.get('/getDefaults', function(req, res){
	res.send(defaults);
});

app.get('/reloadConfiguration', function(req, res){
	configLoad();
});