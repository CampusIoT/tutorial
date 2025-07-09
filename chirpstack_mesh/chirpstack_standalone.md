# TerraForma :: WP3 :: Chirpstack Standalone for testing Chirpstack Mesh Gateway


## `chirpstack.toml` 

`configuration/chirpstack/chirpstack.toml`


Generate Key and Cert in PEM format

```bash
cd configuration/chirpstack
```

```bash
openssl req \
-x509 \
-nodes \
-days 365 \
-newkey rsa:1024 \
-keyout selfsigned.key.pem \
-out ca.crt \
-subj "/C=FR/ST=AURA/L=Grenoble/CN=liglab.fr/emailAddress=admin@liglab.fr"

#Output:
#
#    selfsigned.key.pem - PEM Key
#    ca.crt - x509 Certificate
```

Convert PEM key to PKCS8 format

```bash
openssl pkcs8 \
-topk8 \
-inform PEM \
-outform PEM \
-in selfsigned.key.pem \
-out key.pem
```

Edit `configuration/chirpstack/chirpstack.toml`

```toml
# Global gateway configuration.
# Please note that backend configuration can be found in the per-region
# configuration.
[gateway]

  # CA certificate and key file (optional).
  #
  # If setting the CA certificate and key file options, ChirpStack 
  # will generate client certificates which can be used by the gateway for
  # authentication and authorization. The Common Name of the certificate will
  # be set to the Gateway ID.
  #
  # The ca_key is expected to be in PKCS#8 format (you can use openssl to
  # convert to PKCS#8).
  ca_cert="/etc/ca.crt"
  ca_key="/etc/key.pem"

  # Certificate lifetime.
  #
  # This defines how long (after generating) the certificate remains valid.
  client_cert_lifetime="11months 30days 3h 50m 24s"

  # Allow unknown gateways.
  #
  # If set to true, then uplinks received from gateways not configured in
  # ChirpStack will be allowed.
  allow_unknown_gateways=true
```


