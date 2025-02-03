#include "gfuzz_curl.h"

static int MAX_API_SEQ_LEN = 0;
#define OBJ_POOL_SIZE 0
#define PRIMITIVE_POOL_SIZE 0
#define BUFFER_POOL_SIZE 0
#define API_BLOCK_N 13
#define MAX_BUFFER_SIZE 1048576

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

size_t pool__size_t[PRIMITIVE_POOL_SIZE];
uint8_t* pool_buf_uint8_t_p[BUFFER_POOL_SIZE];
int pool__int[PRIMITIVE_POOL_SIZE];
FUZZ_DATA pool_FUZZ_DATA[OBJ_POOL_SIZE];
CURLoption pool_CURLoption[PRIMITIVE_POOL_SIZE];
TLV pool_TLV[OBJ_POOL_SIZE];

void call_driver_36_to_53 (const APIB_CALL_INPUT& ref);
void call_driver_55_to_74 (const APIB_CALL_INPUT& ref);
void call_driver_80_to_97 (const APIB_CALL_INPUT& ref);
void call_driver_101 (const APIB_CALL_INPUT& ref);
void call_driver_80_to_82 (const APIB_CALL_INPUT& ref);
void call_driver_84_to_86 (const APIB_CALL_INPUT& ref);
void call_driver_88_to_90 (const APIB_CALL_INPUT& ref);
void call_driver_92_to_94 (const APIB_CALL_INPUT& ref);
void call_driver_55_to_66 (const APIB_CALL_INPUT& ref);
void call_driver_81 (const APIB_CALL_INPUT& ref);
void call_driver_85 (const APIB_CALL_INPUT& ref);
void call_driver_89 (const APIB_CALL_INPUT& ref);
void call_driver_93 (const APIB_CALL_INPUT& ref);

CURLoption to_CURLoption (CURLOPTION val) {
  switch (val) {
    case val_CURLOPT_WRITEDATA: return CURLOPT_WRITEDATA;
    case val_CURLOPT_URL: return CURLOPT_URL;
    case val_CURLOPT_PORT: return CURLOPT_PORT;
    case val_CURLOPT_PROXY: return CURLOPT_PROXY;
    case val_CURLOPT_USERPWD: return CURLOPT_USERPWD;
    case val_CURLOPT_PROXYUSERPWD: return CURLOPT_PROXYUSERPWD;
    case val_CURLOPT_RANGE: return CURLOPT_RANGE;
    case val_CURLOPT_READDATA: return CURLOPT_READDATA;
    case val_CURLOPT_ERRORBUFFER: return CURLOPT_ERRORBUFFER;
    case val_CURLOPT_WRITEFUNCTION: return CURLOPT_WRITEFUNCTION;
    case val_CURLOPT_READFUNCTION: return CURLOPT_READFUNCTION;
    case val_CURLOPT_TIMEOUT: return CURLOPT_TIMEOUT;
    case val_CURLOPT_INFILESIZE: return CURLOPT_INFILESIZE;
    case val_CURLOPT_POSTFIELDS: return CURLOPT_POSTFIELDS;
    case val_CURLOPT_REFERER: return CURLOPT_REFERER;
    case val_CURLOPT_FTPPORT: return CURLOPT_FTPPORT;
    case val_CURLOPT_USERAGENT: return CURLOPT_USERAGENT;
    case val_CURLOPT_LOW_SPEED_LIMIT: return CURLOPT_LOW_SPEED_LIMIT;
    case val_CURLOPT_LOW_SPEED_TIME: return CURLOPT_LOW_SPEED_TIME;
    case val_CURLOPT_RESUME_FROM: return CURLOPT_RESUME_FROM;
    case val_CURLOPT_COOKIE: return CURLOPT_COOKIE;
    case val_CURLOPT_HTTPHEADER: return CURLOPT_HTTPHEADER;
    case val_CURLOPT_HTTPPOST: return CURLOPT_HTTPPOST;
    case val_CURLOPT_SSLCERT: return CURLOPT_SSLCERT;
    case val_CURLOPT_KEYPASSWD: return CURLOPT_KEYPASSWD;
    case val_CURLOPT_CRLF: return CURLOPT_CRLF;
    case val_CURLOPT_QUOTE: return CURLOPT_QUOTE;
    case val_CURLOPT_HEADERDATA: return CURLOPT_HEADERDATA;
    case val_CURLOPT_COOKIEFILE: return CURLOPT_COOKIEFILE;
    case val_CURLOPT_SSLVERSION: return CURLOPT_SSLVERSION;
    case val_CURLOPT_TIMECONDITION: return CURLOPT_TIMECONDITION;
    case val_CURLOPT_TIMEVALUE: return CURLOPT_TIMEVALUE;
    case val_CURLOPT_CUSTOMREQUEST: return CURLOPT_CUSTOMREQUEST;
    case val_CURLOPT_STDERR: return CURLOPT_STDERR;
    case val_CURLOPT_POSTQUOTE: return CURLOPT_POSTQUOTE;
    case val_CURLOPT_OBSOLETE40: return CURLOPT_OBSOLETE40;
    case val_CURLOPT_VERBOSE: return CURLOPT_VERBOSE;
    case val_CURLOPT_HEADER: return CURLOPT_HEADER;
    case val_CURLOPT_NOPROGRESS: return CURLOPT_NOPROGRESS;
    case val_CURLOPT_NOBODY: return CURLOPT_NOBODY;
    case val_CURLOPT_FAILONERROR: return CURLOPT_FAILONERROR;
    case val_CURLOPT_UPLOAD: return CURLOPT_UPLOAD;
    case val_CURLOPT_POST: return CURLOPT_POST;
    case val_CURLOPT_DIRLISTONLY: return CURLOPT_DIRLISTONLY;
    case val_CURLOPT_APPEND: return CURLOPT_APPEND;
    case val_CURLOPT_NETRC: return CURLOPT_NETRC;
    case val_CURLOPT_FOLLOWLOCATION: return CURLOPT_FOLLOWLOCATION;
    case val_CURLOPT_TRANSFERTEXT: return CURLOPT_TRANSFERTEXT;
    case val_CURLOPT_PUT: return CURLOPT_PUT;
    case val_CURLOPT_PROGRESSFUNCTION: return CURLOPT_PROGRESSFUNCTION;
    case val_CURLOPT_XFERINFODATA: return CURLOPT_XFERINFODATA;
    case val_CURLOPT_AUTOREFERER: return CURLOPT_AUTOREFERER;
    case val_CURLOPT_PROXYPORT: return CURLOPT_PROXYPORT;
    case val_CURLOPT_POSTFIELDSIZE: return CURLOPT_POSTFIELDSIZE;
    case val_CURLOPT_HTTPPROXYTUNNEL: return CURLOPT_HTTPPROXYTUNNEL;
    case val_CURLOPT_INTERFACE: return CURLOPT_INTERFACE;
    case val_CURLOPT_KRBLEVEL: return CURLOPT_KRBLEVEL;
    case val_CURLOPT_SSL_VERIFYPEER: return CURLOPT_SSL_VERIFYPEER;
    case val_CURLOPT_CAINFO: return CURLOPT_CAINFO;
    case val_CURLOPT_MAXREDIRS: return CURLOPT_MAXREDIRS;
    case val_CURLOPT_FILETIME: return CURLOPT_FILETIME;
    case val_CURLOPT_TELNETOPTIONS: return CURLOPT_TELNETOPTIONS;
    case val_CURLOPT_MAXCONNECTS: return CURLOPT_MAXCONNECTS;
    case val_CURLOPT_OBSOLETE72: return CURLOPT_OBSOLETE72;
    case val_CURLOPT_FRESH_CONNECT: return CURLOPT_FRESH_CONNECT;
    case val_CURLOPT_FORBID_REUSE: return CURLOPT_FORBID_REUSE;
    case val_CURLOPT_RANDOM_FILE: return CURLOPT_RANDOM_FILE;
    case val_CURLOPT_EGDSOCKET: return CURLOPT_EGDSOCKET;
    case val_CURLOPT_CONNECTTIMEOUT: return CURLOPT_CONNECTTIMEOUT;
    case val_CURLOPT_HEADERFUNCTION: return CURLOPT_HEADERFUNCTION;
    case val_CURLOPT_HTTPGET: return CURLOPT_HTTPGET;
    case val_CURLOPT_SSL_VERIFYHOST: return CURLOPT_SSL_VERIFYHOST;
    case val_CURLOPT_COOKIEJAR: return CURLOPT_COOKIEJAR;
    case val_CURLOPT_SSL_CIPHER_LIST: return CURLOPT_SSL_CIPHER_LIST;
    case val_CURLOPT_HTTP_VERSION: return CURLOPT_HTTP_VERSION;
    case val_CURLOPT_FTP_USE_EPSV: return CURLOPT_FTP_USE_EPSV;
    case val_CURLOPT_SSLCERTTYPE: return CURLOPT_SSLCERTTYPE;
    case val_CURLOPT_SSLKEY: return CURLOPT_SSLKEY;
    case val_CURLOPT_SSLKEYTYPE: return CURLOPT_SSLKEYTYPE;
    case val_CURLOPT_SSLENGINE: return CURLOPT_SSLENGINE;
    case val_CURLOPT_SSLENGINE_DEFAULT: return CURLOPT_SSLENGINE_DEFAULT;
    case val_CURLOPT_DNS_USE_GLOBAL_CACHE: return CURLOPT_DNS_USE_GLOBAL_CACHE;
    case val_CURLOPT_DNS_CACHE_TIMEOUT: return CURLOPT_DNS_CACHE_TIMEOUT;
    case val_CURLOPT_PREQUOTE: return CURLOPT_PREQUOTE;
    case val_CURLOPT_DEBUGFUNCTION: return CURLOPT_DEBUGFUNCTION;
    case val_CURLOPT_DEBUGDATA: return CURLOPT_DEBUGDATA;
    case val_CURLOPT_COOKIESESSION: return CURLOPT_COOKIESESSION;
    case val_CURLOPT_CAPATH: return CURLOPT_CAPATH;
    case val_CURLOPT_BUFFERSIZE: return CURLOPT_BUFFERSIZE;
    case val_CURLOPT_NOSIGNAL: return CURLOPT_NOSIGNAL;
    case val_CURLOPT_SHARE: return CURLOPT_SHARE;
    case val_CURLOPT_PROXYTYPE: return CURLOPT_PROXYTYPE;
    case val_CURLOPT_PRIVATE: return CURLOPT_PRIVATE;
    case val_CURLOPT_HTTP200ALIASES: return CURLOPT_HTTP200ALIASES;
    case val_CURLOPT_UNRESTRICTED_AUTH: return CURLOPT_UNRESTRICTED_AUTH;
    case val_CURLOPT_FTP_USE_EPRT: return CURLOPT_FTP_USE_EPRT;
    case val_CURLOPT_HTTPAUTH: return CURLOPT_HTTPAUTH;
    case val_CURLOPT_SSL_CTX_FUNCTION: return CURLOPT_SSL_CTX_FUNCTION;
    case val_CURLOPT_SSL_CTX_DATA: return CURLOPT_SSL_CTX_DATA;
    case val_CURLOPT_FTP_CREATE_MISSING_DIRS: return CURLOPT_FTP_CREATE_MISSING_DIRS;
    case val_CURLOPT_PROXYAUTH: return CURLOPT_PROXYAUTH;
    case val_CURLOPT_SERVER_RESPONSE_TIMEOUT: return CURLOPT_SERVER_RESPONSE_TIMEOUT;
    case val_CURLOPT_IPRESOLVE: return CURLOPT_IPRESOLVE;
    case val_CURLOPT_MAXFILESIZE: return CURLOPT_MAXFILESIZE;
    case val_CURLOPT_INFILESIZE_LARGE: return CURLOPT_INFILESIZE_LARGE;
    case val_CURLOPT_RESUME_FROM_LARGE: return CURLOPT_RESUME_FROM_LARGE;
    case val_CURLOPT_MAXFILESIZE_LARGE: return CURLOPT_MAXFILESIZE_LARGE;
    case val_CURLOPT_NETRC_FILE: return CURLOPT_NETRC_FILE;
    case val_CURLOPT_USE_SSL: return CURLOPT_USE_SSL;
    case val_CURLOPT_POSTFIELDSIZE_LARGE: return CURLOPT_POSTFIELDSIZE_LARGE;
    case val_CURLOPT_TCP_NODELAY: return CURLOPT_TCP_NODELAY;
    case val_CURLOPT_FTPSSLAUTH: return CURLOPT_FTPSSLAUTH;
    case val_CURLOPT_IOCTLFUNCTION: return CURLOPT_IOCTLFUNCTION;
    case val_CURLOPT_FTP_ACCOUNT: return CURLOPT_FTP_ACCOUNT;
    case val_CURLOPT_COOKIELIST: return CURLOPT_COOKIELIST;
    case val_CURLOPT_IGNORE_CONTENT_LENGTH: return CURLOPT_IGNORE_CONTENT_LENGTH;
    case val_CURLOPT_FTP_SKIP_PASV_IP: return CURLOPT_FTP_SKIP_PASV_IP;
    case val_CURLOPT_FTP_FILEMETHOD: return CURLOPT_FTP_FILEMETHOD;
    case val_CURLOPT_LOCALPORT: return CURLOPT_LOCALPORT;
    case val_CURLOPT_LOCALPORTRANGE: return CURLOPT_LOCALPORTRANGE;
    case val_CURLOPT_CONNECT_ONLY: return CURLOPT_CONNECT_ONLY;
    case val_CURLOPT_CONV_FROM_NETWORK_FUNCTION: return CURLOPT_CONV_FROM_NETWORK_FUNCTION;
    case val_CURLOPT_CONV_TO_NETWORK_FUNCTION: return CURLOPT_CONV_TO_NETWORK_FUNCTION;
    case val_CURLOPT_CONV_FROM_UTF8_FUNCTION: return CURLOPT_CONV_FROM_UTF8_FUNCTION;
    case val_CURLOPT_MAX_SEND_SPEED_LARGE: return CURLOPT_MAX_SEND_SPEED_LARGE;
    case val_CURLOPT_MAX_RECV_SPEED_LARGE: return CURLOPT_MAX_RECV_SPEED_LARGE;
    case val_CURLOPT_FTP_ALTERNATIVE_TO_USER: return CURLOPT_FTP_ALTERNATIVE_TO_USER;
    case val_CURLOPT_SOCKOPTFUNCTION: return CURLOPT_SOCKOPTFUNCTION;
    case val_CURLOPT_SOCKOPTDATA: return CURLOPT_SOCKOPTDATA;
    case val_CURLOPT_SSL_SESSIONID_CACHE: return CURLOPT_SSL_SESSIONID_CACHE;
    case val_CURLOPT_SSH_AUTH_TYPES: return CURLOPT_SSH_AUTH_TYPES;
    case val_CURLOPT_SSH_PUBLIC_KEYFILE: return CURLOPT_SSH_PUBLIC_KEYFILE;
    case val_CURLOPT_SSH_PRIVATE_KEYFILE: return CURLOPT_SSH_PRIVATE_KEYFILE;
    case val_CURLOPT_FTP_SSL_CCC: return CURLOPT_FTP_SSL_CCC;
    case val_CURLOPT_TIMEOUT_MS: return CURLOPT_TIMEOUT_MS;
    case val_CURLOPT_CONNECTTIMEOUT_MS: return CURLOPT_CONNECTTIMEOUT_MS;
    case val_CURLOPT_HTTP_TRANSFER_DECODING: return CURLOPT_HTTP_TRANSFER_DECODING;
    case val_CURLOPT_HTTP_CONTENT_DECODING: return CURLOPT_HTTP_CONTENT_DECODING;
    case val_CURLOPT_NEW_FILE_PERMS: return CURLOPT_NEW_FILE_PERMS;
    case val_CURLOPT_NEW_DIRECTORY_PERMS: return CURLOPT_NEW_DIRECTORY_PERMS;
    case val_CURLOPT_SSH_HOST_PUBLIC_KEY_MD5: return CURLOPT_SSH_HOST_PUBLIC_KEY_MD5;
    case val_CURLOPT_OPENSOCKETFUNCTION: return CURLOPT_OPENSOCKETFUNCTION;
    case val_CURLOPT_OPENSOCKETDATA: return CURLOPT_OPENSOCKETDATA;
    case val_CURLOPT_COPYPOSTFIELDS: return CURLOPT_COPYPOSTFIELDS;
    case val_CURLOPT_PROXY_TRANSFER_MODE: return CURLOPT_PROXY_TRANSFER_MODE;
    case val_CURLOPT_SEEKFUNCTION: return CURLOPT_SEEKFUNCTION;
    case val_CURLOPT_SEEKDATA: return CURLOPT_SEEKDATA;
    case val_CURLOPT_CRLFILE: return CURLOPT_CRLFILE;
    case val_CURLOPT_ISSUERCERT: return CURLOPT_ISSUERCERT;
    case val_CURLOPT_ADDRESS_SCOPE: return CURLOPT_ADDRESS_SCOPE;
    case val_CURLOPT_CERTINFO: return CURLOPT_CERTINFO;
    case val_CURLOPT_USERNAME: return CURLOPT_USERNAME;
    case val_CURLOPT_PASSWORD: return CURLOPT_PASSWORD;
    case val_CURLOPT_PROXYUSERNAME: return CURLOPT_PROXYUSERNAME;
    case val_CURLOPT_PROXYPASSWORD: return CURLOPT_PROXYPASSWORD;
    case val_CURLOPT_NOPROXY: return CURLOPT_NOPROXY;
    case val_CURLOPT_TFTP_BLKSIZE: return CURLOPT_TFTP_BLKSIZE;
    case val_CURLOPT_SOCKS5_GSSAPI_SERVICE: return CURLOPT_SOCKS5_GSSAPI_SERVICE;
    case val_CURLOPT_SOCKS5_GSSAPI_NEC: return CURLOPT_SOCKS5_GSSAPI_NEC;
    case val_CURLOPT_PROTOCOLS: return CURLOPT_PROTOCOLS;
    case val_CURLOPT_REDIR_PROTOCOLS: return CURLOPT_REDIR_PROTOCOLS;
    case val_CURLOPT_SSH_KNOWNHOSTS: return CURLOPT_SSH_KNOWNHOSTS;
    case val_CURLOPT_SSH_KEYFUNCTION: return CURLOPT_SSH_KEYFUNCTION;
    case val_CURLOPT_SSH_KEYDATA: return CURLOPT_SSH_KEYDATA;
    case val_CURLOPT_MAIL_FROM: return CURLOPT_MAIL_FROM;
    case val_CURLOPT_MAIL_RCPT: return CURLOPT_MAIL_RCPT;
    case val_CURLOPT_FTP_USE_PRET: return CURLOPT_FTP_USE_PRET;
    case val_CURLOPT_RTSP_REQUEST: return CURLOPT_RTSP_REQUEST;
    case val_CURLOPT_RTSP_SESSION_ID: return CURLOPT_RTSP_SESSION_ID;
    case val_CURLOPT_RTSP_STREAM_URI: return CURLOPT_RTSP_STREAM_URI;
    case val_CURLOPT_RTSP_TRANSPORT: return CURLOPT_RTSP_TRANSPORT;
    case val_CURLOPT_RTSP_CLIENT_CSEQ: return CURLOPT_RTSP_CLIENT_CSEQ;
    case val_CURLOPT_RTSP_SERVER_CSEQ: return CURLOPT_RTSP_SERVER_CSEQ;
    case val_CURLOPT_INTERLEAVEDATA: return CURLOPT_INTERLEAVEDATA;
    case val_CURLOPT_INTERLEAVEFUNCTION: return CURLOPT_INTERLEAVEFUNCTION;
    case val_CURLOPT_WILDCARDMATCH: return CURLOPT_WILDCARDMATCH;
    case val_CURLOPT_CHUNK_BGN_FUNCTION: return CURLOPT_CHUNK_BGN_FUNCTION;
    case val_CURLOPT_CHUNK_END_FUNCTION: return CURLOPT_CHUNK_END_FUNCTION;
    case val_CURLOPT_FNMATCH_FUNCTION: return CURLOPT_FNMATCH_FUNCTION;
    case val_CURLOPT_CHUNK_DATA: return CURLOPT_CHUNK_DATA;
    case val_CURLOPT_FNMATCH_DATA: return CURLOPT_FNMATCH_DATA;
    case val_CURLOPT_RESOLVE: return CURLOPT_RESOLVE;
    case val_CURLOPT_TLSAUTH_USERNAME: return CURLOPT_TLSAUTH_USERNAME;
    case val_CURLOPT_TLSAUTH_PASSWORD: return CURLOPT_TLSAUTH_PASSWORD;
    case val_CURLOPT_TLSAUTH_TYPE: return CURLOPT_TLSAUTH_TYPE;
    case val_CURLOPT_TRANSFER_ENCODING: return CURLOPT_TRANSFER_ENCODING;
    case val_CURLOPT_CLOSESOCKETFUNCTION: return CURLOPT_CLOSESOCKETFUNCTION;
    case val_CURLOPT_CLOSESOCKETDATA: return CURLOPT_CLOSESOCKETDATA;
    case val_CURLOPT_GSSAPI_DELEGATION: return CURLOPT_GSSAPI_DELEGATION;
    case val_CURLOPT_DNS_SERVERS: return CURLOPT_DNS_SERVERS;
    case val_CURLOPT_ACCEPTTIMEOUT_MS: return CURLOPT_ACCEPTTIMEOUT_MS;
    case val_CURLOPT_TCP_KEEPALIVE: return CURLOPT_TCP_KEEPALIVE;
    case val_CURLOPT_TCP_KEEPIDLE: return CURLOPT_TCP_KEEPIDLE;
    case val_CURLOPT_TCP_KEEPINTVL: return CURLOPT_TCP_KEEPINTVL;
    case val_CURLOPT_SSL_OPTIONS: return CURLOPT_SSL_OPTIONS;
    case val_CURLOPT_MAIL_AUTH: return CURLOPT_MAIL_AUTH;
    case val_CURLOPT_SASL_IR: return CURLOPT_SASL_IR;
    case val_CURLOPT_XFERINFOFUNCTION: return CURLOPT_XFERINFOFUNCTION;
    case val_CURLOPT_XOAUTH2_BEARER: return CURLOPT_XOAUTH2_BEARER;
    case val_CURLOPT_DNS_INTERFACE: return CURLOPT_DNS_INTERFACE;
    case val_CURLOPT_DNS_LOCAL_IP4: return CURLOPT_DNS_LOCAL_IP4;
    case val_CURLOPT_DNS_LOCAL_IP6: return CURLOPT_DNS_LOCAL_IP6;
    case val_CURLOPT_LOGIN_OPTIONS: return CURLOPT_LOGIN_OPTIONS;
    case val_CURLOPT_SSL_ENABLE_NPN: return CURLOPT_SSL_ENABLE_NPN;
    case val_CURLOPT_SSL_ENABLE_ALPN: return CURLOPT_SSL_ENABLE_ALPN;
    case val_CURLOPT_EXPECT_100_TIMEOUT_MS: return CURLOPT_EXPECT_100_TIMEOUT_MS;
    case val_CURLOPT_PROXYHEADER: return CURLOPT_PROXYHEADER;
    case val_CURLOPT_HEADEROPT: return CURLOPT_HEADEROPT;
    case val_CURLOPT_PINNEDPUBLICKEY: return CURLOPT_PINNEDPUBLICKEY;
    case val_CURLOPT_UNIX_SOCKET_PATH: return CURLOPT_UNIX_SOCKET_PATH;
    case val_CURLOPT_SSL_VERIFYSTATUS: return CURLOPT_SSL_VERIFYSTATUS;
    case val_CURLOPT_SSL_FALSESTART: return CURLOPT_SSL_FALSESTART;
    case val_CURLOPT_PATH_AS_IS: return CURLOPT_PATH_AS_IS;
    case val_CURLOPT_PROXY_SERVICE_NAME: return CURLOPT_PROXY_SERVICE_NAME;
    case val_CURLOPT_SERVICE_NAME: return CURLOPT_SERVICE_NAME;
    case val_CURLOPT_PIPEWAIT: return CURLOPT_PIPEWAIT;
    case val_CURLOPT_DEFAULT_PROTOCOL: return CURLOPT_DEFAULT_PROTOCOL;
    case val_CURLOPT_STREAM_WEIGHT: return CURLOPT_STREAM_WEIGHT;
    case val_CURLOPT_STREAM_DEPENDS: return CURLOPT_STREAM_DEPENDS;
    case val_CURLOPT_STREAM_DEPENDS_E: return CURLOPT_STREAM_DEPENDS_E;
    case val_CURLOPT_TFTP_NO_OPTIONS: return CURLOPT_TFTP_NO_OPTIONS;
    case val_CURLOPT_CONNECT_TO: return CURLOPT_CONNECT_TO;
    case val_CURLOPT_TCP_FASTOPEN: return CURLOPT_TCP_FASTOPEN;
    case val_CURLOPT_KEEP_SENDING_ON_ERROR: return CURLOPT_KEEP_SENDING_ON_ERROR;
    case val_CURLOPT_PROXY_CAINFO: return CURLOPT_PROXY_CAINFO;
    case val_CURLOPT_PROXY_CAPATH: return CURLOPT_PROXY_CAPATH;
    case val_CURLOPT_PROXY_SSL_VERIFYPEER: return CURLOPT_PROXY_SSL_VERIFYPEER;
    case val_CURLOPT_PROXY_SSL_VERIFYHOST: return CURLOPT_PROXY_SSL_VERIFYHOST;
    case val_CURLOPT_PROXY_SSLVERSION: return CURLOPT_PROXY_SSLVERSION;
    case val_CURLOPT_PROXY_TLSAUTH_USERNAME: return CURLOPT_PROXY_TLSAUTH_USERNAME;
    case val_CURLOPT_PROXY_TLSAUTH_PASSWORD: return CURLOPT_PROXY_TLSAUTH_PASSWORD;
    case val_CURLOPT_PROXY_TLSAUTH_TYPE: return CURLOPT_PROXY_TLSAUTH_TYPE;
    case val_CURLOPT_PROXY_SSLCERT: return CURLOPT_PROXY_SSLCERT;
    case val_CURLOPT_PROXY_SSLCERTTYPE: return CURLOPT_PROXY_SSLCERTTYPE;
    case val_CURLOPT_PROXY_SSLKEY: return CURLOPT_PROXY_SSLKEY;
    case val_CURLOPT_PROXY_SSLKEYTYPE: return CURLOPT_PROXY_SSLKEYTYPE;
    case val_CURLOPT_PROXY_KEYPASSWD: return CURLOPT_PROXY_KEYPASSWD;
    case val_CURLOPT_PROXY_SSL_CIPHER_LIST: return CURLOPT_PROXY_SSL_CIPHER_LIST;
    case val_CURLOPT_PROXY_CRLFILE: return CURLOPT_PROXY_CRLFILE;
    case val_CURLOPT_PROXY_SSL_OPTIONS: return CURLOPT_PROXY_SSL_OPTIONS;
    case val_CURLOPT_PRE_PROXY: return CURLOPT_PRE_PROXY;
    case val_CURLOPT_PROXY_PINNEDPUBLICKEY: return CURLOPT_PROXY_PINNEDPUBLICKEY;
    case val_CURLOPT_ABSTRACT_UNIX_SOCKET: return CURLOPT_ABSTRACT_UNIX_SOCKET;
    case val_CURLOPT_SUPPRESS_CONNECT_HEADERS: return CURLOPT_SUPPRESS_CONNECT_HEADERS;
    case val_CURLOPT_REQUEST_TARGET: return CURLOPT_REQUEST_TARGET;
    case val_CURLOPT_SOCKS5_AUTH: return CURLOPT_SOCKS5_AUTH;
    case val_CURLOPT_SSH_COMPRESSION: return CURLOPT_SSH_COMPRESSION;
    case val_CURLOPT_MIMEPOST: return CURLOPT_MIMEPOST;
    case val_CURLOPT_TIMEVALUE_LARGE: return CURLOPT_TIMEVALUE_LARGE;
    case val_CURLOPT_HAPPY_EYEBALLS_TIMEOUT_MS: return CURLOPT_HAPPY_EYEBALLS_TIMEOUT_MS;
    case val_CURLOPT_RESOLVER_START_FUNCTION: return CURLOPT_RESOLVER_START_FUNCTION;
    case val_CURLOPT_RESOLVER_START_DATA: return CURLOPT_RESOLVER_START_DATA;
    case val_CURLOPT_HAPROXYPROTOCOL: return CURLOPT_HAPROXYPROTOCOL;
    case val_CURLOPT_DNS_SHUFFLE_ADDRESSES: return CURLOPT_DNS_SHUFFLE_ADDRESSES;
    case val_CURLOPT_TLS13_CIPHERS: return CURLOPT_TLS13_CIPHERS;
    case val_CURLOPT_PROXY_TLS13_CIPHERS: return CURLOPT_PROXY_TLS13_CIPHERS;
    case val_CURLOPT_DISALLOW_USERNAME_IN_URL: return CURLOPT_DISALLOW_USERNAME_IN_URL;
    case val_CURLOPT_DOH_URL: return CURLOPT_DOH_URL;
    case val_CURLOPT_UPLOAD_BUFFERSIZE: return CURLOPT_UPLOAD_BUFFERSIZE;
    case val_CURLOPT_UPKEEP_INTERVAL_MS: return CURLOPT_UPKEEP_INTERVAL_MS;
    case val_CURLOPT_CURLU: return CURLOPT_CURLU;
    case val_CURLOPT_TRAILERFUNCTION: return CURLOPT_TRAILERFUNCTION;
    case val_CURLOPT_TRAILERDATA: return CURLOPT_TRAILERDATA;
    case val_CURLOPT_HTTP09_ALLOWED: return CURLOPT_HTTP09_ALLOWED;
    case val_CURLOPT_ALTSVC_CTRL: return CURLOPT_ALTSVC_CTRL;
    case val_CURLOPT_ALTSVC: return CURLOPT_ALTSVC;
    case val_CURLOPT_MAXAGE_CONN: return CURLOPT_MAXAGE_CONN;
    case val_CURLOPT_SASL_AUTHZID: return CURLOPT_SASL_AUTHZID;
    case val_CURLOPT_MAIL_RCPT_ALLOWFAILS: return CURLOPT_MAIL_RCPT_ALLLOWFAILS;
    case val_CURLOPT_SSLCERT_BLOB: return CURLOPT_SSLCERT_BLOB;
    case val_CURLOPT_SSLKEY_BLOB: return CURLOPT_SSLKEY_BLOB;
    //case val_CURLOPT_PROXY_SSLCERT_BLOB: return CURLOPT_PROXY_SSLCERT_BLOB;
    case val_CURLOPT_PROXY_SSLKEY_BLOB: return CURLOPT_PROXY_SSLKEY_BLOB;
    case val_CURLOPT_ISSUERCERT_BLOB: return CURLOPT_ISSUERCERT_BLOB;
    case val_CURLOPT_PROXY_ISSUERCERT: return CURLOPT_PROXY_ISSUERCERT;
    case val_CURLOPT_PROXY_ISSUERCERT_BLOB: return CURLOPT_PROXY_ISSUERCERT_BLOB;
    case val_CURLOPT_SSL_EC_CURVES: return CURLOPT_SSL_EC_CURVES;
    case val_CURLOPT_HSTS_CTRL: return CURLOPT_HSTS_CTRL;
    case val_CURLOPT_HSTS: return CURLOPT_HSTS;
    case val_CURLOPT_HSTSREADFUNCTION: return CURLOPT_HSTSREADFUNCTION;
    case val_CURLOPT_HSTSREADDATA: return CURLOPT_HSTSREADDATA;
    case val_CURLOPT_HSTSWRITEFUNCTION: return CURLOPT_HSTSWRITEFUNCTION;
    case val_CURLOPT_HSTSWRITEDATA: return CURLOPT_HSTSWRITEDATA;
    case val_CURLOPT_AWS_SIGV4: return CURLOPT_AWS_SIGV4;
    case val_CURLOPT_DOH_SSL_VERIFYPEER: return CURLOPT_DOH_SSL_VERIFYPEER;
    case val_CURLOPT_DOH_SSL_VERIFYHOST: return CURLOPT_DOH_SSL_VERIFYHOST;
    case val_CURLOPT_DOH_SSL_VERIFYSTATUS: return CURLOPT_DOH_SSL_VERIFYSTATUS;
    case val_CURLOPT_CAINFO_BLOB: return CURLOPT_CAINFO_BLOB;
    case val_CURLOPT_PROXY_CAINFO_BLOB: return CURLOPT_PROXY_CAINFO_BLOB;
    case val_CURLOPT_SSH_HOST_PUBLIC_KEY_SHA256: return CURLOPT_SSH_HOST_PUBLIC_KEY_SHA256;
    case val_CURLOPT_PREREQFUNCTION: return CURLOPT_PREREQFUNCTION;
    case val_CURLOPT_PREREQDATA: return CURLOPT_PREREQDATA;
    case val_CURLOPT_MAXLIFETIME_CONN: return CURLOPT_MAXLIFETIME_CONN;
    case val_CURLOPT_MIME_OPTIONS: return CURLOPT_MIME_OPTIONS;
    case val_CURLOPT_SSH_HOSTKEYFUNCTION: return CURLOPT_SSH_HOSTKEYFUNCTION;
    case val_CURLOPT_SSH_HOSTKEYDATA: return CURLOPT_SSH_HOSTKEYDATA;
    case val_CURLOPT_PROTOCOLS_STR: return CURLOPT_PROTOCOLS_STR;
    case val_CURLOPT_REDIR_PROTOCOLS_STR: return CURLOPT_REDIR_PROTOCOLS_STR;
    case val_CURLOPT_WS_OPTIONS: return CURLOPT_WS_OPTIONS;
    //case val_CURLOPT_CA_CACHE_TIMEOUT: return CURLOPT_CA_CACHE_TIMEOUT;
    //case val_CURLOPT_QUICK_EXIT: return CURLOPT_QUICK_EXIT;
    //case val_CURLOPT_SERVER_RESPONSE_TIMEOUT_MS: return CURLOPT_SERVER_RESPONSE_TIMEOUT_MS;
    //case val_CURLOPT_ECH: return CURLOPT_ECH;
    //case val_CURLOPT_TCP_KEEPCNT: return CURLOPT_TCP_KEEPCNT;
    case val_CURLOPT_LASTENTRY: return CURLOPT_LASTENTRY;
  }
}
int check_validity (const FUZZING_BYTES& fuzzing_bytes) {
  if (fuzzing_bytes.pool_init_values().buf_uint8_t_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._int_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().curloption_size() != PRIMITIVE_POOL_SIZE) { return 1; }

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

    api_block_call_input->set_in_idx__size_t_0(api_block_call_input->in_idx__size_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__size_t_0(api_block_call_input->out_idx__size_t_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_uint8_t_p_0(api_block_call_input->in_idx_buf_uint8_t_p_0() % BUFFER_POOL_SIZE);

    api_block_call_input->set_in_idx__int_0(api_block_call_input->in_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_1(api_block_call_input->in_idx__int_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_0(api_block_call_input->out_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_1(api_block_call_input->out_idx__int_1() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_fuzz_data_0(api_block_call_input->in_idx_fuzz_data_0() % OBJ_POOL_SIZE);
    api_block_call_input->set_out_idx_fuzz_data_0(api_block_call_input->out_idx_fuzz_data_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx_curloption_0(api_block_call_input->in_idx_curloption_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx_curloption_1(api_block_call_input->in_idx_curloption_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx_curloption_2(api_block_call_input->in_idx_curloption_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx_curloption_3(api_block_call_input->in_idx_curloption_3() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_curloption_0(api_block_call_input->out_idx_curloption_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_curloption_1(api_block_call_input->out_idx_curloption_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_curloption_2(api_block_call_input->out_idx_curloption_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_curloption_3(api_block_call_input->out_idx_curloption_3() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_tlv_0(api_block_call_input->in_idx_tlv_0() % OBJ_POOL_SIZE);
    api_block_call_input->set_out_idx_tlv_0(api_block_call_input->out_idx_tlv_0() % OBJ_POOL_SIZE);

  }
  return fuzzing_bytes;
}

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZING_BYTES& fuzzing_bytes) {
    update_max_api_seq_len();
    if (check_validity(fuzzing_bytes)) return;

    FUZZING_BYTES serialized_bytes = bound_bank_index(fuzzing_bytes);

    for (int i = 0; i < PRIMITIVE_POOL_SIZE; i++) {
      pool__int[i] = (int)serialized_bytes.pool_init_values()._int(i).val();

      pool_CURLoption[i] = to_CURLoption(serialized_bytes.pool_init_values().curloption(i));

    }


    std::string buf;
    for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
      buf = serialized_bytes.pool_init_values().buf_uint8_t_p(i).val();
      pool__size_t[i] = buf.length();
      buf += '\0';
      pool_buf_uint8_t_p[i] = (uint8_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_uint8_t_p[i], buf.data(), buf.size());

    }


  for (int i = 0; i < serialized_bytes.api_block_call_seq_size(); i++) {
    uint32_t api_block_call_num  = serialized_bytes.api_block_call_seq(i).api_block_call_num();
    const APIB_CALL_INPUT& api_block_call_input = serialized_bytes.api_block_call_seq(i).api_block_call_input();

    switch(api_block_call_num) {

      case 0:
        call_driver_36_to_53(api_block_call_input);
        break;

      case 1:
        call_driver_55_to_74(api_block_call_input);
        break;

      case 2:
        call_driver_80_to_97(api_block_call_input);
        break;

      case 3:
        call_driver_101(api_block_call_input);
        break;

      case 4:
        call_driver_80_to_82(api_block_call_input);
        break;

      case 5:
        call_driver_84_to_86(api_block_call_input);
        break;

      case 6:
        call_driver_88_to_90(api_block_call_input);
        break;

      case 7:
        call_driver_92_to_94(api_block_call_input);
        break;

      case 8:
        call_driver_55_to_66(api_block_call_input);
        break;

      case 9:
        call_driver_81(api_block_call_input);
        break;

      case 10:
        call_driver_85(api_block_call_input);
        break;

      case 11:
        call_driver_89(api_block_call_input);
        break;

      case 12:
        call_driver_93(api_block_call_input);
        break;
    };
  }
}

void call_driver_36_to_53 (const APIB_CALL_INPUT& ref) {
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t size = pool__size_t[ref.in_idx__size_t_0()];

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
    return; //goto EXIT_LABEL;
  }

  /* Try to initialize the fuzz data */
  fuzz_initialize_fuzz_data(&fuzz, data, size);

  pool__size_t[ref.out_idx__size_t_0()] = size;
  pool__int[ref.out_idx__int_0()] = rc ;
  pool__int[ref.out_idx__int_1()] = tlv_rc ;
  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz ;
  pool_TLV[ref.out_idx_tlv_0()] = tlv ;
}

void call_driver_55_to_74 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  TLV tlv = pool_TLV[ref.in_idx_tlv_0()];
  int rc = pool__int[ref.in_idx__int_0()];
  int tlv_rc = pool__int[ref.in_idx__int_1()];

  for(tlv_rc = fuzz_get_first_tlv(&fuzz, &tlv);
      tlv_rc == 0;
      tlv_rc = fuzz_get_next_tlv(&fuzz, &tlv)) {

    /* Have the TLV in hand. Parse the TLV. */
    rc = fuzz_parse_tlv(&fuzz, &tlv);

    if(rc != 0) {
      /* Failed to parse the TLV. Can't continue. */
      return; //goto EXIT_LABEL;
    }
  }

  if(tlv_rc != TLV_RC_NO_MORE_TLVS) {
    /* A TLV call failed. Can't continue. */
    return; //goto EXIT_LABEL;
  }

  /* Set up the standard easy options. */
  fuzz_set_easy_options(&fuzz);

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_TLV[ref.out_idx_tlv_0()] = tlv;
  pool__int[ref.out_idx__int_0()] = rc;
  pool__int[ref.out_idx__int_1()] = tlv_rc;
}

void call_driver_80_to_97 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  CURLoption _t0_ = pool_CURLoption[ref.in_idx_curloption_0()];
  CURLoption _t1_ = pool_CURLoption[ref.in_idx_curloption_1()];
  CURLoption _t2_ = pool_CURLoption[ref.in_idx_curloption_2()];
  CURLoption _t3_ = pool_CURLoption[ref.in_idx_curloption_3()];

  if(fuzz.header_list != NULL) {
    curl_easy_setopt(fuzz.easy, _t0_, fuzz.header_list);
  }

  if(fuzz.mail_recipients_list != NULL) {
    curl_easy_setopt(fuzz.easy, _t1_, fuzz.mail_recipients_list);
  }

  if(fuzz.mime != NULL) {
    curl_easy_setopt(fuzz.easy, _t2_, fuzz.mime);
  }

  if (fuzz.httppost != NULL) {
    curl_easy_setopt(fuzz.easy, _t3_, fuzz.httppost);
  }

  /* Run the transfer. */
  fuzz_handle_transfer(&fuzz);

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_CURLoption[ref.out_idx_curloption_0()] = _t0_;
  pool_CURLoption[ref.out_idx_curloption_1()] = _t1_;
  pool_CURLoption[ref.out_idx_curloption_2()] = _t2_;
  pool_CURLoption[ref.out_idx_curloption_3()] = _t3_;
}

void call_driver_101 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];

  fuzz_terminate_fuzz_data(&fuzz);

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
}

void call_driver_80_to_82 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  CURLoption _t0_ = pool_CURLoption[ref.in_idx_curloption_0()];

  if(fuzz.header_list != NULL) {
    curl_easy_setopt(fuzz.easy, _t0_, fuzz.header_list);
  }

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_CURLoption[ref.out_idx_curloption_0()] = _t0_;
}

void call_driver_84_to_86 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  CURLoption _t0_ = pool_CURLoption[ref.in_idx_curloption_0()];

  if(fuzz.mail_recipients_list != NULL) {
    curl_easy_setopt(fuzz.easy, _t0_, fuzz.mail_recipients_list);
  }

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_CURLoption[ref.out_idx_curloption_0()] = _t0_;
}

void call_driver_88_to_90 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  CURLoption _t0_ = pool_CURLoption[ref.in_idx_curloption_0()];

  if(fuzz.mime != NULL) {
    curl_easy_setopt(fuzz.easy, _t0_, fuzz.mime);
  }

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_CURLoption[ref.out_idx_curloption_0()] = _t0_;
}

void call_driver_92_to_94 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];

  if (fuzz.httppost != NULL) {
    curl_easy_setopt(fuzz.easy, CURLOPT_HTTPPOST, fuzz.httppost);
  }

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
}

void call_driver_55_to_66 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  TLV tlv = pool_TLV[ref.in_idx_tlv_0()];
  int rc = pool__int[ref.in_idx__int_0()];
  int tlv_rc = pool__int[ref.in_idx__int_1()];

  for(tlv_rc = fuzz_get_first_tlv(&fuzz, &tlv);
      tlv_rc == 0;
      tlv_rc = fuzz_get_next_tlv(&fuzz, &tlv)) {

    /* Have the TLV in hand. Parse the TLV. */
    rc = fuzz_parse_tlv(&fuzz, &tlv);

    if(rc != 0) {
      /* Failed to parse the TLV. Can't continue. */
      return; //goto EXIT_LABEL;
    }
  }

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_TLV[ref.out_idx_tlv_0()] = tlv;
  pool__int[ref.out_idx__int_0()] = rc;
  pool__int[ref.out_idx__int_1()] = tlv_rc;
}

void call_driver_81 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  CURLoption _t0_ = pool_CURLoption[ref.in_idx_curloption_0()];

    curl_easy_setopt(fuzz.easy, _t0_, fuzz.header_list);

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_CURLoption[ref.out_idx_curloption_0()] = _t0_;
}

void call_driver_85 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  CURLoption _t0_ = pool_CURLoption[ref.in_idx_curloption_0()];

    curl_easy_setopt(fuzz.easy, _t0_, fuzz.mail_recipients_list);

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_CURLoption[ref.out_idx_curloption_0()] = _t0_;
}

void call_driver_89 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  CURLoption _t0_ = pool_CURLoption[ref.in_idx_curloption_0()];

    curl_easy_setopt(fuzz.easy, _t0_, fuzz.mime);

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_CURLoption[ref.out_idx_curloption_0()] = _t0_;
}

void call_driver_93 (const APIB_CALL_INPUT& ref) {
  FUZZ_DATA fuzz = pool_FUZZ_DATA[ref.in_idx_fuzz_data_0()];
  CURLoption _t0_ = pool_CURLoption[ref.in_idx_curloption_0()];

    curl_easy_setopt(fuzz.easy, _t0_, fuzz.httppost);

  pool_FUZZ_DATA[ref.out_idx_fuzz_data_0()] = fuzz;
  pool_CURLoption[ref.out_idx_curloption_0()] = _t0_;
}
