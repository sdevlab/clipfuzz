#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "curl_fuzzer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  int rc = 0;
  int tlv_rc;
  FUZZ_DATA fuzz;
  TLV tlv;

  /* Ignore SIGPIPE errors. We'll handle the errors ourselves. */
  signal(SIGPIPE, SIG_IGN);

  /* Have to set all fields to zero before getting to the terminate function */
  memset(&fuzz, 0, sizeof(FUZZ_DATA));

  if(size < sizeof(TLV_RAW)) {
    /* Not enough data for a single TLV - don't continue */
    goto EXIT_LABEL;
  }

  /* Try to initialize the fuzz data */
  FTRY(fuzz_initialize_fuzz_data(&fuzz, data, size));

  for(tlv_rc = fuzz_get_first_tlv(&fuzz, &tlv);
      tlv_rc == 0;
      tlv_rc = fuzz_get_next_tlv(&fuzz, &tlv)) {

    /* Have the TLV in hand. Parse the TLV. */
    rc = fuzz_parse_tlv(&fuzz, &tlv);

    if(rc != 0) {
      /* Failed to parse the TLV. Can't continue. */
      goto EXIT_LABEL;
    }
  }

  if(tlv_rc != TLV_RC_NO_MORE_TLVS) {
    /* A TLV call failed. Can't continue. */
    goto EXIT_LABEL;
  }

  /* Set up the standard easy options. */
  FTRY(fuzz_set_easy_options(&fuzz));

  /**
   * Add in more curl options that have been accumulated over possibly
   * multiple TLVs.
   */
  if(fuzz.header_list != NULL) {
    curl_easy_setopt(fuzz.easy, CURLOPT_HTTPHEADER, fuzz.header_list);
  }

  if(fuzz.mail_recipients_list != NULL) {
    curl_easy_setopt(fuzz.easy, CURLOPT_MAIL_RCPT, fuzz.mail_recipients_list);
  }

  if(fuzz.mime != NULL) {
    curl_easy_setopt(fuzz.easy, CURLOPT_MIMEPOST, fuzz.mime);
  }

  if (fuzz.httppost != NULL) {
    curl_easy_setopt(fuzz.easy, CURLOPT_HTTPPOST, fuzz.httppost);
  }

  /* Run the transfer. */
  fuzz_handle_transfer(&fuzz);

EXIT_LABEL:

  fuzz_terminate_fuzz_data(&fuzz);

  /* This function must always return 0. Non-zero codes are reserved. */
  return 0;
}


#include <iostream>
#include <fstream>
#include <vector>

//extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), buffer.size())) {
        std::cerr << "Failed to read from file: " << argv[1] << std::endl;
        return 1;
    }

    LLVMFuzzerTestOneInput(buffer.data(), buffer.size());

    return 0;
}
