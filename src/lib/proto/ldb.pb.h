// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ldb.proto

#ifndef PROTOBUF_ldb_2eproto__INCLUDED
#define PROTOBUF_ldb_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace login_dbmgr {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ldb_2eproto();
void protobuf_AssignDesc_ldb_2eproto();
void protobuf_ShutdownFile_ldb_2eproto();

class AccountLogin;
class AccountLoginQueryResult;

// ===================================================================

class AccountLogin : public ::google::protobuf::Message {
 public:
  AccountLogin();
  virtual ~AccountLogin();

  AccountLogin(const AccountLogin& from);

  inline AccountLogin& operator=(const AccountLogin& from) {
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
  static const AccountLogin& default_instance();

  void Swap(AccountLogin* other);

  // implements Message ----------------------------------------------

  AccountLogin* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AccountLogin& from);
  void MergeFrom(const AccountLogin& from);
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

  // optional string accountName = 1;
  inline bool has_accountname() const;
  inline void clear_accountname();
  static const int kAccountNameFieldNumber = 1;
  inline const ::std::string& accountname() const;
  inline void set_accountname(const ::std::string& value);
  inline void set_accountname(const char* value);
  inline void set_accountname(const char* value, size_t size);
  inline ::std::string* mutable_accountname();
  inline ::std::string* release_accountname();
  inline void set_allocated_accountname(::std::string* accountname);

  // optional string password = 2;
  inline bool has_password() const;
  inline void clear_password();
  static const int kPasswordFieldNumber = 2;
  inline const ::std::string& password() const;
  inline void set_password(const ::std::string& value);
  inline void set_password(const char* value);
  inline void set_password(const char* value, size_t size);
  inline ::std::string* mutable_password();
  inline ::std::string* release_password();
  inline void set_allocated_password(::std::string* password);

  // optional string extraData = 3;
  inline bool has_extradata() const;
  inline void clear_extradata();
  static const int kExtraDataFieldNumber = 3;
  inline const ::std::string& extradata() const;
  inline void set_extradata(const ::std::string& value);
  inline void set_extradata(const char* value);
  inline void set_extradata(const char* value, size_t size);
  inline ::std::string* mutable_extradata();
  inline ::std::string* release_extradata();
  inline void set_allocated_extradata(::std::string* extradata);

  // @@protoc_insertion_point(class_scope:login_dbmgr.AccountLogin)
 private:
  inline void set_has_accountname();
  inline void clear_has_accountname();
  inline void set_has_password();
  inline void clear_has_password();
  inline void set_has_extradata();
  inline void clear_has_extradata();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* accountname_;
  ::std::string* password_;
  ::std::string* extradata_;
  friend void  protobuf_AddDesc_ldb_2eproto();
  friend void protobuf_AssignDesc_ldb_2eproto();
  friend void protobuf_ShutdownFile_ldb_2eproto();

  void InitAsDefaultInstance();
  static AccountLogin* default_instance_;
};
// -------------------------------------------------------------------

class AccountLoginQueryResult : public ::google::protobuf::Message {
 public:
  AccountLoginQueryResult();
  virtual ~AccountLoginQueryResult();

  AccountLoginQueryResult(const AccountLoginQueryResult& from);

  inline AccountLoginQueryResult& operator=(const AccountLoginQueryResult& from) {
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
  static const AccountLoginQueryResult& default_instance();

  void Swap(AccountLoginQueryResult* other);

  // implements Message ----------------------------------------------

  AccountLoginQueryResult* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AccountLoginQueryResult& from);
  void MergeFrom(const AccountLoginQueryResult& from);
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

  // optional uint32 retcode = 1;
  inline bool has_retcode() const;
  inline void clear_retcode();
  static const int kRetcodeFieldNumber = 1;
  inline ::google::protobuf::uint32 retcode() const;
  inline void set_retcode(::google::protobuf::uint32 value);

  // optional string loginName = 2;
  inline bool has_loginname() const;
  inline void clear_loginname();
  static const int kLoginNameFieldNumber = 2;
  inline const ::std::string& loginname() const;
  inline void set_loginname(const ::std::string& value);
  inline void set_loginname(const char* value);
  inline void set_loginname(const char* value, size_t size);
  inline ::std::string* mutable_loginname();
  inline ::std::string* release_loginname();
  inline void set_allocated_loginname(::std::string* loginname);

  // optional string accountName = 3;
  inline bool has_accountname() const;
  inline void clear_accountname();
  static const int kAccountNameFieldNumber = 3;
  inline const ::std::string& accountname() const;
  inline void set_accountname(const ::std::string& value);
  inline void set_accountname(const char* value);
  inline void set_accountname(const char* value, size_t size);
  inline ::std::string* mutable_accountname();
  inline ::std::string* release_accountname();
  inline void set_allocated_accountname(::std::string* accountname);

  // optional string password = 4;
  inline bool has_password() const;
  inline void clear_password();
  static const int kPasswordFieldNumber = 4;
  inline const ::std::string& password() const;
  inline void set_password(const ::std::string& value);
  inline void set_password(const char* value);
  inline void set_password(const char* value, size_t size);
  inline ::std::string* mutable_password();
  inline ::std::string* release_password();
  inline void set_allocated_password(::std::string* password);

  // optional uint64 componentID = 5;
  inline bool has_componentid() const;
  inline void clear_componentid();
  static const int kComponentIDFieldNumber = 5;
  inline ::google::protobuf::uint64 componentid() const;
  inline void set_componentid(::google::protobuf::uint64 value);

  // optional int32 entityID = 6;
  inline bool has_entityid() const;
  inline void clear_entityid();
  static const int kEntityIDFieldNumber = 6;
  inline ::google::protobuf::int32 entityid() const;
  inline void set_entityid(::google::protobuf::int32 value);

  // optional uint64 dbid = 7;
  inline bool has_dbid() const;
  inline void clear_dbid();
  static const int kDbidFieldNumber = 7;
  inline ::google::protobuf::uint64 dbid() const;
  inline void set_dbid(::google::protobuf::uint64 value);

  // optional uint32 flags = 8;
  inline bool has_flags() const;
  inline void clear_flags();
  static const int kFlagsFieldNumber = 8;
  inline ::google::protobuf::uint32 flags() const;
  inline void set_flags(::google::protobuf::uint32 value);

  // optional string getdatas = 9;
  inline bool has_getdatas() const;
  inline void clear_getdatas();
  static const int kGetdatasFieldNumber = 9;
  inline const ::std::string& getdatas() const;
  inline void set_getdatas(const ::std::string& value);
  inline void set_getdatas(const char* value);
  inline void set_getdatas(const char* value, size_t size);
  inline ::std::string* mutable_getdatas();
  inline ::std::string* release_getdatas();
  inline void set_allocated_getdatas(::std::string* getdatas);

  // @@protoc_insertion_point(class_scope:login_dbmgr.AccountLoginQueryResult)
 private:
  inline void set_has_retcode();
  inline void clear_has_retcode();
  inline void set_has_loginname();
  inline void clear_has_loginname();
  inline void set_has_accountname();
  inline void clear_has_accountname();
  inline void set_has_password();
  inline void clear_has_password();
  inline void set_has_componentid();
  inline void clear_has_componentid();
  inline void set_has_entityid();
  inline void clear_has_entityid();
  inline void set_has_dbid();
  inline void clear_has_dbid();
  inline void set_has_flags();
  inline void clear_has_flags();
  inline void set_has_getdatas();
  inline void clear_has_getdatas();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* loginname_;
  ::std::string* accountname_;
  ::google::protobuf::uint32 retcode_;
  ::google::protobuf::int32 entityid_;
  ::std::string* password_;
  ::google::protobuf::uint64 componentid_;
  ::google::protobuf::uint64 dbid_;
  ::std::string* getdatas_;
  ::google::protobuf::uint32 flags_;
  friend void  protobuf_AddDesc_ldb_2eproto();
  friend void protobuf_AssignDesc_ldb_2eproto();
  friend void protobuf_ShutdownFile_ldb_2eproto();

  void InitAsDefaultInstance();
  static AccountLoginQueryResult* default_instance_;
};
// ===================================================================


// ===================================================================

// AccountLogin

// optional string accountName = 1;
inline bool AccountLogin::has_accountname() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AccountLogin::set_has_accountname() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AccountLogin::clear_has_accountname() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AccountLogin::clear_accountname() {
  if (accountname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_->clear();
  }
  clear_has_accountname();
}
inline const ::std::string& AccountLogin::accountname() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLogin.accountName)
  return *accountname_;
}
inline void AccountLogin::set_accountname(const ::std::string& value) {
  set_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_ = new ::std::string;
  }
  accountname_->assign(value);
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLogin.accountName)
}
inline void AccountLogin::set_accountname(const char* value) {
  set_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_ = new ::std::string;
  }
  accountname_->assign(value);
  // @@protoc_insertion_point(field_set_char:login_dbmgr.AccountLogin.accountName)
}
inline void AccountLogin::set_accountname(const char* value, size_t size) {
  set_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_ = new ::std::string;
  }
  accountname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:login_dbmgr.AccountLogin.accountName)
}
inline ::std::string* AccountLogin::mutable_accountname() {
  set_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:login_dbmgr.AccountLogin.accountName)
  return accountname_;
}
inline ::std::string* AccountLogin::release_accountname() {
  clear_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = accountname_;
    accountname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AccountLogin::set_allocated_accountname(::std::string* accountname) {
  if (accountname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete accountname_;
  }
  if (accountname) {
    set_has_accountname();
    accountname_ = accountname;
  } else {
    clear_has_accountname();
    accountname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:login_dbmgr.AccountLogin.accountName)
}

// optional string password = 2;
inline bool AccountLogin::has_password() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AccountLogin::set_has_password() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AccountLogin::clear_has_password() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AccountLogin::clear_password() {
  if (password_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_->clear();
  }
  clear_has_password();
}
inline const ::std::string& AccountLogin::password() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLogin.password)
  return *password_;
}
inline void AccountLogin::set_password(const ::std::string& value) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(value);
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLogin.password)
}
inline void AccountLogin::set_password(const char* value) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(value);
  // @@protoc_insertion_point(field_set_char:login_dbmgr.AccountLogin.password)
}
inline void AccountLogin::set_password(const char* value, size_t size) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:login_dbmgr.AccountLogin.password)
}
inline ::std::string* AccountLogin::mutable_password() {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:login_dbmgr.AccountLogin.password)
  return password_;
}
inline ::std::string* AccountLogin::release_password() {
  clear_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = password_;
    password_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AccountLogin::set_allocated_password(::std::string* password) {
  if (password_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete password_;
  }
  if (password) {
    set_has_password();
    password_ = password;
  } else {
    clear_has_password();
    password_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:login_dbmgr.AccountLogin.password)
}

// optional string extraData = 3;
inline bool AccountLogin::has_extradata() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AccountLogin::set_has_extradata() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AccountLogin::clear_has_extradata() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AccountLogin::clear_extradata() {
  if (extradata_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    extradata_->clear();
  }
  clear_has_extradata();
}
inline const ::std::string& AccountLogin::extradata() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLogin.extraData)
  return *extradata_;
}
inline void AccountLogin::set_extradata(const ::std::string& value) {
  set_has_extradata();
  if (extradata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    extradata_ = new ::std::string;
  }
  extradata_->assign(value);
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLogin.extraData)
}
inline void AccountLogin::set_extradata(const char* value) {
  set_has_extradata();
  if (extradata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    extradata_ = new ::std::string;
  }
  extradata_->assign(value);
  // @@protoc_insertion_point(field_set_char:login_dbmgr.AccountLogin.extraData)
}
inline void AccountLogin::set_extradata(const char* value, size_t size) {
  set_has_extradata();
  if (extradata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    extradata_ = new ::std::string;
  }
  extradata_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:login_dbmgr.AccountLogin.extraData)
}
inline ::std::string* AccountLogin::mutable_extradata() {
  set_has_extradata();
  if (extradata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    extradata_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:login_dbmgr.AccountLogin.extraData)
  return extradata_;
}
inline ::std::string* AccountLogin::release_extradata() {
  clear_has_extradata();
  if (extradata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = extradata_;
    extradata_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AccountLogin::set_allocated_extradata(::std::string* extradata) {
  if (extradata_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete extradata_;
  }
  if (extradata) {
    set_has_extradata();
    extradata_ = extradata;
  } else {
    clear_has_extradata();
    extradata_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:login_dbmgr.AccountLogin.extraData)
}

// -------------------------------------------------------------------

// AccountLoginQueryResult

// optional uint32 retcode = 1;
inline bool AccountLoginQueryResult::has_retcode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AccountLoginQueryResult::set_has_retcode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AccountLoginQueryResult::clear_has_retcode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AccountLoginQueryResult::clear_retcode() {
  retcode_ = 0u;
  clear_has_retcode();
}
inline ::google::protobuf::uint32 AccountLoginQueryResult::retcode() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.retcode)
  return retcode_;
}
inline void AccountLoginQueryResult::set_retcode(::google::protobuf::uint32 value) {
  set_has_retcode();
  retcode_ = value;
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.retcode)
}

// optional string loginName = 2;
inline bool AccountLoginQueryResult::has_loginname() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AccountLoginQueryResult::set_has_loginname() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AccountLoginQueryResult::clear_has_loginname() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AccountLoginQueryResult::clear_loginname() {
  if (loginname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    loginname_->clear();
  }
  clear_has_loginname();
}
inline const ::std::string& AccountLoginQueryResult::loginname() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.loginName)
  return *loginname_;
}
inline void AccountLoginQueryResult::set_loginname(const ::std::string& value) {
  set_has_loginname();
  if (loginname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    loginname_ = new ::std::string;
  }
  loginname_->assign(value);
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.loginName)
}
inline void AccountLoginQueryResult::set_loginname(const char* value) {
  set_has_loginname();
  if (loginname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    loginname_ = new ::std::string;
  }
  loginname_->assign(value);
  // @@protoc_insertion_point(field_set_char:login_dbmgr.AccountLoginQueryResult.loginName)
}
inline void AccountLoginQueryResult::set_loginname(const char* value, size_t size) {
  set_has_loginname();
  if (loginname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    loginname_ = new ::std::string;
  }
  loginname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:login_dbmgr.AccountLoginQueryResult.loginName)
}
inline ::std::string* AccountLoginQueryResult::mutable_loginname() {
  set_has_loginname();
  if (loginname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    loginname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:login_dbmgr.AccountLoginQueryResult.loginName)
  return loginname_;
}
inline ::std::string* AccountLoginQueryResult::release_loginname() {
  clear_has_loginname();
  if (loginname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = loginname_;
    loginname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AccountLoginQueryResult::set_allocated_loginname(::std::string* loginname) {
  if (loginname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete loginname_;
  }
  if (loginname) {
    set_has_loginname();
    loginname_ = loginname;
  } else {
    clear_has_loginname();
    loginname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:login_dbmgr.AccountLoginQueryResult.loginName)
}

// optional string accountName = 3;
inline bool AccountLoginQueryResult::has_accountname() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AccountLoginQueryResult::set_has_accountname() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AccountLoginQueryResult::clear_has_accountname() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AccountLoginQueryResult::clear_accountname() {
  if (accountname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_->clear();
  }
  clear_has_accountname();
}
inline const ::std::string& AccountLoginQueryResult::accountname() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.accountName)
  return *accountname_;
}
inline void AccountLoginQueryResult::set_accountname(const ::std::string& value) {
  set_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_ = new ::std::string;
  }
  accountname_->assign(value);
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.accountName)
}
inline void AccountLoginQueryResult::set_accountname(const char* value) {
  set_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_ = new ::std::string;
  }
  accountname_->assign(value);
  // @@protoc_insertion_point(field_set_char:login_dbmgr.AccountLoginQueryResult.accountName)
}
inline void AccountLoginQueryResult::set_accountname(const char* value, size_t size) {
  set_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_ = new ::std::string;
  }
  accountname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:login_dbmgr.AccountLoginQueryResult.accountName)
}
inline ::std::string* AccountLoginQueryResult::mutable_accountname() {
  set_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accountname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:login_dbmgr.AccountLoginQueryResult.accountName)
  return accountname_;
}
inline ::std::string* AccountLoginQueryResult::release_accountname() {
  clear_has_accountname();
  if (accountname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = accountname_;
    accountname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AccountLoginQueryResult::set_allocated_accountname(::std::string* accountname) {
  if (accountname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete accountname_;
  }
  if (accountname) {
    set_has_accountname();
    accountname_ = accountname;
  } else {
    clear_has_accountname();
    accountname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:login_dbmgr.AccountLoginQueryResult.accountName)
}

// optional string password = 4;
inline bool AccountLoginQueryResult::has_password() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AccountLoginQueryResult::set_has_password() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AccountLoginQueryResult::clear_has_password() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AccountLoginQueryResult::clear_password() {
  if (password_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_->clear();
  }
  clear_has_password();
}
inline const ::std::string& AccountLoginQueryResult::password() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.password)
  return *password_;
}
inline void AccountLoginQueryResult::set_password(const ::std::string& value) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(value);
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.password)
}
inline void AccountLoginQueryResult::set_password(const char* value) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(value);
  // @@protoc_insertion_point(field_set_char:login_dbmgr.AccountLoginQueryResult.password)
}
inline void AccountLoginQueryResult::set_password(const char* value, size_t size) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:login_dbmgr.AccountLoginQueryResult.password)
}
inline ::std::string* AccountLoginQueryResult::mutable_password() {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:login_dbmgr.AccountLoginQueryResult.password)
  return password_;
}
inline ::std::string* AccountLoginQueryResult::release_password() {
  clear_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = password_;
    password_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AccountLoginQueryResult::set_allocated_password(::std::string* password) {
  if (password_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete password_;
  }
  if (password) {
    set_has_password();
    password_ = password;
  } else {
    clear_has_password();
    password_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:login_dbmgr.AccountLoginQueryResult.password)
}

// optional uint64 componentID = 5;
inline bool AccountLoginQueryResult::has_componentid() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void AccountLoginQueryResult::set_has_componentid() {
  _has_bits_[0] |= 0x00000010u;
}
inline void AccountLoginQueryResult::clear_has_componentid() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void AccountLoginQueryResult::clear_componentid() {
  componentid_ = GOOGLE_ULONGLONG(0);
  clear_has_componentid();
}
inline ::google::protobuf::uint64 AccountLoginQueryResult::componentid() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.componentID)
  return componentid_;
}
inline void AccountLoginQueryResult::set_componentid(::google::protobuf::uint64 value) {
  set_has_componentid();
  componentid_ = value;
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.componentID)
}

// optional int32 entityID = 6;
inline bool AccountLoginQueryResult::has_entityid() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void AccountLoginQueryResult::set_has_entityid() {
  _has_bits_[0] |= 0x00000020u;
}
inline void AccountLoginQueryResult::clear_has_entityid() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void AccountLoginQueryResult::clear_entityid() {
  entityid_ = 0;
  clear_has_entityid();
}
inline ::google::protobuf::int32 AccountLoginQueryResult::entityid() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.entityID)
  return entityid_;
}
inline void AccountLoginQueryResult::set_entityid(::google::protobuf::int32 value) {
  set_has_entityid();
  entityid_ = value;
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.entityID)
}

// optional uint64 dbid = 7;
inline bool AccountLoginQueryResult::has_dbid() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void AccountLoginQueryResult::set_has_dbid() {
  _has_bits_[0] |= 0x00000040u;
}
inline void AccountLoginQueryResult::clear_has_dbid() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void AccountLoginQueryResult::clear_dbid() {
  dbid_ = GOOGLE_ULONGLONG(0);
  clear_has_dbid();
}
inline ::google::protobuf::uint64 AccountLoginQueryResult::dbid() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.dbid)
  return dbid_;
}
inline void AccountLoginQueryResult::set_dbid(::google::protobuf::uint64 value) {
  set_has_dbid();
  dbid_ = value;
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.dbid)
}

// optional uint32 flags = 8;
inline bool AccountLoginQueryResult::has_flags() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void AccountLoginQueryResult::set_has_flags() {
  _has_bits_[0] |= 0x00000080u;
}
inline void AccountLoginQueryResult::clear_has_flags() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void AccountLoginQueryResult::clear_flags() {
  flags_ = 0u;
  clear_has_flags();
}
inline ::google::protobuf::uint32 AccountLoginQueryResult::flags() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.flags)
  return flags_;
}
inline void AccountLoginQueryResult::set_flags(::google::protobuf::uint32 value) {
  set_has_flags();
  flags_ = value;
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.flags)
}

// optional string getdatas = 9;
inline bool AccountLoginQueryResult::has_getdatas() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void AccountLoginQueryResult::set_has_getdatas() {
  _has_bits_[0] |= 0x00000100u;
}
inline void AccountLoginQueryResult::clear_has_getdatas() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void AccountLoginQueryResult::clear_getdatas() {
  if (getdatas_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    getdatas_->clear();
  }
  clear_has_getdatas();
}
inline const ::std::string& AccountLoginQueryResult::getdatas() const {
  // @@protoc_insertion_point(field_get:login_dbmgr.AccountLoginQueryResult.getdatas)
  return *getdatas_;
}
inline void AccountLoginQueryResult::set_getdatas(const ::std::string& value) {
  set_has_getdatas();
  if (getdatas_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    getdatas_ = new ::std::string;
  }
  getdatas_->assign(value);
  // @@protoc_insertion_point(field_set:login_dbmgr.AccountLoginQueryResult.getdatas)
}
inline void AccountLoginQueryResult::set_getdatas(const char* value) {
  set_has_getdatas();
  if (getdatas_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    getdatas_ = new ::std::string;
  }
  getdatas_->assign(value);
  // @@protoc_insertion_point(field_set_char:login_dbmgr.AccountLoginQueryResult.getdatas)
}
inline void AccountLoginQueryResult::set_getdatas(const char* value, size_t size) {
  set_has_getdatas();
  if (getdatas_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    getdatas_ = new ::std::string;
  }
  getdatas_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:login_dbmgr.AccountLoginQueryResult.getdatas)
}
inline ::std::string* AccountLoginQueryResult::mutable_getdatas() {
  set_has_getdatas();
  if (getdatas_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    getdatas_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:login_dbmgr.AccountLoginQueryResult.getdatas)
  return getdatas_;
}
inline ::std::string* AccountLoginQueryResult::release_getdatas() {
  clear_has_getdatas();
  if (getdatas_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = getdatas_;
    getdatas_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AccountLoginQueryResult::set_allocated_getdatas(::std::string* getdatas) {
  if (getdatas_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete getdatas_;
  }
  if (getdatas) {
    set_has_getdatas();
    getdatas_ = getdatas;
  } else {
    clear_has_getdatas();
    getdatas_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:login_dbmgr.AccountLoginQueryResult.getdatas)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace login_dbmgr

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ldb_2eproto__INCLUDED