#pragma once




#define GP_VERSION 0x0001




// Settings
#ifndef GP_TEAM_COUNT_MAX
# define GP_TEAM_COUNT_MAX 64
#endif

#ifndef GP_PLAYER_COUNT_MAX
# define GP_PLAYER_COUNT_MAX 256
#endif

#ifndef GP_RULE_COUNT_MAX
# define GP_RULE_COUNT_MAX 1024
#endif

#ifndef GP_LIMIT_COUNT_MAX
# define GP_LIMIT_COUNT_MAX 8
#endif


#define GP_REQUEST_TYPE_PING                  0x00
#define GP_REQUEST_TYPE_UPLINK                0x01
#define GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY  0x02
#define GP_REQUEST_TYPE_TEST                  0xFE
#define GP_REQUEST_TYPE_ERROR                 0xFF

#define GP_SERVER_FLAG_TYPE_UNKNOWN   0x0
#define GP_SERVER_FLAG_TYPE_LISTEN    0x1
#define GP_SERVER_FLAG_TYPE_DEDICATED 0x2


#define GP_SERVER_FLAG_OS_UNKNOWN     0x0
#define GP_SERVER_FLAG_OS_WINDOWS     0x1
#define GP_SERVER_FLAG_OS_LINUX       0x2
#define GP_SERVER_FLAG_OS_MAC         0x3

#define GP_MAP_INFO_TYPE_GP_V1  0x00
#define GP_MAP_INFO_TYPE_FILE   0x01    // cfield 01-03 is used: path, size, digest(md5)

#define GP_PLAYER_STATE_DEAD    0x0
#define GP_PLAYER_STATE_ALIVE   0x1

#define GP_PLAYER_TEAM_STATE_NOT_ASSIGNED   0x0
#define GP_PLAYER_TEAM_STATE_ASSIGNED       0x1
#define GP_PLAYER_TEAM_STATE_SPECTATOR      0x2

#define GP_ERROR_UNKNOWN                      0x0000
#define GP_ERROR_QUERY_INVALID_HEADER         0x0001
#define GP_ERROR_QUERY_INVALID_TYPE           0x0002  // type in header is wrong
#define GP_ERROR_QUERY_INVALID_RECIEVER_TYPE  0x0003  // type in


typedef quint32 u_int32_t;
typedef quint16 u_int16_t;
typedef quint8  u_int8_t;


namespace gp {

  #include <cstdlib>

  // Header perfix ( 64 bits - 8 bytes )
  struct gp_header_prefix__ {
    u_int32_t   reserved;
    u_int32_t   id;

    gp_header_prefix__() : reserved(0xFFFFFFFF), id(0x04000609)  {}
  };

  typedef gp_header_prefix__ gp_header_prefix;




  // Header flags (8 bit - 1 byte)
  typedef struct {

    bool      answer    : 1;
    u_int8_t  _reserved : 7;
  } gp_header_flags;

  // Header (64 bit - 8 bytes)
  typedef struct {
    gp_header_prefix  prefix;
    u_int16_t         size;         // header_size in bytes
    u_int8_t          type;         // Request type
    gp_header_flags   flags;        // Header flags
    u_int32_t         request_id;   // Request ID
  } gp_header;



  // Server flags (8 bit - 1 byte)
  typedef struct {
    u_int8_t    type              : 2;
    u_int8_t    password          : 1;
    u_int8_t    operating_system  : 2;
    u_int8_t    _reserved         : 3;
  } gp_server_flags;

  // Map Fields( 8 bit - 1 byte )
  typedef struct {
    u_int8_t    name      : 1;
    u_int8_t    version   : 1;
    u_int8_t    url       : 1;
    u_int8_t    author    : 1;
    u_int8_t    cfield01  : 1;
    u_int8_t    cfield02  : 1;
    u_int8_t    cfield03  : 1;
    u_int8_t    cfield04  : 1;
  } gp_map_info_t;



  // Map Info()
  typedef struct {

    u_int8_t        type      : 2;
    u_int8_t        _reserved : 6;

    gp_map_info_t   map_fields;

    char            name[64];
    char            version[32];
    char            url[256];
    char            author[32];
    char            cfield01[32];
    char            cfield02[32];
    char            cfield03[32];
    char            cfield04[32];
  } gp_map_info;



  // Server Info flags ( 16 bits - 2 bytes )
  typedef struct {
    u_int8_t          game_name       : 1;
    u_int8_t          server_flags    : 1;
    u_int8_t          host_name       : 1;
    u_int8_t          connect_port    : 1;
    u_int8_t          game_type       : 1;
    u_int8_t          game_state      : 1;
    u_int8_t          _reserved1      : 2;

    u_int8_t          max_slots       : 1;
    u_int8_t          reserved_slots  : 1;
    u_int8_t          player_count    : 1;
    u_int8_t          bot_count       : 1;
    u_int8_t          _reserved2      : 4;

  } gp_server_info_t;


  // Server Info ()
  typedef struct {
    char              game_name[64];
    gp_server_flags   flags;
    char              host_name[64];
    u_int16_t         connect_port;

    u_int8_t          game_type;
    u_int8_t          game_state;

    u_int32_t         player_count;
    u_int32_t         max_slots;
    u_int32_t         bot_count;
    u_int32_t         reserved_slots;
  } gp_server_info;


  // Team info fields ( 8 bits - 1 byte )
  typedef struct {
    u_int8_t  name          : 1;
    u_int8_t  id            : 1;
    u_int8_t  score         : 1;
    u_int8_t  avg_ping      : 1;
    u_int8_t  avg_loss      : 1;
    u_int8_t  member_count  : 1;
    u_int8_t  _reserved     : 2;
  } gp_team_info_t;

  // Team info ( 608 bits - bytes 76 )
  typedef struct {
    char        name[64];
    u_int32_t     id;

    u_int32_t   score;

    u_int16_t   avg_ping;
    u_int16_t   avg_loss;

    u_int32_t   member_count;
  } gp_team_info;

  // Team list ( varsize )
  typedef struct {
    u_int32_t         count;
    gp_team_info_t    info_fiels;
    gp_team_info      list[GP_TEAM_COUNT_MAX];

  } gp_team_list;



  // Player flags ( 8 bits - 1 byte )
  typedef struct {
    u_int8_t    npc         : 1;  //
    u_int8_t    state       : 2;  // dead/alive (state)
    u_int8_t    team_state  : 2;  // assigned/not assigned/spectator
    u_int8_t    _reserved   : 3;
  } gp_player_flags;



  // Player info fields ( 24 bits - 3 bytes )
  typedef struct {
    u_int8_t    name        : 1;
    u_int8_t    flags       : 1;
    u_int8_t    id          : 1;
    u_int8_t    slot        : 1;
    u_int8_t    team_id     : 1;
    u_int8_t    race        : 1;
    u_int8_t    class_      : 1;
    u_int8_t    _reserved1  : 1;

    u_int8_t    score       : 1;
    u_int8_t    frags       : 1;
    u_int8_t    kills       : 1;
    u_int8_t    deaths      : 1;
    u_int8_t    suicides    : 1;
    u_int8_t    team_kills  : 1;
    u_int8_t    _reserved2  : 2;

    u_int8_t    ping        : 1;
    u_int8_t    loss        : 1;
    u_int8_t    model       : 1;
    u_int8_t    time        : 1;
    u_int8_t    _reserved3  : 4;

  } gp_player_info_t;

  // Player info ( bits - bytes )
  typedef struct {

    char              name[64];
    gp_player_flags   flags;

    u_int32_t         id;
    u_int32_t         slot;

    u_int32_t         team_id;
    char              race[32];
    char              class_[32];

    u_int32_t         score;
    u_int32_t         frags;
    u_int32_t         kills;
    u_int32_t         deaths;
    u_int32_t         suicides;
    u_int32_t         team_kills;

    u_int16_t         ping;
    u_int16_t         loss;

    char              model[32];
    u_int16_t         time;
  } gp_player_info;

  // Player list
  typedef struct {
    u_int32_t         count;
    gp_player_info_t  info_fields;
    gp_player_info    list[GP_PLAYER_COUNT_MAX];
  } gp_player_list;


  // Rule ( 2560 bits - 320 bytes )
  typedef struct {
    char    key[64];
    char    value[256];
  } gp_rule;

  // Rule list ( varsize )
  typedef struct {
    u_int32_t   count;
    gp_rule     rules[GP_RULE_COUNT_MAX];
  } gp_rule_list;


  // Limit flags( 8 bits - 1 byte )
  typedef struct {
    u_int8_t    limit_left : 1;
    u_int8_t    type       : 4;
    u_int8_t    _reserved  : 3;
  } gp_limit_flags;

  // Limit (
  typedef struct {
    gp_limit_flags  flags;
    u_int32_t       limit;
    u_int32_t       limit_left;
  } gp_limit;

  // Limit list ( varsize )
  typedef struct {
    u_int32_t       count;
    gp_limit        limits[GP_LIMIT_COUNT_MAX];
  } gp_limit_list;


  // Default query request flags
  typedef struct {
    u_int8_t          server_info : 1;
    u_int8_t          map_info    : 1;
    u_int8_t          team_list   : 1;
    u_int8_t          player_list : 1;
    u_int8_t          rule_list   : 1;
    u_int8_t          limit_list  : 1;
    u_int8_t          _reserved   : 2;
  } gp_default_server_query_flags_t;


  // Default server query ( bits - bytes )
  typedef struct {
    gp_default_server_query_flags_t   request_flags;
    gp_server_info_t                  server_fields;
    gp_map_info_t                     map_fields;
    gp_team_info_t                    team_fields;
    gp_player_info_t                  player_fields;
  } gp_default_server_query;


  // Default server answer ( bits - bytes )
  typedef struct {
    gp_server_info    server_info;
    gp_map_info       map_info;
    gp_team_list      team_list;
    gp_player_list    player_list;
    gp_rule_list      rule_list;
    gp_limit_list     limit_list;
  } gp_default_server_query_answer;

} // END namespace gp
