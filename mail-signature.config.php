<?php

// DKIM is used to sign e-mails. If you change your RSA key, apply modifications to the DNS DKIM record of the mailing (sub)domain too !
// Disclaimer : the php openssl extension can be buggy with Windows, try with Linux first

// To generate a new private key with Linux :
// openssl genrsa -des3 -out private.pem 1024
// Then get the public key
// openssl rsa -in private.pem -out public.pem -outform PEM -pubout

// Edit with your own info :

define('MAIL_RSA_PASSPHRASE', "");

define('MAIL_RSA_PRIV',
'-----BEGIN RSA PRIVATE KEY-----
MIICXwIBAAKBgQDTgb5Tzu+D89Chdt13PDQ3FKLPbcukF0aXq6+k4rnOxesSOhNS
u7H7f6XIftKrRaYVRzaXJ4IDUxb/T395nBnrz7f+9BCxV2Y/DRT3wRs3s1gnrX5d
9WlxFQnTa3QycMI8J/yxkgULf9IFsesCmX8oI4JkneoPnjPZzi7GNTrGXQIDAQAB
AoGBAMK8DjSzrqra7Rf8jOOfNqQQB+bbvEcUdxZmKI2zgkfyygA6IFhoH/LjEAyN
WAIBWmz06Do7UeUlt2LSGxgotWNPeqJMMiKC+oDNHcojayRkn1otusEDRdjtfGcT
Lf+i+tXoLHL6Y+7Hx2A4NG/Xs5B+ZR8DkscMYmw4RcbzmC8BAkEA7oDMSBckEzOC
B2BYouA0TqqHYwNrp0pokJWisvg1H62S+1nmmTW3kw3vbC/3H6ofPsiMELcRISxU
h8Gbld6GDQJBAOMF8SdU4CVGDT5TOyPGQct4OZ1k6Dupgv8PYhbwBZgb1emtYtQx
MRXtYFEDY86I0cPUjS7AMcs0y5s8jJ8O/ZECQQCJ0Di6S0zYH4I6Guz8qIrxDc6P
YxGYqAFF0oEh4xRnSpfMz4TU8NozifDX1dt5G4dUcvOkUPP/9CqgCzqI3f0dAkEA
vDx9DCOwBrfi2z6f1rXYcCErhHnapT2URHA44NP7j3flEnCVdWOkU44TQpkQ9Hs1
kq52scDiiJ8qA3ldD7WaQQJBAII2pVVmAtNGnIpoylnnDN6toloafyiiaHL/SZ4U
G9lBBzqdDbcfoQsEyKfm4VgHRWJOURqfgn75lrQWhSxLadE=
-----END RSA PRIVATE KEY-----');

define('MAIL_RSA_PUBL',
'-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDTgb5Tzu+D89Chdt13PDQ3FKLP
bcukF0aXq6+k4rnOxesSOhNSu7H7f6XIftKrRaYVRzaXJ4IDUxb/T395nBnrz7f+
9BCxV2Y/DRT3wRs3s1gnrX5d9WlxFQnTa3QycMI8J/yxkgULf9IFsesCmX8oI4Jk
neoPnjPZzi7GNTrGXQIDAQAB
-----END PUBLIC KEY-----');

// Domain or subdomain of the signing entity (i.e. the domain where the e-mail comes from)
define('MAIL_DOMAIN', 'groupanizer.com');  

// Allowed user, defaults is "@<MAIL_DKIM_DOMAIN>", meaning anybody in the MAIL_DKIM_DOMAIN domain. Ex: 'admin@mydomain.tld'. You'll never have to use this unless you do not control the "From" value in the e-mails you send.
define('MAIL_IDENTITY', NULL);

// Selector used in your DKIM DNS record, e.g. : selector._domainkey.MAIL_DKIM_DOMAIN
define('MAIL_SELECTOR', 'sing3');

?>