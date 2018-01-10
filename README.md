# Aes256GcmDecrypt

Decrypt AES256GCM-encrypted data in Apple Pay Payment Tokens.

This library is necessary for Ruby < 2.4 (if you use the stdlib openssl rather than the [openssl gem](https://rubygems.org/gems/openssl)), as the OpenSSL bindings do not support setting the length of the initialisation vector (IV). Setting the IV length is necessary for decrypting Apple Pay data.

The library becomes obsolete when we start using Ruby >= 2.4.

## Usage

```
rake compile

irb -r base64 -r ./lib/aes256gcm_decrypt.so

ciphertext_and_tag = Base64.decode64(File.read('test/token_data_base64.txt'))
key = [File.read('test/key_hex.txt').strip].pack('H*')

puts Aes256GcmDecrypt::decrypt(ciphertext_and_tag, key)
```

`#decrypt` returns a string with plaintext if authenticated decryption is successful. If the authentication part is unsuccessful, it returns `false`. If anything is wrong, e.g. the length of `key` is not 32, it returns `nil`.

## Inspirational sources

* [Your first Ruby native extension: C](https://blog.jcoglan.com/2012/07/29/your-first-ruby-native-extension-c/)
* [Step-by-Step Guide to Building Your First Ruby Gem](https://quickleft.com/blog/engineering-lunch-series-step-by-step-guide-to-building-your-first-ruby-gem/)
* [OpenSSL EVP Authenticated Decryption using GCM](https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption#Authenticated_Decryption_using_GCM_mode)
* [The Ruby C API](http://silverhammermba.github.io/emberb/c/)
