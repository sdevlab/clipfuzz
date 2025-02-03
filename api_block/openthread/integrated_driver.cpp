#include "gfuzz_openthread.h"

#define OBJ_POOL_SIZE 0
#define PRIMITIVE_POOL_SIZE 0
#define BUFFER_POOL_SIZE 0
#define API_BLOCK_N 13
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


otMessagePriority pool_otMessagePriority[PRIMITIVE_POOL_SIZE];
otMessageSettings pool_otMessageSettings[OBJ_POOL_SIZE];
otInstance* pool_otInstance_p[PRIMITIVE_POOL_SIZE];
bool pool__bool[PRIMITIVE_POOL_SIZE];
otMessage* pool_otMessage_p[PRIMITIVE_POOL_SIZE];
uint8_t* pool_buf_uint8_t_p[BUFFER_POOL_SIZE];
int pool__int[PRIMITIVE_POOL_SIZE];
otPanId pool__otPanId[PRIMITIVE_POOL_SIZE];
size_t pool__size_t[PRIMITIVE_POOL_SIZE];

void call_driver_62_to_73 (const APIB_CALL_INPUT& ref);
void call_driver_74 (const APIB_CALL_INPUT& ref);
void call_driver_75 (const APIB_CALL_INPUT& ref);
void call_driver_76 (const APIB_CALL_INPUT& ref);
void call_driver_77 (const APIB_CALL_INPUT& ref);
void call_driver_78 (const APIB_CALL_INPUT& ref);
void call_driver_80 (const APIB_CALL_INPUT& ref);
void call_driver_82_to_85 (const APIB_CALL_INPUT& ref);
void call_driver_88 (const APIB_CALL_INPUT& ref);
void call_driver_91 (const APIB_CALL_INPUT& ref);
void call_driver_93_to_95 (const APIB_CALL_INPUT& ref);
void call_driver_97 (const APIB_CALL_INPUT& ref);
void call_driver_101_to_109 (const APIB_CALL_INPUT& ref);

otMessagePriority to_otMessagePriority (OTMESSAGEPRIORITY val) {
  switch (val) {
    case val_OT_MESSAGE_PRIORITY_LOW: return OT_MESSAGE_PRIORITY_LOW;
    case val_OT_MESSAGE_PRIORITY_NORMAL: return OT_MESSAGE_PRIORITY_NORMAL;
    case val_OT_MESSAGE_PRIORITY_HIGH: return OT_MESSAGE_PRIORITY_HIGH;
  }
}
int check_validity (const FUZZING_BYTES& fuzzing_bytes) {
  if (fuzzing_bytes.pool_init_values().otmessagepriority_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._bool_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_uint8_t_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._int_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._otpanid_size() != PRIMITIVE_POOL_SIZE) { return 1; }

  if (fuzzing_bytes.api_block_call_seq_size() > MAX_API_SEQ_LEN) { return 1; }

  for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
    if (fuzzing_bytes.pool_init_values().buf_uint8_t_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
  }
  return 0;
}
FUZZING_BYTES bound_bank_index (FUZZING_BYTES fuzzing_bytes) {
  for (int i = 0; i < fuzzing_bytes.api_block_call_seq_size(); i++) {

    fuzzing_bytes.mutable_api_block_call_seq(i)->set_api_block_call_num(fuzzing_bytes.mutable_api_block_call_seq(i)->api_block_call_num() % API_BLOCK_N);
    APIB_CALL_INPUT *api_block_call_input = fuzzing_bytes.mutable_api_block_call_seq(i)->mutable_api_block_call_input();

    api_block_call_input->set_in_idx_otmessagepriority_0(api_block_call_input->in_idx_otmessagepriority_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_otmessagepriority_0(api_block_call_input->out_idx_otmessagepriority_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_otmessagesettings_0(api_block_call_input->in_idx_otmessagesettings_0() % OBJ_POOL_SIZE);
    api_block_call_input->set_out_idx_otmessagesettings_0(api_block_call_input->out_idx_otmessagesettings_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx_otinstance_p_0(api_block_call_input->in_idx_otinstance_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_otinstance_p_0(api_block_call_input->out_idx_otinstance_p_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx__bool_0(api_block_call_input->in_idx__bool_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__bool_0(api_block_call_input->out_idx__bool_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_otmessage_p_0(api_block_call_input->in_idx_otmessage_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_otmessage_p_0(api_block_call_input->out_idx_otmessage_p_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_uint8_t_p_0(api_block_call_input->in_idx_buf_uint8_t_p_0() % BUFFER_POOL_SIZE);

    api_block_call_input->set_in_idx__int_0(api_block_call_input->in_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_0(api_block_call_input->out_idx__int_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__otpanid_0(api_block_call_input->in_idx__otpanid_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__otpanid_0(api_block_call_input->out_idx__otpanid_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__size_t_0(api_block_call_input->in_idx__size_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__size_t_0(api_block_call_input->out_idx__size_t_0() % PRIMITIVE_POOL_SIZE);

  }
  return fuzzing_bytes;
}

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZING_BYTES& fuzzing_bytes) {
    update_max_api_seq_len();
    if (check_validity(fuzzing_bytes)) return;

    FUZZING_BYTES serialized_bytes = bound_bank_index(fuzzing_bytes);

    for (int i = 0; i < PRIMITIVE_POOL_SIZE; i++) {
      pool_otMessagePriority[i] = to_otMessagePriority(serialized_bytes.pool_init_values().otmessagepriority(i));

      pool__bool[i] = (bool)serialized_bytes.pool_init_values()._bool(i).val();

      pool__int[i] = (int)serialized_bytes.pool_init_values()._int(i).val();

      pool__otPanId[i] = (otPanId)serialized_bytes.pool_init_values()._otpanid(i).val();

    }
    

    std::string buf;
    for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
      buf = serialized_bytes.pool_init_values().buf_uint8_t_p(i).val();
      pool__size_t[i] = buf.length();
      buf += '\0';
      pool_buf_uint8_t_p[i] = (uint8_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_uint8_t_p[i], buf.data(), buf.size());

    }
    FuzzerPlatformInit();

  for (int i = 0; i < serialized_bytes.api_block_call_seq_size(); i++) {
    uint32_t api_block_call_num  = serialized_bytes.api_block_call_seq(i).api_block_call_num();
    const APIB_CALL_INPUT& api_block_call_input = serialized_bytes.api_block_call_seq(i).api_block_call_input();

    switch(api_block_call_num) {

      case 0:
        call_driver_62_to_73(api_block_call_input);
        break;

      case 1:
        call_driver_74(api_block_call_input);
        break;

      case 2:
        call_driver_75(api_block_call_input);
        break;

      case 3:
        call_driver_76(api_block_call_input);
        break;

      case 4:
        call_driver_77(api_block_call_input);
        break;

      case 5:
        call_driver_78(api_block_call_input);
        break;

      case 6:
        call_driver_80(api_block_call_input);
        break;

      case 7:
        call_driver_82_to_85(api_block_call_input);
        break;

      case 8:
        call_driver_88(api_block_call_input);
        break;

      case 9:
        call_driver_91(api_block_call_input);
        break;

      case 10:
        call_driver_93_to_95(api_block_call_input);
        break;

      case 11:
        call_driver_97(api_block_call_input);
        break;

      case 12:
        call_driver_101_to_109(api_block_call_input);
        break;
    };
  }
}

void call_driver_62_to_73 (const APIB_CALL_INPUT& ref) {

    const otPanId panId = 0xdead;

    otInstance       *instance = nullptr;
    otMessage        *message  = nullptr;
    //otError           error    = OT_ERROR_NONE;
    otMessageSettings settings;

    //VerifyOrExit(size > 0);

    FuzzerPlatformInit();

    instance = otInstanceInitSingle();

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance ;
  pool_otMessage_p[ref.out_idx_otmessage_p_0()] = message ;
  pool_otMessageSettings[ref.out_idx_otmessagesettings_0()] = settings ;
  pool__otPanId[ref.out_idx__otpanid_0()] = ( otPanId)panId ;
}

void call_driver_74 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  const otPanId panId = pool__otPanId[ref.in_idx__otpanid_0()];

    otLinkSetPanId(instance, panId);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
}

void call_driver_75 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  const otPanId panId = pool__otPanId[ref.in_idx__otpanid_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

    otIp6SetEnabled(instance, _t0_);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_76 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

    otThreadSetEnabled(instance, _t0_);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_77 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

    otSrpServerSetEnabled(instance, _t0_);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_78 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];

    otThreadBecomeLeader(instance);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
}

void call_driver_80 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];

    AdvanceTime(instance, _t0_);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
  pool__int[ref.out_idx__int_0()] = _t0_;
}

void call_driver_82_to_85 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  otMessage* message = pool_otMessage_p[ref.in_idx_otmessage_p_0()];
  otMessageSettings settings = pool_otMessageSettings[ref.in_idx_otmessagesettings_0()];
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];
  otMessagePriority _t1_ = pool_otMessagePriority[ref.in_idx_otmessagepriority_0()];

    settings.mLinkSecurityEnabled = (data[0] & 0x1) != 0;
    settings.mPriority            = _t1_;

    message = otIp6NewMessage(instance, &settings);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
  pool_otMessage_p[ref.out_idx_otmessage_p_0()] = message;
  pool_otMessageSettings[ref.out_idx_otmessagesettings_0()] = settings;
  pool__int[ref.out_idx__int_0()] = _t0_;
  pool_otMessagePriority[ref.out_idx_otmessagepriority_0()] = _t1_;
}

void call_driver_88 (const APIB_CALL_INPUT& ref) {
  otMessage* message = pool_otMessage_p[ref.in_idx_otmessage_p_0()];
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t size = pool__size_t[ref.in_idx__size_t_0()];

    otMessageAppend(message, data + 1, static_cast<uint16_t>(size - 1));

  pool_otMessage_p[ref.out_idx_otmessage_p_0()] = message;
  pool__size_t[ref.out_idx__size_t_0()] = size;
}

void call_driver_91 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  otMessage* message = pool_otMessage_p[ref.in_idx_otmessage_p_0()];

    otIp6Send(instance, message);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
  pool_otMessage_p[ref.out_idx_otmessage_p_0()] = message;
}

void call_driver_93_to_95 (const APIB_CALL_INPUT& ref) {
  otMessage* message = pool_otMessage_p[ref.in_idx_otmessage_p_0()];

    message = nullptr;

    FuzzerPlatformResetWasRequested();

  pool_otMessage_p[ref.out_idx_otmessage_p_0()] = message;
}

void call_driver_97 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];

    AdvanceTime(instance, _t0_);

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
  pool__int[ref.out_idx__int_0()] = _t0_;
}

void call_driver_101_to_109 (const APIB_CALL_INPUT& ref) {
  otInstance* instance = pool_otInstance_p[ref.in_idx_otinstance_p_0()];
  otMessage* message = pool_otMessage_p[ref.in_idx_otmessage_p_0()];

    if (message != nullptr)
    {
        otMessageFree(message);
    }

    if (instance != nullptr)
    {
        otInstanceFinalize(instance);
    }

  pool_otInstance_p[ref.out_idx_otinstance_p_0()] = instance;
  pool_otMessage_p[ref.out_idx_otmessage_p_0()] = message;
}
