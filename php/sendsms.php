<?php
include "conf.php";

$data = array(
			"sender" => $SENDER,
			"receivers" => $RECEIVERS,
			"content" => $CONTENT,
		);

$ch = curl_init("https://api.bluehouselab.com/smscenter/v1.0/sendsms");
curl_setopt($ch, CURLOPT_TIMEOUT, 30);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($ch, CURLOPT_USERPWD, "$APPID:$APIKEY");
curl_setopt($ch, CURLOPT_HTTPHEADER, Array("Content-Type: application/json; charset=utf-8"));
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));



$response = curl_exec($ch);
$response_header = curl_getinfo($ch);
echo $response_header["http_code"]."\n";
print_r(json_decode($response, true));
curl_close($ch);
?>
