#!/bin/bash

mkdir keys
openssl req -x509 -nodes -days 1000 -newkey rsa:1024 -keyout keys/server_pkey.pem -out keys/server_cert.pem
