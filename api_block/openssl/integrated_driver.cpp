#include "gfuzz_openssl.h"

//#define MAX_API_SEQ_LEN 12
#define OBJ_POOL_SIZE 0
#define PRIMITIVE_POOL_SIZE 0
#define BUFFER_POOL_SIZE 0
#define API_BLOCK_N 10
#define MAX_BUFFER_SIZE 1048576
static int MAX_API_SEQ_LEN = 0;

#include "api_block.pb.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "port/protobuf.h"
#include "src/libfuzzer/libfuzzer_macro.h"

int check_validity (const FUZZING_BYTES& fuzzing_bytes);
FUZZING_BYTES bound_bank_index (FUZZING_BYTES fuzzing_bytes);
void update_max_api_seq_len () {
    if (MAX_API_SEQ_LEN == 0) {
        MAX_API_SEQ_LEN = atoi(getenv("MAX_API_SEQ_LEN"));
    }
}


X509* pool_X509_p[PRIMITIVE_POOL_SIZE];
size_t pool__size_t[PRIMITIVE_POOL_SIZE];
uint8_t* pool_buf_uint8_t_p[BUFFER_POOL_SIZE];
unsigned char* pool_buf_unsigned_char_p[BUFFER_POOL_SIZE];
BIO* pool_BIO_p[PRIMITIVE_POOL_SIZE];

void call_driver_30_to_33 (const APIB_CALL_INPUT& ref);
void call_driver_34_to_45 (const APIB_CALL_INPUT& ref);
void call_driver_33 (const APIB_CALL_INPUT& ref);
void call_driver_35 (const APIB_CALL_INPUT& ref);
void call_driver_37 (const APIB_CALL_INPUT& ref);
void call_driver_38 (const APIB_CALL_INPUT& ref);
void call_driver_40 (const APIB_CALL_INPUT& ref);
void call_driver_41 (const APIB_CALL_INPUT& ref);
void call_driver_43 (const APIB_CALL_INPUT& ref);
void call_driver_45 (const APIB_CALL_INPUT& ref);


int check_validity (const FUZZING_BYTES& fuzzing_bytes) {
  if (fuzzing_bytes.pool_init_values().buf_uint8_t_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_unsigned_char_p_size() != BUFFER_POOL_SIZE) { return 1; }

  if (fuzzing_bytes.api_block_call_seq_size() > MAX_API_SEQ_LEN) { return 1; }

  for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
    if (fuzzing_bytes.pool_init_values().buf_uint8_t_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_unsigned_char_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
  }
  return 0;
}
FUZZING_BYTES bound_bank_index (FUZZING_BYTES fuzzing_bytes) {
  for (int i = 0; i < fuzzing_bytes.api_block_call_seq_size(); i++) {

    fuzzing_bytes.mutable_api_block_call_seq(i)->set_api_block_call_num(fuzzing_bytes.mutable_api_block_call_seq(i)->api_block_call_num() % API_BLOCK_N);
    APIB_CALL_INPUT *api_block_call_input = fuzzing_bytes.mutable_api_block_call_seq(i)->mutable_api_block_call_input();

    api_block_call_input->set_in_idx_x509_p_0(api_block_call_input->in_idx_x509_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_x509_p_0(api_block_call_input->out_idx_x509_p_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx__size_t_0(api_block_call_input->in_idx__size_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__size_t_0(api_block_call_input->out_idx__size_t_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_uint8_t_p_0(api_block_call_input->in_idx_buf_uint8_t_p_0() % BUFFER_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_unsigned_char_p_0(api_block_call_input->in_idx_buf_unsigned_char_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_in_idx_buf_unsigned_char_p_1(api_block_call_input->in_idx_buf_unsigned_char_p_1() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_unsigned_char_p_0(api_block_call_input->out_idx_buf_unsigned_char_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_unsigned_char_p_1(api_block_call_input->out_idx_buf_unsigned_char_p_1() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_bio_p_0(api_block_call_input->in_idx_bio_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_bio_p_0(api_block_call_input->out_idx_bio_p_0() % OBJ_POOL_SIZE);

  }
  return fuzzing_bytes;
}

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZING_BYTES& fuzzing_bytes) {
    update_max_api_seq_len();
    if (check_validity(fuzzing_bytes)) return;

    FUZZING_BYTES serialized_bytes = bound_bank_index(fuzzing_bytes);

    for (int i = 0; i < PRIMITIVE_POOL_SIZE; i++) {
    }


    std::string buf;
    for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
      buf = serialized_bytes.pool_init_values().buf_uint8_t_p(i).val();
      pool__size_t[i] = buf.length();
      buf += '\0';
      pool_buf_uint8_t_p[i] = (uint8_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_uint8_t_p[i], buf.data(), buf.size());

      buf = serialized_bytes.pool_init_values().buf_unsigned_char_p(i).val();
      buf += '\0';
      pool_buf_unsigned_char_p[i] = (unsigned char*)malloc(buf.length());
      std::memcpy((void*)pool_buf_unsigned_char_p[i], buf.data(), buf.size());

    }


  for (int i = 0; i < serialized_bytes.api_block_call_seq_size(); i++) {
    uint32_t api_block_call_num  = serialized_bytes.api_block_call_seq(i).api_block_call_num();
    const APIB_CALL_INPUT& api_block_call_input = serialized_bytes.api_block_call_seq(i).api_block_call_input();

    switch(api_block_call_num) {

      case 0:
        call_driver_30_to_33(api_block_call_input);
        break;

      case 1:
        call_driver_34_to_45(api_block_call_input);
        break;

      case 2:
        call_driver_33(api_block_call_input);
        break;

      case 3:
        call_driver_35(api_block_call_input);
        break;

      case 4:
        call_driver_37(api_block_call_input);
        break;

      case 5:
        call_driver_38(api_block_call_input);
        break;

      case 6:
        call_driver_40(api_block_call_input);
        break;

      case 7:
        call_driver_41(api_block_call_input);
        break;

      case 8:
        call_driver_43(api_block_call_input);
        break;

      case 9:
        call_driver_45(api_block_call_input);
        break;
    };
  }
}

void call_driver_30_to_33 (const APIB_CALL_INPUT& ref) {
  const uint8_t* buf = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t len = pool__size_t[ref.in_idx__size_t_0()];

    const unsigned char *p = buf;
    unsigned char *der = NULL;

    X509 *x509 = d2i_X509(NULL, &p, len);

  pool__size_t[ref.out_idx__size_t_0()] = len;
  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = ( unsigned char*)p ;
  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_1()] = der ;
  pool_X509_p[ref.out_idx_x509_p_0()] = x509 ;
}

void call_driver_34_to_45 (const APIB_CALL_INPUT& ref) {
  X509* x509 = pool_X509_p[ref.in_idx_x509_p_0()];
  unsigned char* der = pool_buf_unsigned_char_p[ref.in_idx_buf_unsigned_char_p_0()];

    if (x509 != NULL) {
        BIO *bio = BIO_new(BIO_s_null());
        /* This will load and print the public key as well as extensions */
        X509_print(bio, x509);
        BIO_free(bio);

        i2d_X509(x509, &der);
        OPENSSL_free(der);

        X509_free(x509);
    }
    ERR_clear_error();

  pool_X509_p[ref.out_idx_x509_p_0()] = x509;
  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = der;
}

void call_driver_33 (const APIB_CALL_INPUT& ref) {
  const unsigned char* p = pool_buf_unsigned_char_p[ref.in_idx_buf_unsigned_char_p_0()];
  size_t len = pool__size_t[ref.in_idx__size_t_0()];

    X509 *x509 = d2i_X509(NULL, &p, len);

  pool__size_t[ref.out_idx__size_t_0()] = len;
  pool_X509_p[ref.out_idx_x509_p_0()] = x509 ;
}

void call_driver_35 (const APIB_CALL_INPUT& ref) {

        BIO *bio = BIO_new(BIO_s_null());

  pool_BIO_p[ref.out_idx_bio_p_0()] = bio ;
}

void call_driver_37 (const APIB_CALL_INPUT& ref) {
  BIO* bio = pool_BIO_p[ref.in_idx_bio_p_0()];
  X509* x509 = pool_X509_p[ref.in_idx_x509_p_0()];

        X509_print(bio, x509);

  pool_BIO_p[ref.out_idx_bio_p_0()] = bio;
  pool_X509_p[ref.out_idx_x509_p_0()] = x509;
}

void call_driver_38 (const APIB_CALL_INPUT& ref) {
  BIO* bio = pool_BIO_p[ref.in_idx_bio_p_0()];

        BIO_free(bio);

  pool_BIO_p[ref.out_idx_bio_p_0()] = bio;
}

void call_driver_40 (const APIB_CALL_INPUT& ref) {
  X509* x509 = pool_X509_p[ref.in_idx_x509_p_0()];
  unsigned char* der = pool_buf_unsigned_char_p[ref.in_idx_buf_unsigned_char_p_0()];

        i2d_X509(x509, &der);

  pool_X509_p[ref.out_idx_x509_p_0()] = x509;
  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = der;
}

void call_driver_41 (const APIB_CALL_INPUT& ref) {
  unsigned char* der = pool_buf_unsigned_char_p[ref.in_idx_buf_unsigned_char_p_0()];

        OPENSSL_free(der);

  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = der;
}

void call_driver_43 (const APIB_CALL_INPUT& ref) {
  X509* x509 = pool_X509_p[ref.in_idx_x509_p_0()];

        X509_free(x509);

  pool_X509_p[ref.out_idx_x509_p_0()] = x509;
}

void call_driver_45 (const APIB_CALL_INPUT& ref) {
  unsigned char* der = pool_buf_unsigned_char_p[ref.in_idx_buf_unsigned_char_p_0()];

    ERR_clear_error();

  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = der;
}
