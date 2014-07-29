#!/usr/bin/env ruby

require 'net/https'
require 'uri'
require 'json'
require './conf.rb'

uri = URI.parse('https://api.bluehouselab.com/smscenter/v1.0/sendsms')

http = Net::HTTP.new(uri.host, uri.port)
http.use_ssl = true
req = Net::HTTP::Post.new(uri.request_uri, initheader={'Content-Type' =>'application/json; charset=utf-8'})

req.basic_auth Conf::APPID, Conf::APIKEY
req.body = {
  sender: Conf::SENDER,
  receivers: Conf::RECEIVERS,
  content: Conf::CONTENT
}.to_json


resp = http.request(req)
puts resp.code
puts resp.body
