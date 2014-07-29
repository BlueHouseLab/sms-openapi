#!/usr/bin/env ruby

require 'net/https'
require 'uri'
require './conf.rb'
if ARGV.size != 1
	puts 'Usage:'
	puts ' '+__FILE__+' delivery-id'
	exit
end
did = ARGV[0]

uri = URI.parse('https://api.bluehouselab.com/smscenter/v1.0/result/'+did)

http = Net::HTTP.new(uri.host, uri.port)
http.use_ssl = true
req = Net::HTTP::Get.new(uri.request_uri)
req.basic_auth Conf::APPID, Conf::APIKEY

resp = http.request(req)
puts resp.code
puts resp.body
