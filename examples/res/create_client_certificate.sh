#!/bin/bash

mkdir keys
openssl req -x509 -nodes -days 1000 -newkey rsa:1024 -keyout keys/client_pkey.pem -out keys/client_cert.pem
