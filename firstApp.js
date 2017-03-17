//Load the libraries

var mraa = require('mraa');
var restify = require('restify');

// create a http server
var server = restify.createServer();

// use a body parser, needed for post request with body
server.use(restify.bodyParser());

// Set the route with callback function method GET and POST
server.get('/gpio/:id', getValue);
server.post('/gpio/:id', setValue);

function getValue(req, res, next)
{
// check if all parameters are present
    if(req.params.id === undefined || req.params.value === undefined){
        res.json({error: "missing value"});
    }
    else{
        // connect the mraa lib to the GPIO needed
        var currentPin = new mraa.Gpio(req.params.id);
       
        // set it in input to read data
        currentPin.dir(mraa.DIR_IN);

        // send response with reading the GPIO
        res.json({value: currentPin.read(),id: req.params.id, dir: mraa.DIR_IN});
    }
    next();
}

function setValue(req, res, next)
{
// check if all parameters are present

    if(req.params.id === undefined || req.params.value === undefined){
        res.json({error: "missing value"});
    }
    else{

        // connect the mraa lib to the GPIO needed
        var currentPin = new mraa.Gpio(req.params.id);
       
        // set it in output to write data
        currentPin.dir(mraa.DIR_OUT);
       
        // write the output needed
        currentPin.write(req.params.value);
       
        // send response to client
        res.json({value: req.params.value,id: req.params.id, dir: mraa.DIR_OUT});
    }
    next();
}
