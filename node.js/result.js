var c = require('./conf');
var https = require("https");
var credential = 'Basic '+new Buffer(c.APPID+':'+c.APIKEY).toString('base64');
if(process.argv.length != 3) {
	console.log('Usage: ');
	console.log(' node result.js delivery-id');
	process.exit(1);
}
var deliveryid = process.argv[2];

var options = {
  host: 'api.bluehouselab.com',
  port: 443,
  path: '/smscenter/v1.0/result/'+deliveryid,
  headers: {
    'Authorization': credential,
  },
  method: 'GET'
};
var req = https.request(options, function(res) {
  console.log(res.statusCode);
  var body = "";
  res.on('data', function(d) {
    body += d;
  });
  res.on('end', function(d) {
  	if(res.statusCode==200)
		console.log(JSON.parse(body));
	else
		console.log(body);
  });
});
req.end();
req.on('error', function(e) {
	console.error(e);
});
