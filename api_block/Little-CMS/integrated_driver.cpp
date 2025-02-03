#include "gfuzz_Little-CMS.h"

//#define MAX_API_SEQ_LEN 0
#define OBJ_POOL_SIZE 0
#define PRIMITIVE_POOL_SIZE 0
#define BUFFER_POOL_SIZE 0
#define API_BLOCK_N 11
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

cmsHTRANSFORM pool_cmsHTRANSFORM[OBJ_POOL_SIZE];
uint8_t* pool_buf_uint8_t_p[BUFFER_POOL_SIZE];
double* pool_buf_double_p[BUFFER_POOL_SIZE];
int pool__int[PRIMITIVE_POOL_SIZE];
cmsUInt32Number pool__cmsUInt32Number[PRIMITIVE_POOL_SIZE];
size_t pool__size_t[PRIMITIVE_POOL_SIZE];
cmsHPROFILE pool_cmsHPROFILE[OBJ_POOL_SIZE];
cmsColorSpaceSignature pool_cmsColorSpaceSignature[PRIMITIVE_POOL_SIZE];

void call_driver_20 (const APIB_CALL_INPUT& ref);
void call_driver_21_to_29 (const APIB_CALL_INPUT& ref);
void call_driver_30 (const APIB_CALL_INPUT& ref);
void call_driver_31_to_43 (const APIB_CALL_INPUT& ref);
void call_driver_44 (const APIB_CALL_INPUT& ref);
void call_driver_45 (const APIB_CALL_INPUT& ref);
void call_driver_46_to_58 (const APIB_CALL_INPUT& ref);
void call_driver_52 (const APIB_CALL_INPUT& ref);
void call_driver_56 (const APIB_CALL_INPUT& ref);
void call_driver_24_to_27 (const APIB_CALL_INPUT& ref);
void call_driver_49_to_57 (const APIB_CALL_INPUT& ref);

cmsColorSpaceSignature to_cmsColorSpaceSignature (CMSCOLORSPACESIGNATURE val) {
  switch (val) {
    case val_cmsSigXYZData: return cmsSigXYZData;
    case val_cmsSigLabData: return cmsSigLabData;
    case val_cmsSigLuvData: return cmsSigLuvData;
    case val_cmsSigYCbCrData: return cmsSigYCbCrData;
    case val_cmsSigYxyData: return cmsSigYxyData;
    case val_cmsSigRgbData: return cmsSigRgbData;
    case val_cmsSigGrayData: return cmsSigGrayData;
    case val_cmsSigHsvData: return cmsSigHsvData;
    case val_cmsSigHlsData: return cmsSigHlsData;
    case val_cmsSigCmykData: return cmsSigCmykData;
    case val_cmsSigCmyData: return cmsSigCmyData;
    case val_cmsSigMCH1Data: return cmsSigMCH1Data;
    case val_cmsSigMCH2Data: return cmsSigMCH2Data;
    case val_cmsSigMCH3Data: return cmsSigMCH3Data;
    case val_cmsSigMCH4Data: return cmsSigMCH4Data;
    case val_cmsSigMCH5Data: return cmsSigMCH5Data;
    case val_cmsSigMCH6Data: return cmsSigMCH6Data;
    case val_cmsSigMCH7Data: return cmsSigMCH7Data;
    case val_cmsSigMCH8Data: return cmsSigMCH8Data;
    case val_cmsSigMCH9Data: return cmsSigMCH9Data;
    case val_cmsSigMCHAData: return cmsSigMCHAData;
    case val_cmsSigMCHBData: return cmsSigMCHBData;
    case val_cmsSigMCHCData: return cmsSigMCHCData;
    case val_cmsSigMCHDData: return cmsSigMCHDData;
    case val_cmsSigMCHEData: return cmsSigMCHEData;
    case val_cmsSigMCHFData: return cmsSigMCHFData;
    case val_cmsSigNamedData: return cmsSigNamedData;
    case val_cmsSig1colorData: return cmsSig1colorData;
    case val_cmsSig2colorData: return cmsSig2colorData;
    case val_cmsSig3colorData: return cmsSig3colorData;
    case val_cmsSig4colorData: return cmsSig4colorData;
    case val_cmsSig5colorData: return cmsSig5colorData;
    case val_cmsSig6colorData: return cmsSig6colorData;
    case val_cmsSig7colorData: return cmsSig7colorData;
    case val_cmsSig8colorData: return cmsSig8colorData;
    case val_cmsSig9colorData: return cmsSig9colorData;
    case val_cmsSig10colorData: return cmsSig10colorData;
    case val_cmsSig11colorData: return cmsSig11colorData;
    case val_cmsSig12colorData: return cmsSig12colorData;
    case val_cmsSig13colorData: return cmsSig13colorData;
    case val_cmsSig14colorData: return cmsSig14colorData;
    case val_cmsSig15colorData: return cmsSig15colorData;
    case val_cmsSigLuvKData: return cmsSigLuvKData;
  }
}
int check_validity (const FUZZING_BYTES& fuzzing_bytes) {
  if (fuzzing_bytes.pool_init_values().buf_uint8_t_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_double_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._int_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._cmsuint32number_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().cmscolorspacesignature_size() != PRIMITIVE_POOL_SIZE) { return 1; }

  if (fuzzing_bytes.api_block_call_seq_size() > MAX_API_SEQ_LEN) { return 1; }

  for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
    if (fuzzing_bytes.pool_init_values().buf_uint8_t_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_double_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
  }
  return 0;
}
FUZZING_BYTES bound_bank_index (FUZZING_BYTES fuzzing_bytes) {
  for (int i = 0; i < fuzzing_bytes.api_block_call_seq_size(); i++) {

    fuzzing_bytes.mutable_api_block_call_seq(i)->set_api_block_call_num(fuzzing_bytes.mutable_api_block_call_seq(i)->api_block_call_num() % API_BLOCK_N);
    APIB_CALL_INPUT *api_block_call_input = fuzzing_bytes.mutable_api_block_call_seq(i)->mutable_api_block_call_input();

    api_block_call_input->set_in_idx_cmshtransform_0(api_block_call_input->in_idx_cmshtransform_0() % OBJ_POOL_SIZE);
    api_block_call_input->set_out_idx_cmshtransform_0(api_block_call_input->out_idx_cmshtransform_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_uint8_t_p_0(api_block_call_input->in_idx_buf_uint8_t_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_in_idx_buf_uint8_t_p_1(api_block_call_input->in_idx_buf_uint8_t_p_1() % BUFFER_POOL_SIZE);
    api_block_call_input->set_in_idx_buf_uint8_t_p_2(api_block_call_input->in_idx_buf_uint8_t_p_2() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_uint8_t_p_0(api_block_call_input->out_idx_buf_uint8_t_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_uint8_t_p_1(api_block_call_input->out_idx_buf_uint8_t_p_1() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_double_p_0(api_block_call_input->in_idx_buf_double_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_double_p_0(api_block_call_input->out_idx_buf_double_p_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__int_0(api_block_call_input->in_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_1(api_block_call_input->in_idx__int_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_2(api_block_call_input->in_idx__int_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_3(api_block_call_input->in_idx__int_3() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_0(api_block_call_input->out_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_1(api_block_call_input->out_idx__int_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_2(api_block_call_input->out_idx__int_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_3(api_block_call_input->out_idx__int_3() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__cmsuint32number_0(api_block_call_input->in_idx__cmsuint32number_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__cmsuint32number_1(api_block_call_input->in_idx__cmsuint32number_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__cmsuint32number_0(api_block_call_input->out_idx__cmsuint32number_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__cmsuint32number_1(api_block_call_input->out_idx__cmsuint32number_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__cmsuint32number_2(api_block_call_input->out_idx__cmsuint32number_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__cmsuint32number_3(api_block_call_input->out_idx__cmsuint32number_3() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__size_t_0(api_block_call_input->in_idx__size_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__size_t_0(api_block_call_input->out_idx__size_t_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_cmshprofile_0(api_block_call_input->in_idx_cmshprofile_0() % OBJ_POOL_SIZE);
    api_block_call_input->set_in_idx_cmshprofile_1(api_block_call_input->in_idx_cmshprofile_1() % OBJ_POOL_SIZE);
    api_block_call_input->set_out_idx_cmshprofile_0(api_block_call_input->out_idx_cmshprofile_0() % OBJ_POOL_SIZE);
    api_block_call_input->set_out_idx_cmshprofile_1(api_block_call_input->out_idx_cmshprofile_1() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx_cmscolorspacesignature_0(api_block_call_input->in_idx_cmscolorspacesignature_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_cmscolorspacesignature_0(api_block_call_input->out_idx_cmscolorspacesignature_0() % PRIMITIVE_POOL_SIZE);

  }
  return fuzzing_bytes;
}

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZING_BYTES& fuzzing_bytes) {
    update_max_api_seq_len();
    if (check_validity(fuzzing_bytes)) return;

    FUZZING_BYTES serialized_bytes = bound_bank_index(fuzzing_bytes);

    for (int i = 0; i < PRIMITIVE_POOL_SIZE; i++) {
      pool__int[i] = (int)serialized_bytes.pool_init_values()._int(i).val();

      pool__cmsUInt32Number[i] = (cmsUInt32Number)serialized_bytes.pool_init_values()._cmsuint32number(i).val();

      pool_cmsColorSpaceSignature[i] = to_cmsColorSpaceSignature(serialized_bytes.pool_init_values().cmscolorspacesignature(i));

    }


    std::string buf;
    for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
      buf = serialized_bytes.pool_init_values().buf_uint8_t_p(i).val();
      pool__size_t[i] = buf.length();
      buf += '\0';
      pool_buf_uint8_t_p[i] = (uint8_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_uint8_t_p[i], buf.data(), buf.size());

      buf = serialized_bytes.pool_init_values().buf_double_p(i).val();
      buf += '\0';
      pool_buf_double_p[i] = (double*)malloc(buf.length());
      std::memcpy((void*)pool_buf_double_p[i], buf.data(), buf.size());

    }


  for (int i = 0; i < serialized_bytes.api_block_call_seq_size(); i++) {
    uint32_t api_block_call_num  = serialized_bytes.api_block_call_seq(i).api_block_call_num();
    const APIB_CALL_INPUT& api_block_call_input = serialized_bytes.api_block_call_seq(i).api_block_call_input();

    switch(api_block_call_num) {

      case 0:
        call_driver_20(api_block_call_input);
        break;

      case 1:
        call_driver_21_to_29(api_block_call_input);
        break;

      case 2:
        call_driver_30(api_block_call_input);
        break;

      case 3:
        call_driver_31_to_43(api_block_call_input);
        break;

      case 4:
        call_driver_44(api_block_call_input);
        break;

      case 5:
        call_driver_45(api_block_call_input);
        break;

      case 6:
        call_driver_46_to_58(api_block_call_input);
        break;

      case 7:
        call_driver_52(api_block_call_input);
        break;

      case 8:
        call_driver_56(api_block_call_input);
        break;

      case 9:
        call_driver_24_to_27(api_block_call_input);
        break;

      case 10:
        call_driver_49_to_57(api_block_call_input);
        break;
    };
  }
}

void call_driver_20 (const APIB_CALL_INPUT& ref) {
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t size = pool__size_t[ref.in_idx__size_t_0()];

  cmsHPROFILE srcProfile = cmsOpenProfileFromMem(data, size);

  pool__size_t[ref.out_idx__size_t_0()] = size;
  pool_cmsHPROFILE[ref.out_idx__size_t_0()] = srcProfile ;
}

void call_driver_21_to_29 (const APIB_CALL_INPUT& ref) {
  cmsHPROFILE srcProfile = pool_cmsHPROFILE[ref.in_idx_cmshprofile_0()];

  if (!srcProfile) return;

  cmsHPROFILE dstProfile = cmsCreate_sRGBProfile();
  if (!dstProfile) {
    cmsCloseProfile(srcProfile);
    return;
  }

  cmsColorSpaceSignature srcCS = cmsGetColorSpace(srcProfile);

  pool_cmsHPROFILE[ref.out_idx_cmshprofile_0()] = srcProfile;
  pool_cmsHPROFILE[ref.out_idx_cmshprofile_0()] = dstProfile ;
  pool_cmsColorSpaceSignature[ref.out_idx_cmshprofile_0()] = srcCS ;
}

void call_driver_30 (const APIB_CALL_INPUT& ref) {
  cmsColorSpaceSignature srcCS = pool_cmsColorSpaceSignature[ref.in_idx_cmscolorspacesignature_0()];

  cmsUInt32Number nSrcComponents = cmsChannelsOf(srcCS);

  pool_cmsColorSpaceSignature[ref.out_idx_cmscolorspacesignature_0()] = srcCS;
  pool__cmsUInt32Number[ref.out_idx_cmscolorspacesignature_0()] = nSrcComponents ;
}

void call_driver_31_to_43 (const APIB_CALL_INPUT& ref) {
  cmsUInt32Number nSrcComponents = pool__cmsUInt32Number[ref.in_idx__cmsuint32number_0()];
  cmsHPROFILE srcProfile = pool_cmsHPROFILE[ref.in_idx_cmshprofile_0()];
  cmsHPROFILE dstProfile = pool_cmsHPROFILE[ref.in_idx_cmshprofile_1()];
  cmsColorSpaceSignature srcCS = pool_cmsColorSpaceSignature[ref.in_idx_cmscolorspacesignature_0()];
  int _t3_ = pool__int[ref.in_idx__int_0()];
  int _t4_ = pool__int[ref.in_idx__int_1()];
  int _t5_ = pool__int[ref.in_idx__int_2()];
  int _t6_ = pool__int[ref.in_idx__int_3()];

  cmsUInt32Number srcFormat;
  if (srcCS == cmsSigLabData) {
    srcFormat =
        COLORSPACE_SH(PT_Lab) | CHANNELS_SH(nSrcComponents) | BYTES_SH(_t3_);
  } else {
    srcFormat =
        COLORSPACE_SH(PT_ANY) | CHANNELS_SH(nSrcComponents) | BYTES_SH(_t4_);
  }

  cmsUInt32Number intent = _t5_;
  cmsUInt32Number flags = _t6_;
  cmsHTRANSFORM hTransform = cmsCreateTransform(
      srcProfile, srcFormat, dstProfile, TYPE_BGR_8, intent, flags);

  pool__cmsUInt32Number[ref.out_idx__cmsuint32number_0()] = nSrcComponents;
  pool_cmsHPROFILE[ref.out_idx_cmshprofile_0()] = srcProfile;
  pool_cmsHPROFILE[ref.out_idx_cmshprofile_0()] = dstProfile;
  pool_cmsColorSpaceSignature[ref.out_idx_cmscolorspacesignature_0()] = srcCS;
  pool__int[ref.out_idx__int_0()] = _t3_;
  pool__int[ref.out_idx__int_0()] = _t4_;
  pool__int[ref.out_idx__int_0()] = _t5_;
  pool__int[ref.out_idx__int_0()] = _t6_;
  pool__cmsUInt32Number[ref.out_idx__int_0()] = srcFormat ;
  pool__cmsUInt32Number[ref.out_idx__int_0()] = intent ;
  pool__cmsUInt32Number[ref.out_idx__int_0()] = flags ;
}

void call_driver_44 (const APIB_CALL_INPUT& ref) {
  cmsHPROFILE srcProfile = pool_cmsHPROFILE[ref.in_idx_cmshprofile_0()];

  cmsCloseProfile(srcProfile);

  pool_cmsHPROFILE[ref.out_idx_cmshprofile_0()] = srcProfile;
}

void call_driver_45 (const APIB_CALL_INPUT& ref) {
  cmsHPROFILE dstProfile = pool_cmsHPROFILE[ref.in_idx_cmshprofile_0()];

  cmsCloseProfile(dstProfile);

  pool_cmsHPROFILE[ref.out_idx_cmshprofile_0()] = dstProfile;
}

void call_driver_46_to_58 (const APIB_CALL_INPUT& ref) {
  cmsHTRANSFORM hTransform = pool_cmsHTRANSFORM[ref.in_idx_cmshtransform_0()];
  cmsUInt32Number srcFormat = pool__cmsUInt32Number[ref.in_idx__cmsuint32number_0()];
  cmsUInt32Number nSrcComponents = pool__cmsUInt32Number[ref.in_idx__cmsuint32number_1()];

  if (!hTransform) return;

  uint8_t output[4];
  if (T_BYTES(srcFormat) == 0) {  // 0 means double
    double input[nSrcComponents];
    for (uint32_t i = 0; i < nSrcComponents; i++) input[i] = 0.5f;
    cmsDoTransform(hTransform, input, output, 1);
  } else {
    uint8_t input[nSrcComponents];
    for (uint32_t i = 0; i < nSrcComponents; i++) input[i] = 128;
    cmsDoTransform(hTransform, input, output, 1);
  }
  cmsDeleteTransform(hTransform);

  pool_cmsHTRANSFORM[ref.out_idx_cmshtransform_0()] = hTransform;
  pool__cmsUInt32Number[ref.out_idx__cmsuint32number_0()] = srcFormat;
  pool__cmsUInt32Number[ref.out_idx__cmsuint32number_0()] = nSrcComponents;
  pool_buf_uint8_t_p[ref.out_idx__cmsuint32number_0()] = output ;
}

void call_driver_52 (const APIB_CALL_INPUT& ref) {
  cmsHTRANSFORM hTransform = pool_cmsHTRANSFORM[ref.in_idx_cmshtransform_0()];
  uint8_t* output = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  double* input = pool_buf_double_p[ref.in_idx_buf_double_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];

    cmsDoTransform(hTransform, input, output, _t0_);

  pool_cmsHTRANSFORM[ref.out_idx_cmshtransform_0()] = hTransform;
  pool_buf_uint8_t_p[ref.out_idx_buf_uint8_t_p_0()] = output;
  pool_buf_double_p[ref.out_idx_buf_double_p_0()] = input;
  pool__int[ref.out_idx__int_0()] = _t0_;
  pool_buf_uint8_t_p[ref.out_idx__int_0()] = output ;
}

void call_driver_56 (const APIB_CALL_INPUT& ref) {
  cmsHTRANSFORM hTransform = pool_cmsHTRANSFORM[ref.in_idx_cmshtransform_0()];
  uint8_t* output = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  uint8_t* input = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_1()];
  int _t0_ = pool__int[ref.in_idx__int_0()];

    cmsDoTransform(hTransform, input, output, _t0_);

  pool_cmsHTRANSFORM[ref.out_idx_cmshtransform_0()] = hTransform;
  pool_buf_uint8_t_p[ref.out_idx_buf_uint8_t_p_0()] = output;
  pool_buf_uint8_t_p[ref.out_idx_buf_uint8_t_p_0()] = input;
  pool__int[ref.out_idx__int_0()] = _t0_;
}

void call_driver_24_to_27 (const APIB_CALL_INPUT& ref) {
  cmsUInt32Number nSrcComponents = pool__cmsUInt32Number[ref.in_idx__cmsuint32number_0()];
  cmsHPROFILE srcProfile = pool_cmsHPROFILE[ref.in_idx_cmshprofile_0()];
  cmsHPROFILE dstProfile = pool_cmsHPROFILE[ref.in_idx_cmshprofile_1()];

  if (!dstProfile) {
    cmsCloseProfile(srcProfile);
    return;
  }

  pool__cmsUInt32Number[ref.out_idx__cmsuint32number_0()] = nSrcComponents;
  pool_cmsHPROFILE[ref.out_idx_cmshprofile_0()] = srcProfile;
  pool_cmsHPROFILE[ref.out_idx_cmshprofile_0()] = dstProfile;
}

void call_driver_49_to_57 (const APIB_CALL_INPUT& ref) {
  cmsHTRANSFORM hTransform = pool_cmsHTRANSFORM[ref.in_idx_cmshtransform_0()];
  cmsUInt32Number srcFormat = pool__cmsUInt32Number[ref.in_idx__cmsuint32number_0()];
  cmsUInt32Number nSrcComponents = pool__cmsUInt32Number[ref.in_idx__cmsuint32number_1()];
  uint8_t* output = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];

  if (T_BYTES(srcFormat) == 0) {  // 0 means double
    double input[nSrcComponents];
    for (uint32_t i = 0; i < nSrcComponents; i++) input[i] = 0.5f;
    cmsDoTransform(hTransform, input, output, 1);
  } else {
    uint8_t input[nSrcComponents];
    for (uint32_t i = 0; i < nSrcComponents; i++) input[i] = 128;
    cmsDoTransform(hTransform, input, output, 1);
  }

  pool_cmsHTRANSFORM[ref.out_idx_cmshtransform_0()] = hTransform;
  pool__cmsUInt32Number[ref.out_idx__cmsuint32number_0()] = srcFormat;
  pool__cmsUInt32Number[ref.out_idx__cmsuint32number_0()] = nSrcComponents;
  pool_buf_uint8_t_p[ref.out_idx_buf_uint8_t_p_0()] = output;
}

