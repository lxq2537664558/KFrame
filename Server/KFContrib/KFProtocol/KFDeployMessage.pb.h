// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: KFDeployMessage.proto

#ifndef PROTOBUF_KFDeployMessage_2eproto__INCLUDED
#define PROTOBUF_KFDeployMessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace KFMsg {

// Internal implementation detail -- do not call these.
void LIBPROTOC_EXPORT protobuf_AddDesc_KFDeployMessage_2eproto();
void protobuf_AssignDesc_KFDeployMessage_2eproto();
void protobuf_ShutdownFile_KFDeployMessage_2eproto();

class S2SRegisterAgentToServerReq;
class S2SUpdateServerStatusReq;

enum DeployProtocol {
  S2S_REGISTER_AGENT_TO_SERVER_REQ = 10301,
  S2S_UPDATE_SERVER_STATUS_REQ = 10302
};
LIBPROTOC_EXPORT bool DeployProtocol_IsValid(int value);
const DeployProtocol DeployProtocol_MIN = S2S_REGISTER_AGENT_TO_SERVER_REQ;
const DeployProtocol DeployProtocol_MAX = S2S_UPDATE_SERVER_STATUS_REQ;
const int DeployProtocol_ARRAYSIZE = DeployProtocol_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* DeployProtocol_descriptor();
inline const ::std::string& DeployProtocol_Name(DeployProtocol value) {
  return ::google::protobuf::internal::NameOfEnum(
    DeployProtocol_descriptor(), value);
}
inline bool DeployProtocol_Parse(
    const ::std::string& name, DeployProtocol* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DeployProtocol>(
    DeployProtocol_descriptor(), name, value);
}
// ===================================================================

class LIBPROTOC_EXPORT S2SRegisterAgentToServerReq : public ::google::protobuf::Message {
 public:
  S2SRegisterAgentToServerReq();
  virtual ~S2SRegisterAgentToServerReq();

  S2SRegisterAgentToServerReq(const S2SRegisterAgentToServerReq& from);

  inline S2SRegisterAgentToServerReq& operator=(const S2SRegisterAgentToServerReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const S2SRegisterAgentToServerReq& default_instance();

  void Swap(S2SRegisterAgentToServerReq* other);

  // implements Message ----------------------------------------------

  S2SRegisterAgentToServerReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const S2SRegisterAgentToServerReq& from);
  void MergeFrom(const S2SRegisterAgentToServerReq& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 agentid = 1;
  inline bool has_agentid() const;
  inline void clear_agentid();
  static const int kAgentidFieldNumber = 1;
  inline ::google::protobuf::uint32 agentid() const;
  inline void set_agentid(::google::protobuf::uint32 value);

  // required string localip = 2;
  inline bool has_localip() const;
  inline void clear_localip();
  static const int kLocalipFieldNumber = 2;
  inline const ::std::string& localip() const;
  inline void set_localip(const ::std::string& value);
  inline void set_localip(const char* value);
  inline void set_localip(const char* value, size_t size);
  inline ::std::string* mutable_localip();
  inline ::std::string* release_localip();
  inline void set_allocated_localip(::std::string* localip);

  // required string interanetip = 3;
  inline bool has_interanetip() const;
  inline void clear_interanetip();
  static const int kInteranetipFieldNumber = 3;
  inline const ::std::string& interanetip() const;
  inline void set_interanetip(const ::std::string& value);
  inline void set_interanetip(const char* value);
  inline void set_interanetip(const char* value, size_t size);
  inline ::std::string* mutable_interanetip();
  inline ::std::string* release_interanetip();
  inline void set_allocated_interanetip(::std::string* interanetip);

  // @@protoc_insertion_point(class_scope:KFMsg.S2SRegisterAgentToServerReq)
 private:
  inline void set_has_agentid();
  inline void clear_has_agentid();
  inline void set_has_localip();
  inline void clear_has_localip();
  inline void set_has_interanetip();
  inline void clear_has_interanetip();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* localip_;
  ::std::string* interanetip_;
  ::google::protobuf::uint32 agentid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void LIBPROTOC_EXPORT protobuf_AddDesc_KFDeployMessage_2eproto();
  friend void protobuf_AssignDesc_KFDeployMessage_2eproto();
  friend void protobuf_ShutdownFile_KFDeployMessage_2eproto();

  void InitAsDefaultInstance();
  static S2SRegisterAgentToServerReq* default_instance_;
};
// -------------------------------------------------------------------

class LIBPROTOC_EXPORT S2SUpdateServerStatusReq : public ::google::protobuf::Message {
 public:
  S2SUpdateServerStatusReq();
  virtual ~S2SUpdateServerStatusReq();

  S2SUpdateServerStatusReq(const S2SUpdateServerStatusReq& from);

  inline S2SUpdateServerStatusReq& operator=(const S2SUpdateServerStatusReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const S2SUpdateServerStatusReq& default_instance();

  void Swap(S2SUpdateServerStatusReq* other);

  // implements Message ----------------------------------------------

  S2SUpdateServerStatusReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const S2SUpdateServerStatusReq& from);
  void MergeFrom(const S2SUpdateServerStatusReq& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 agentid = 1;
  inline bool has_agentid() const;
  inline void clear_agentid();
  static const int kAgentidFieldNumber = 1;
  inline ::google::protobuf::uint32 agentid() const;
  inline void set_agentid(::google::protobuf::uint32 value);

  // required uint32 appid = 2;
  inline bool has_appid() const;
  inline void clear_appid();
  static const int kAppidFieldNumber = 2;
  inline ::google::protobuf::uint32 appid() const;
  inline void set_appid(::google::protobuf::uint32 value);

  // required string appname = 3;
  inline bool has_appname() const;
  inline void clear_appname();
  static const int kAppnameFieldNumber = 3;
  inline const ::std::string& appname() const;
  inline void set_appname(const ::std::string& value);
  inline void set_appname(const char* value);
  inline void set_appname(const char* value, size_t size);
  inline ::std::string* mutable_appname();
  inline ::std::string* release_appname();
  inline void set_allocated_appname(::std::string* appname);

  // required string apptype = 4;
  inline bool has_apptype() const;
  inline void clear_apptype();
  static const int kApptypeFieldNumber = 4;
  inline const ::std::string& apptype() const;
  inline void set_apptype(const ::std::string& value);
  inline void set_apptype(const char* value);
  inline void set_apptype(const char* value, size_t size);
  inline ::std::string* mutable_apptype();
  inline ::std::string* release_apptype();
  inline void set_allocated_apptype(::std::string* apptype);

  // required uint32 process = 5;
  inline bool has_process() const;
  inline void clear_process();
  static const int kProcessFieldNumber = 5;
  inline ::google::protobuf::uint32 process() const;
  inline void set_process(::google::protobuf::uint32 value);

  // required uint64 startuptime = 6;
  inline bool has_startuptime() const;
  inline void clear_startuptime();
  static const int kStartuptimeFieldNumber = 6;
  inline ::google::protobuf::uint64 startuptime() const;
  inline void set_startuptime(::google::protobuf::uint64 value);

  // required uint32 isshutdown = 7;
  inline bool has_isshutdown() const;
  inline void clear_isshutdown();
  static const int kIsshutdownFieldNumber = 7;
  inline ::google::protobuf::uint32 isshutdown() const;
  inline void set_isshutdown(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:KFMsg.S2SUpdateServerStatusReq)
 private:
  inline void set_has_agentid();
  inline void clear_has_agentid();
  inline void set_has_appid();
  inline void clear_has_appid();
  inline void set_has_appname();
  inline void clear_has_appname();
  inline void set_has_apptype();
  inline void clear_has_apptype();
  inline void set_has_process();
  inline void clear_has_process();
  inline void set_has_startuptime();
  inline void clear_has_startuptime();
  inline void set_has_isshutdown();
  inline void clear_has_isshutdown();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 agentid_;
  ::google::protobuf::uint32 appid_;
  ::std::string* appname_;
  ::std::string* apptype_;
  ::google::protobuf::uint64 startuptime_;
  ::google::protobuf::uint32 process_;
  ::google::protobuf::uint32 isshutdown_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  friend void LIBPROTOC_EXPORT protobuf_AddDesc_KFDeployMessage_2eproto();
  friend void protobuf_AssignDesc_KFDeployMessage_2eproto();
  friend void protobuf_ShutdownFile_KFDeployMessage_2eproto();

  void InitAsDefaultInstance();
  static S2SUpdateServerStatusReq* default_instance_;
};
// ===================================================================


// ===================================================================

// S2SRegisterAgentToServerReq

// required uint32 agentid = 1;
inline bool S2SRegisterAgentToServerReq::has_agentid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void S2SRegisterAgentToServerReq::set_has_agentid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void S2SRegisterAgentToServerReq::clear_has_agentid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void S2SRegisterAgentToServerReq::clear_agentid() {
  agentid_ = 0u;
  clear_has_agentid();
}
inline ::google::protobuf::uint32 S2SRegisterAgentToServerReq::agentid() const {
  return agentid_;
}
inline void S2SRegisterAgentToServerReq::set_agentid(::google::protobuf::uint32 value) {
  set_has_agentid();
  agentid_ = value;
}

// required string localip = 2;
inline bool S2SRegisterAgentToServerReq::has_localip() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void S2SRegisterAgentToServerReq::set_has_localip() {
  _has_bits_[0] |= 0x00000002u;
}
inline void S2SRegisterAgentToServerReq::clear_has_localip() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void S2SRegisterAgentToServerReq::clear_localip() {
  if (localip_ != &::google::protobuf::internal::kEmptyString) {
    localip_->clear();
  }
  clear_has_localip();
}
inline const ::std::string& S2SRegisterAgentToServerReq::localip() const {
  return *localip_;
}
inline void S2SRegisterAgentToServerReq::set_localip(const ::std::string& value) {
  set_has_localip();
  if (localip_ == &::google::protobuf::internal::kEmptyString) {
    localip_ = new ::std::string;
  }
  localip_->assign(value);
}
inline void S2SRegisterAgentToServerReq::set_localip(const char* value) {
  set_has_localip();
  if (localip_ == &::google::protobuf::internal::kEmptyString) {
    localip_ = new ::std::string;
  }
  localip_->assign(value);
}
inline void S2SRegisterAgentToServerReq::set_localip(const char* value, size_t size) {
  set_has_localip();
  if (localip_ == &::google::protobuf::internal::kEmptyString) {
    localip_ = new ::std::string;
  }
  localip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* S2SRegisterAgentToServerReq::mutable_localip() {
  set_has_localip();
  if (localip_ == &::google::protobuf::internal::kEmptyString) {
    localip_ = new ::std::string;
  }
  return localip_;
}
inline ::std::string* S2SRegisterAgentToServerReq::release_localip() {
  clear_has_localip();
  if (localip_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = localip_;
    localip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void S2SRegisterAgentToServerReq::set_allocated_localip(::std::string* localip) {
  if (localip_ != &::google::protobuf::internal::kEmptyString) {
    delete localip_;
  }
  if (localip) {
    set_has_localip();
    localip_ = localip;
  } else {
    clear_has_localip();
    localip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string interanetip = 3;
inline bool S2SRegisterAgentToServerReq::has_interanetip() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void S2SRegisterAgentToServerReq::set_has_interanetip() {
  _has_bits_[0] |= 0x00000004u;
}
inline void S2SRegisterAgentToServerReq::clear_has_interanetip() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void S2SRegisterAgentToServerReq::clear_interanetip() {
  if (interanetip_ != &::google::protobuf::internal::kEmptyString) {
    interanetip_->clear();
  }
  clear_has_interanetip();
}
inline const ::std::string& S2SRegisterAgentToServerReq::interanetip() const {
  return *interanetip_;
}
inline void S2SRegisterAgentToServerReq::set_interanetip(const ::std::string& value) {
  set_has_interanetip();
  if (interanetip_ == &::google::protobuf::internal::kEmptyString) {
    interanetip_ = new ::std::string;
  }
  interanetip_->assign(value);
}
inline void S2SRegisterAgentToServerReq::set_interanetip(const char* value) {
  set_has_interanetip();
  if (interanetip_ == &::google::protobuf::internal::kEmptyString) {
    interanetip_ = new ::std::string;
  }
  interanetip_->assign(value);
}
inline void S2SRegisterAgentToServerReq::set_interanetip(const char* value, size_t size) {
  set_has_interanetip();
  if (interanetip_ == &::google::protobuf::internal::kEmptyString) {
    interanetip_ = new ::std::string;
  }
  interanetip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* S2SRegisterAgentToServerReq::mutable_interanetip() {
  set_has_interanetip();
  if (interanetip_ == &::google::protobuf::internal::kEmptyString) {
    interanetip_ = new ::std::string;
  }
  return interanetip_;
}
inline ::std::string* S2SRegisterAgentToServerReq::release_interanetip() {
  clear_has_interanetip();
  if (interanetip_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = interanetip_;
    interanetip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void S2SRegisterAgentToServerReq::set_allocated_interanetip(::std::string* interanetip) {
  if (interanetip_ != &::google::protobuf::internal::kEmptyString) {
    delete interanetip_;
  }
  if (interanetip) {
    set_has_interanetip();
    interanetip_ = interanetip;
  } else {
    clear_has_interanetip();
    interanetip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// S2SUpdateServerStatusReq

// required uint32 agentid = 1;
inline bool S2SUpdateServerStatusReq::has_agentid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void S2SUpdateServerStatusReq::set_has_agentid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void S2SUpdateServerStatusReq::clear_has_agentid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void S2SUpdateServerStatusReq::clear_agentid() {
  agentid_ = 0u;
  clear_has_agentid();
}
inline ::google::protobuf::uint32 S2SUpdateServerStatusReq::agentid() const {
  return agentid_;
}
inline void S2SUpdateServerStatusReq::set_agentid(::google::protobuf::uint32 value) {
  set_has_agentid();
  agentid_ = value;
}

// required uint32 appid = 2;
inline bool S2SUpdateServerStatusReq::has_appid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void S2SUpdateServerStatusReq::set_has_appid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void S2SUpdateServerStatusReq::clear_has_appid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void S2SUpdateServerStatusReq::clear_appid() {
  appid_ = 0u;
  clear_has_appid();
}
inline ::google::protobuf::uint32 S2SUpdateServerStatusReq::appid() const {
  return appid_;
}
inline void S2SUpdateServerStatusReq::set_appid(::google::protobuf::uint32 value) {
  set_has_appid();
  appid_ = value;
}

// required string appname = 3;
inline bool S2SUpdateServerStatusReq::has_appname() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void S2SUpdateServerStatusReq::set_has_appname() {
  _has_bits_[0] |= 0x00000004u;
}
inline void S2SUpdateServerStatusReq::clear_has_appname() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void S2SUpdateServerStatusReq::clear_appname() {
  if (appname_ != &::google::protobuf::internal::kEmptyString) {
    appname_->clear();
  }
  clear_has_appname();
}
inline const ::std::string& S2SUpdateServerStatusReq::appname() const {
  return *appname_;
}
inline void S2SUpdateServerStatusReq::set_appname(const ::std::string& value) {
  set_has_appname();
  if (appname_ == &::google::protobuf::internal::kEmptyString) {
    appname_ = new ::std::string;
  }
  appname_->assign(value);
}
inline void S2SUpdateServerStatusReq::set_appname(const char* value) {
  set_has_appname();
  if (appname_ == &::google::protobuf::internal::kEmptyString) {
    appname_ = new ::std::string;
  }
  appname_->assign(value);
}
inline void S2SUpdateServerStatusReq::set_appname(const char* value, size_t size) {
  set_has_appname();
  if (appname_ == &::google::protobuf::internal::kEmptyString) {
    appname_ = new ::std::string;
  }
  appname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* S2SUpdateServerStatusReq::mutable_appname() {
  set_has_appname();
  if (appname_ == &::google::protobuf::internal::kEmptyString) {
    appname_ = new ::std::string;
  }
  return appname_;
}
inline ::std::string* S2SUpdateServerStatusReq::release_appname() {
  clear_has_appname();
  if (appname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = appname_;
    appname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void S2SUpdateServerStatusReq::set_allocated_appname(::std::string* appname) {
  if (appname_ != &::google::protobuf::internal::kEmptyString) {
    delete appname_;
  }
  if (appname) {
    set_has_appname();
    appname_ = appname;
  } else {
    clear_has_appname();
    appname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string apptype = 4;
inline bool S2SUpdateServerStatusReq::has_apptype() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void S2SUpdateServerStatusReq::set_has_apptype() {
  _has_bits_[0] |= 0x00000008u;
}
inline void S2SUpdateServerStatusReq::clear_has_apptype() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void S2SUpdateServerStatusReq::clear_apptype() {
  if (apptype_ != &::google::protobuf::internal::kEmptyString) {
    apptype_->clear();
  }
  clear_has_apptype();
}
inline const ::std::string& S2SUpdateServerStatusReq::apptype() const {
  return *apptype_;
}
inline void S2SUpdateServerStatusReq::set_apptype(const ::std::string& value) {
  set_has_apptype();
  if (apptype_ == &::google::protobuf::internal::kEmptyString) {
    apptype_ = new ::std::string;
  }
  apptype_->assign(value);
}
inline void S2SUpdateServerStatusReq::set_apptype(const char* value) {
  set_has_apptype();
  if (apptype_ == &::google::protobuf::internal::kEmptyString) {
    apptype_ = new ::std::string;
  }
  apptype_->assign(value);
}
inline void S2SUpdateServerStatusReq::set_apptype(const char* value, size_t size) {
  set_has_apptype();
  if (apptype_ == &::google::protobuf::internal::kEmptyString) {
    apptype_ = new ::std::string;
  }
  apptype_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* S2SUpdateServerStatusReq::mutable_apptype() {
  set_has_apptype();
  if (apptype_ == &::google::protobuf::internal::kEmptyString) {
    apptype_ = new ::std::string;
  }
  return apptype_;
}
inline ::std::string* S2SUpdateServerStatusReq::release_apptype() {
  clear_has_apptype();
  if (apptype_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = apptype_;
    apptype_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void S2SUpdateServerStatusReq::set_allocated_apptype(::std::string* apptype) {
  if (apptype_ != &::google::protobuf::internal::kEmptyString) {
    delete apptype_;
  }
  if (apptype) {
    set_has_apptype();
    apptype_ = apptype;
  } else {
    clear_has_apptype();
    apptype_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required uint32 process = 5;
inline bool S2SUpdateServerStatusReq::has_process() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void S2SUpdateServerStatusReq::set_has_process() {
  _has_bits_[0] |= 0x00000010u;
}
inline void S2SUpdateServerStatusReq::clear_has_process() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void S2SUpdateServerStatusReq::clear_process() {
  process_ = 0u;
  clear_has_process();
}
inline ::google::protobuf::uint32 S2SUpdateServerStatusReq::process() const {
  return process_;
}
inline void S2SUpdateServerStatusReq::set_process(::google::protobuf::uint32 value) {
  set_has_process();
  process_ = value;
}

// required uint64 startuptime = 6;
inline bool S2SUpdateServerStatusReq::has_startuptime() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void S2SUpdateServerStatusReq::set_has_startuptime() {
  _has_bits_[0] |= 0x00000020u;
}
inline void S2SUpdateServerStatusReq::clear_has_startuptime() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void S2SUpdateServerStatusReq::clear_startuptime() {
  startuptime_ = GOOGLE_ULONGLONG(0);
  clear_has_startuptime();
}
inline ::google::protobuf::uint64 S2SUpdateServerStatusReq::startuptime() const {
  return startuptime_;
}
inline void S2SUpdateServerStatusReq::set_startuptime(::google::protobuf::uint64 value) {
  set_has_startuptime();
  startuptime_ = value;
}

// required uint32 isshutdown = 7;
inline bool S2SUpdateServerStatusReq::has_isshutdown() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void S2SUpdateServerStatusReq::set_has_isshutdown() {
  _has_bits_[0] |= 0x00000040u;
}
inline void S2SUpdateServerStatusReq::clear_has_isshutdown() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void S2SUpdateServerStatusReq::clear_isshutdown() {
  isshutdown_ = 0u;
  clear_has_isshutdown();
}
inline ::google::protobuf::uint32 S2SUpdateServerStatusReq::isshutdown() const {
  return isshutdown_;
}
inline void S2SUpdateServerStatusReq::set_isshutdown(::google::protobuf::uint32 value) {
  set_has_isshutdown();
  isshutdown_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KFMsg

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::DeployProtocol>() {
  return ::KFMsg::DeployProtocol_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_KFDeployMessage_2eproto__INCLUDED
