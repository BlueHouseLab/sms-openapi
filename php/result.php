<?php
include "conf.php";

if ($argc != 2) {
	error_log("Usage:\n  ".$argv[0]." delivery-id");
	exit(1);
}
$delivery_id = $argv[1];

$ch = curl_init("https://api.bluehouselab.com/smscenter/v1.0/result/".$delivery_id);
curl_setopt($ch, CURLOPT_TIMEOUT, 30);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($ch, CURLOPT_USERPWD, "$APPID:$APIKEY");

$response = curl_exec($ch);
$response_header = curl_getinfo($ch);
echo $response_header["http_code"]."\n";
print_r(json_decode($response, true));
curl_close($ch);
?>
