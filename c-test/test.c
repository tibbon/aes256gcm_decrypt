#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

int main(int argc, char *argv[]) {

  /* Prepare variables */
  unsigned char ciphertext[] = {
    0xe0, 0xe6, 0x61, 0xa3, 0x5e, 0x5e, 0xf5, 0x8a, 0x79, 0x2b, 0x41,
    0x2d, 0x29, 0xea, 0xe0, 0x2b, 0x37, 0x91, 0xa4, 0xf0, 0x23, 0x9c,
    0xa1, 0xf0, 0x99, 0x23, 0x67, 0x6a, 0x0c, 0x61, 0x8f, 0x08, 0x4a,
    0x43, 0x97, 0x76, 0xf6, 0xc7, 0xd3, 0x5e, 0x37, 0x5b, 0x87, 0x50,
    0xad, 0x4c, 0x9e, 0x03, 0x62, 0x3b, 0x03, 0xea, 0x47, 0xee, 0x94,
    0xd5, 0x27, 0x62, 0x60, 0x53, 0xb2, 0xbb, 0xa9, 0x84, 0x1c, 0xfb,
    0x45, 0x15, 0x48, 0xd5, 0x62, 0x3c, 0x3f, 0x42, 0xeb, 0x99, 0xf4,
    0xe7, 0x22, 0x68, 0xdc, 0xab, 0x59, 0xa2, 0xf8, 0x14, 0x4d, 0xec,
    0x4b, 0x51, 0xdb, 0x2e, 0x8c, 0x90, 0x39, 0x80, 0xaf, 0xbf, 0x1a,
    0x9d, 0xf7, 0xfd, 0xd6, 0x19, 0x5c, 0xfb, 0x1f, 0x1e, 0x58, 0x3f,
    0xcd, 0xa4, 0xef, 0xe8, 0x67, 0x57, 0xb2, 0xe6, 0xa5, 0x79, 0x44,
    0x1c, 0xbf, 0x26, 0x9e, 0x73, 0x87, 0xa9, 0xdd, 0x55, 0x45, 0x6a,
    0xf0, 0xc1, 0xc7, 0x86, 0xf4, 0x2f, 0xe2, 0x92, 0xf2, 0xe5, 0x37,
    0xe2, 0xe7, 0xb6, 0x28, 0xe1, 0x15, 0x21, 0x02, 0xcc, 0x97, 0xc9,
    0x38, 0x78, 0xc7, 0xfa, 0x75, 0xdf, 0xad, 0x01, 0x66, 0x6a, 0x16,
    0xa2, 0x62, 0xb5, 0xe4, 0xd7, 0x09, 0x7d, 0x49, 0xa8, 0x50, 0x2b,
    0xb0, 0x11, 0x8a, 0x22, 0xef, 0x15, 0x24, 0x47, 0x03, 0x6b, 0xd7,
    0x3e, 0x0c, 0x2a, 0x7c, 0xcc, 0x7e, 0x77, 0x92, 0x46, 0x95, 0x20,
    0x75, 0xcd, 0x30, 0x00, 0x33, 0x1e, 0x07, 0xab, 0xb5, 0x8d, 0xcb,
    0xb0, 0xa9, 0x09, 0xe7, 0x87, 0x67, 0x2e, 0xb2, 0x26, 0xa0, 0x39,
    0x30, 0x9f, 0x0f, 0xa8, 0xce, 0xea, 0xd9, 0xa8, 0xba, 0xfb, 0xba,
    0x28, 0xee, 0x78, 0xb9, 0x4e, 0xdb, 0x01, 0xb2, 0xb3, 0xe9, 0xca,
    0x1c, 0x20, 0xe1, 0x00, 0x39, 0xce, 0xa4, 0x7b, 0x21, 0x57, 0x1b,
    0x97, 0x5f, 0xc3, 0xc8, 0xb7, 0x84, 0x98, 0x3a, 0x1b, 0x6b, 0xc8,
    0x79, 0xf1, 0xc2, 0xc1, 0xc2, 0xae, 0xd7, 0x31, 0x42, 0x1e, 0xbe,
    0x0f, 0xee, 0x32, 0xe7, 0x60, 0x50, 0xc4, 0x86, 0xfc, 0x4b, 0x9b,
    0x52, 0xac, 0x90, 0x37, 0x2e, 0x65, 0xe4, 0x07, 0x02, 0x40, 0x4c,
    0x98, 0xb4, 0x52, 0x82, 0x3f, 0x4d
  };
  unsigned int ciphertext_len = sizeof(ciphertext);

  unsigned char tag[] = {
    0x21, 0xca, 0x41, 0x6b, 0xde, 0x15, 0x37, 0xf2, 0x53, 0x81, 0xaf,
    0x16, 0xef, 0x92, 0x16, 0x00
  };
  unsigned int tag_len = sizeof(tag);

  unsigned char key[] = {
    0x1c, 0xe4, 0x9a, 0x82, 0x8f, 0x59, 0xd4, 0x38, 0x61, 0xba, 0x44,
    0x2f, 0xce, 0x68, 0x29, 0xb8, 0x21, 0x8f, 0xbb, 0x0a, 0xb5, 0x5b,
    0x40, 0x20, 0x6a, 0xc3, 0x10, 0x58, 0xd6, 0x6f, 0x50, 0x86
  };

  unsigned int iv_len = 16;
  unsigned char *iv = calloc(iv_len, sizeof(unsigned char));
  for (int i = 0; i < iv_len; i++) {
    iv[i] = '\0';
  }

  int plaintext_len, len;
  unsigned char *plaintext = calloc(ciphertext_len * 2, sizeof(unsigned char));

  int result = 1;
  EVP_CIPHER_CTX *ctx;

  /* Create and initialise context */
  if (!(ctx = EVP_CIPHER_CTX_new())) {
    goto cleanup2;
  }

  /* Initialise decryption operation */
  if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL)) {
    goto cleanup1;
  }

  /* Set initialisation vector (IV) length */
  if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL)) {
    goto cleanup1;
  }

  /* Initialise key and IV */
  if (!EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv)) {
    goto cleanup1;
  }

  /* Provide empty string as additional authenticated data (AAD) */
  if (!EVP_DecryptUpdate(ctx, NULL, &len, (unsigned char*)"", 0)) {
    goto cleanup1;
  }

  /* Provide message to be decrypted */
  if (!EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
    goto cleanup1;
  }
  plaintext_len = len;

  /* Set expected tag */
  if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tag_len, tag)) {
    goto cleanup1;
  }

  /* Finalise decryption */
  if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) > 0) {
    plaintext_len += len;
    printf("Decrypted plaintext:\n%s\n", plaintext);
    result = 0;
  } else {
    result = 2;
  }

cleanup1:
  EVP_CIPHER_CTX_free(ctx);
cleanup2:
  free(plaintext);
  free(iv);
  return result;
}
